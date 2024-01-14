import dataclasses

from manim import *


class MultiplicationRepresentation(VGroup):
    def __init__(self, upper_text: str | int, lower_text: str | int, result: str | int):
        self.upper_tex = Tex(upper_text)
        self.lower_tex = Tex(lower_text)
        self.result_tex = Tex(result)

        self.multiplication_bin_dot = Tex(r"$\times$")
        self.lower_tex.next_to(self.upper_tex, DOWN)
        self.multiplication_bin_dot.next_to(self.lower_tex, LEFT)
        left_point = self.multiplication_bin_dot.get_left()
        right_point = self.lower_tex.get_right()
        self.line = Line(left_point, right_point)
        self.line.set_y(-1.1, DOWN)

        super().__init__(
            self.upper_tex, self.lower_tex, self.multiplication_bin_dot, self.line
        )

    def add_result_to_group(self):
        self.add(self.result_tex)
        self.result_tex.next_to(self.line, 1.2 * DOWN)


@dataclasses.dataclass
class TexCharAssociation:
    latex_char: Mobject
    char: str


@dataclasses.dataclass
class NumberExponentTex:
    number: int
    exponent: int
    latex_component: Tex
