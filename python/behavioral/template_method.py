"""RoboWorks — Chapter 22: The Boot Sequence

STORY: Every robot boots the same way, in the same order: power on,
self-test, load drivers, announce readiness. The sequence itself never
changes — but HOW each robot self-tests (calibrate the welding laser,
spin up the rotors) and how it announces differ per model.

PATTERN: Template Method — define the skeleton of an algorithm in a base
class and let subclasses override specific steps without changing the
algorithm's structure.

Run: python3 template_method.py
"""

from abc import ABC, abstractmethod


class BootSequence(ABC):
    """The base class owns the boot sequence's skeleton."""

    def boot(self) -> None:
        """The template method: fixed order of steps."""
        self._power_on()
        self.self_test()
        self._load_drivers()
        self.announce_ready()  # optional hook with a default

    # Steps subclasses must provide.
    @abstractmethod
    def self_test(self) -> None: ...

    # Hook: sensible default, override only if needed.
    def announce_ready(self) -> None:
        print("  (standard ready beep)")

    # Steps identical for every robot stay fixed.
    def _power_on(self) -> None:
        print("  power on")

    def _load_drivers(self) -> None:
        print("  loading drivers")


class WelderBot(BootSequence):
    def self_test(self) -> None:
        print("  calibrating welding laser")

    def announce_ready(self) -> None:
        print("  announces: welding systems online")


class ScoutDrone(BootSequence):
    def self_test(self) -> None:
        print("  spinning up rotors")


def main():
    print("Booting WelderBot:")
    WelderBot().boot()

    print("Booting ScoutDrone:")
    ScoutDrone().boot()


if __name__ == "__main__":
    main()
