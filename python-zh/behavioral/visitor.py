"""机器人工厂 RoboWorks — 第 23 章：巡检员

故事：今天有两位巡检员到车间：安全审计员统计功率风险，估价师
给设备贴价值标签。设备本身（焊接机器人、无人机）不需要任何修改——
每台设备只是"接待"（accept）巡检员，巡检员对每种设备各干各的活。
下个月来一位新巡检员，也不用动任何设备类。

模式：访问者（Visitor）——把作用于对象结构中各元素的操作独立出来，
让你在不修改元素类的情况下新增操作。
核心机制是 accept()/visit() 的双重分派。

运行：python3 visitor.py
"""

from abc import ABC, abstractmethod


class FloorVisitor(ABC):
    """每种元素类型一个 visit 方法。"""

    @abstractmethod
    def visit_welder(self, welder: "WelderBot") -> None: ...

    @abstractmethod
    def visit_drone(self, drone: "ScoutDrone") -> None: ...


class Machine(ABC):
    @abstractmethod
    def accept(self, visitor: FloorVisitor) -> None: ...


class WelderBot(Machine):
    def __init__(self, watts: int):
        self.watts = watts

    def accept(self, visitor: FloorVisitor) -> None:
        visitor.visit_welder(self)


class ScoutDrone(Machine):
    def __init__(self, rotors: int):
        self.rotors = rotors

    def accept(self, visitor: FloorVisitor) -> None:
        visitor.visit_drone(self)


# 新操作以新访问者的形式加入——设备类一行不改。
class SafetyAuditor(FloorVisitor):
    def __init__(self):
        self.risk_score = 0

    def visit_welder(self, welder: WelderBot) -> None:
        self.risk_score += welder.watts // 100

    def visit_drone(self, drone: ScoutDrone) -> None:
        self.risk_score += drone.rotors


class ValueAppraiser(FloorVisitor):
    def visit_welder(self, welder: WelderBot) -> None:
        print(f"标签：焊接机器人，{welder.watts} 瓦 — $12,000")

    def visit_drone(self, drone: ScoutDrone) -> None:
        print(f"标签：侦察无人机，{drone.rotors} 旋翼 — $3,500")


def main():
    floor: list[Machine] = [WelderBot(400), ScoutDrone(4)]

    auditor = SafetyAuditor()
    appraiser = ValueAppraiser()
    for machine in floor:
        machine.accept(auditor)
        machine.accept(appraiser)

    print(f"总风险分：{auditor.risk_score}")


if __name__ == "__main__":
    main()
