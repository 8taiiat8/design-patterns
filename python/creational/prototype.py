"""Prototype — create new objects by copying an existing object instead of
building them from scratch.

Use when object creation is expensive, or when code shouldn't depend on
the concrete classes of the objects it copies. Python's `copy` module
(copy.copy / copy.deepcopy) provides the mechanism out of the box.

Run: python3 prototype.py
"""

import copy


class Shape:
    def __init__(self, color):
        self.color = color

    def clone(self):
        # deepcopy so nested/mutable attributes are copied too
        return copy.deepcopy(self)


class Circle(Shape):
    def __init__(self, radius, color, tags=None):
        super().__init__(color)
        self.radius = radius
        self.tags = tags or []

    def __repr__(self):
        return f"Circle(radius={self.radius}, color={self.color!r}, tags={self.tags})"


def main():
    original = Circle(5.0, "red", tags=["important"])

    # Clone without knowing or naming the concrete class.
    duplicate = original.clone()
    duplicate.color = "blue"
    duplicate.tags.append("copy")  # deepcopy: doesn't leak into the original

    print("original: ", original)
    print("duplicate:", duplicate)

    # Shallow vs deep copy: the classic trap with mutable attributes.
    shallow = copy.copy(original)
    shallow.tags.append("shared!")
    print("after shallow-copy mutation, original tags:", original.tags)


if __name__ == "__main__":
    main()
