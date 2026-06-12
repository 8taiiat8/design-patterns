"""RoboWorks — Chapter 1: The Master Control Unit

STORY: Your factory has exactly ONE Master Control Unit. Every assembly
line reports to the same MCU — if there were two, they would issue
conflicting orders and the factory would tear itself apart. The MCU boots
the first time someone needs it, and everyone shares it.

PATTERN: Singleton — ensure a class has only one instance and provide a
global access point to it. Note: in Python a plain module is often the
simplest singleton — module-level state is created once and shared. This
file shows the two most common class-based approaches.

Run: python3 singleton.py
"""


class SingletonMeta(type):
    """Metaclass approach: intercepts instantiation and caches the instance."""

    _instances = {}

    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            cls._instances[cls] = super().__call__(*args, **kwargs)
        return cls._instances[cls]


class MasterControlUnit(metaclass=SingletonMeta):
    def __init__(self):
        self.tasks = 0

    def log_task(self, task):
        self.tasks += 1
        print(f"[MCU task #{self.tasks}] {task}")


class FactoryConfig:
    """__new__ approach: the class itself caches its only instance."""

    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance.settings = {"night_shift": False}
        return cls._instance


def main():
    MasterControlUnit().log_task("power up line A")
    MasterControlUnit().log_task("calibrate welding lasers")
    print("same MCU?", MasterControlUnit() is MasterControlUnit())

    line_a = FactoryConfig()
    line_b = FactoryConfig()
    line_a.settings["night_shift"] = True
    print("same config?", line_a is line_b, "| line B sees:", line_b.settings)


if __name__ == "__main__":
    main()
