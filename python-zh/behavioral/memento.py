"""机器人工厂 RoboWorks — 第 18 章：固件回滚

故事：每次冒险改固件（"实验性激光模块"？）之前，你都会先给机器人
的配置拍个快照。一旦升级把功能搞坏，就回滚到上一个快照。
快照存在备份保险库里——保险库从不查看快照内容，只负责原样归还。

模式：备忘录（Memento）——把对象的内部状态捕获到快照中以便日后恢复，
且不暴露对象的内部细节。发起人 = 固件配置，备忘录 = 快照，
负责人 = 保险库。

运行：python3 memento.py
"""

from dataclasses import dataclass


@dataclass(frozen=True)
class Snapshot:
    """备忘录：不可变，对负责人来说是不透明的。"""

    modules: str


class FirmwareConfig:
    """发起人：要被快照的对象。"""

    def __init__(self):
        self._modules = ""

    def install(self, module: str) -> None:
        self._modules += module

    def save(self) -> Snapshot:
        return Snapshot(self._modules)

    def restore(self, snapshot: Snapshot) -> None:
        self._modules = snapshot.modules

    def show(self) -> None:
        print(f"固件：「{self._modules}」")


class BackupVault:
    """负责人：保存快照，但从不查看内容。"""

    def __init__(self):
        self._stack: list[Snapshot] = []

    def keep(self, snapshot: Snapshot) -> None:
        self._stack.append(snapshot)

    def rollback(self, config: FirmwareConfig) -> bool:
        if not self._stack:
            return False
        config.restore(self._stack.pop())
        return True


def main():
    config = FirmwareConfig()
    vault = BackupVault()

    config.install("核心 v1.0")
    vault.keep(config.save())

    config.install(" + 导航模块")
    vault.keep(config.save())

    config.install(" + 实验性激光模块")  # 大胆。太大胆了。
    config.show()

    vault.rollback(config)  # 激光模块把夹爪搞坏了
    config.show()

    vault.rollback(config)  # 一路回滚到核心版本
    config.show()


if __name__ == "__main__":
    main()
