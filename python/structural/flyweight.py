"""Café Patterna — Chapter 11: A Thousand Tickets, Three Drinks

STORY: On a busy Saturday the kitchen prints thousands of order tickets.
But the café only sells a handful of drink types — printing the full
recipe on every ticket would waste mountains of paper (and in code,
memory). So each ticket carries only its order number and table, plus a
REFERENCE to the one shared drink definition.

PATTERN: Flyweight — share common (intrinsic) state between many objects;
varying (extrinsic) state is passed in from outside. In CPython, small
ints and interned strings are flyweights maintained by the runtime.

Run: python3 flyweight.py
"""

from dataclasses import dataclass


@dataclass(frozen=True)
class DrinkType:
    """Flyweight: heavy intrinsic state shared by many tickets
    (the drink's name and full recipe)."""

    name: str
    recipe: str

    def print_ticket(self, order_no: int, table: int) -> None:
        # Extrinsic state (order number, table) is supplied by the caller.
        print(f"ticket #{order_no} (table {table}): {self.name} — {self.recipe}")


class DrinkTypeFactory:
    """Caches and reuses DrinkType instances."""

    def __init__(self):
        self._cache: dict[str, DrinkType] = {}

    def get(self, name: str, recipe: str) -> DrinkType:
        if name not in self._cache:
            self._cache[name] = DrinkType(name, recipe)
            print(f"(created new flyweight: {name})")
        return self._cache[name]

    def unique_types(self) -> int:
        return len(self._cache)


@dataclass
class OrderTicket:
    """Context object: tiny — extrinsic state plus a shared flyweight."""

    order_no: int
    table: int
    type: DrinkType


def main():
    factory = DrinkTypeFactory()
    rail = [
        OrderTicket(101, 1, factory.get("latte", "2 shots + steamed milk")),
        OrderTicket(102, 3, factory.get("latte", "2 shots + steamed milk")),
        OrderTicket(103, 2, factory.get("matcha", "whisked matcha + milk")),
        OrderTicket(104, 5, factory.get("latte", "2 shots + steamed milk")),
        OrderTicket(105, 4, factory.get("matcha", "whisked matcha + milk")),
        OrderTicket(106, 1, factory.get("latte", "2 shots + steamed milk")),
    ]

    for ticket in rail:
        ticket.type.print_ticket(ticket.order_no, ticket.table)

    print(f"tickets: {len(rail)}, drink flyweights: {factory.unique_types()}")
    print("latte flyweight shared?", rail[0].type is rail[1].type)


if __name__ == "__main__":
    main()
