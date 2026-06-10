"""Café Patterna — Chapter 17: The Counter Intercom

STORY: With cashier, barista and baker all working at once, the shop
turned into a shouting match — everyone yelling at everyone. So you
installed an intercom: staff speak INTO the intercom, and it relays the
message to everyone else. Nobody needs to know who else is on shift.

PATTERN: Mediator — define an object that encapsulates how a set of
objects interact, so they don't reference each other directly; turns
many-to-many links into one-to-many.

Run: python3 mediator.py
"""

from abc import ABC, abstractmethod


class Intercom(ABC):
    @abstractmethod
    def relay(self, sender: "StaffMember", message: str) -> None: ...

    @abstractmethod
    def sign_in(self, member: "StaffMember") -> None: ...


class StaffMember:
    """Colleague: only knows the intercom, not the other staff."""

    def __init__(self, name: str, intercom: Intercom):
        self.name = name
        self.intercom = intercom
        intercom.sign_in(self)

    def announce(self, message: str) -> None:
        print(f"{self.name} announces: {message}")
        self.intercom.relay(self, message)

    def hear(self, sender: str, message: str) -> None:
        print(f"  {self.name} hears {sender}: {message}")


class CounterIntercom(Intercom):
    """Concrete mediator: relays announcements to everyone else on shift."""

    def __init__(self):
        self.staff: list[StaffMember] = []

    def sign_in(self, member: StaffMember) -> None:
        self.staff.append(member)

    def relay(self, sender: StaffMember, message: str) -> None:
        for member in self.staff:
            if member is not sender:
                member.hear(sender.name, message)


def main():
    intercom = CounterIntercom()
    cleo = StaffMember("Cleo (cashier)", intercom)
    ben = StaffMember("Ben (barista)", intercom)
    StaffMember("Mara (baker)", intercom)

    cleo.announce("two lattes and a croissant for table 4!")
    ben.announce("milk steamer is free again")


if __name__ == "__main__":
    main()
