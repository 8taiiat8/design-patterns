"""Decorator — attach additional responsibilities to an object dynamically
by wrapping it in objects that share its interface.

Note: this is the GoF *object* decorator. Python's `@decorator` syntax is
the same idea applied to functions — both are shown below.

Run: python3 decorator.py
"""

import functools
from abc import ABC, abstractmethod


# --- GoF object decorator -------------------------------------------------
class Coffee(ABC):
    @abstractmethod
    def description(self) -> str: ...

    @abstractmethod
    def cost(self) -> float: ...


class Espresso(Coffee):
    def description(self) -> str:
        return "espresso"

    def cost(self) -> float:
        return 2.0


class CoffeeDecorator(Coffee):
    """Base decorator: wraps a Coffee and delegates by default."""

    def __init__(self, inner: Coffee):
        self._inner = inner

    def description(self) -> str:
        return self._inner.description()

    def cost(self) -> float:
        return self._inner.cost()


class Milk(CoffeeDecorator):
    def description(self) -> str:
        return super().description() + " + milk"

    def cost(self) -> float:
        return super().cost() + 0.5


class Sugar(CoffeeDecorator):
    def description(self) -> str:
        return super().description() + " + sugar"

    def cost(self) -> float:
        return super().cost() + 0.2


# --- Pythonic function decorator: same pattern, applied to callables ------
def logged(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        print(f"calling {func.__name__}{args}")
        return func(*args, **kwargs)

    return wrapper


@logged
def brew(kind):
    return f"a cup of {kind}"


def main():
    order = Sugar(Milk(Espresso()))  # stack wrappers in any combination
    print(f"{order.description()} costs ${order.cost():.2f}")

    plain = Espresso()
    print(f"{plain.description()} costs ${plain.cost():.2f}")

    print(brew("flat white"))


if __name__ == "__main__":
    main()
