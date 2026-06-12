"""RoboWorks — Chapter 21: The Power Modes

STORY: The same robot burns different energy depending on the moment:
full power in the day rush, half power in eco mode, 10% off in night
mode. The robot doesn't care WHICH rule is active — it just asks the
current power strategy what to draw, and you can swap the strategy when
the night shift starts.

PATTERN: Strategy — define a family of interchangeable algorithms and
make them swappable at run time behind a common interface. In Python,
plain functions often serve as lightweight strategies — both styles are
shown below.

Run: python3 strategy.py
"""

from abc import ABC, abstractmethod


# Classic OO style: strategy interface + concrete strategies.
class PowerStrategy(ABC):
    @abstractmethod
    def draw(self, base_watts: float) -> float: ...


class PerformanceMode(PowerStrategy):
    def draw(self, base_watts: float) -> float:
        return base_watts


class EcoMode(PowerStrategy):
    def draw(self, base_watts: float) -> float:
        return base_watts * 0.5


class NightMode(PowerStrategy):
    def draw(self, base_watts: float) -> float:
        return base_watts * 0.9


class Robot:
    """Context: configured with a strategy, unaware of which one."""

    def __init__(self, strategy: PowerStrategy):
        self.strategy = strategy

    def run_task(self, base_watts: float) -> None:
        print(f"task base {base_watts}W -> draws {self.strategy.draw(base_watts)}W")


def main():
    robot = Robot(PerformanceMode())
    robot.run_task(400.0)

    robot.strategy = EcoMode()  # the grid bill arrived
    robot.run_task(400.0)

    robot.strategy = NightMode()
    robot.run_task(400.0)

    # Pythonic alternative: any callable works as a strategy.
    modes = {
        "standby": lambda base: base * 0.1,
        "overdrive": lambda base: base * 1.5,
    }
    for name, draw in modes.items():
        print(f"{name}: draws {draw(400.0)}W")


if __name__ == "__main__":
    main()
