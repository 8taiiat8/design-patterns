"""Café Patterna — Chapter 1: The One Cash Register

STORY: On opening day you buy exactly ONE cash register. Every barista
rings up sales on the same machine — if there were two, the day's totals
would never add up. The register is created the first time someone needs
it, and everyone shares it from then on.

PATTERN: Singleton — ensure a class has only one instance and provide a
global access point to it. Note: in Python a plain module is often the
simplest singleton — module-level state is created once and shared. This
file shows the two most common class-based approaches.

Run: python3 singleton.py
"""


class SingletonMeta(type):
    """Metaclass approach: intercepts instantiation and caches the instance."""

    _instances = {}

    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            cls._instances[cls] = super().__call__(*args, **kwargs)
        return cls._instances[cls]


class CashRegister(metaclass=SingletonMeta):
    def __init__(self):
        self.sales = 0
        self.total = 0.0

    def ring_up(self, item, price):
        self.sales += 1
        self.total += price
        print(f"[sale #{self.sales}] {item} ${price} (day total: ${self.total})")


class ShopConfig:
    """__new__ approach: the class itself caches its only instance."""

    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance.settings = {"happy_hour": False}
        return cls._instance


def main():
    CashRegister().ring_up("espresso", 2.0)
    CashRegister().ring_up("croissant", 3.5)
    print("same register?", CashRegister() is CashRegister())

    morning = ShopConfig()
    evening = ShopConfig()
    morning.settings["happy_hour"] = True
    print("same config?", morning is evening, "| evening sees:", evening.settings)


if __name__ == "__main__":
    main()
