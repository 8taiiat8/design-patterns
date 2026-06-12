"""机器人工厂 RoboWorks — 第 19 章："42 号下线了！"

故事：经理们过去每小时给车间打电话问"42 批好了没？"
现在他们订阅了通知：每当一台机器人下线，大屏看板自动刷新，
工程师的传呼机同时震动——装配线根本不知道、也不关心谁在听。

模式：观察者（Observer）——定义一对多依赖，主题状态一变，
所有注册的观察者都收到通知。事件系统和 UI 更新的基石。

运行：python3 observer.py
"""

from abc import ABC, abstractmethod


class LineObserver(ABC):
    @abstractmethod
    def unit_finished(self, serial: int) -> None: ...


class AssemblyLine:
    """主题：维护观察者列表，状态变化时逐个通知。"""

    def __init__(self):
        self._observers: list[LineObserver] = []

    def attach(self, observer: LineObserver) -> None:
        self._observers.append(observer)

    def detach(self, observer: LineObserver) -> None:
        self._observers.remove(observer)

    def roll_off(self, serial: int) -> None:
        print(f"装配线：#{serial} 号机下线")
        for observer in self._observers:
            observer.unit_finished(serial)


class Dashboard(LineObserver):
    def unit_finished(self, serial: int) -> None:
        print(f"  看板刷新：#{serial} 号机完工")


class EngineerPager(LineObserver):
    def unit_finished(self, serial: int) -> None:
        print(f"  传呼机震动：#{serial} 号机等待质检！")


def main():
    line = AssemblyLine()
    dashboard = Dashboard()
    pager = EngineerPager()

    line.attach(dashboard)
    line.attach(pager)

    line.roll_off(41)
    line.roll_off(42)

    line.detach(pager)  # 工程师下班了
    line.roll_off(43)   # 现在只有看板有反应


if __name__ == "__main__":
    main()
