"""RoboWorks — Chapter 2: The Assembly Lines

STORY: Demand grows, so you open assembly lines. Every line follows the
same roll-out routine (assemble, test, ship). What differs is WHICH robot
each line builds: the welder line produces WelderBots, the cleaner line
produces CleanerBots.

PATTERN: Factory Method — define an interface for creating an object, but
let subclasses decide which concrete class to instantiate.

Run: python3 factory_method.py
"""

from abc import ABC, abstractmethod


# Product interface
class Robot(ABC):
    @abstractmethod
    def describe(self) -> str: ...


class WelderBot(Robot):
    def describe(self) -> str:
        return "a WelderBot with twin plasma torches"


class CleanerBot(Robot):
    def describe(self) -> str:
        return "a CleanerBot with spinning brushes"


# Creator: the roll-out routine relies only on the Robot interface;
# the factory method defers the concrete choice to subclasses.
class AssemblyLine(ABC):
    def roll_out(self) -> None:
        robot = self.build_robot()  # the factory method
        print(f"Line ships {robot.describe()}")

    @abstractmethod
    def build_robot(self) -> Robot: ...


class WelderLine(AssemblyLine):
    def build_robot(self) -> Robot:
        return WelderBot()


class CleanerLine(AssemblyLine):
    def build_robot(self) -> Robot:
        return CleanerBot()


def main():
    WelderLine().roll_out()
    CleanerLine().roll_out()


if __name__ == "__main__":
    main()
