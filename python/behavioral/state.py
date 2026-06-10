"""Café Patterna — Chapter 20: The Moody Espresso Machine

STORY: The espresso machine has moods. When idle, it accepts an order;
when loaded, pressing "order" again just beeps angrily, but pressing
"brew" pours the shot and returns it to idle. Instead of one giant
if/else on a status flag, each mood is its own class.

PATTERN: State — let an object change its behavior when its internal
state changes, by delegating behavior to a state object and swapping it
on transitions.

Run: python3 state.py
"""

from abc import ABC, abstractmethod


class MachineState(ABC):
    """One method per event the machine can receive."""

    @abstractmethod
    def press_order(self, machine: "EspressoMachine") -> None: ...

    @abstractmethod
    def press_brew(self, machine: "EspressoMachine") -> None: ...


class IdleState(MachineState):
    def press_order(self, machine: "EspressoMachine") -> None:
        print("order accepted, grounds loaded")
        machine.state = LoadedState()

    def press_brew(self, machine: "EspressoMachine") -> None:
        print("nothing loaded, place an order first")


class LoadedState(MachineState):
    def press_order(self, machine: "EspressoMachine") -> None:
        print("machine beeps: already loaded with an order")

    def press_brew(self, machine: "EspressoMachine") -> None:
        print("brewing... shot poured, back to idle")
        machine.state = IdleState()


class EspressoMachine:
    """Context: forwards events to its current state object."""

    def __init__(self):
        self.state: MachineState = IdleState()

    def press_order(self) -> None:
        self.state.press_order(self)

    def press_brew(self) -> None:
        self.state.press_brew(self)


def main():
    machine = EspressoMachine()
    machine.press_brew()   # idle: refuses
    machine.press_order()  # idle -> loaded
    machine.press_order()  # loaded: beeps
    machine.press_brew()   # loaded -> idle, pours the shot
    machine.press_brew()   # idle again: refuses


if __name__ == "__main__":
    main()
