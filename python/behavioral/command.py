"""RoboWorks — Chapter 14: The Job Queue

STORY: The control panel doesn't shout at the factory floor — every job
becomes a JOB CARD pushed onto the queue. The floor executes cards in its
own time, and when a client cancels, the last card is simply recalled
(undo).

PATTERN: Command — encapsulate a request as an object, letting you queue
requests, log them, and support undo. Decouples the object that invokes
an operation (control panel) from the one performing it (floor).

Run: python3 command.py
"""

from abc import ABC, abstractmethod


class FactoryFloor:
    """Receiver: the object that actually does the work."""

    def start(self, job: str) -> None:
        print(f"floor starts: {job}")

    def recall(self, job: str) -> None:
        print(f"floor recalls: {job}")


class JobCard(ABC):
    @abstractmethod
    def execute(self) -> None: ...

    @abstractmethod
    def undo(self) -> None: ...


class WeldJob(JobCard):
    def __init__(self, floor: FactoryFloor, seam: str):
        self.floor = floor
        self.seam = seam

    def execute(self) -> None:
        self.floor.start(f"weld {self.seam}")

    def undo(self) -> None:
        self.floor.recall(f"weld {self.seam}")


class TransportJob(JobCard):
    def __init__(self, floor: FactoryFloor, cargo: str):
        self.floor = floor
        self.cargo = cargo

    def execute(self) -> None:
        self.floor.start(f"transport {self.cargo}")

    def undo(self) -> None:
        self.floor.recall(f"transport {self.cargo}")


class ControlPanel:
    """Invoker: issues job cards; keeps a history for cancellation."""

    def __init__(self):
        self._history: list[JobCard] = []

    def issue(self, job: JobCard) -> None:
        job.execute()
        self._history.append(job)

    def cancel_last(self) -> None:
        if self._history:
            self._history.pop().undo()


def main():
    floor = FactoryFloor()
    panel = ControlPanel()

    panel.issue(WeldJob(floor, "chassis seam #7"))
    panel.issue(TransportJob(floor, "crate of servos"))

    print("-- client cancels the order --")
    panel.cancel_last()


if __name__ == "__main__":
    main()
