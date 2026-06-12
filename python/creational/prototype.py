"""RoboWorks — Chapter 5: Clone the Blueprint

STORY: Designing a robot from a blank sheet takes months of R&D. So when
a client wants "the same WelderBot, but with a longer reach", you CLONE
the proven blueprint and tweak one spec. The original blueprint stays
untouched in the archive.

PATTERN: Prototype — create new objects by copying an existing object
instead of building them from scratch. Python's `copy` module
(copy.copy / copy.deepcopy) provides the mechanism out of the box.

Run: python3 prototype.py
"""

import copy


class Blueprint:
    def __init__(self, model):
        self.model = model

    def clone(self):
        # deepcopy so nested/mutable attributes are copied too
        return copy.deepcopy(self)


class RobotBlueprint(Blueprint):
    def __init__(self, model, spec, certified_tests=None):
        super().__init__(model)
        self.spec = spec
        self.certified_tests = certified_tests or []

    def __repr__(self):
        return f"RobotBlueprint({self.model}: {self.spec}, tests={self.certified_tests})"


def main():
    proven = RobotBlueprint("WelderBot Mk2", "arm reach 1.2m", certified_tests=["stress"])

    # Clone the blueprint without naming the concrete class.
    custom = proven.clone()
    custom.spec = "arm reach 2.0m, reinforced joints"
    custom.certified_tests.append("extended-reach")  # deepcopy: original untouched

    print("original:    ", proven)
    print("client order:", custom)

    # Shallow vs deep copy: the classic trap with mutable attributes.
    careless = copy.copy(proven)
    careless.certified_tests.append("scribbled on the original!")
    print("after shallow-copy mutation, original tests:", proven.certified_tests)


if __name__ == "__main__":
    main()
