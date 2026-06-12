"""机器人工厂 RoboWorks — 第 7 章：任意机器人配任意控制器

故事：你生产焊接机器人和无人机；它们可以由远程操作员驾驶，也可以
由自主 AI 驾驶。不加设计的话就需要"远程焊接机器人、自主焊接机器人、
远程无人机……"每种组合一个类。正确做法：每台机器人持有一个控制器
的引用——新机器人和新控制器从此可以独立增加。

模式：桥接（Bridge）——把抽象（Robot）与实现（Controller）解耦，
让两个继承体系独立变化。

运行：python3 bridge.py
"""

from abc import ABC, abstractmethod


# 实现体系
class Controller(ABC):
    @abstractmethod
    def drive(self, power: int) -> None: ...


class RemoteOperator(Controller):
    def drive(self, power: int) -> None:
        print(f"远程操作员小心驾驶，功率 {power}")


class AutonomousAI(Controller):
    def drive(self, power: int) -> None:
        print(f"自主 AI 优化路线，功率 {power}")


# 抽象体系：持有指向实现的"桥"。
class Robot(ABC):
    def __init__(self, controller: Controller):
        self.controller = controller

    @abstractmethod
    def operate(self) -> None: ...


class WelderBot(Robot):
    def __init__(self, controller: Controller, power: int):
        super().__init__(controller)
        self.power = power

    def operate(self) -> None:
        self.controller.drive(self.power)

    def boost_power(self) -> None:
        self.power += 1


def main():
    # 任何机器人都能在运行时搭配任何控制器。
    night_shift = WelderBot(AutonomousAI(), 3)
    delicate_job = WelderBot(RemoteOperator(), 3)
    night_shift.operate()
    delicate_job.operate()

    night_shift.boost_power()
    night_shift.operate()


if __name__ == "__main__":
    main()
