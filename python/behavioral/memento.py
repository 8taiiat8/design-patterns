"""RoboWorks — Chapter 18: The Firmware Rollback

STORY: Before every risky firmware tweak ("experimental laser module"?)
you snapshot the robot's config. When an update bricks the behavior, you
roll back to the last snapshot. The snapshots sit in the backup vault —
the vault never reads them, it just hands them back.

PATTERN: Memento — capture an object's internal state in a snapshot so it
can be restored later, without exposing the object's internals.
Originator = firmware config, memento = snapshot, caretaker = vault.

Run: python3 memento.py
"""

from dataclasses import dataclass


@dataclass(frozen=True)
class Snapshot:
    """Memento: immutable, treated as opaque by the caretaker."""

    modules: str


class FirmwareConfig:
    """Originator: the object whose state we snapshot."""

    def __init__(self):
        self._modules = ""

    def install(self, module: str) -> None:
        self._modules += module

    def save(self) -> Snapshot:
        return Snapshot(self._modules)

    def restore(self, snapshot: Snapshot) -> None:
        self._modules = snapshot.modules

    def show(self) -> None:
        print(f'firmware: "{self._modules}"')


class BackupVault:
    """Caretaker: stores snapshots without inspecting them."""

    def __init__(self):
        self._stack: list[Snapshot] = []

    def keep(self, snapshot: Snapshot) -> None:
        self._stack.append(snapshot)

    def rollback(self, config: FirmwareConfig) -> bool:
        if not self._stack:
            return False
        config.restore(self._stack.pop())
        return True


def main():
    config = FirmwareConfig()
    vault = BackupVault()

    config.install("core v1.0")
    vault.keep(config.save())

    config.install(" + nav module")
    vault.keep(config.save())

    config.install(" + experimental laser module")  # bold. too bold.
    config.show()

    vault.rollback(config)  # the laser module bricked the gripper
    config.show()

    vault.rollback(config)  # all the way back to core
    config.show()


if __name__ == "__main__":
    main()
