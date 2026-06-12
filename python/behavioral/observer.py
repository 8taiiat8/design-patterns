"""RoboWorks — Chapter 19: "Unit 42 Rolled Off the Line!"

STORY: Managers used to phone the floor every hour asking "is batch 42
done yet?" Now they subscribe: when a unit rolls off the line, the
dashboard updates AND the engineer's pager buzzes — automatically,
without the line knowing or caring who's listening.

PATTERN: Observer — define a one-to-many dependency so that when the
subject changes state, all registered observers are notified. The
backbone of event systems and UI updates.

Run: python3 observer.py
"""

from abc import ABC, abstractmethod


class LineObserver(ABC):
    @abstractmethod
    def unit_finished(self, serial: int) -> None: ...


class AssemblyLine:
    """Subject: maintains observers and notifies them on change."""

    def __init__(self):
        self._observers: list[LineObserver] = []

    def attach(self, observer: LineObserver) -> None:
        self._observers.append(observer)

    def detach(self, observer: LineObserver) -> None:
        self._observers.remove(observer)

    def roll_off(self, serial: int) -> None:
        print(f"line: unit #{serial} rolled off")
        for observer in self._observers:
            observer.unit_finished(serial)


class Dashboard(LineObserver):
    def unit_finished(self, serial: int) -> None:
        print(f"  dashboard updates: unit #{serial} complete")


class EngineerPager(LineObserver):
    def unit_finished(self, serial: int) -> None:
        print(f"  pager buzzes: unit #{serial} ready for QA!")


def main():
    line = AssemblyLine()
    dashboard = Dashboard()
    pager = EngineerPager()

    line.attach(dashboard)
    line.attach(pager)

    line.roll_off(41)
    line.roll_off(42)

    line.detach(pager)  # engineer went home
    line.roll_off(43)   # only the dashboard reacts now


if __name__ == "__main__":
    main()
