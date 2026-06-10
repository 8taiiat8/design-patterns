"""Iterator — provide a way to traverse a collection without exposing its
internal representation.

Python bakes this pattern into the language: the iterator protocol is
__iter__/__next__, `for` loops use it implicitly, and generators create
iterators with almost no code. All three styles are shown below.

Run: python3 iterator.py
"""


class Playlist:
    """A collection whose storage layout stays private."""

    def __init__(self):
        self._songs: list[str] = []

    def add(self, song: str) -> "Playlist":
        self._songs.append(song)
        return self

    def __iter__(self):
        """Return a fresh iterator (the explicit protocol)."""
        return PlaylistIterator(self._songs)

    def shuffled(self):
        """Generator: the Pythonic way to expose an alternative traversal."""
        import random

        order = self._songs[:]
        random.shuffle(order)
        yield from order


class PlaylistIterator:
    """Explicit iterator object implementing __next__."""

    def __init__(self, songs):
        self._songs = songs
        self._pos = 0

    def __iter__(self):
        return self

    def __next__(self) -> str:
        if self._pos >= len(self._songs):
            raise StopIteration
        song = self._songs[self._pos]
        self._pos += 1
        return song


def main():
    playlist = (
        Playlist().add("Bohemian Rhapsody").add("Hotel California").add("Stairway to Heaven")
    )

    # `for` calls __iter__/__next__ under the hood.
    for song in playlist:
        print("playing:", song)

    # Manual protocol usage — what `for` does internally.
    it = iter(playlist)
    print("first via next():", next(it))

    print("shuffled:", list(playlist.shuffled()))


if __name__ == "__main__":
    main()
