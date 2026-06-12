"""机器人工厂 RoboWorks — 第 3 章：产品系列

故事：工厂出售两个产品系列。工业系列 = 重型底盘 + 液压机械臂；
家用系列 = 轻型底盘 + 软抓机械臂。同一系列的零件永远配套——
软抓臂装到重型底盘上，第一天就会折断。

模式：抽象工厂（Abstract Factory）——提供创建"一族相关对象"的接口，
而无需指定具体类。

运行：python3 abstract_factory.py
"""

from abc import ABC, abstractmethod


# 抽象产品
class Chassis(ABC):
    @abstractmethod
    def assemble(self) -> None: ...


class Arm(ABC):
    @abstractmethod
    def attach(self) -> None: ...


# 工业系列
class HeavyChassis(Chassis):
    def assemble(self) -> None:
        print("拼装重型钢制底盘")


class HydraulicArm(Arm):
    def attach(self) -> None:
        print("安装液压机械臂")


# 家用系列
class LightChassis(Chassis):
    def assemble(self) -> None:
        print("卡装轻型合金底盘")


class SoftGripArm(Arm):
    def attach(self) -> None:
        print("安装软抓机械臂")


# 抽象工厂：每种产品对应一个创建方法
class RobotSeriesFactory(ABC):
    @abstractmethod
    def create_chassis(self) -> Chassis: ...

    @abstractmethod
    def create_arm(self) -> Arm: ...


class IndustrialSeries(RobotSeriesFactory):
    def create_chassis(self) -> Chassis:
        return HeavyChassis()

    def create_arm(self) -> Arm:
        return HydraulicArm()


class DomesticSeries(RobotSeriesFactory):
    def create_chassis(self) -> Chassis:
        return LightChassis()

    def create_arm(self) -> Arm:
        return SoftGripArm()


def produce_robot(series: RobotSeriesFactory) -> None:
    """生产计划员只依赖抽象工厂接口。"""
    series.create_chassis().assemble()
    series.create_arm().attach()


def main():
    print("—— 工业系列 ——")
    produce_robot(IndustrialSeries())
    print("—— 家用系列 ——")
    produce_robot(DomesticSeries())


if __name__ == "__main__":
    main()
