"""Bridge — decouple an abstraction from its implementation so the two can
vary independently.

Use when a class hierarchy would otherwise explode combinatorially
(Shape x RenderApi). The abstraction (Shape) holds a reference to the
implementation (Renderer), and the two hierarchies grow separately.

Run: python3 bridge.py
"""

from abc import ABC, abstractmethod


# Implementation hierarchy
class Renderer(ABC):
    @abstractmethod
    def render_circle(self, radius: float) -> None: ...


class VectorRenderer(Renderer):
    def render_circle(self, radius: float) -> None:
        print(f"drawing a circle of radius {radius} with vectors")


class RasterRenderer(Renderer):
    def render_circle(self, radius: float) -> None:
        print(f"drawing pixels for a circle of radius {radius}")


# Abstraction hierarchy: holds the "bridge" to the implementation.
class Shape(ABC):
    def __init__(self, renderer: Renderer):
        self.renderer = renderer

    @abstractmethod
    def draw(self) -> None: ...


class Circle(Shape):
    def __init__(self, renderer: Renderer, radius: float):
        super().__init__(renderer)
        self.radius = radius

    def draw(self) -> None:
        self.renderer.render_circle(self.radius)

    def resize(self, factor: float) -> None:
        self.radius *= factor


def main():
    # Any shape can be combined with any renderer at run time.
    a = Circle(VectorRenderer(), 5.0)
    b = Circle(RasterRenderer(), 5.0)
    a.draw()
    b.draw()

    a.resize(2.0)
    a.draw()


if __name__ == "__main__":
    main()
