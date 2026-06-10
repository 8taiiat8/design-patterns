"""Café Patterna — Chapter 8: The Menu Grows

STORY: The menu used to be five drinks. Now it has sections, sections
inside sections, and combo deals. The owner just wants to ask any line on
the menu — a single croissant or the entire "Breakfast" section — the
same question: "what does this cost?"

PATTERN: Composite — compose objects into tree structures and let clients
treat individual items and groups uniformly.

Run: python3 composite.py
"""

from abc import ABC, abstractmethod


# Component: common interface for single items and whole sections.
class MenuComponent(ABC):
    def __init__(self, name: str):
        self.name = name

    @abstractmethod
    def price_cents(self) -> int: ...

    @abstractmethod
    def print(self, indent: int = 0) -> None: ...


# Leaf
class MenuItem(MenuComponent):
    def __init__(self, name: str, price_cents: int):
        super().__init__(name)
        self._price_cents = price_cents

    def price_cents(self) -> int:
        return self._price_cents

    def print(self, indent: int = 0) -> None:
        print(f"{' ' * indent}- {self.name} (${self._price_cents / 100})")


# Composite: holds children and forwards operations to them.
class MenuSection(MenuComponent):
    def __init__(self, name: str):
        super().__init__(name)
        self.children: list[MenuComponent] = []

    def add(self, component: MenuComponent) -> "MenuSection":
        self.children.append(component)
        return self

    def price_cents(self) -> int:
        return sum(child.price_cents() for child in self.children)

    def print(self, indent: int = 0) -> None:
        print(f"{' ' * indent}+ {self.name}")
        for child in self.children:
            child.print(indent + 2)


def main():
    breakfast = (
        MenuSection("Breakfast combo")
        .add(MenuItem("latte", 350))
        .add(MenuItem("croissant", 300))
    )
    menu = MenuSection("Café Patterna Menu").add(MenuItem("espresso", 200)).add(breakfast)

    menu.print()
    print(f"whole menu, one of each: ${menu.price_cents() / 100}")


if __name__ == "__main__":
    main()
