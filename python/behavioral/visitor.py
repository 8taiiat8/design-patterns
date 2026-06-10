"""Café Patterna — Chapter 23: The Inspectors

STORY: Two visitors walk the menu today: the nutritionist tallies
calories, the accountant prints price tags. The menu items themselves
(espresso, muffin) don't change — each item simply ACCEPTS the visitor
and the visitor does its own job per item type. Next month a new
inspector can visit without touching a single menu class.

PATTERN: Visitor — represent an operation on the elements of an object
structure, letting you add new operations without modifying the element
classes. The key mechanism is double dispatch via accept()/visit().

Run: python3 visitor.py
"""

from abc import ABC, abstractmethod


class MenuVisitor(ABC):
    """One visit method per element type."""

    @abstractmethod
    def visit_espresso(self, espresso: "EspressoItem") -> None: ...

    @abstractmethod
    def visit_muffin(self, muffin: "MuffinItem") -> None: ...


class MenuItem(ABC):
    @abstractmethod
    def accept(self, visitor: MenuVisitor) -> None: ...


class EspressoItem(MenuItem):
    def __init__(self, shots: int):
        self.shots = shots

    def accept(self, visitor: MenuVisitor) -> None:
        visitor.visit_espresso(self)


class MuffinItem(MenuItem):
    def __init__(self, grams: int):
        self.grams = grams

    def accept(self, visitor: MenuVisitor) -> None:
        visitor.visit_muffin(self)


# New operations are added as new visitors — no MenuItem class changes.
class CalorieCounter(MenuVisitor):
    def __init__(self):
        self.total = 0

    def visit_espresso(self, espresso: EspressoItem) -> None:
        self.total += 5 * espresso.shots

    def visit_muffin(self, muffin: MuffinItem) -> None:
        self.total += 4 * muffin.grams


class PriceTagPrinter(MenuVisitor):
    def visit_espresso(self, espresso: EspressoItem) -> None:
        print(f"tag: espresso, {espresso.shots} shot(s) — $2.00")

    def visit_muffin(self, muffin: MuffinItem) -> None:
        print(f"tag: muffin, {muffin.grams}g — $3.50")


def main():
    menu: list[MenuItem] = [EspressoItem(2), MuffinItem(120)]

    nutritionist = CalorieCounter()
    accountant = PriceTagPrinter()
    for item in menu:
        item.accept(nutritionist)
        item.accept(accountant)

    print(f"total calories on the menu: {nutritionist.total}")


if __name__ == "__main__":
    main()
