"""Café Patterna — Chapter 12: The Secret Recipe Book

STORY: The original recipe book lives in the office safe. Fetching it is
slow and you'd rather not do it at all on quiet days. So the counter
keeps a stand-in: it looks exactly like the recipe book, but only walks
to the safe the FIRST time someone actually asks for a recipe.

PATTERN: Proxy — provide a placeholder for another object to control
access to it. Variants: virtual proxy (lazy loading, shown here),
protection proxy, remote proxy, caching/logging proxy.

Run: python3 proxy.py
"""

from abc import ABC, abstractmethod


class RecipeBook(ABC):
    @abstractmethod
    def look_up(self, drink: str) -> None: ...


class SecretRecipeBook(RecipeBook):
    """Real subject: expensive to construct (a trip to the safe)."""

    def __init__(self):
        print("walking to the safe, unlocking the recipe book (slow!)")

    def look_up(self, drink: str) -> None:
        print(f"reading the secret recipe for {drink}")


class RecipeBookProxy(RecipeBook):
    """Same interface; fetches the real book only on first use."""

    def __init__(self):
        self._real: SecretRecipeBook | None = None

    def look_up(self, drink: str) -> None:
        if self._real is None:
            self._real = SecretRecipeBook()  # lazy load
        self._real.look_up(drink)


def main():
    book = RecipeBookProxy()
    print("proxy on the counter, safe still locked")

    book.look_up("midnight mocha")  # triggers the trip to the safe
    book.look_up("winter chai")     # reuses the already-fetched book


if __name__ == "__main__":
    main()
