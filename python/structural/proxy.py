"""RoboWorks — Chapter 12: The Heavy Diagnostics Suite

STORY: The full diagnostics suite takes ages to boot — gigabytes of
sensor models and calibration tables. On most shifts nobody needs it. So
the workbench keeps a stand-in: it looks exactly like the suite, but only
boots the real thing the FIRST time an engineer runs a scan.

PATTERN: Proxy — provide a placeholder for another object to control
access to it. Variants: virtual proxy (lazy loading, shown here),
protection proxy, remote proxy, caching/logging proxy.

Run: python3 proxy.py
"""

from abc import ABC, abstractmethod


class Diagnostics(ABC):
    @abstractmethod
    def scan(self, robot: str) -> None: ...


class FullDiagnosticsSuite(Diagnostics):
    """Real subject: expensive to construct (boots the full suite)."""

    def __init__(self):
        print("booting the full diagnostics suite (slow!)")

    def scan(self, robot: str) -> None:
        print(f"running deep scan on {robot}")


class DiagnosticsProxy(Diagnostics):
    """Same interface; boots the real suite only on first use."""

    def __init__(self):
        self._real: FullDiagnosticsSuite | None = None

    def scan(self, robot: str) -> None:
        if self._real is None:
            self._real = FullDiagnosticsSuite()  # lazy load
        self._real.scan(robot)


def main():
    workbench = DiagnosticsProxy()
    print("proxy ready, suite not booted yet")

    workbench.scan("WelderBot #7")    # triggers the expensive boot
    workbench.scan("ScoutDrone #42")  # reuses the already-booted suite


if __name__ == "__main__":
    main()
