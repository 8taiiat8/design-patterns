"""Café Patterna — Chapter 22: The House Ritual

STORY: Every hot drink follows the same house ritual, in the same order:
boil water, brew, pour into cup, add the finishing touch. The ritual
itself never changes — but HOW you brew (drip the coffee, steep the tea)
and the finishing touch differ per drink.

PATTERN: Template Method — define the skeleton of an algorithm in a base
class and let subclasses override specific steps without changing the
algorithm's structure.

Run: python3 template_method.py
"""

from abc import ABC, abstractmethod


class HotDrinkRecipe(ABC):
    """The base class owns the ritual's skeleton."""

    def prepare(self) -> None:
        """The template method: fixed order of steps."""
        self._boil_water()
        self.brew()
        self._pour_in_cup()
        self.add_condiments()  # optional hook with a default

    # Steps subclasses must provide.
    @abstractmethod
    def brew(self) -> None: ...

    # Hook: sensible default, override only if needed.
    def add_condiments(self) -> None:
        print("  (served as is)")

    # Steps identical for every drink stay fixed.
    def _boil_water(self) -> None:
        print("  boiling water")

    def _pour_in_cup(self) -> None:
        print("  pouring into cup")


class Coffee(HotDrinkRecipe):
    def brew(self) -> None:
        print("  dripping coffee through filter")

    def add_condiments(self) -> None:
        print("  adding sugar and milk")


class Tea(HotDrinkRecipe):
    def brew(self) -> None:
        print("  steeping the tea leaves")


def main():
    print("Making coffee:")
    Coffee().prepare()

    print("Making tea:")
    Tea().prepare()


if __name__ == "__main__":
    main()
