"""Café Patterna — Chapter 19: "Order 42 Is Ready!"

STORY: Customers used to crowd the counter asking "is mine done yet?"
Now they subscribe: when the barista finishes an order, the pickup screen
lights up AND the customer's phone buzzes — automatically, without the
barista knowing or caring who's listening.

PATTERN: Observer — define a one-to-many dependency so that when the
subject changes state, all registered observers are notified. The
backbone of event systems and UI updates.

Run: python3 observer.py
"""

from abc import ABC, abstractmethod


class OrderObserver(ABC):
    @abstractmethod
    def order_ready(self, order_no: int) -> None: ...


class PickupCounter:
    """Subject: maintains observers and notifies them on change."""

    def __init__(self):
        self._observers: list[OrderObserver] = []

    def attach(self, observer: OrderObserver) -> None:
        self._observers.append(observer)

    def detach(self, observer: OrderObserver) -> None:
        self._observers.remove(observer)

    def announce_ready(self, order_no: int) -> None:
        print(f"barista: order #{order_no} is done")
        for observer in self._observers:
            observer.order_ready(order_no)


class PickupScreen(OrderObserver):
    def order_ready(self, order_no: int) -> None:
        print(f"  screen flashes: NOW SERVING #{order_no}")


class CustomerPhone(OrderObserver):
    def order_ready(self, order_no: int) -> None:
        print(f"  phone buzzes: your order #{order_no} is ready!")


def main():
    counter = PickupCounter()
    screen = PickupScreen()
    phone = CustomerPhone()

    counter.attach(screen)
    counter.attach(phone)

    counter.announce_ready(41)
    counter.announce_ready(42)

    counter.detach(phone)  # customer picked up and left
    counter.announce_ready(43)  # only the screen reacts now


if __name__ == "__main__":
    main()
