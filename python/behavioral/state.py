"""RoboWorks — Chapter 20: The Robot's Modes

STORY: A floor robot has modes. When idle, it accepts a task; when busy,
assigning another task just triggers an angry beep, but pressing
"complete" finishes the job and returns it to idle. Instead of one giant
if/else on a status flag, each mode is its own class.

PATTERN: State — let an object change its behavior when its internal
state changes, by delegating behavior to a state object and swapping it
on transitions.

Run: python3 state.py
"""

from abc import ABC, abstractmethod


class RobotState(ABC):
    """One method per event the robot can receive."""

    @abstractmethod
    def assign_task(self, robot: "FloorRobot") -> None: ...

    @abstractmethod
    def complete_task(self, robot: "FloorRobot") -> None: ...


class IdleState(RobotState):
    def assign_task(self, robot: "FloorRobot") -> None:
        print("task accepted, motors spinning up")
        robot.state = BusyState()

    def complete_task(self, robot: "FloorRobot") -> None:
        print("nothing to complete, robot is idle")


class BusyState(RobotState):
    def assign_task(self, robot: "FloorRobot") -> None:
        print("robot beeps: already busy with a task")

    def complete_task(self, robot: "FloorRobot") -> None:
        print("task finished, back to idle")
        robot.state = IdleState()


class FloorRobot:
    """Context: forwards events to its current state object."""

    def __init__(self):
        self.state: RobotState = IdleState()

    def assign_task(self) -> None:
        self.state.assign_task(self)

    def complete_task(self) -> None:
        self.state.complete_task(self)


def main():
    robot = FloorRobot()
    robot.complete_task()  # idle: refuses
    robot.assign_task()    # idle -> busy
    robot.assign_task()    # busy: beeps
    robot.complete_task()  # busy -> idle, job done
    robot.complete_task()  # idle again: refuses


if __name__ == "__main__":
    main()
