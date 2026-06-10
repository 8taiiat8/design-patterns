"""Template Method — define the skeleton of an algorithm in a base class
and let subclasses override specific steps without changing the
algorithm's structure.

Use when several classes share the same overall workflow but differ in
some steps (data importers, report generators, test fixtures).

Run: python3 template_method.py
"""

from abc import ABC, abstractmethod


class DataImporter(ABC):
    """The base class owns the algorithm's skeleton."""

    def run(self) -> None:
        """The template method: fixed order of steps."""
        self.open()
        self.parse()
        self.validate()  # optional hook with a default
        self._save()
        self._close()

    # Steps subclasses must provide.
    @abstractmethod
    def open(self) -> None: ...

    @abstractmethod
    def parse(self) -> None: ...

    # Hook: sensible default, override only if needed.
    def validate(self) -> None:
        print("  (default validation: none)")

    # Steps identical for everyone stay fixed.
    def _save(self) -> None:
        print("  saving records to database")

    def _close(self) -> None:
        print("  closing source")


class CsvImporter(DataImporter):
    def open(self) -> None:
        print("  opening data.csv")

    def parse(self) -> None:
        print("  parsing comma-separated rows")


class JsonImporter(DataImporter):
    def open(self) -> None:
        print("  opening data.json")

    def parse(self) -> None:
        print("  parsing JSON objects")

    def validate(self) -> None:
        print("  validating against JSON schema")


def main():
    print("CSV import:")
    CsvImporter().run()

    print("JSON import:")
    JsonImporter().run()


if __name__ == "__main__":
    main()
