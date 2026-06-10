"""State — let an object change its behavior when its internal state
changes, by delegating behavior to a state object.

Use when an object has large conditionals on its current state
(if status == ... everywhere); each state becomes a class and transitions
swap the current state object.

Run: python3 state.py
"""

from abc import ABC, abstractmethod


class State(ABC):
    """One method per event the machine can receive."""

    @abstractmethod
    def insert_coin(self, machine: "VendingMachine") -> None: ...

    @abstractmethod
    def dispense(self, machine: "VendingMachine") -> None: ...


class IdleState(State):
    def insert_coin(self, machine: "VendingMachine") -> None:
        print("coin accepted")
        machine.state = HasCoinState()

    def dispense(self, machine: "VendingMachine") -> None:
        print("insert a coin first")


class HasCoinState(State):
    def insert_coin(self, machine: "VendingMachine") -> None:
        print("coin already inserted, returning it")

    def dispense(self, machine: "VendingMachine") -> None:
        print("dispensing snack, back to idle")
        machine.state = IdleState()


class VendingMachine:
    """Context: forwards events to its current state object."""

    def __init__(self):
        self.state: State = IdleState()

    def insert_coin(self) -> None:
        self.state.insert_coin(self)

    def dispense(self) -> None:
        self.state.dispense(self)


def main():
    machine = VendingMachine()
    machine.dispense()     # idle: refuses
    machine.insert_coin()  # idle -> has coin
    machine.insert_coin()  # has coin: rejects second coin
    machine.dispense()     # has coin -> idle, dispenses
    machine.dispense()     # idle again: refuses


if __name__ == "__main__":
    main()
