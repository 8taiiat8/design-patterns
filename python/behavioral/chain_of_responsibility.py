"""RoboWorks — Chapter 13: The Fault Report

STORY: A robot jams on line B. The line technician can authorize repairs
up to $100 on the spot. More than that? The floor engineer. A melted
assembly cell? Only the chief engineer. The fault is reported once — it
climbs the chain until someone can authorize the fix.

PATTERN: Chain of Responsibility — pass a request along a chain of
handlers; each one processes it or forwards it to the next.

Run: python3 chain_of_responsibility.py
"""


class FaultHandler:
    """Handler: knows its successor and the repair budget it may authorize."""

    def __init__(self, title: str, budget: float):
        self.title = title
        self.budget = budget
        self.next: "FaultHandler | None" = None

    def set_next(self, handler: "FaultHandler") -> "FaultHandler":
        self.next = handler
        return handler  # allows chaining: a.set_next(b).set_next(c)

    def handle(self, fault: str, cost: float) -> None:
        if cost <= self.budget:
            print(f'{self.title} authorizes ${cost} repair: "{fault}"')
        elif self.next:
            print(f"{self.title} can't authorize ${cost}, escalating...")
            self.next.handle(fault, cost)
        else:
            print(f'nobody can authorize ${cost} for "{fault}"')


def main():
    technician = FaultHandler("Line technician", 100)
    floor_engineer = FaultHandler("Floor engineer", 1_000)
    chief_engineer = FaultHandler("Chief engineer", 10_000)

    # Build the chain: technician -> floor engineer -> chief engineer.
    technician.set_next(floor_engineer).set_next(chief_engineer)

    # Faults are always reported to whoever is on the line.
    technician.handle("gripper misaligned", 45)
    technician.handle("conveyor belt torn", 800)
    technician.handle("assembly cell melted", 7_500)
    technician.handle("the whole west wing is on fire", 2_000_000)


if __name__ == "__main__":
    main()
