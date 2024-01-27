import itertools
import math

from manim import *
from manim_slides import Slide

from multiplication_repr import (
    MultiplicationRepresentation,
    TexCharAssociation,
    NumberExponentTex,
)


def number_to_base_10_parts(number: int) -> (str, list[str]):
    if number == 0:
        return "0"
    n_digits = math.ceil(math.log2(number))
    digits: list[str] = []
    for i in range(n_digits):
        digit = number % 10
        number //= 10
        if digit == 0:
            continue

        digits.append(rf"{digit} \cdot 10^{{{i}}}")

    return f'${"+".join(digits[::-1])}$', digits[::-1]


def number_to_base_2_parts(number: int, grouping_size: int) -> (str, list[str]):
    n_digits = math.ceil(math.log2(number))
    mask = (grouping_size ** 2) - 1
    digits: list[str] = []
    for i in range(0, n_digits, grouping_size):
        digit = number & mask
        number >>= grouping_size

        digit_bin = bin(digit)[2:].zfill(4)

        digits.append(rf"{digit_bin}\verb|<<|{{{i}}}")

    return f'${"+".join(digits[::-1])}$', digits[::-1]


class CreateCircle(Slide):
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

        base_10_group, bin_group = self.scene_1(
            num1, num2, result, result_base10_lower_bits, result_base10_upper_bits
        )

        self.next_slide()

        # Explain Base 2

        self.scene_2(bin_group, num1, num2)

    def scene_1(
            self, num1, num2, result, result_base10_lower_bits, result_base10_upper_bits
    ):
        base_10_parts_text = f"${result_base10_upper_bits}+{result_base10_lower_bits}$"
        base10_parts_text = Tex(base_10_parts_text)
        # BIN SIDE
        num1_tex = f"$({bin(num1)[2:]})_{{2}}$"
        num2_tex = f"$({bin(num2)[2:]})_{{2}}$"
        result_tex = f"$({bin(result)[2:]})_{{2}}$"
        bin_group = MultiplicationRepresentation(
            num1_tex,
            num2_tex,
            result_tex,
        )
        bin_group.set_x(-5, LEFT)
        self.play(Create(bin_group))
        # BASE_10
        base_10_group = MultiplicationRepresentation(
            num1,
            num2,
            result,
        )
        base_10_group.set_x(5, RIGHT)
        self.play(TransformFromCopy(bin_group, base_10_group))
        self.next_slide()
        # Add Result
        base_10_group.add_result_to_group()
        bin_group.add_result_to_group()
        self.play(Create(bin_group.result_tex), Create(base_10_group.result_tex))
        self.next_slide()
        # # Show Overflow of numbers
        size_of_upper = len(str(result_base10_upper_bits))
        base10_parts_text[0][0:size_of_upper].set_color(RED)
        base10_parts_text.set_y(base_10_group.result_tex.get_y())
        base10_parts_text.set_x(base_10_group.result_tex.get_x())
        self.play(
            FadeToColor(bin_group.result_tex[0][1:9], color=RED),
            Transform(base_10_group.result_tex, base10_parts_text),
        )
        self.next_slide()

        self.play(
            bin_group.animate.move_to(np.array([0, 2, 0])),
            base_10_group.animate.fade(1),
        )

        return base_10_group, bin_group

    def scene_2(self, base_2_group, num1, num2):
        num1_latex, num1_parts = number_to_base_2_parts(num1, 4)
        num2_latex, num2_parts = number_to_base_2_parts(num2, 4)

        base_2_split = MultiplicationRepresentation(num1_latex, num2_latex, "")
        print(base_2_split[0])

        base_2_split.set_x(1.75, RIGHT)
        base_2_split.set_y(3, UP)

        self.next_slide()

        self.play(Transform(base_2_group.upper_tex, base_2_split.upper_tex),
                  Transform(base_2_group.lower_tex, base_2_split.lower_tex),
                  Transform(base_2_group.line, base_2_split.line),
                  Transform(base_2_group.multiplication_bin_dot, base_2_split.multiplication_bin_dot),
                  Transform(base_2_group.result_tex, Tex("")))

        print(base_2_split.upper_tex[0])
        print(num1_parts)

        upper_base_2_split_left_num = TexCharAssociation(
            base_2_split.upper_tex[0][0:4], num1_parts[0][0:4]
        )
        upper_base_2_split_left_num_pow = TexCharAssociation(
            base_2_split.upper_tex[0][6], num1_parts[0][-2]
        )
        upper_base_2_split_right_num = TexCharAssociation(
            base_2_split.upper_tex[0][8:12], num1_parts[1][0:4]
        )
        upper_base_2_split_right_num_pow = TexCharAssociation(
            base_2_split.upper_tex[0][14], num1_parts[1][-2]
        )
        lower_base_2_split_left_num = TexCharAssociation(
            base_2_split.lower_tex[0][0:4], num2_parts[0][0:4]
        )
        lower_base_2_split_left_num_pow = TexCharAssociation(
            base_2_split.lower_tex[0][6], num2_parts[0][-2]
        )
        lower_base_2_split_right_num = TexCharAssociation(
            base_2_split.lower_tex[0][8:12], num2_parts[1][0:4]
        )
        lower_base_2_split_right_num_pow = TexCharAssociation(
            base_2_split.lower_tex[0][14], num2_parts[1][-2]
        )
        self.play(
            FadeToColor(upper_base_2_split_left_num.latex_char, color=BLUE),
            FadeToColor(upper_base_2_split_left_num_pow.latex_char, color=BLUE),
            FadeToColor(upper_base_2_split_right_num.latex_char, color=YELLOW),
            FadeToColor(upper_base_2_split_right_num_pow.latex_char, color=YELLOW),
            FadeToColor(lower_base_2_split_left_num.latex_char, color=GREEN),
            FadeToColor(lower_base_2_split_left_num_pow.latex_char, color=GREEN),
            FadeToColor(lower_base_2_split_right_num.latex_char, color=RED),
            FadeToColor(lower_base_2_split_right_num_pow.latex_char, color=RED),
        )
        self.next_slide()

        # Multiplying out
        top_split_nums = [upper_base_2_split_left_num, upper_base_2_split_right_num]
        top_split_pows = [
            upper_base_2_split_left_num_pow,
            upper_base_2_split_right_num_pow,
        ]
        lower_split_nums = [lower_base_2_split_left_num, lower_base_2_split_right_num]
        lower_split_pows = [
            lower_base_2_split_left_num_pow,
            lower_base_2_split_right_num_pow,
        ]
        multiplication_split_number: list[
            (TexCharAssociation, TexCharAssociation)
        ] = list(itertools.product(top_split_nums, lower_split_nums))
        multiplication_split_pows: list[
            (TexCharAssociation, TexCharAssociation)
        ] = list(itertools.product(top_split_pows, lower_split_pows))
        base_2_split.get_y()
        result_rows, result_with_plus = self.multiply_by_parts(
            multiplication_split_number, multiplication_split_pows, base_2_split
        )
        # base_2_exponent_representations = self.evaluate_base_2_result(result_rows)
        # self.next_slide()
        # self.write_out_exponent_results(base_2_exponent_representations)

    def multiply_by_parts(
            self, multiplication_split_number, multiplication_split_pows, top_element
    ):
        result_rows: list[Tex] = []
        result_with_plus: list[VGroup] = []
        current_top = top_element
        for index, (
                (number_left, number_right),
                (exponent_left, exponent_right),
        ) in enumerate(
            zip(
                multiplication_split_number,
                multiplication_split_pows,
            )
        ):
            number_left: TexCharAssociation
            number_right: TexCharAssociation
            exponent_left: TexCharAssociation
            exponent_right: TexCharAssociation

            text = rf"${number_left.char} \cdot {number_right.char} (\verb|<<|{exponent_left.char} + {exponent_right.char})$"
            print(text)
            base_result = Tex(text)

            number_left_res = base_result[0][0:4].set_color(
                number_left.latex_char[0].get_color()
            )
            number_right_res = base_result[0][5:9].set_color(
                number_right.latex_char[0].get_color()
            )
            exponent_left_res = base_result[0][12].set_color(
                exponent_left.latex_char[0].get_color()
            )
            exponent_right_res = base_result[0][14].set_color(
                exponent_right.latex_char[0].get_color()
            )

            plus_sign = Tex("+")
            if len(result_rows) == 0:
                plus_sign = Tex("")

            base_result.next_to(current_top, DOWN)

            if len(result_rows) != 0:
                base_result.next_to(result_rows[-1], DOWN)
                plus_sign.next_to(result_rows[-1], np.array([-1, -1.35, 0]))

            result_rows.append(base_result)
            result_with_plus.append(VGroup(base_result, plus_sign))

            current_top = base_result

            self.play(
                Wiggle(number_left.latex_char),
                Wiggle(number_right.latex_char),
                Wiggle(exponent_left.latex_char),
                Wiggle(exponent_right.latex_char),
            )
            self.next_slide()

            self.play(
                TransformFromCopy(number_left.latex_char, number_left_res),
                TransformFromCopy(number_right.latex_char, number_right_res),
                TransformFromCopy(exponent_left.latex_char, exponent_left_res),
                TransformFromCopy(exponent_right.latex_char, exponent_right_res),
                Create(base_result[0][4]),  # Multiplication
                Create(base_result[0][9:12]),  # Shifts
                Create(base_result[0][13]),  # plus exponent
                Create(base_result[0][15]),  # # rest of the bracket
                Create(plus_sign),
            )

            self.next_slide()

        return result_rows, result_with_plus

    def evaluate_base_10_result(
            self, result_rows: list[Tex]
    ) -> list[NumberExponentTex]:
        new_results: list[NumberExponentTex] = []
        for result in result_rows:
            result_tex = result.tex_string
            left_number = int(result_tex[1])
            right_number = int(result_tex[9])
            left_number_exp = int(result_tex[21])
            right_number_exp = int(result_tex[25])

            base_result = left_number * right_number
            exponent_result = left_number_exp + right_number_exp
            new_result = Tex(rf"${base_result} \cdot 10^{{{exponent_result}}}$")

            new_result.set_x(result.get_x())
            new_result.set_y(result.get_y())

            self.play(
                Transform(result, new_result),
            )
            new_results.append(NumberExponentTex(base_result, exponent_result, result))

        return new_results

    def write_out_exponent_results(
            self, exponenet_represenataions: list[NumberExponentTex]
    ):
        for exponenet_repr in exponenet_represenataions:
            print(exponenet_repr)
            base_10_value = Tex(
                f"{exponenet_repr.number * (10 ** exponenet_repr.exponent)}"
            )
            base_10_value.set_x(exponenet_repr.latex_component.get_x())
            base_10_value.set_y(exponenet_repr.latex_component.get_y())

            self.play(Transform(exponenet_repr.latex_component, base_10_value))

            exponenet_repr.latex_component = base_10_value


if __name__ == "__main__":
    scene = CreateCircle()
    scene.construct()
