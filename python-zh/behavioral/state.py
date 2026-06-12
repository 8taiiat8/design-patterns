"""机器人工厂 RoboWorks — 第 20 章：机器人的工作模式

故事：车间机器人有不同的"模式"。空闲时它接受任务；忙碌时再派任务
只会触发一声不耐烦的蜂鸣，但按下"完成"就交付任务并回到空闲。
与其写一个围绕状态标志的巨型 if/else，不如让每个模式都成为一个类。

模式：状态（State）——把行为委托给状态对象，并在状态转换时更换它，
让对象在内部状态改变时改变自己的行为。

运行：python3 state.py
"""

from abc import ABC, abstractmethod


class RobotState(ABC):
    """机器人能接收的每种事件对应一个方法。"""

    @abstractmethod
    def assign_task(self, robot: "FloorRobot") -> None: ...

    @abstractmethod
    def complete_task(self, robot: "FloorRobot") -> None: ...


class IdleState(RobotState):
    def assign_task(self, robot: "FloorRobot") -> None:
        print("任务已接受，电机启动")
        robot.state = BusyState()

    def complete_task(self, robot: "FloorRobot") -> None:
        print("没有任务可完成，机器人空闲中")


class BusyState(RobotState):
    def assign_task(self, robot: "FloorRobot") -> None:
        print("机器人蜂鸣：已经在忙了")

    def complete_task(self, robot: "FloorRobot") -> None:
        print("任务完成，回到空闲")
        robot.state = IdleState()


class FloorRobot:
    """上下文：把事件转发给当前状态对象。"""

    def __init__(self):
        self.state: RobotState = IdleState()

    def assign_task(self) -> None:
        self.state.assign_task(self)

    def complete_task(self) -> None:
        self.state.complete_task(self)


def main():
    robot = FloorRobot()
    robot.complete_task()  # 空闲：拒绝
    robot.assign_task()    # 空闲 -> 忙碌
    robot.assign_task()    # 忙碌：蜂鸣
    robot.complete_task()  # 忙碌 -> 空闲，交付任务
    robot.complete_task()  # 又是空闲：拒绝


if __name__ == "__main__":
    main()
