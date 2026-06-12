"""RoboWorks — Chapter 15: The Robot Script

STORY: Engineers program shifts in a tiny script language:
"weld + move - powersave". The scheduler understands it: each word is a
grammar rule, and evaluating the sentence computes the shift's energy
budget in watts.

PATTERN: Interpreter — for a small language, define a class per grammar
rule with an interpret() method that evaluates sentences. Use for simple
DSLs; for anything complex, prefer a real parser library.

This example evaluates the script tree: (weld + move) - powersave.

Run: python3 interpreter.py
"""

from abc import ABC, abstractmethod


class ScriptExpression(ABC):
    """Abstract expression: everything evaluates to watts."""

    @abstractmethod
    def watts(self) -> int: ...


class Action(ScriptExpression):
    """Terminal expression: a single robot action."""

    def __init__(self, name: str, watts: int):
        self.name = name
        self._watts = watts

    def watts(self) -> int:
        return self._watts


class Sequence(ScriptExpression):
    """Non-terminal expression: combines two sub-expressions."""

    def __init__(self, left: ScriptExpression, right: ScriptExpression):
        self.left, self.right = left, right

    def watts(self) -> int:
        return self.left.watts() + self.right.watts()


class PowerSave(ScriptExpression):
    def __init__(self, script: ScriptExpression, saved_watts: int):
        self.script = script
        self.saved_watts = saved_watts

    def watts(self) -> int:
        return self.script.watts() - self.saved_watts


def main():
    # Syntax tree for: (weld + move) - powersave(100)
    script = PowerSave(Sequence(Action("weld", 200), Action("move", 50)), 100)
    print('"weld + move - powersave" =', script.watts(), "watts")


if __name__ == "__main__":
    main()
