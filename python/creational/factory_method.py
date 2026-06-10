"""Café Patterna — Chapter 2: Hiring Baristas

STORY: Business grows, so you hire baristas. You don't tell each barista
HOW to serve a customer — the routine is the same (greet, craft the drink,
hand it over). What differs is WHICH drink each specialist crafts: the
espresso barista pulls shots, the tea master whisks matcha.

PATTERN: Factory Method — define an interface for creating an object, but
let subclasses decide which concrete class to instantiate.

Run: python3 factory_method.py
"""

from abc import ABC, abstractmethod


# Product interface
class Drink(ABC):
    @abstractmethod
    def describe(self) -> str: ...


class Espresso(Drink):
    def describe(self) -> str:
        return "a double espresso, rich crema"


class MatchaLatte(Drink):
    def describe(self) -> str:
        return "a matcha latte, whisked to order"


# Creator: the serving routine relies only on the Drink interface;
# the factory method defers the concrete choice to subclasses.
class Barista(ABC):
    def serve_customer(self) -> None:
        drink = self.craft_signature_drink()  # the factory method
        print(f"Barista serves {drink.describe()}")

    @abstractmethod
    def craft_signature_drink(self) -> Drink: ...


class EspressoBarista(Barista):
    def craft_signature_drink(self) -> Drink:
        return Espresso()


class TeaMaster(Barista):
    def craft_signature_drink(self) -> Drink:
        return MatchaLatte()


def main():
    EspressoBarista().serve_customer()
    TeaMaster().serve_customer()


if __name__ == "__main__":
    main()
