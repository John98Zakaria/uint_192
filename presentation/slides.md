---
highlighter: shikiji
addons:
  - slidev-addon-animattr
title: Unsigned Bigints
transition: slide-left
---

# Unsigned Bigints

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
layout: center
---
# Goals

* Implement the basic math operations + - * $\div$

* Implement some bitwise operations >>

* Logical operators = < >

* Learn some C++ quirks

---
transition: slide-up
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
src: ./slides/carry-proof.md
---

---
layout: default
transition: slide-up
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
src: ./slides/base-10-inspiration.md
---


---
src: ./slides/base-2-code.md
---

---
    
# Summary
What did we learn so far?

<v-click>

* Addition

</v-click>

<v-click>

* Multiplication

</v-click>

<v-click>

## What is left to explore ?

</v-click>

<v-click>

* Shifting

</v-click>

<v-click>

* Division

</v-click>

<v-click>

* BigInt to string

</v-click>

---
layout: end
---
