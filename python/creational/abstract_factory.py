"""RoboWorks — Chapter 3: The Product Series

STORY: RoboWorks sells two product series. The Industrial series pairs a
heavy chassis WITH hydraulic arms; the Domestic series pairs a light
chassis WITH soft-grip arms. Parts from one series always match — a
soft-grip arm on a heavy chassis would snap off on day one.

PATTERN: Abstract Factory — provide an interface for creating families of
related objects without specifying their concrete classes.

Run: python3 abstract_factory.py
"""

from abc import ABC, abstractmethod


# Abstract products
class Chassis(ABC):
    @abstractmethod
    def assemble(self) -> None: ...


class Arm(ABC):
    @abstractmethod
    def attach(self) -> None: ...


# The Industrial series
class HeavyChassis(Chassis):
    def assemble(self) -> None:
        print("bolting together a heavy steel chassis")


class HydraulicArm(Arm):
    def attach(self) -> None:
        print("attaching a hydraulic arm")


# The Domestic series
class LightChassis(Chassis):
    def assemble(self) -> None:
        print("clipping together a light alloy chassis")


class SoftGripArm(Arm):
    def attach(self) -> None:
        print("attaching a soft-grip arm")


# Abstract factory: one creation method per product type
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
    """The production planner depends only on the abstract factory."""
    series.create_chassis().assemble()
    series.create_arm().attach()


def main():
    print("-- Industrial series --")
    produce_robot(IndustrialSeries())
    print("-- Domestic series --")
    produce_robot(DomesticSeries())


if __name__ == "__main__":
    main()
