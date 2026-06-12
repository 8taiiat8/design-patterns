"""RoboWorks — Chapter 8: Assemblies of Assemblies

STORY: A robot isn't one part — it's assemblies inside assemblies. The
torso contains the arm assembly, which contains servos and grippers. The
cost engineer wants to ask any node — a single bolt or the entire torso —
the same question: "what does this cost?"

PATTERN: Composite — compose objects into tree structures and let clients
treat individual parts and whole assemblies uniformly.

Run: python3 composite.py
"""

from abc import ABC, abstractmethod


# Component: common interface for single parts and whole assemblies.
class PartComponent(ABC):
    def __init__(self, name: str):
        self.name = name

    @abstractmethod
    def cost_cents(self) -> int: ...

    @abstractmethod
    def print(self, indent: int = 0) -> None: ...


# Leaf
class Part(PartComponent):
    def __init__(self, name: str, cost_cents: int):
        super().__init__(name)
        self._cost_cents = cost_cents

    def cost_cents(self) -> int:
        return self._cost_cents

    def print(self, indent: int = 0) -> None:
        print(f"{' ' * indent}- {self.name} (${self._cost_cents / 100})")


# Composite: holds children and forwards operations to them.
class Assembly(PartComponent):
    def __init__(self, name: str):
        super().__init__(name)
        self.children: list[PartComponent] = []

    def add(self, component: PartComponent) -> "Assembly":
        self.children.append(component)
        return self

    def cost_cents(self) -> int:
        return sum(child.cost_cents() for child in self.children)

    def print(self, indent: int = 0) -> None:
        print(f"{' ' * indent}+ {self.name}")
        for child in self.children:
            child.print(indent + 2)


def main():
    arm = Assembly("arm assembly").add(Part("servo motor", 4500)).add(Part("gripper", 3000))
    torso = Assembly("torso assembly").add(Part("steel frame", 12000)).add(arm)

    torso.print()
    print(f"total cost: ${torso.cost_cents() / 100}")


if __name__ == "__main__":
    main()
