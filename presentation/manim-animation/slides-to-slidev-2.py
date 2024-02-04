import json
import shutil
from pathlib import Path

PROJECT_NAME = "BASE_2_IMPLEMENTATION"

OUTPUT_PATH = f"/home/jn98zk/CLionProjects/uint_192/presentation/public/{PROJECT_NAME}"
INPUT_JSON = "/home/jn98zk/CLionProjects/uint_192/presentation/manim-animation/slides/CreateCircle.json"
input_json_path = Path(INPUT_JSON)
output_path = Path(OUTPUT_PATH)

with open(
        input_json_path,
        "r",
) as f:
    slides_json = json.load(f)

files_paths = [Path(slide["file"]) for slide in slides_json["slides"]]

output_paths = [output_path / f"{video_path.stem}.webm" for video_path in files_paths]


def slidev_slide(file_paths: list[Path]):

    video_componenets = []
    for index,file in enumerate(file_paths):
        comp = f'<VideoComponent v-show="$clicks=={index}" src="{PROJECT_NAME}/{file.stem}.webm"/>'
        video_componenets.append(comp)

    comp_str = "\n".join(video_componenets)
    return f"""---
layout: default
---
# Data

<div class="absolute left-500px w-70%">

<br>
<br>
<br>

{comp_str}

</div>
"""


out = slidev_slide(files_paths)

with open("/home/jn98zk/CLionProjects/uint_192/presentation/slides/base_2_repr-2.md", "w") as f:
    f.write(out)
