"""Composite — compose objects into tree structures and let clients treat
individual objects and compositions uniformly.

Use when your domain is naturally a tree (file systems, GUI widgets,
org charts) and you want one interface for both leaves and groups.

Run: python3 composite.py
"""

from abc import ABC, abstractmethod


# Component: common interface for files and directories.
class FileSystemNode(ABC):
    def __init__(self, name: str):
        self.name = name

    @abstractmethod
    def size(self) -> int: ...

    @abstractmethod
    def print(self, indent: int = 0) -> None: ...


# Leaf
class File(FileSystemNode):
    def __init__(self, name: str, size: int):
        super().__init__(name)
        self._size = size

    def size(self) -> int:
        return self._size

    def print(self, indent: int = 0) -> None:
        print(f"{' ' * indent}- {self.name} ({self._size} bytes)")


# Composite: holds children and forwards operations to them.
class Directory(FileSystemNode):
    def __init__(self, name: str):
        super().__init__(name)
        self.children: list[FileSystemNode] = []

    def add(self, node: FileSystemNode) -> "Directory":
        self.children.append(node)
        return self

    def size(self) -> int:
        return sum(child.size() for child in self.children)

    def print(self, indent: int = 0) -> None:
        print(f"{' ' * indent}+ {self.name}/")
        for child in self.children:
            child.print(indent + 2)


def main():
    src = Directory("src").add(File("main.py", 3400)).add(File("util.py", 2100))
    root = Directory("project").add(File("README.md", 1200)).add(src)

    root.print()
    print(f"total size: {root.size()} bytes")


if __name__ == "__main__":
    main()
