from copy import deepcopy

from manim import *


class CreateCircle(Scene):
    def construct(self):
        # Start

        num1 = 230
        num2 = 180
        result = num1 * num2

        result_bin_lower_bits = bin(result)[2:].zfill(16)[8:]
        result_bin_upper_bits = bin(result)[2:].zfill(16)
        result_bin_upper_bits = result_bin_upper_bits[:8] + "0" * 8

        result_base10_lower_bits = int(result_bin_lower_bits, 2)
        result_base10_upper_bits = int(result_bin_upper_bits, 2)

        base_10_parts_text = f"${result_base10_upper_bits}+{result_base10_lower_bits}$"

        base10_parts_text = Tex(base_10_parts_text)

        # BIN SIDE
        num1_tex = f"$({bin(num1)[2:]})_{{2}}$"
        num2_tex = f"$({bin(num2)[2:]})_{{2}}$"
        result_tex = f"$({bin(result)[2:]})_{{2}}$"

        upper_bin_text = Tex(num1_tex)
        lower_bin_text = Tex(num2_tex)
        result_bin_text = Tex(result_tex)
        multiplication_bin_dot = Tex(r"$\times$")
        lower_bin_text.next_to(upper_bin_text, DOWN)
        multiplication_bin_dot.next_to(lower_bin_text, LEFT)
        left_point = deepcopy(multiplication_bin_dot.get_left().copy())
        right_point = deepcopy(lower_bin_text.get_right().copy())
        line = Line(left_point, right_point)
        line.set_y(-1.1, DOWN)

        bin_group = VGroup(upper_bin_text, lower_bin_text, multiplication_bin_dot, line)
        bin_group.set_x(-5, LEFT)
        self.play(Create(bin_group))

        # BASE_10

        upper_base10_text = Tex(num1)
        lower_base10_text = Tex(num2)
        result_base10_text = Tex(result)
        lower_base10_text.next_to(upper_base10_text, DOWN)
        multiplication_base10_dot = Tex(r"$\times$")

        multiplication_base10_dot.next_to(lower_base10_text, LEFT)
        left_point = deepcopy(multiplication_base10_dot.get_left().copy())
        right_point = deepcopy(lower_base10_text.get_right().copy())
        line = Line(left_point, right_point)
        line.set_y(-1.1, DOWN)

        base_10_group = VGroup(upper_base10_text, lower_base10_text, multiplication_base10_dot, line)
        base_10_group.set_x(5, RIGHT)
        self.play(TransformFromCopy(bin_group, base_10_group))

        self.play(Wait(2))

        # Add Result

        result_bin_text.next_to(lower_bin_text, 1.2 * DOWN)
        bin_group.add(result_bin_text)
        result_base10_text.next_to(base_10_group, 1.2 * DOWN)
        base_10_group.add(result_base10_text)

        self.play(Create(result_bin_text), Create(result_base10_text))

        self.wait(2)

        # Show Overflow of numbers
        size_of_upper = len(str(result_base10_upper_bits))
        base10_parts_text[0][0:size_of_upper].set_color(RED)
        base10_parts_text.set_y(result_base10_text.get_y())
        base10_parts_text.set_x(result_base10_text.get_x())

        self.play(FadeToColor(result_bin_text[0][1:9], color=RED),
                  Transform(result_base10_text, base10_parts_text))

        self.wait(2)

        # Translate Base10

        self.play(base_10_group.animate.move_to(np.array([-4, 2, 0])), bin_group.animate.fade(1))

        self.wait(2)


if __name__ == '__main__':
    scene = CreateCircle()
    scene.construct()
