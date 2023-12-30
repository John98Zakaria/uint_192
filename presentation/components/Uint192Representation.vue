<script setup lang="ts">
import {ref} from 'vue'
import config from "/@slidev/configs"
import {getHighlighter} from 'shikiji'
import katex from 'katex';

const highlighter = await getHighlighter({langs: ["cpp",], themes: ['vitesse-dark']})
const html = ref(highlighter.codeToHtml("uint_192 ones{1,1,1};", {theme: "vitesse-dark", lang: 'cpp'})
    .replace('<pre class="shiki', '<pre class="slidev-code shiki shiki-dark'))


const latex_sum = ref(katex.renderToString("2^{128}+2^{64}+2^{0}"))
console.log(html)
</script>

<template>
  <div v-click class="flex flex-justify-center flex-col flex-content-center flex-items-center">
    <pre class="shikiji" v-html="html"/>
    <div class="grid grid-cols-4 grid-rows-4 gap-x-9xl pa-2">
      <div class="flex flex-justify-center">
        Binary
      </div>
      <div class="flex flex-justify-center">
        00001
      </div>
      <div class="flex flex-justify-center">
        00001
      </div>
      <div class="flex flex-justify-center">
        00001
      </div>
      <div class="flex flex-justify-center">
        Base10
      </div>
      <div class="flex flex-justify-center">
        1
      </div>
      <div class="flex flex-justify-center">
        1
      </div>
      <div class="flex flex-justify-center">
        1
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

        <div v-html="latex_sum"/>


      </div>
    </div>
  </div>
</template>
