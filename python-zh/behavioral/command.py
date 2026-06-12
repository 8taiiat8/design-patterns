"""机器人工厂 RoboWorks — 第 14 章：工单队列

故事：控制台不会对着车间大喊大叫——每个任务都变成一张"工单"
压进队列。车间按自己的节奏执行工单；客户取消订单时，
直接撤回最后一张工单（撤销）。

模式：命令（Command）——把请求封装成对象，从而可以排队、记录日志、
支持撤销。把发出操作的对象（控制台）与执行操作的对象（车间）解耦。

运行：python3 command.py
"""

from abc import ABC, abstractmethod


class FactoryFloor:
    """接收者：真正干活的对象。"""

    def start(self, job: str) -> None:
        print(f"车间开工：{job}")

    def recall(self, job: str) -> None:
        print(f"车间撤回：{job}")


class JobCard(ABC):
    @abstractmethod
    def execute(self) -> None: ...

    @abstractmethod
    def undo(self) -> None: ...


class WeldJob(JobCard):
    def __init__(self, floor: FactoryFloor, seam: str):
        self.floor = floor
        self.seam = seam

    def execute(self) -> None:
        self.floor.start(f"焊接 {self.seam}")

    def undo(self) -> None:
        self.floor.recall(f"焊接 {self.seam}")


class TransportJob(JobCard):
    def __init__(self, floor: FactoryFloor, cargo: str):
        self.floor = floor
        self.cargo = cargo

    def execute(self) -> None:
        self.floor.start(f"运输 {self.cargo}")

    def undo(self) -> None:
        self.floor.recall(f"运输 {self.cargo}")


class ControlPanel:
    """调用者：签发工单并保存历史，以便撤销。"""

    def __init__(self):
        self._history: list[JobCard] = []

    def issue(self, job: JobCard) -> None:
        job.execute()
        self._history.append(job)

    def cancel_last(self) -> None:
        if self._history:
            self._history.pop().undo()


def main():
    floor = FactoryFloor()
    panel = ControlPanel()

    panel.issue(WeldJob(floor, "底盘 7 号焊缝"))
    panel.issue(TransportJob(floor, "一箱伺服电机"))

    print("—— 客户取消订单 ——")
    panel.cancel_last()


if __name__ == "__main__":
    main()
