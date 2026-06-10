"""Café Patterna — Chapter 13: "I'd Like a Refund"

STORY: An unhappy customer asks for money back. The barista can refund up
to $5 on the spot. More than that? The shift manager. A catering
disaster? Only the owner. The customer just complains once — the request
climbs the chain until someone can handle it.

PATTERN: Chain of Responsibility — pass a request along a chain of
handlers; each one processes it or forwards it to the next.

Run: python3 chain_of_responsibility.py
"""


class RefundHandler:
    """Handler: knows its successor and the amount it may refund."""

    def __init__(self, title: str, limit: float):
        self.title = title
        self.limit = limit
        self.next: "RefundHandler | None" = None

    def set_next(self, handler: "RefundHandler") -> "RefundHandler":
        self.next = handler
        return handler  # allows chaining: a.set_next(b).set_next(c)

    def handle(self, complaint: str, amount: float) -> None:
        if amount <= self.limit:
            print(f'{self.title} refunds ${amount} for "{complaint}"')
        elif self.next:
            print(f"{self.title} can't refund ${amount}, escalating...")
            self.next.handle(complaint, amount)
        else:
            print(f'nobody can refund ${amount} for "{complaint}"')


def main():
    barista = RefundHandler("Barista", 5)
    shift_manager = RefundHandler("Shift manager", 50)
    owner = RefundHandler("Owner", 500)

    # Build the chain: barista -> shift manager -> owner.
    barista.set_next(shift_manager).set_next(owner)

    # Customers always complain to whoever is at the counter.
    barista.handle("latte was cold", 4.5)
    barista.handle("birthday cake never arrived", 35)
    barista.handle("catering for 50 was a disaster", 400)
    barista.handle("you ruined my wedding", 25_000)


if __name__ == "__main__":
    main()
