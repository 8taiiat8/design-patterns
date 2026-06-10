"""Café Patterna — Chapter 6: Grandpa's Grinder

STORY: The new kitchen line expects every grinder to respond to
grind(beans). But grandpa's beloved cast-iron grinder only understands
turn_crank() — and it makes the best grounds in town. You won't rewire
the kitchen and you can't modify a family heirloom, so you build an
adapter that fits the old crank into the new interface.

PATTERN: Adapter — convert the interface of an existing class into the
interface clients expect, letting incompatible classes work together.

Run: python3 adapter.py
"""

from abc import ABC, abstractmethod


# The interface the kitchen line expects.
class Grinder(ABC):
    @abstractmethod
    def grind(self, beans: str) -> None: ...


# The family heirloom with an incompatible interface (the adaptee).
# Imagine we cannot modify it.
class VintageGrinder:
    def turn_crank(self, contents: str) -> None:
        print(f"vintage grinder slowly cranks through: {contents}")


# The adapter implements the expected interface and delegates to the adaptee.
class VintageGrinderAdapter(Grinder):
    def __init__(self):
        self._heirloom = VintageGrinder()

    def grind(self, beans: str) -> None:
        self._heirloom.turn_crank(beans)  # translate the call


class ElectricGrinder(Grinder):
    def grind(self, beans: str) -> None:
        print(f"electric grinder whizzes through: {beans}")


def main():
    kitchen_line = [ElectricGrinder(), VintageGrinderAdapter()]
    for grinder in kitchen_line:
        grinder.grind("Ethiopian beans")


if __name__ == "__main__":
    main()
