"""机器人工厂 RoboWorks — 第 6 章：老焊接臂

故事：新装配线要求所有机械臂都响应 actuate(task)。但老厂传下来的
传奇焊接臂只听得懂 pulse_crank()——而它的焊缝质量至今无人能敌。
你不会为它重排整条线，也改不了停产的老零件，
于是你做了一个适配器，把老协议接到新接口上。

模式：适配器（Adapter）——把现有类的接口转换成客户端期望的接口，
让本不兼容的类协同工作。

运行：python3 adapter.py
"""

from abc import ABC, abstractmethod


# 装配线期望的接口。
class RoboticArm(ABC):
    @abstractmethod
    def actuate(self, task: str) -> None: ...


# 接口不兼容的老零件（被适配者）。假设我们无法修改它。
class LegacyWeldingArm:
    def pulse_crank(self, job: str) -> None:
        print(f"老焊接臂脉冲运转，完成：{job}")


# 适配器实现期望接口，并把调用转发给被适配者。
class LegacyArmAdapter(RoboticArm):
    def __init__(self):
        self._legacy = LegacyWeldingArm()

    def actuate(self, task: str) -> None:
        self._legacy.pulse_crank(task)  # 翻译调用


class ServoArm(RoboticArm):
    def actuate(self, task: str) -> None:
        print(f"伺服机械臂平滑执行：{task}")


def main():
    assembly_line = [ServoArm(), LegacyArmAdapter()]
    for arm in assembly_line:
        arm.actuate("焊接底盘 7 号焊缝")


if __name__ == "__main__":
    main()
