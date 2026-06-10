"""Memento — capture an object's internal state in a snapshot so it can be
restored later, without exposing the object's internals.

Use for undo, checkpoints, and transactional rollback. The originator
creates/restores mementos; the caretaker stores them but never looks
inside.

Run: python3 memento.py
"""

from dataclasses import dataclass


@dataclass(frozen=True)
class Snapshot:
    """Memento: immutable, treated as opaque by the caretaker."""

    text: str


class TextEditor:
    """Originator: the object whose state we snapshot."""

    def __init__(self):
        self._text = ""

    def type(self, words: str) -> None:
        self._text += words

    def save(self) -> Snapshot:
        return Snapshot(self._text)

    def restore(self, snapshot: Snapshot) -> None:
        self._text = snapshot.text

    def show(self) -> None:
        print(f'editor: "{self._text}"')


class History:
    """Caretaker: manages snapshots without inspecting them."""

    def __init__(self):
        self._stack: list[Snapshot] = []

    def push(self, snapshot: Snapshot) -> None:
        self._stack.append(snapshot)

    def undo(self, editor: TextEditor) -> bool:
        if not self._stack:
            return False
        editor.restore(self._stack.pop())
        return True


def main():
    editor = TextEditor()
    history = History()

    editor.type("Hello")
    history.push(editor.save())

    editor.type(", world")
    history.push(editor.save())

    editor.type("!!! oops, typo")
    editor.show()

    history.undo(editor)  # back to "Hello, world"
    editor.show()

    history.undo(editor)  # back to "Hello"
    editor.show()


if __name__ == "__main__":
    main()
