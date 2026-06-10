"""Café Patterna — Chapter 18: The Chalkboard Specials

STORY: Every morning you draft today's specials on the chalkboard. Before
each risky idea ("durian latte"?) you photograph the board. When an idea
flops, you restore the board from the last photo. The photos go in a
drawer — whoever keeps them never reads the board off of them, they just
hand them back.

PATTERN: Memento — capture an object's internal state in a snapshot so it
can be restored later, without exposing the object's internals.
Originator = chalkboard, memento = photo, caretaker = the drawer.

Run: python3 memento.py
"""

from dataclasses import dataclass


@dataclass(frozen=True)
class Photo:
    """Memento: immutable, treated as opaque by the caretaker."""

    text: str


class Chalkboard:
    """Originator: the object whose state we snapshot."""

    def __init__(self):
        self._text = ""

    def write(self, chalk: str) -> None:
        self._text += chalk

    def snap(self) -> Photo:
        return Photo(self._text)

    def restore(self, photo: Photo) -> None:
        self._text = photo.text

    def show(self) -> None:
        print(f'chalkboard: "{self._text}"')


class PhotoDrawer:
    """Caretaker: stores photos without inspecting them."""

    def __init__(self):
        self._stack: list[Photo] = []

    def keep(self, photo: Photo) -> None:
        self._stack.append(photo)

    def undo(self, board: Chalkboard) -> bool:
        if not self._stack:
            return False
        board.restore(self._stack.pop())
        return True


def main():
    board = Chalkboard()
    drawer = PhotoDrawer()

    board.write("TODAY: flat white $3")
    drawer.keep(board.snap())

    board.write(" | pumpkin latte $4")
    drawer.keep(board.snap())

    board.write(" | durian latte $6")  # bold. too bold.
    board.show()

    drawer.undo(board)  # scrap the durian idea
    board.show()

    drawer.undo(board)  # back to just the flat white
    board.show()


if __name__ == "__main__":
    main()
