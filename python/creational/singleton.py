"""Singleton — ensure a class has only one instance and provide a global
access point to it.

Use when exactly one object must coordinate something system-wide
(configuration, logging). Note: in Python a plain module is often the
simplest singleton — module-level state is created once and shared.
This file shows the two most common class-based approaches.

Run: python3 singleton.py
"""


class SingletonMeta(type):
    """Metaclass approach: intercepts instantiation and caches the instance."""

    _instances = {}

    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            cls._instances[cls] = super().__call__(*args, **kwargs)
        return cls._instances[cls]


class Logger(metaclass=SingletonMeta):
    def __init__(self):
        self.count = 0

    def log(self, message):
        self.count += 1
        print(f"[log #{self.count}] {message}")


class Config:
    """__new__ approach: the class itself caches its only instance."""

    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance.settings = {"debug": False}
        return cls._instance


def main():
    Logger().log("application started")
    Logger().log("doing some work")
    print("same Logger instance?", Logger() is Logger())

    a = Config()
    b = Config()
    a.settings["debug"] = True
    print("same Config instance?", a is b, "| b sees the change:", b.settings)


if __name__ == "__main__":
    main()
