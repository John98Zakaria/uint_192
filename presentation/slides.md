---
highlighter: shikiji
addons:
  - slidev-addon-animattr
title: Arbitrary-sized unsigned integers
---

# Arbitrary-sized unsigned integers

By John Sorial


---
layout: default
---

# Motivation

<div class="grid grid-cols-2 gap-5">
<div class="flex flex-justify-center flex-col flex-items-center flex-content-center h-100">


<img src="/img.png">
</div>
<div>

<div class="flex flex-justify-center flex-col flex-content-center h-100">
<div class="-translate-y-10">
Implementieren Sie nun folgende Funktionen:
</div>

1. `printBigUInt()`: gibt die ganze Zahl zur Basis 10 auf der Kommandozeile aus.
2. `addBigUInt()`: summiert zwei BigUInts
3. `multiplyBigUInt()`: Multipliziert zwei BigUInts

</div>
</div>

</div>


---

# Goals

* Implement the basic math operations + - * $\div$

* Implement some bitwise operations >>

* Logical operators = < >

* Learn some C++ quirks


---

<div style="display: flex; align-items: center; justify-content: center;flex-direction: column">
    <h1>The holy rule</h1>
    <h4>The operations of the base type must be used</h4>
</div>

## Forbidden

1. Multiplication is repeated addition.
2. Division is repeated subtraction.
3. Manipulate bits one by one.


---
src: ./slides/class-structure.md
---

---
layout: section
---

# Addition

---
src: ./slides/naiive-addition.md
---

---
src: ./slides/8-bit-example.md
---

layout: default
---

# Addition

<div class="flex flex-justify-center flex-items-center flex-col flex h-90">

## Is the carry just a bit?

</div>


---
layout: two-cols-header
clicks: 7
---

# Addition: Maximal 1 bit needs to be carried over

<!-- Removes spacing caused by .katex-display -->

<style>
.katex-display{
    display: flex;
    padding-left: 50px;
}
</style>

::left::

$$ {1|1-2|2-3|3-4|4-5|5-6|6-7|7-8}

\begin{align*}

R=& (111....)_2 + (111....)_2 \\
=& \sum_{x=0}^{n-1} 2^x + \sum_{x=0}^{n-1} 2^x \\

=& \: 2*{\sum_{x=0}^{n-1} 2^x} \\

=& \: 2*(2^{n} - 1)\\

=& \: 2^{n+1} - 2 \\

=& \: \sum_{x=0}^{n} 2^x - 1 \\

=& \: \sum_{x=1}^{n} 2^x \\

%<& \: 2^{n+1}

=& \: (11...10)_2

\end{align*}
$$

::right::

$$ {1|1-2|2-3|3-4|4-5|5-6|6-7|7-8}{at:0}
\begin{align*}

R=& (1111)_2 + (1111)_2 \\
=& \sum_{x=0}^{3} 2^x + \sum_{x=0}^{3} 2^x \\

=& \: 2*{\sum_{x=0}^{3} 2^x} \\

=& \: 2*(2^{4} - 1)\\

=& \: 2^{5} - 2 \\

=& \: \sum_{x=0}^{4} 2^x - 1 \\

=& \: \sum_{x=1}^{4} 2^x = 2^{1} + 2^{2} + 2^{3} + 2^{4} \\

=& \: (11110)_2
\end{align*}
$$


---
layout: default
---

# Addition: Final implementation

<div class="relative left-25 top-30">

```cpp {all}{lines:true}
constexpr uint_192 operator+(const uint_192 &lhs, const uint_192 &rhs) noexcept {
    uint_192 result{};
    uint64_t carry_bit{0};

    for (uint64_t i = 0; i < lhs.parts.size(); ++i) {
        result.parts[i] += carry_bit;
        result.parts[i] += lhs.parts[i] + rhs.parts[i];
        carry_bit = result.parts[i] < lhs.parts[i];
    }
    return result;
}
```

</div>


---
layout: section
---

# Multiplication

---
layout: statement
---

## "Multiplication is repeated addition"

Just use a for loop ™


---
layout: default
---

# Multiplication

The problem



<div class="relative bottom-20 grid h-full">

<div class="place-self-center">


<div class="text-left pa-2 text-green">

### Multiplication of two $n$-bit numbers requires a result size of $2n$-bits

</div>

<div class="grid w-full">

<div class="place-self-center">

* $32$-bits $\times$ $32$-bits = $64$ bits
* $64$-bits $\times$ $64$-bits = $128$ bits

</div>
</div>

</div>



</div>

---
src: ./slides/manim.md
---

layout: default
---

# Multiplication

<br>

* Multiplication by 10 in base-10 "just add a zero on the left"

<br>

* The equivalent idea in base-2 is a left shift (<<)

<br>
<br>


<div>

$${1|1-2|1-3|1-4}
\begin{align*}
\textcolor{2e8b57}{1=(00001)_2} &&&&&& \textcolor{60a5fa}{(00001)_2 << 1} &&&&&& \textcolor{cd6090}{1 \times 2 = (
00010)_2} \\
\textcolor{2e8b57}{2=(00010)_2} &&&&&& \textcolor{60a5fa}{(00010)_2 << 1} &&&&&& \textcolor{cd6090}{2 \times 2 = (
00100)_2} \\
\textcolor{2e8b57}{4=(00100)_2} &&&&&& \textcolor{60a5fa}{(00100)_2 << 1} &&&&&& \textcolor{cd6090}{4 \times 2 = (
01000)_2} \\
\textcolor{2e8b57}{8=(01000)_2} &&&&&& \textcolor{60a5fa}{(01000)_2 << 1} &&&&&& \textcolor{cd6090}{8 \times 2 = (
10000)_2} \\
\end{align*}
$$

</div>