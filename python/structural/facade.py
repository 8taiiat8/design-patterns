"""Facade — provide a single simplified interface to a complex subsystem.

Use when clients only need a small slice of a subsystem's functionality,
or when you want to decouple client code from the subsystem's internals.

Run: python3 facade.py
"""


# Complex subsystem parts. Clients could call these directly, but the
# correct order and wiring is easy to get wrong.
class Inventory:
    def reserve(self, item: str) -> bool:
        print(f"inventory: reserved {item}")
        return True


class Payment:
    def charge(self, amount: float) -> bool:
        print(f"payment: charged ${amount}")
        return True


class Shipping:
    def schedule(self, item: str, address: str) -> None:
        print(f"shipping: {item} -> {address}")


# The facade exposes one high-level operation that orchestrates the parts.
class OrderFacade:
    def __init__(self):
        self._inventory = Inventory()
        self._payment = Payment()
        self._shipping = Shipping()

    def place_order(self, item: str, price: float, address: str) -> bool:
        if not self._inventory.reserve(item):
            return False
        if not self._payment.charge(price):
            return False
        self._shipping.schedule(item, address)
        print("order complete")
        return True


def main():
    shop = OrderFacade()
    shop.place_order("mechanical keyboard", 89.99, "42 Wallaby Way")


if __name__ == "__main__":
    main()
