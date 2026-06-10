"""Café Patterna — Chapter 14: Tickets on the Rail

STORY: The cashier doesn't shout orders into the kitchen — every order
becomes a TICKET clipped to the rail. The kitchen executes tickets in its
own time, and when a customer changes their mind, the last ticket is
simply pulled off the rail (undo).

PATTERN: Command — encapsulate a request as an object, letting you queue
requests, log them, and support undo. Decouples the object that invokes
an operation (cashier) from the one performing it (kitchen).

Run: python3 command.py
"""

from abc import ABC, abstractmethod


class Kitchen:
    """Receiver: the object that actually does the work."""

    def prepare(self, item: str) -> None:
        print(f"kitchen starts: {item}")

    def scrap(self, item: str) -> None:
        print(f"kitchen scraps: {item}")


class OrderTicket(ABC):
    @abstractmethod
    def execute(self) -> None: ...

    @abstractmethod
    def undo(self) -> None: ...


class DrinkTicket(OrderTicket):
    def __init__(self, kitchen: Kitchen, drink: str):
        self.kitchen = kitchen
        self.drink = drink

    def execute(self) -> None:
        self.kitchen.prepare(self.drink)

    def undo(self) -> None:
        self.kitchen.scrap(self.drink)


class PastryTicket(OrderTicket):
    def __init__(self, kitchen: Kitchen, pastry: str):
        self.kitchen = kitchen
        self.pastry = pastry

    def execute(self) -> None:
        self.kitchen.prepare(self.pastry)

    def undo(self) -> None:
        self.kitchen.scrap(self.pastry)


class TicketRail:
    """Invoker: clips tickets to the rail; keeps history for cancellation."""

    def __init__(self):
        self._history: list[OrderTicket] = []

    def place(self, ticket: OrderTicket) -> None:
        ticket.execute()
        self._history.append(ticket)

    def cancel_last(self) -> None:
        if self._history:
            self._history.pop().undo()


def main():
    kitchen = Kitchen()
    rail = TicketRail()

    rail.place(DrinkTicket(kitchen, "oat latte"))
    rail.place(PastryTicket(kitchen, "almond croissant"))

    print("-- customer changes their mind --")
    rail.cancel_last()


if __name__ == "__main__":
    main()
