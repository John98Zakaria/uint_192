---
transition: slide-up
---
# Why use integers as basis for big integers?

<div class="grid grid-cols-3 pb">
<div>

- A byte for each bit

```cpp
struct uint192{
char data[192];
};
```

- Each bit is easy accessible

<div class="text-red">

* Wasteful memory usage

</div>

</div>

<div>

* Exact size in raw bytes

```cpp
struct uint192{
char data[24];
};
```

- Compactness

<div class="text-red">

* Inefficient bit access

</div>


</div>


<div>

- C++ Bitsets

```cpp
struct uint192{
std::bitset<192> data;
};
```

* Built-in shift and bit access

<div class="text-red">

* Wasteful memory usage

</div>


</div>

</div>

<br>

<div class="grid place-self-center place-items-center relative">

<div>


<div class="flex flex-col flex-items-center flex-justify-center flex-content-center">

## General Disadvantages

<br>

\- Need to simulate hardware operations in software.

\- Doesn't utilize the CPU architecture.


</div>

</div>
</div>


---
clicks: 1
---
# Why use integers as basis for big integers? 

<div ref="fullAdderGrid" class="grid grid-cols-2">

<div>
Full Adder Network

```cpp
std::bitset<192> operator+(
        const std::bitset<192> &a,
        const std::bitset<192> &b) 
{
    std::size_t carry = false;
    std::bitset<192> sum;
    for (std::size_t i = 0; i < 192; ++i) {
        sum[i] = a[i] ^ b[i] ^ carry;
        carry = (a[i] & b[i]) 
                | (a[i] & carry) 
                | (b[i] & carry);
    }
    return sum;
}

```

</div>

![full-adder.svg](full-adder.svg)

</div>

<div ref="benchmarks" class="absolute top-50 left-65 opacity-0">

```
--------------------------------------------------------------
Benchmark                    Time             CPU   Iterations
--------------------------------------------------------------
BM_FullAdderCircuit    6593437 ns      6592864 ns          110
BM_Number_Basis           6990 ns         6990 ns       100156
```

</div>

<script setup lang="ts">

import {watch,ref,Ref} from 'vue';

const clicks = $clicks;

const fullAdderGrid: Ref<HTMLElement> = ref<HTMLElement>(null);
const benchmarks: Ref<HTMLElement> = ref<HTMLElement>(null);


watch(clicks, (new_value,_) => {
    if (new_value === 1){
        fullAdderGrid.value.classList.toggle("blur-2xl",true);
        benchmarks.value.classList.replace("opacity-0","opacity-100");
    } else {
        fullAdderGrid.value.classList.remove("blur-2xl");
        benchmarks.value.classList.replace("opacity-100","opacity-0");
    }
})

</script>