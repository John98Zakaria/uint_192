# Addition

The Problem


<div class="grid grid-cols-5">

<div class="col-span-3">

Assume we have 8 bits unsigned numbers (range 0-255)


<div class="flex gap-x-12 h-60px">

$a=230$

$b=180$

</div>

<div v-click class="h-60px">

$a+b=\textcolor{orange}{154}\enspace?!$

<div v-if="$clicks<3" :class="relativeBinary">

$\textcolor{orange}{(010011010)_{2}}$

</div>

<div v-show="$clicks>=3" :class="relativeBinary">

$(0\textcolor{orange}{10011010})_{2}$

</div>


</div>

<div v-click class="h-60px">

$a+b\neq410$

<div v-if="$clicks<4" :class="relativeBinary">

$(110011010)_{2}$

</div>

<div v-show="$clicks>=4"   :class="relativeBinary">

$(\textcolor{green}{1}\textcolor{orange}{10011010})_{2}$

</div>


</div>

<div v-click="5" class="h-60px">

$a+b\neq\textcolor{green}{256} + \textcolor{orange}{154}$

<div :class="relativeBinary">

$(\textcolor{green}{1}\textcolor{orange}{10011010})_{2}$

</div>


</div>

<div v-click="6" class="h-60px">

$a+b\neq\textcolor{green}{2^8} + \textcolor{orange}{154}$

<div :class="relativeBinary">

$(\textcolor{green}{1}\textcolor{orange}{10011010})_{2}$

</div>

</div>

</div>

<div class="col-span-2 h-full">


<v-clicks at="7">

1. Addition with overflow breaks an arithmatic rule:


<div class="flex gap-4">

<div class="relative left-5">

* if $a,b \in \mathbb N_{0}$


* $c=a+b$
* $c \geq a$
  ,
  $c \geq b$


</div>

</div>



2. Could the carry be just one bit ?


</v-clicks>

</div>

</div>




<script setup lang="ts">
const relativeBinary = "relative left-60 bottom-10.8";
</script>
