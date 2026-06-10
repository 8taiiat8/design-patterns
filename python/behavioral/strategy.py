"""Strategy — define a family of interchangeable algorithms and make them
swappable at run time behind a common interface.

Use when a class needs one of several behaviors (pricing rules,
compression formats) and you want to avoid conditionals. In Python,
plain functions often serve as lightweight strategies — both styles are
shown below.

Run: python3 strategy.py
"""

from abc import ABC, abstractmethod


# Classic OO style: strategy interface + concrete strategies.
class PricingStrategy(ABC):
    @abstractmethod
    def final_price(self, base: float) -> float: ...


class RegularPricing(PricingStrategy):
    def final_price(self, base: float) -> float:
        return base


class BlackFridayPricing(PricingStrategy):
    def final_price(self, base: float) -> float:
        return base * 0.5


class MemberPricing(PricingStrategy):
    def final_price(self, base: float) -> float:
        return base * 0.9


class Checkout:
    """Context: configured with a strategy, unaware of which one."""

    def __init__(self, strategy: PricingStrategy):
        self.strategy = strategy

    def pay(self, base: float) -> None:
        print(f"base ${base} -> pay ${self.strategy.final_price(base)}")


def main():
    checkout = Checkout(RegularPricing())
    checkout.pay(100.0)

    checkout.strategy = BlackFridayPricing()
    checkout.pay(100.0)

    checkout.strategy = MemberPricing()
    checkout.pay(100.0)

    # Pythonic alternative: any callable works as a strategy.
    strategies = {
        "clearance": lambda base: base * 0.3,
        "employee": lambda base: base * 0.7,
    }
    for name, price in strategies.items():
        print(f"{name}: pay ${price(100.0)}")


if __name__ == "__main__":
    main()
