"""Café Patterna — Chapter 4: "Can I Get That With Oat Milk?"

STORY: Customers never order a plain drink. It's "large, two shots, oat
milk, vanilla, extra hot". A constructor with seven parameters would be a
nightmare, so the counter assembles each drink step by step — and the
menu board keeps recipes (a director) for the house favorites.

PATTERN: Builder — separate the construction of a complex object from its
representation, so the same process can create different configurations
step by step. Note: Python's keyword arguments and dataclasses cover many
simple cases; the builder shines when construction involves ordering,
validation, or reusable recipes.

Run: python3 builder.py
"""

from dataclasses import dataclass, field


@dataclass
class Drink:
    base: str = ""
    size: str = ""
    shots: int = 0
    milk: str = ""
    extras: list = field(default_factory=list)


class DrinkBuilder:
    """Fluent builder: each step returns self so calls can be chained."""

    def __init__(self):
        self._drink = Drink()

    def base(self, value: str) -> "DrinkBuilder":
        self._drink.base = value
        return self

    def size(self, value: str) -> "DrinkBuilder":
        self._drink.size = value
        return self

    def shots(self, count: int) -> "DrinkBuilder":
        self._drink.shots = count
        return self

    def milk(self, value: str) -> "DrinkBuilder":
        self._drink.milk = value
        return self

    def extra(self, value: str) -> "DrinkBuilder":
        self._drink.extras.append(value)
        return self

    def build(self) -> Drink:
        if not self._drink.base:
            raise ValueError("a drink needs a base")
        return self._drink


class MenuBoard:
    """The menu board (director): encapsulates well-known recipes."""

    @staticmethod
    def house_latte() -> Drink:
        return (
            DrinkBuilder()
            .base("espresso")
            .size("medium")
            .shots(2)
            .milk("whole, steamed")
            .build()
        )

    @staticmethod
    def triple_mocha() -> Drink:
        return (
            DrinkBuilder()
            .base("mocha")
            .size("large")
            .shots(3)
            .milk("oat, extra foam")
            .extra("chocolate dust")
            .build()
        )


def main():
    # A picky customer builds a custom drink step by step.
    custom = DrinkBuilder().base("espresso").size("large").shots(2).milk("oat").build()
    print("custom:", custom)

    # Or order straight off the menu board's recipes.
    print("house: ", MenuBoard.house_latte())
    print("mocha: ", MenuBoard.triple_mocha())


if __name__ == "__main__":
    main()
