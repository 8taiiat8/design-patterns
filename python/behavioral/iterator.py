"""Café Patterna — Chapter 16: The Vinyl Crate

STORY: The café's atmosphere lives and dies by its playlist. The records
sit in a crate behind the counter — customers can flip through the
playlist song by song, but NOBODY touches the crate itself or needs to
know how the records are stored.

PATTERN: Iterator — provide a way to traverse a collection without
exposing its internal representation. Python bakes this in: the iterator
protocol is __iter__/__next__, `for` loops use it implicitly, and
generators create iterators with almost no code.

Run: python3 iterator.py
"""


class Playlist:
    """The café playlist; the storage (vinyl crate) stays private."""

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
    morning_set = Playlist().add("Blue in Green").add("Take Five").add("Misty")

    # `for` calls __iter__/__next__ under the hood.
    for song in morning_set:
        print("now playing:", song)

    # Manual protocol usage — what `for` does internally.
    it = iter(morning_set)
    print("first via next():", next(it))

    print("evening shuffle:", list(morning_set.shuffled()))


if __name__ == "__main__":
    main()
