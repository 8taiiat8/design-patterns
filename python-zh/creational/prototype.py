"""机器人工厂 RoboWorks — 第 5 章：克隆图纸

故事：从零设计一台机器人要做几个月的研发。所以当客户想要
"同款焊接机器人，但臂展更长"时，你直接克隆成熟图纸，只改一项参数。
档案室里的原版图纸原封不动。

模式：原型（Prototype）——通过复制现有对象来创建新对象，
而不是从头构建。Python 的 `copy` 模块（copy.copy / copy.deepcopy）
开箱即用地提供了这一机制。

运行：python3 prototype.py
"""

import copy


class Blueprint:
    def __init__(self, model):
        self.model = model

    def clone(self):
        # 用 deepcopy，嵌套/可变属性也会被复制
        return copy.deepcopy(self)


class RobotBlueprint(Blueprint):
    def __init__(self, model, spec, certified_tests=None):
        super().__init__(model)
        self.spec = spec
        self.certified_tests = certified_tests or []

    def __repr__(self):
        return f"机器人图纸（{self.model}：{self.spec}，已认证测试={self.certified_tests}）"


def main():
    proven = RobotBlueprint("焊接机器人 Mk2", "臂展 1.2 米", certified_tests=["压力测试"])

    # 不需要点名具体类即可克隆图纸。
    custom = proven.clone()
    custom.spec = "臂展 2.0 米，关节加固"
    custom.certified_tests.append("加长臂测试")  # deepcopy：不会影响原版

    print("原版图纸：", proven)
    print("客户订单：", custom)

    # 浅拷贝 vs 深拷贝：可变属性的经典陷阱。
    careless = copy.copy(proven)
    careless.certified_tests.append("乱写到原版上了！")
    print("浅拷贝被修改后，原版的测试记录：", proven.certified_tests)


if __name__ == "__main__":
    main()
