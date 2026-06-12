"""RoboWorks — Chapter 9: The Upgrade Modules

STORY: Armor plating. Solar charger. AI voice module. Clients bolt
upgrades onto the base bot in every combination imaginable. You are NOT
creating an ArmoredSolarTalkingBot class for each combo — instead every
upgrade WRAPS the robot underneath and adds its own spec and price.

PATTERN: Decorator — attach additional responsibilities to an object
dynamically by wrapping it in objects that share its interface. Note:
this is the GoF *object* decorator; Python's `@decorator` syntax is the
same idea applied to functions — both are shown below.

Run: python3 decorator.py
"""

import functools
from abc import ABC, abstractmethod


# --- GoF object decorator -------------------------------------------------
class Robot(ABC):
    @abstractmethod
    def specs(self) -> str: ...

    @abstractmethod
    def cost(self) -> float: ...


class BasicBot(Robot):
    def specs(self) -> str:
        return "basic bot"

    def cost(self) -> float:
        return 2000.0


class UpgradeDecorator(Robot):
    """Base decorator: wraps a Robot and delegates by default."""

    def __init__(self, inner: Robot):
        self._inner = inner

    def specs(self) -> str:
        return self._inner.specs()

    def cost(self) -> float:
        return self._inner.cost()


class ArmorPlating(UpgradeDecorator):
    def specs(self) -> str:
        return super().specs() + " + armor plating"

    def cost(self) -> float:
        return super().cost() + 500.0


class SolarCharger(UpgradeDecorator):
    def specs(self) -> str:
        return super().specs() + " + solar charger"

    def cost(self) -> float:
        return super().cost() + 200.0


class AiVoice(UpgradeDecorator):
    def specs(self) -> str:
        return super().specs() + " + AI voice"

    def cost(self) -> float:
        return super().cost() + 700.0


# --- Pythonic function decorator: same pattern, applied to callables ------
def logged_to_mcu(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        print(f"MCU log: {func.__name__}{args}")
        return func(*args, **kwargs)

    return wrapper


@logged_to_mcu
def deploy(model):
    return f"{model} deployed to the floor"


def main():
    order = AiVoice(SolarCharger(ArmorPlating(BasicBot())))  # stack upgrades freely
    print(f"{order.specs()} costs ${order.cost():.2f}")

    plain = BasicBot()
    print(f"{plain.specs()} costs ${plain.cost():.2f}")

    print(deploy("WelderBot Mk2"))


if __name__ == "__main__":
    main()
