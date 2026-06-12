"""机器人工厂 RoboWorks — 第 4 章：定制订单

故事：客户从不订购"标准机器人"，而是"履带底盘、四个传感器、两条
机械臂、夜视固件"。七个参数的构造函数是噩梦，所以配置台一步一步
组装机器人——产品目录（指挥者）里还存着标准机型的配方。

模式：建造者（Builder）——把复杂对象的构建过程与表示分离，
同一个构建过程可以一步步生成不同配置。
注意：Python 的关键字参数和 dataclass 能覆盖很多简单场景；
当构建涉及顺序、校验或可复用配方时，建造者才真正发挥威力。

运行：python3 builder.py
"""

from dataclasses import dataclass, field


@dataclass
class Robot:
    chassis: str = ""
    sensors: int = 0
    arms: int = 0
    firmware: str = ""
    extras: list = field(default_factory=list)


class RobotBuilder:
    """流式建造者：每一步都返回 self，可以链式调用。"""

    def __init__(self):
        self._robot = Robot()

    def chassis(self, value: str) -> "RobotBuilder":
        self._robot.chassis = value
        return self

    def sensors(self, count: int) -> "RobotBuilder":
        self._robot.sensors = count
        return self

    def arms(self, count: int) -> "RobotBuilder":
        self._robot.arms = count
        return self

    def firmware(self, value: str) -> "RobotBuilder":
        self._robot.firmware = value
        return self

    def extra(self, value: str) -> "RobotBuilder":
        self._robot.extras.append(value)
        return self

    def build(self) -> Robot:
        if not self._robot.chassis:
            raise ValueError("机器人必须有底盘")
        return self._robot


class Catalog:
    """产品目录（指挥者）：封装常见机型的构建配方。"""

    @staticmethod
    def worker_bot() -> Robot:
        return (
            RobotBuilder()
            .chassis("履带式")
            .sensors(4)
            .arms(2)
            .firmware("重载版 v3")
            .build()
        )

    @staticmethod
    def scout_bot() -> Robot:
        return (
            RobotBuilder()
            .chassis("轮式")
            .sensors(8)
            .arms(0)
            .firmware("夜视版 v2")
            .extra("静音电机")
            .build()
        )


def main():
    # 挑剔的客户一步一步定制机器人。
    custom = RobotBuilder().chassis("六足式").sensors(6).arms(4).firmware("实验版").build()
    print("定制：", custom)

    # 也可以直接按目录配方下单。
    print("工人型：", Catalog.worker_bot())
    print("侦察型：", Catalog.scout_bot())


if __name__ == "__main__":
    main()
