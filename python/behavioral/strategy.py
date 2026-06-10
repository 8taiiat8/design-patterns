"""Café Patterna — Chapter 21: Happy Hour

STORY: The same latte costs different money depending on the moment: full
price in the morning rush, half price during happy hour, 10% off for
members. The till doesn't care WHICH rule is active — it just asks the
current pricing rule for the final price, and you can swap the rule when
the clock strikes five.

PATTERN: Strategy — define a family of interchangeable algorithms and
make them swappable at run time behind a common interface. In Python,
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


class HappyHourPricing(PricingStrategy):
    def final_price(self, base: float) -> float:
        return base * 0.5


class MemberPricing(PricingStrategy):
    def final_price(self, base: float) -> float:
        return base * 0.9


class Till:
    """Context: configured with a strategy, unaware of which one."""

    def __init__(self, strategy: PricingStrategy):
        self.strategy = strategy

    def charge(self, base: float) -> None:
        print(f"latte base ${base} -> pay ${self.strategy.final_price(base)}")


def main():
    till = Till(RegularPricing())
    till.charge(4.0)

    till.strategy = HappyHourPricing()  # it's 5pm somewhere
    till.charge(4.0)

    till.strategy = MemberPricing()
    till.charge(4.0)

    # Pythonic alternative: any callable works as a strategy.
    discounts = {
        "staff": lambda base: base * 0.3,
        "regulars' tuesday": lambda base: base * 0.7,
    }
    for name, price in discounts.items():
        print(f"{name}: pay ${price(4.0)}")


if __name__ == "__main__":
    main()
