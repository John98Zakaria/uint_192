<script setup lang="ts">
import {Ref, ref} from 'vue'
import {vElementVisibility} from '@vueuse/components'

const props = defineProps({
  src: {
    type: String,
    required: true
  }
})

const video_ref: Ref<HTMLVideoElement> = ref();

const clicks = $clicks;

function onElementVisibility(visible: boolean) {
  if (visible) {
    video_ref.value.play()
  } else {
    video_ref.value.pause()
    video_ref.value.currentTime = 0
  }
}

</script>

<template>
  <video muted v-element-visibility="onElementVisibility" ref="video_ref" :key="src" autoplay :src="src"
         type="video/webm" width="80%"/>
</template>
