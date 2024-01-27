---
layout: default
---

# Addition

The naive version

<div class="relative grid grid-cols-5 content-start place-items-stretch right-3">


<div class="col-span-3 h-40vh flex flex-content-center flex-items-center">

```cpp {all|2|4-6|8|all}{lines:true}
uint_192 operator+(const uint_192 &lhs, const uint_192 &rhs) {
    uint_192 result{};
    
    for (uint64_t i = 0; i < lhs.parts.size(); ++i) {
        result.parts[i] += lhs.parts[i] + rhs.parts[i];
    }
    
    return result;
}
```

</div>

<div class="grid grid-rows-3">

<div>

<v-clicks >

```cpp {1|1-2|all} 
uint_192 a{0,0,0} // 0;
uint_192 b{0,0,0}; // 0;
auto c = a + b; 
// {0,0,0}
// 0
```

```cpp {1|1-2|all} 
uint_192 a{1,2,0} // 55340232221128654848;
uint_192 b{1,0,0}; // 1
auto c = a + b; 
// {2,2,0}
// 55340232221128654849
```

</v-clicks>


<v-click>

```cpp {1|1-2|all|all}
uint_192 a{UINT64_MAX,0,0} // 18446744073709551615;
uint_192 b{1,0,0}; // 1
auto c = a + b; 
// {0,0,0}
// 0
```

<div v-if="$clicks>=14" v-motion-roll-bottom>
<mdi-lightning-bolt color="red" class="text-4xl relative left-30 bottom-15 rotate-15"/>
</div>


</v-click>

</div>


</div>

</div>


