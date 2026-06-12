"""RoboWorks — Chapter 10: The Big Green Button

STORY: Starting production is chaos behind the scenes: reserve parts,
power up the grid, run the assembly cell, pass quality control — in
exactly that order. The client sees none of it. They press the big green
button labeled "PRODUCE" and the facade orchestrates everything.

PATTERN: Facade — provide a single simplified interface to a complex
subsystem.

Run: python3 facade.py
"""


# Complex subsystem parts. Clients could call these directly, but the
# correct order and wiring is easy to get wrong.
class PartsDepot:
    def reserve_parts_for(self, model: str) -> bool:
        print(f"depot: parts reserved for {model}")
        return True


class PowerGrid:
    def power_up(self, kilowatts: int) -> bool:
        print(f"grid: {kilowatts} kW allocated")
        return True


class AssemblyCell:
    def assemble(self, model: str) -> None:
        print(f"cell: assembling {model}")


class QualityControl:
    def inspect(self, model: str) -> None:
        print(f"QC: {model} passed inspection")


# The facade exposes one high-level operation that orchestrates the parts.
class ProductionFacade:
    def __init__(self):
        self._depot = PartsDepot()
        self._grid = PowerGrid()
        self._cell = AssemblyCell()
        self._qc = QualityControl()

    def produce(self, model: str, kilowatts: int) -> bool:
        if not self._depot.reserve_parts_for(model):
            return False
        if not self._grid.power_up(kilowatts):
            return False
        self._cell.assemble(model)
        self._qc.inspect(model)
        print("production run complete")
        return True


def main():
    big_green_button = ProductionFacade()
    big_green_button.produce("WelderBot Mk2", 40)


if __name__ == "__main__":
    main()
