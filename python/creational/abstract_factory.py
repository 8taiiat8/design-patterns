"""Café Patterna — Chapter 3: The Franchise Kits

STORY: Café Patterna goes international! Each franchise orders a "kit":
the Italian kit ships a lever espresso machine WITH porcelain cups, the
Japanese kit ships a siphon brewer WITH ceramic cups. Machines and cups
from one kit always match — you never mix a siphon with porcelain.

PATTERN: Abstract Factory — provide an interface for creating families of
related objects without specifying their concrete classes.

Run: python3 abstract_factory.py
"""

from abc import ABC, abstractmethod


# Abstract products
class CoffeeMachine(ABC):
    @abstractmethod
    def brew(self) -> None: ...


class Cup(ABC):
    @abstractmethod
    def fill(self) -> None: ...


# The Italian family
class LeverMachine(CoffeeMachine):
    def brew(self) -> None:
        print("lever machine pulls a shot")


class PorcelainCup(Cup):
    def fill(self) -> None:
        print("filling a porcelain cup")


# The Japanese family
class SiphonBrewer(CoffeeMachine):
    def brew(self) -> None:
        print("siphon brewer bubbles away")


class CeramicCup(Cup):
    def fill(self) -> None:
        print("filling a ceramic cup")


# Abstract factory: one creation method per product type
class FranchiseKit(ABC):
    @abstractmethod
    def create_machine(self) -> CoffeeMachine: ...

    @abstractmethod
    def create_cup(self) -> Cup: ...


class ItalianKit(FranchiseKit):
    def create_machine(self) -> CoffeeMachine:
        return LeverMachine()

    def create_cup(self) -> Cup:
        return PorcelainCup()


class JapaneseKit(FranchiseKit):
    def create_machine(self) -> CoffeeMachine:
        return SiphonBrewer()

    def create_cup(self) -> Cup:
        return CeramicCup()


def open_franchise(kit: FranchiseKit) -> None:
    """The franchise owner depends only on the abstract kit interface."""
    kit.create_machine().brew()
    kit.create_cup().fill()


def main():
    print("-- Rome branch --")
    open_franchise(ItalianKit())
    print("-- Kyoto branch --")
    open_franchise(JapaneseKit())


if __name__ == "__main__":
    main()
