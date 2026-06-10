"""Adapter — convert the interface of an existing class into the interface
clients expect, letting otherwise incompatible classes work together.

Use when you want to reuse an existing (often third-party or legacy) class
whose interface doesn't match what your code needs.

Run: python3 adapter.py
"""

from abc import ABC, abstractmethod


# The interface our application expects.
class MediaPlayer(ABC):
    @abstractmethod
    def play(self, file: str) -> None: ...


# Legacy class with an incompatible interface (the adaptee).
# Imagine we cannot modify it.
class VlcEngine:
    def start_vlc_playback(self, path: str) -> None:
        print(f"VLC engine playing: {path}")


# The adapter implements the expected interface and delegates to the adaptee.
class VlcAdapter(MediaPlayer):
    def __init__(self):
        self._engine = VlcEngine()

    def play(self, file: str) -> None:
        self._engine.start_vlc_playback(file)  # translate the call


class Mp3Player(MediaPlayer):
    def play(self, file: str) -> None:
        print(f"MP3 player playing: {file}")


def main():
    players = [Mp3Player(), VlcAdapter()]
    for player in players:
        player.play("song.mp3")


if __name__ == "__main__":
    main()
