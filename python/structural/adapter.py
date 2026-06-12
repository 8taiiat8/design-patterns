"""RoboWorks — Chapter 6: The Legacy Welding Arm

STORY: The new assembly line expects every arm to respond to
actuate(task). But the legendary legacy welding arm from the old plant
only understands pulse_crank() — and it still welds better than anything
on the market. You won't rewire the line and you can't modify a
discontinued part, so you build an adapter that fits the old protocol
into the new interface.

PATTERN: Adapter — convert the interface of an existing class into the
interface clients expect, letting incompatible classes work together.

Run: python3 adapter.py
"""

from abc import ABC, abstractmethod


# The interface the assembly line expects.
class RoboticArm(ABC):
    @abstractmethod
    def actuate(self, task: str) -> None: ...


# The legacy part with an incompatible interface (the adaptee).
# Imagine we cannot modify it.
class LegacyWeldingArm:
    def pulse_crank(self, job: str) -> None:
        print(f"legacy arm pulses through: {job}")


# The adapter implements the expected interface and delegates to the adaptee.
class LegacyArmAdapter(RoboticArm):
    def __init__(self):
        self._legacy = LegacyWeldingArm()

    def actuate(self, task: str) -> None:
        self._legacy.pulse_crank(task)  # translate the call


class ServoArm(RoboticArm):
    def actuate(self, task: str) -> None:
        print(f"servo arm smoothly executes: {task}")


def main():
    assembly_line = [ServoArm(), LegacyArmAdapter()]
    for arm in assembly_line:
        arm.actuate("weld chassis seam #7")


if __name__ == "__main__":
    main()
