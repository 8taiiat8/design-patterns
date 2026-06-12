"""机器人工厂 RoboWorks — 第 22 章：开机流程

故事：每台机器人都按同样的顺序开机：上电、自检、加载驱动、宣告
就绪。流程本身永远不变——但每个机型"如何自检"（校准焊接激光、
启动旋翼）以及如何宣告就绪各不相同。

模式：模板方法（Template Method）——在基类中定义算法骨架，
让子类重写特定步骤，而不改变算法的整体结构。

运行：python3 template_method.py
"""

from abc import ABC, abstractmethod


class BootSequence(ABC):
    """基类拥有开机流程的骨架。"""

    def boot(self) -> None:
        """模板方法：步骤顺序固定。"""
        self._power_on()
        self.self_test()
        self._load_drivers()
        self.announce_ready()  # 带默认实现的可选钩子

    # 子类必须提供的步骤。
    @abstractmethod
    def self_test(self) -> None: ...

    # 钩子：有合理默认值，需要时才重写。
    def announce_ready(self) -> None:
        print("  （标准就绪提示音）")

    # 所有机器人完全相同的步骤保持固定。
    def _power_on(self) -> None:
        print("  上电")

    def _load_drivers(self) -> None:
        print("  加载驱动")


class WelderBot(BootSequence):
    def self_test(self) -> None:
        print("  校准焊接激光")

    def announce_ready(self) -> None:
        print("  宣告：焊接系统在线")


class ScoutDrone(BootSequence):
    def self_test(self) -> None:
        print("  启动旋翼")


def main():
    print("焊接机器人开机：")
    WelderBot().boot()

    print("侦察无人机开机：")
    ScoutDrone().boot()


if __name__ == "__main__":
    main()
