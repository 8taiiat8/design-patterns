"""机器人工厂 RoboWorks — 第 15 章：机器人脚本

故事：工程师用一种极简的脚本语言排班："焊接 + 移动 - 省电"。
调度器看得懂：每个词对应一条文法规则，对整个句子求值
就能算出这一班的能耗预算（瓦特）。

模式：解释器（Interpreter）——为小型语言的每条文法规则定义一个类，
用 interpret() 方法对语言中的句子求值。适合简单 DSL；
复杂语言请使用真正的解析库。

本例对脚本树 (焊接 + 移动) - 省电 求值。

运行：python3 interpreter.py
"""

from abc import ABC, abstractmethod


class ScriptExpression(ABC):
    """抽象表达式：一切都求值为瓦特数。"""

    @abstractmethod
    def watts(self) -> int: ...


class Action(ScriptExpression):
    """终结符表达式：单个机器人动作。"""

    def __init__(self, name: str, watts: int):
        self.name = name
        self._watts = watts

    def watts(self) -> int:
        return self._watts


class Sequence(ScriptExpression):
    """非终结符表达式：组合两个子表达式。"""

    def __init__(self, left: ScriptExpression, right: ScriptExpression):
        self.left, self.right = left, right

    def watts(self) -> int:
        return self.left.watts() + self.right.watts()


class PowerSave(ScriptExpression):
    def __init__(self, script: ScriptExpression, saved_watts: int):
        self.script = script
        self.saved_watts = saved_watts

    def watts(self) -> int:
        return self.script.watts() - self.saved_watts


def main():
    # 语法树：(焊接 + 移动) - 省电(100)
    script = PowerSave(Sequence(Action("焊接", 200), Action("移动", 50)), 100)
    print("「焊接 + 移动 - 省电」 =", script.watts(), "瓦")


if __name__ == "__main__":
    main()
