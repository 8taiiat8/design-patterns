"""RoboWorks — Chapter 4: The Custom Order

STORY: A client never orders a plain robot. It's "tracked chassis, four
sensors, two arms, night-vision firmware". A constructor with seven
parameters would be a nightmare, so the configurator assembles each robot
step by step — and the catalog keeps blueprints (a director) for the
standard models.

PATTERN: Builder — separate the construction of a complex object from its
representation, so the same process can create different configurations
step by step. Note: Python's keyword arguments and dataclasses cover many
simple cases; the builder shines when construction involves ordering,
validation, or reusable recipes.

Run: python3 builder.py
"""

from dataclasses import dataclass, field


@dataclass
class Robot:
    chassis: str = ""
    sensors: int = 0
    arms: int = 0
    firmware: str = ""
    extras: list = field(default_factory=list)


class RobotBuilder:
    """Fluent builder: each step returns self so calls can be chained."""

    def __init__(self):
        self._robot = Robot()

    def chassis(self, value: str) -> "RobotBuilder":
        self._robot.chassis = value
        return self

    def sensors(self, count: int) -> "RobotBuilder":
        self._robot.sensors = count
        return self

    def arms(self, count: int) -> "RobotBuilder":
        self._robot.arms = count
        return self

    def firmware(self, value: str) -> "RobotBuilder":
        self._robot.firmware = value
        return self

    def extra(self, value: str) -> "RobotBuilder":
        self._robot.extras.append(value)
        return self

    def build(self) -> Robot:
        if not self._robot.chassis:
            raise ValueError("a robot needs a chassis")
        return self._robot


class Catalog:
    """The catalog (director): encapsulates well-known build blueprints."""

    @staticmethod
    def worker_bot() -> Robot:
        return (
            RobotBuilder()
            .chassis("tracked")
            .sensors(4)
            .arms(2)
            .firmware("heavy-duty v3")
            .build()
        )

    @staticmethod
    def scout_bot() -> Robot:
        return (
            RobotBuilder()
            .chassis("wheeled")
            .sensors(8)
            .arms(0)
            .firmware("night-vision v2")
            .extra("silent motors")
            .build()
        )


def main():
    # A picky client configures a custom robot step by step.
    custom = RobotBuilder().chassis("hexapod").sensors(6).arms(4).firmware("experimental").build()
    print("custom:", custom)

    # Or order straight from the catalog's blueprints.
    print("worker:", Catalog.worker_bot())
    print("scout: ", Catalog.scout_bot())


if __name__ == "__main__":
    main()
