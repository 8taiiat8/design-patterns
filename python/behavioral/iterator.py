"""RoboWorks — Chapter 16: Walking the Conveyor

STORY: The production queue lives on the conveyor system. Supervisors can
walk the queue job by job — but NOBODY reaches into the conveyor's
machinery or needs to know how jobs are stored inside it.

PATTERN: Iterator — provide a way to traverse a collection without
exposing its internal representation. Python bakes this in: the iterator
protocol is __iter__/__next__, `for` loops use it implicitly, and
generators create iterators with almost no code.

Run: python3 iterator.py
"""


class ProductionQueue:
    """The production queue; the storage (conveyor internals) stays private."""

    def __init__(self):
        self._jobs: list[str] = []

    def add(self, job: str) -> "ProductionQueue":
        self._jobs.append(job)
        return self

    def __iter__(self):
        """Return a fresh iterator (the explicit protocol)."""
        return QueueIterator(self._jobs)

    def rush_orders_first(self):
        """Generator: the Pythonic way to expose an alternative traversal."""
        rush = [j for j in self._jobs if j.startswith("RUSH")]
        normal = [j for j in self._jobs if not j.startswith("RUSH")]
        yield from rush + normal


class QueueIterator:
    """Explicit iterator object implementing __next__."""

    def __init__(self, jobs):
        self._jobs = jobs
        self._pos = 0

    def __iter__(self):
        return self

    def __next__(self) -> str:
        if self._pos >= len(self._jobs):
            raise StopIteration
        job = self._jobs[self._pos]
        self._pos += 1
        return job


def main():
    morning_shift = (
        ProductionQueue()
        .add("weld chassis #7")
        .add("RUSH: paint drone shell #12")
        .add("install firmware on batch 3")
    )

    # `for` calls __iter__/__next__ under the hood.
    for job in morning_shift:
        print("executing:", job)

    # Manual protocol usage — what `for` does internally.
    it = iter(morning_shift)
    print("first via next():", next(it))

    print("rush first:", list(morning_shift.rush_orders_first()))


if __name__ == "__main__":
    main()
