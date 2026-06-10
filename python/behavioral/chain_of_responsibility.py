"""Chain of Responsibility — pass a request along a chain of handlers; each
handler decides to process the request or forward it to the next one.

Use when more than one object may handle a request and the handler isn't
known in advance (approval workflows, middleware, event bubbling).

Run: python3 chain_of_responsibility.py
"""


class Approver:
    """Handler: knows its successor and the amount it may approve."""

    def __init__(self, title: str, limit: float):
        self.title = title
        self.limit = limit
        self.next: "Approver | None" = None

    def set_next(self, approver: "Approver") -> "Approver":
        self.next = approver
        return approver  # allows chaining: a.set_next(b).set_next(c)

    def approve(self, item: str, amount: float) -> None:
        if amount <= self.limit:
            print(f'{self.title} approved "{item}" (${amount})')
        elif self.next:
            print(f"{self.title} can't approve ${amount}, escalating...")
            self.next.approve(item, amount)
        else:
            print(f'nobody can approve "{item}" (${amount})')


def main():
    team_lead = Approver("Team lead", 1_000)
    manager = Approver("Manager", 10_000)
    cfo = Approver("CFO", 100_000)

    # Build the chain: team lead -> manager -> CFO.
    team_lead.set_next(manager).set_next(cfo)

    # Clients always talk to the head of the chain.
    team_lead.approve("new keyboards", 400)
    team_lead.approve("team offsite", 8_000)
    team_lead.approve("office renovation", 75_000)
    team_lead.approve("private jet", 5_000_000)


if __name__ == "__main__":
    main()
