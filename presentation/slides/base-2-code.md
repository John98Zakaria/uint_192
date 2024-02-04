---
clicks: 4
transition: view-transition
---

<VideoComponent class="absolute" v-show="$clicks==0" src="BASE_2_IMPLEMENTATION/5ec02e3688849a1cc0c7ec4f95d5bbc6facabeaf49a7ed6e44a85482528b9d3d.webm"/>
<VideoComponent class="absolute" v-show="$clicks==1" src="BASE_2_IMPLEMENTATION/d51adbb147ae7e48ba3369f61d9aadc611df3c9bbc36633c76538b183fe9fe45.webm"/>
<VideoComponent class="absolute" v-show="$clicks==2" src="BASE_2_IMPLEMENTATION/abe52801ba72d6c7a18800a16aba9a77eb2befd7cece79755ce6f1baba74ded2.webm"/>
<VideoComponent class="absolute" v-show="$clicks==3"  src="BASE_2_IMPLEMENTATION/7d432089dbd3eb0aaa6dd25d474c6e3a04105fe83de7da03b360d80362b068b3.webm"/>
<img v-show="$clicks==4" class="absolute w-80%"  style="view-transition-name: video; display: inline-block;" src="/BASE_2_IMPLEMENTATION/videoframe_1000.png"/>


---
layout: default
clicks: 9
transition: view-transition
---
# Base-2 multiplication


<div class="absolute left-1">

```cpp {0|5-10|6,9|5-6,8-9,12,19,21|6,10|5,8,6,10,13,17-18,22|7,9|7-9,14,17-18,23|7,10|7-8,10,15,17,24|all}{lines:true,maxHeight:'400px'}
uint_192 operator*(const uint_192 &lhs, const uint_192 &rhs) {

uint_192 result{};

for (uint64_t lhs_iterator = 0; lhs_iterator < lhs.parts.size(); ++lhs_iterator) {
    const uint64_t lhs_upper_bits = lhs.parts[lhs_iterator] >> UINT32_WIDTH;
    const uint64_t lhs_lower_bits = lhs.parts[lhs_iterator] & LOWER_BITMASK;
    for (uint64_t rhs_iterator = 0; rhs_iterator < rhs.parts.size(); ++rhs_iterator) {
        const uint64_t rhs_upper_bits = rhs.parts[rhs_iterator] >> UINT32_WIDTH;
        const uint64_t rhs_lower_bits = rhs.parts[rhs_iterator] & LOWER_BITMASK;
        
        const uint_192 upper_upper = uint_192{lhs_upper_bits * rhs_upper_bits};
        const uint_192 upper_lower = uint_192{lhs_upper_bits * rhs_lower_bits};
        const uint_192 lower_upper = uint_192{lhs_lower_bits * rhs_upper_bits};
        const uint_192 lower_lower = uint_192{lhs_lower_bits * rhs_lower_bits};
        
        uint64_t iteration_shift = (lhs_iterator + rhs_iterator) * UINT64_WIDTH;
        uint64_t lower_upper_shift = iteration_shift + UINT32_WIDTH;
        uint64_t upper_upper_shift = iteration_shift + UINT64_WIDTH;
        
        result += (upper_upper << upper_upper_shift);
        result += (upper_lower << lower_upper_shift);
        result += (lower_upper << lower_upper_shift);
        result += (lower_lower << iteration_shift);
    }
}

    return result;
}
```
</div>

<div class="absolute left-530px w-80%">

<br>
<br>
<br>

<img class="w-80%" style="view-transition-name: video; display: inline-block;" v-show="$clicks==0" src="/BASE_2_IMPLEMENTATION/videoframe_1000.png"/>

<VideoComponent v-show="$clicks==1" src="BASE_2_IMPLEMENTATION/98e31740181c2ea41f6e57a53dc6d30fafb4bf35435ebf9eaad147e117a2ffd5.webm"/>
<VideoComponent v-show="$clicks==2" src="BASE_2_IMPLEMENTATION/f1f880d5e44e3adfdc450e3f57c845596f2bfbaac5430d21cf3ac04b4c45058b.webm"/>
<VideoComponent v-show="$clicks==3" src="BASE_2_IMPLEMENTATION/350500c5c3cc7dbc7abd5056e01e4fc5c475a60ea0f8bea42ff9a66c3c806198.webm"/>
<VideoComponent v-show="$clicks==4" src="BASE_2_IMPLEMENTATION/9ecd8ef6f1ed69c5b42b6ea11ae9165729e2845bd48a1e09b25073ae1c5eee7e.webm"/>
<VideoComponent v-show="$clicks==5" src="BASE_2_IMPLEMENTATION/9c7dff55c2bb0d33e4ff204b1e51e5e5ae497f57576e648a0edbf52fbf6f6dec.webm"/>
<VideoComponent v-show="$clicks==6" src="BASE_2_IMPLEMENTATION/dd9851acdb37083393d16a52780b9f2ff098253a5bd849e5cf947c25da0559fd.webm"/>
<VideoComponent v-show="$clicks==7" src="BASE_2_IMPLEMENTATION/fc1344e3a41378b23ab5703508507eb9ff8c83b8684e478812e936a8d1fb84d5.webm"/>
<VideoComponent v-show="$clicks==8" src="BASE_2_IMPLEMENTATION/84a02fa20c8d30bac9fb249f55b50f7288125e538a6bbc6aedc2dbe64ed8d4f4.webm"/>
<VideoComponent v-show="$clicks==9" src="BASE_2_IMPLEMENTATION/33b49e62dcdf641da3799480e4e1bfaf9e2421ba2c2026ce6114d6fa8c8df302.webm"/>

</div>


