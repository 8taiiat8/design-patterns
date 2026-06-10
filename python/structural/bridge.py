"""Café Patterna — Chapter 7: Any Drink, Any Machine

STORY: You sell lattes and cappuccinos; you own a home machine and an
industrial one. Without care you'd need HomeLatte, IndustrialLatte,
HomeCappuccino... a class for every combination. Instead, each DRINK
holds a reference to a MACHINE: new drinks and new machines can now be
added independently.

PATTERN: Bridge — decouple an abstraction (Drink) from its implementation
(BrewMachine) so the two hierarchies vary independently.

Run: python3 bridge.py
"""

from abc import ABC, abstractmethod


# Implementation hierarchy
class BrewMachine(ABC):
    @abstractmethod
    def brew_shots(self, shots: int) -> None: ...


class HomeMachine(BrewMachine):
    def brew_shots(self, shots: int) -> None:
        print(f"home machine gently brews {shots} shot(s)")


class IndustrialMachine(BrewMachine):
    def brew_shots(self, shots: int) -> None:
        print(f"industrial machine blasts out {shots} shot(s)")


# Abstraction hierarchy: holds the "bridge" to the implementation.
class Drink(ABC):
    def __init__(self, machine: BrewMachine):
        self.machine = machine

    @abstractmethod
    def prepare(self) -> None: ...


class Latte(Drink):
    def __init__(self, machine: BrewMachine, shots: int):
        super().__init__(machine)
        self.shots = shots

    def prepare(self) -> None:
        self.machine.brew_shots(self.shots)

    def make_it_stronger(self) -> None:
        self.shots += 1


def main():
    # Any drink can be paired with any machine at run time.
    cozy = Latte(HomeMachine(), 1)
    rush = Latte(IndustrialMachine(), 1)
    cozy.prepare()
    rush.prepare()

    cozy.make_it_stronger()
    cozy.prepare()


if __name__ == "__main__":
    main()
