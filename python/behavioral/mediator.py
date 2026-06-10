"""Mediator — define an object that encapsulates how a set of objects
interact, so they don't reference each other directly.

Use when many objects communicate in complex ways (chat rooms, UI forms,
air traffic control); the mediator turns many-to-many links into
one-to-many.

Run: python3 mediator.py
"""

from abc import ABC, abstractmethod


class ChatRoom(ABC):
    @abstractmethod
    def broadcast(self, sender: "User", message: str) -> None: ...

    @abstractmethod
    def join(self, user: "User") -> None: ...


class User:
    """Colleague: only knows the mediator, not the other users."""

    def __init__(self, name: str, room: ChatRoom):
        self.name = name
        self.room = room
        room.join(self)

    def send(self, message: str) -> None:
        print(f"{self.name} sends: {message}")
        self.room.broadcast(self, message)

    def receive(self, sender: str, message: str) -> None:
        print(f"  {self.name} receives from {sender}: {message}")


class SimpleChatRoom(ChatRoom):
    """Concrete mediator: routes messages between registered users."""

    def __init__(self):
        self.users: list[User] = []

    def join(self, user: User) -> None:
        self.users.append(user)

    def broadcast(self, sender: User, message: str) -> None:
        for user in self.users:
            if user is not sender:
                user.receive(sender.name, message)


def main():
    room = SimpleChatRoom()
    alice = User("Alice", room)
    bob = User("Bob", room)
    User("Carol", room)

    alice.send("hi everyone!")
    bob.send("hey Alice")


if __name__ == "__main__":
    main()
