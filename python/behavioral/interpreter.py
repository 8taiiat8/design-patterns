"""Café Patterna — Chapter 15: The Regulars' Shorthand

STORY: Regulars order in shorthand: "espresso + milk - coupon". The till
understands this tiny language: each word is a grammar rule, and
evaluating the sentence computes the price in cents.

PATTERN: Interpreter — for a small language, define a class per grammar
rule with an interpret() method that evaluates sentences. Use for simple
DSLs; for anything complex, prefer a real parser library.

This example evaluates the order tree: (espresso + milk) - coupon.

Run: python3 interpreter.py
"""

from abc import ABC, abstractmethod


class OrderExpression(ABC):
    """Abstract expression: everything evaluates to a price in cents."""

    @abstractmethod
    def price_cents(self) -> int: ...


class Item(OrderExpression):
    """Terminal expression: a single menu item."""

    def __init__(self, name: str, cents: int):
        self.name = name
        self.cents = cents

    def price_cents(self) -> int:
        return self.cents


class Plus(OrderExpression):
    """Non-terminal expression: combines two sub-expressions."""

    def __init__(self, left: OrderExpression, right: OrderExpression):
        self.left, self.right = left, right

    def price_cents(self) -> int:
        return self.left.price_cents() + self.right.price_cents()


class Coupon(OrderExpression):
    def __init__(self, order: OrderExpression, discount_cents: int):
        self.order = order
        self.discount_cents = discount_cents

    def price_cents(self) -> int:
        return self.order.price_cents() - self.discount_cents


def main():
    # Syntax tree for: (espresso + milk) - coupon(100)
    order = Coupon(Plus(Item("espresso", 200), Item("milk", 50)), 100)
    print('"espresso + milk - coupon" =', order.price_cents() / 100, "dollars")


if __name__ == "__main__":
    main()
