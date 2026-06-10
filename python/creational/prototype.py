"""Café Patterna — Chapter 5: The Drink of the Day

STORY: Inventing a recipe from scratch takes weeks of tasting. So every
morning you take yesterday's bestseller card from the recipe box, CLONE
it, and tweak one thing — "same latte, but with cinnamon". The original
card stays untouched in the box.

PATTERN: Prototype — create new objects by copying an existing object
instead of building them from scratch. Python's `copy` module
(copy.copy / copy.deepcopy) provides the mechanism out of the box.

Run: python3 prototype.py
"""

import copy


class RecipeCard:
    def __init__(self, name):
        self.name = name

    def clone(self):
        # deepcopy so nested/mutable attributes are copied too
        return copy.deepcopy(self)


class DrinkRecipe(RecipeCard):
    def __init__(self, name, secret, tasting_notes=None):
        super().__init__(name)
        self.secret = secret
        self.tasting_notes = tasting_notes or []

    def __repr__(self):
        return f"DrinkRecipe({self.name}: {self.secret}, notes={self.tasting_notes})"


def main():
    bestseller = DrinkRecipe("house latte", "steam milk to 60C", tasting_notes=["smooth"])

    # Clone today's special without naming the concrete class.
    special = bestseller.clone()
    special.secret = "steam milk to 60C + cinnamon dust"
    special.tasting_notes.append("spicy")  # deepcopy: doesn't leak into the original

    print("original:         ", bestseller)
    print("drink of the day: ", special)

    # Shallow vs deep copy: the classic trap with mutable attributes.
    careless = copy.copy(bestseller)
    careless.tasting_notes.append("scribbled on the original!")
    print("after shallow-copy mutation, original notes:", bestseller.tasting_notes)


if __name__ == "__main__":
    main()
