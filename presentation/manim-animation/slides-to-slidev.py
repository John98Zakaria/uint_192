import json
import subprocess
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
import shutil


PROJECT_NAME = "BASE_10_INSPIRATION"

OUTPUT_PATH = f"/home/jn98zk/CLionProjects/uint_192/presentation/public/{PROJECT_NAME}"
INPUT_JSON = "/home/jn98zk/CLionProjects/uint_192/presentation/manim-animation/slides/CreateCircle.json"
input_json_path = Path(INPUT_JSON)
output_path = Path(OUTPUT_PATH)
output_path.mkdir(exist_ok=True)
shutil.rmtree(output_path)
output_path.mkdir(exist_ok=True)


def convert_video_to_webm(video_path: Path):
    video_output_path = output_path / f"{video_path.stem}.webm"
    absolute_ = [
        "/usr/bin/ffmpeg",
        "-i",
        str(video_path.absolute()),
        str(video_output_path.absolute()),
    ]
    print(" ".join(absolute_))
    subprocess.run(
        absolute_,
    )
    return video_output_path


def convert_videos_to_webm(videos_path: list[Path]):
    with ThreadPoolExecutor(max_workers=4) as pool:
        return pool.map(convert_video_to_webm, videos_path)


with open(
    input_json_path,
    "r",
) as f:
    slides_json = json.load(f)

files_paths = [Path(slide["file"]) for slide in slides_json["slides"]]

output_paths = convert_videos_to_webm(files_paths)


def slidev_slide(file_path: Path):
    return f"""---
layout: default
---
# Data

<div class="grid place-items-center">

<VideoComponent  src="{file_path.relative_to(output_path.parent).name}"/>

</div>
"""


out = ""

for file in output_paths:
    out += slidev_slide(file)

with open("/home/jn98zk/CLionProjects/uint_192/presentation/slides/manim.md", "w") as f:
    f.write(out)
