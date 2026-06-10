"""Flyweight — share common (intrinsic) state between many objects to save
memory; varying (extrinsic) state is passed in from outside.

Use when a program creates huge numbers of similar objects (glyphs,
particles, map tiles). In CPython, small ints and interned strings are
flyweights maintained by the runtime itself.

Run: python3 flyweight.py
"""

from dataclasses import dataclass


@dataclass(frozen=True)
class TreeType:
    """Flyweight: heavy intrinsic state shared by many trees
    (imagine a texture/mesh)."""

    name: str
    color: str

    def draw(self, x: int, y: int) -> None:
        # Extrinsic state (position) is supplied by the caller.
        print(f"draw {self.color} {self.name} at ({x}, {y})")


class TreeTypeFactory:
    """Caches and reuses TreeType instances."""

    def __init__(self):
        self._cache: dict[tuple[str, str], TreeType] = {}

    def get(self, name: str, color: str) -> TreeType:
        key = (name, color)
        if key not in self._cache:
            self._cache[key] = TreeType(name, color)
            print(f"(created new flyweight: {name}/{color})")
        return self._cache[key]

    def unique_types(self) -> int:
        return len(self._cache)


@dataclass
class Tree:
    """Context object: tiny — position plus a shared flyweight."""

    x: int
    y: int
    type: TreeType


def main():
    factory = TreeTypeFactory()
    forest = [
        Tree(1, 2, factory.get("oak", "green")),
        Tree(3, 1, factory.get("oak", "green")),
        Tree(5, 7, factory.get("pine", "dark-green")),
        Tree(2, 8, factory.get("oak", "green")),
        Tree(9, 4, factory.get("pine", "dark-green")),
        Tree(6, 6, factory.get("oak", "green")),
    ]

    for tree in forest:
        tree.type.draw(tree.x, tree.y)

    print(f"trees: {len(forest)}, flyweights: {factory.unique_types()}")
    print("oak flyweight shared?", forest[0].type is forest[1].type)


if __name__ == "__main__":
    main()
