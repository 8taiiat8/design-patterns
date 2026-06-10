"""Visitor — represent an operation on the elements of an object structure,
letting you add new operations without modifying the element classes.

Use when you have a stable hierarchy of element types and frequently need
new operations across all of them (exporters, pretty-printers, metrics).
The key mechanism is double dispatch via accept()/visit().

Run: python3 visitor.py
"""

import math
from abc import ABC, abstractmethod


class ShapeVisitor(ABC):
    """One visit method per element type."""

    @abstractmethod
    def visit_circle(self, circle: "Circle") -> None: ...

    @abstractmethod
    def visit_square(self, square: "Square") -> None: ...


class Shape(ABC):
    @abstractmethod
    def accept(self, visitor: ShapeVisitor) -> None: ...


class Circle(Shape):
    def __init__(self, radius: float):
        self.radius = radius

    def accept(self, visitor: ShapeVisitor) -> None:
        visitor.visit_circle(self)


class Square(Shape):
    def __init__(self, side: float):
        self.side = side

    def accept(self, visitor: ShapeVisitor) -> None:
        visitor.visit_square(self)


# New operations are added as new visitors — no Shape class changes.
class AreaCalculator(ShapeVisitor):
    def __init__(self):
        self.total = 0.0

    def visit_circle(self, circle: Circle) -> None:
        self.total += math.pi * circle.radius**2

    def visit_square(self, square: Square) -> None:
        self.total += square.side**2


class SvgExporter(ShapeVisitor):
    def visit_circle(self, circle: Circle) -> None:
        print(f'<circle r="{circle.radius}"/>')

    def visit_square(self, square: Square) -> None:
        print(f'<rect width="{square.side}" height="{square.side}"/>')


def main():
    shapes: list[Shape] = [Circle(2.0), Square(3.0)]

    area = AreaCalculator()
    svg = SvgExporter()
    for shape in shapes:
        shape.accept(area)
        shape.accept(svg)

    print(f"total area: {area.total:.2f}")


if __name__ == "__main__":
    main()
