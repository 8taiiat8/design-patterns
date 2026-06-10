"""Command — encapsulate a request as an object, letting you parameterize
clients with operations, queue them, and support undo.

Use for undo/redo stacks, task queues, macro recording, and decoupling
the object that invokes an operation from the one that performs it.

Run: python3 command.py
"""

from abc import ABC, abstractmethod


class Light:
    """Receiver: the object that actually does the work."""

    def on(self):
        print("light is ON")

    def off(self):
        print("light is OFF")


class Command(ABC):
    @abstractmethod
    def execute(self) -> None: ...

    @abstractmethod
    def undo(self) -> None: ...


class LightOnCommand(Command):
    def __init__(self, light: Light):
        self.light = light

    def execute(self) -> None:
        self.light.on()

    def undo(self) -> None:
        self.light.off()


class LightOffCommand(Command):
    def __init__(self, light: Light):
        self.light = light

    def execute(self) -> None:
        self.light.off()

    def undo(self) -> None:
        self.light.on()


class RemoteControl:
    """Invoker: triggers commands and keeps a history for undo."""

    def __init__(self):
        self._history: list[Command] = []

    def press(self, command: Command) -> None:
        command.execute()
        self._history.append(command)

    def undo_last(self) -> None:
        if self._history:
            self._history.pop().undo()


def main():
    living_room = Light()
    remote = RemoteControl()

    remote.press(LightOnCommand(living_room))
    remote.press(LightOffCommand(living_room))

    print("-- undo twice --")
    remote.undo_last()
    remote.undo_last()


if __name__ == "__main__":
    main()
