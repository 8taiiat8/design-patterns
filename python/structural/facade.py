"""Café Patterna — Chapter 10: One Counter to Rule Them All

STORY: Behind the counter it's chaos: check the bean inventory, brew the
drink, charge the card, stamp the loyalty card — in exactly that order.
The customer sees none of it. They say "one latte please" and the counter
orchestrates everything.

PATTERN: Facade — provide a single simplified interface to a complex
subsystem.

Run: python3 facade.py
"""


# Complex subsystem parts. Clients could call these directly, but the
# correct order and wiring is easy to get wrong.
class BeanInventory:
    def reserve_beans_for(self, drink: str) -> bool:
        print(f"inventory: beans reserved for {drink}")
        return True


class BrewStation:
    def brew(self, drink: str) -> None:
        print(f"brew station: making {drink}")


class Payment:
    def charge(self, amount: float) -> bool:
        print(f"payment: charged ${amount}")
        return True


class LoyaltyProgram:
    def stamp(self, customer: str) -> None:
        print(f"loyalty: stamped {customer}'s card")


# The facade exposes one high-level operation that orchestrates the parts.
class OrderCounter:
    def __init__(self):
        self._inventory = BeanInventory()
        self._brew_station = BrewStation()
        self._payment = Payment()
        self._loyalty = LoyaltyProgram()

    def place_order(self, drink: str, price: float, customer: str) -> bool:
        if not self._inventory.reserve_beans_for(drink):
            return False
        if not self._payment.charge(price):
            return False
        self._brew_station.brew(drink)
        self._loyalty.stamp(customer)
        print("order complete, enjoy!")
        return True


def main():
    counter = OrderCounter()
    counter.place_order("oat latte", 4.5, "Nora")


if __name__ == "__main__":
    main()
