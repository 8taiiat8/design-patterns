"""Abstract Factory — provide an interface for creating families of related
objects without specifying their concrete classes.

Use when your code must work with several families of related products
(e.g. UI widgets per operating system) and products from one family must
be used together.

Run: python3 abstract_factory.py
"""

from abc import ABC, abstractmethod


# Abstract products
class Button(ABC):
    @abstractmethod
    def render(self) -> None: ...


class Checkbox(ABC):
    @abstractmethod
    def render(self) -> None: ...


# The "Windows" family
class WindowsButton(Button):
    def render(self) -> None:
        print("render a Windows button")


class WindowsCheckbox(Checkbox):
    def render(self) -> None:
        print("render a Windows checkbox")


# The "Mac" family
class MacButton(Button):
    def render(self) -> None:
        print("render a Mac button")


class MacCheckbox(Checkbox):
    def render(self) -> None:
        print("render a Mac checkbox")


# Abstract factory: one creation method per product type
class GuiFactory(ABC):
    @abstractmethod
    def create_button(self) -> Button: ...

    @abstractmethod
    def create_checkbox(self) -> Checkbox: ...


class WindowsFactory(GuiFactory):
    def create_button(self) -> Button:
        return WindowsButton()

    def create_checkbox(self) -> Checkbox:
        return WindowsCheckbox()


class MacFactory(GuiFactory):
    def create_button(self) -> Button:
        return MacButton()

    def create_checkbox(self) -> Checkbox:
        return MacCheckbox()


def render_dialog(factory: GuiFactory) -> None:
    """Client code depends only on the abstract interfaces."""
    factory.create_button().render()
    factory.create_checkbox().render()


def main():
    print("-- Windows family --")
    render_dialog(WindowsFactory())
    print("-- Mac family --")
    render_dialog(MacFactory())


if __name__ == "__main__":
    main()
