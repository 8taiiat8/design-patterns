"""机器人工厂 RoboWorks — 第 2 章：装配线

故事：订单越来越多，你开设了多条装配线。每条线的下线流程都一样
（组装、测试、出厂），不同的是每条线生产"哪种"机器人：
焊接线生产焊接机器人，清洁线生产清洁机器人。

模式：工厂方法（Factory Method）——定义创建对象的接口，
但由子类决定实例化哪个具体类。

运行：python3 factory_method.py
"""

from abc import ABC, abstractmethod


# 产品接口
class Robot(ABC):
    @abstractmethod
    def describe(self) -> str: ...


class WelderBot(Robot):
    def describe(self) -> str:
        return "一台双等离子焊枪的焊接机器人"


class CleanerBot(Robot):
    def describe(self) -> str:
        return "一台带旋转刷头的清洁机器人"


# 创建者：下线流程只依赖 Robot 接口；
# 工厂方法把"造哪种机器人"的决定推迟给子类。
class AssemblyLine(ABC):
    def roll_out(self) -> None:
        robot = self.build_robot()  # 工厂方法
        print(f"装配线下线：{robot.describe()}")

    @abstractmethod
    def build_robot(self) -> Robot: ...


class WelderLine(AssemblyLine):
    def build_robot(self) -> Robot:
        return WelderBot()


class CleanerLine(AssemblyLine):
    def build_robot(self) -> Robot:
        return CleanerBot()


def main():
    WelderLine().roll_out()
    CleanerLine().roll_out()


if __name__ == "__main__":
    main()
