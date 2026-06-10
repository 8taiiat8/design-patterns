"""Proxy — provide a placeholder for another object to control access to it.

Common variants: virtual proxy (lazy loading), protection proxy (access
control), remote proxy, caching/logging proxy. This example shows a
virtual proxy that delays loading a large image until it is displayed.

Run: python3 proxy.py
"""

from abc import ABC, abstractmethod


class Image(ABC):
    @abstractmethod
    def display(self) -> None: ...


class RealImage(Image):
    """Real subject: expensive to construct (pretend it loads from disk)."""

    def __init__(self, filename: str):
        self.filename = filename
        print(f"loading {filename} from disk (slow!)")

    def display(self) -> None:
        print(f"displaying {self.filename}")


class ImageProxy(Image):
    """Same interface; creates the real subject only on first use."""

    def __init__(self, filename: str):
        self.filename = filename
        self._real: RealImage | None = None

    def display(self) -> None:
        if self._real is None:
            self._real = RealImage(self.filename)  # lazy load
        self._real.display()


def main():
    photo = ImageProxy("vacation.png")
    print("proxy created, nothing loaded yet")

    photo.display()  # triggers the expensive load
    photo.display()  # reuses the already-loaded image


if __name__ == "__main__":
    main()
