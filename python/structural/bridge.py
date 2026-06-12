"""RoboWorks — Chapter 7: Any Robot, Any Controller

STORY: You build welders and drones; they can be driven by a remote
operator or by the autonomous AI. Without care you'd need RemoteWelder,
AutonomousWelder, RemoteDrone... a class for every combination. Instead,
each ROBOT holds a reference to a CONTROLLER: new robots and new
controllers can now be added independently.

PATTERN: Bridge — decouple an abstraction (Robot) from its implementation
(Controller) so the two hierarchies vary independently.

Run: python3 bridge.py
"""

from abc import ABC, abstractmethod


# Implementation hierarchy
class Controller(ABC):
    @abstractmethod
    def drive(self, power: int) -> None: ...


class RemoteOperator(Controller):
    def drive(self, power: int) -> None:
        print(f"remote operator steers carefully at power {power}")


class AutonomousAI(Controller):
    def drive(self, power: int) -> None:
        print(f"autonomous AI optimizes the route at power {power}")


# Abstraction hierarchy: holds the "bridge" to the implementation.
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
    # Any robot can be paired with any controller at run time.
    night_shift = WelderBot(AutonomousAI(), 3)
    delicate_job = WelderBot(RemoteOperator(), 3)
    night_shift.operate()
    delicate_job.operate()

    night_shift.boost_power()
    night_shift.operate()


if __name__ == "__main__":
    main()
