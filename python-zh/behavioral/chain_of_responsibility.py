"""机器人工厂 RoboWorks — 第 13 章：故障上报

故事：B 线一台机器人卡死了。线上技术员可以当场批准 100 美元以内的
维修；再贵就要找楼层工程师；装配单元烧熔了？只有总工程师能批。
故障只上报一次——它沿着链条向上爬，直到有人能批准为止。

模式：责任链（Chain of Responsibility）——把请求沿处理者链传递；
每个处理者要么处理它，要么转发给下一个。

运行：python3 chain_of_responsibility.py
"""


class FaultHandler:
    """处理者：知道自己的后继者，以及自己能批准的维修预算。"""

    def __init__(self, title: str, budget: float):
        self.title = title
        self.budget = budget
        self.next: "FaultHandler | None" = None

    def set_next(self, handler: "FaultHandler") -> "FaultHandler":
        self.next = handler
        return handler  # 支持链式调用：a.set_next(b).set_next(c)

    def handle(self, fault: str, cost: float) -> None:
        if cost <= self.budget:
            print(f"{self.title} 批准 ${cost} 维修：「{fault}」")
        elif self.next:
            print(f"{self.title} 无权批准 ${cost}，向上汇报……")
            self.next.handle(fault, cost)
        else:
            print(f"没人能为「{fault}」批准 ${cost}")


def main():
    technician = FaultHandler("线上技术员", 100)
    floor_engineer = FaultHandler("楼层工程师", 1_000)
    chief_engineer = FaultHandler("总工程师", 10_000)

    # 搭建链条：技术员 -> 楼层工程师 -> 总工程师。
    technician.set_next(floor_engineer).set_next(chief_engineer)

    # 故障总是先报给线上的人。
    technician.handle("夹爪错位", 45)
    technician.handle("传送带撕裂", 800)
    technician.handle("装配单元烧熔", 7_500)
    technician.handle("整个西厂区着火了", 2_000_000)


if __name__ == "__main__":
    main()
