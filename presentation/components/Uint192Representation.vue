<script setup lang="ts">
import {ref} from 'vue'
import {getHighlighter} from 'shikiji'
import katex from 'katex';

const props = defineProps<{ low: number; med: number; high: number }>();


const highlighter = await getHighlighter({langs: ["cpp",], themes: ['vitesse-dark']})
const html = ref(highlighter.codeToHtml(`uint_192 ones{${props.low},${props.med},${props.high}};`, {
      theme: "vitesse-dark",
      lang: 'cpp'
    }).replace('<pre class="shiki', '<pre class="slidev-code shikiji-dark')
        .replace("style", "")
)

const binRepresentation = props.high.toString(2).padStart(64, "0")
    + props.med.toString(2).padStart(64, "0")
    + props.low.toString(2).padStart(64, "0")

const reversedRepresentation = binRepresentation.split("").reverse().join("");

const indexOfOnes = [...reversedRepresentation.matchAll(new RegExp("1", 'gi'))].map(a => a.index).reverse()
const powerOfTwos = indexOfOnes.map(power => `2^{${power}}`)
let latex_string = powerOfTwos.join("+");
if (latex_string == "") {
  latex_string = "0";
}
const latex_html = ref(katex.renderToString(latex_string))

</script>

<template>
  <div v-click class="flex flex-justify-center flex-col flex-content-center flex-items-center">
    <pre class="shikiji" v-html="html"/>
    <div class="grid grid-cols-4 grid-rows-4 gap-x-9xl gap-y-2  pa-2">
      <div class="flex flex-justify-center">
        Binary
      </div>
      <div class="flex flex-justify-center">
        {{ props.high.toString(2).padStart(5, "0") }}
      </div>
      <div class="flex flex-justify-center">
        {{ props.med.toString(2).padStart(5, "0") }}
      </div>
      <div class="flex flex-justify-center">
        {{ props.low.toString(2).padStart(5, "0") }}

      </div>

      <div class="flex flex-justify-center">
        Base10
      </div>
      <div class="flex flex-justify-center">
        {{ props.high.toString(10) }}
      </div>
      <div class="flex flex-justify-center">
        {{ props.med.toString(10) }}
      </div>
      <div class="flex flex-justify-center">
        {{ props.low.toString(10) }}
      </div>
      <div class="flex flex-justify-center">
        Index
      </div>
      <div class="flex flex-justify-center">
        2
      </div>
      <div class="flex flex-justify-center">
        1
      </div>
      <div class="flex flex-justify-center">
        0
      </div>
      <div class="flex flex-justify-center">
        Value
      </div>
      <div class="flex flex-justify-center max-h-2em col-span-3">
        <div v-html="latex_html"/>
      </div>
    </div>
  </div>
</template>
