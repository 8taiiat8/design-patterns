"""RoboWorks — Chapter 23: The Inspectors

STORY: Two inspectors walk the floor today: the safety auditor tallies
power risk, the appraiser prints value tags. The machines themselves
(welders, drones) don't change — each machine simply ACCEPTS the
inspector and the inspector does its own job per machine type. Next month
a new inspector can visit without touching a single machine class.

PATTERN: Visitor — represent an operation on the elements of an object
structure, letting you add new operations without modifying the element
classes. The key mechanism is double dispatch via accept()/visit().

Run: python3 visitor.py
"""

from abc import ABC, abstractmethod


class FloorVisitor(ABC):
    """One visit method per element type."""

    @abstractmethod
    def visit_welder(self, welder: "WelderBot") -> None: ...

    @abstractmethod
    def visit_drone(self, drone: "ScoutDrone") -> None: ...


class Machine(ABC):
    @abstractmethod
    def accept(self, visitor: FloorVisitor) -> None: ...


class WelderBot(Machine):
    def __init__(self, watts: int):
        self.watts = watts

    def accept(self, visitor: FloorVisitor) -> None:
        visitor.visit_welder(self)


class ScoutDrone(Machine):
    def __init__(self, rotors: int):
        self.rotors = rotors

    def accept(self, visitor: FloorVisitor) -> None:
        visitor.visit_drone(self)


# New operations are added as new visitors — no Machine class changes.
class SafetyAuditor(FloorVisitor):
    def __init__(self):
        self.risk_score = 0

    def visit_welder(self, welder: WelderBot) -> None:
        self.risk_score += welder.watts // 100

    def visit_drone(self, drone: ScoutDrone) -> None:
        self.risk_score += drone.rotors


class ValueAppraiser(FloorVisitor):
    def visit_welder(self, welder: WelderBot) -> None:
        print(f"tag: WelderBot, {welder.watts}W — $12,000")

    def visit_drone(self, drone: ScoutDrone) -> None:
        print(f"tag: ScoutDrone, {drone.rotors} rotors — $3,500")


def main():
    floor: list[Machine] = [WelderBot(400), ScoutDrone(4)]

    auditor = SafetyAuditor()
    appraiser = ValueAppraiser()
    for machine in floor:
        machine.accept(auditor)
        machine.accept(appraiser)

    print(f"total risk score: {auditor.risk_score}")


if __name__ == "__main__":
    main()
