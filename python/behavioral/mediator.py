"""RoboWorks — Chapter 17: The Dispatch Tower

STORY: When robots radioed each other directly, the factory floor was
chaos — every robot needed every other robot's frequency. So you built
the dispatch tower: robots report INTO the tower, and it relays the
message to everyone else. No robot needs to know who else is online.

PATTERN: Mediator — define an object that encapsulates how a set of
objects interact, so they don't reference each other directly; turns
many-to-many links into one-to-many.

Run: python3 mediator.py
"""

from abc import ABC, abstractmethod


class DispatchTower(ABC):
    @abstractmethod
    def relay(self, sender: "FloorRobot", message: str) -> None: ...

    @abstractmethod
    def register(self, robot: "FloorRobot") -> None: ...


class FloorRobot:
    """Colleague: only knows the tower, not the other robots."""

    def __init__(self, callsign: str, tower: DispatchTower):
        self.callsign = callsign
        self.tower = tower
        tower.register(self)

    def report(self, message: str) -> None:
        print(f"{self.callsign} reports: {message}")
        self.tower.relay(self, message)

    def receive(self, sender: str, message: str) -> None:
        print(f"  {self.callsign} receives {sender}: {message}")


class CentralTower(DispatchTower):
    """Concrete mediator: relays reports to every other robot."""

    def __init__(self):
        self.robots: list[FloorRobot] = []

    def register(self, robot: FloorRobot) -> None:
        self.robots.append(robot)

    def relay(self, sender: FloorRobot, message: str) -> None:
        for robot in self.robots:
            if robot is not sender:
                robot.receive(sender.callsign, message)


def main():
    tower = CentralTower()
    welder = FloorRobot("Welder-01", tower)
    crane = FloorRobot("Crane-02", tower)
    FloorRobot("Drone-03", tower)

    welder.report("chassis seam #7 finished, ready for pickup")
    crane.report("picking up at line B, clear the aisle")


if __name__ == "__main__":
    main()
