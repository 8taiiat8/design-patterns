"""Interpreter — given a small language, define a class per grammar rule
with an interpret() method that evaluates sentences of the language.

Use for simple domain-specific languages: filters, arithmetic, rule
engines. For anything complex, prefer a real parser library.

This example interprets arithmetic expressions built as an object tree:
(5 + 3) - 2.

Run: python3 interpreter.py
"""

from abc import ABC, abstractmethod


class Expression(ABC):
    @abstractmethod
    def interpret(self) -> int: ...


class Number(Expression):
    """Terminal expression: a literal value."""

    def __init__(self, value: int):
        self.value = value

    def interpret(self) -> int:
        return self.value


class Add(Expression):
    """Non-terminal expression: combines two sub-expressions."""

    def __init__(self, left: Expression, right: Expression):
        self.left, self.right = left, right

    def interpret(self) -> int:
        return self.left.interpret() + self.right.interpret()


class Subtract(Expression):
    def __init__(self, left: Expression, right: Expression):
        self.left, self.right = left, right

    def interpret(self) -> int:
        return self.left.interpret() - self.right.interpret()


def main():
    # Abstract syntax tree for: (5 + 3) - 2
    expression = Subtract(Add(Number(5), Number(3)), Number(2))
    print("(5 + 3) - 2 =", expression.interpret())


if __name__ == "__main__":
    main()
