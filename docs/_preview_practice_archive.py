#!/usr/bin/env python3
"""Preview platform folders and build an index from source header tags."""

from __future__ import annotations

import argparse
from collections import Counter, defaultdict
from dataclasses import asdict, dataclass
import hashlib
import json
import os
from pathlib import Path, PurePosixPath
import re
from urllib.parse import quote

from _build_algorithm_practice_list import ARCHIVE, CODE_EXTS, parse_problem_url, problem_sort_key


URL = re.compile(r'https?://[^\s<>"、，。；）】]+')
TAG = re.compile(r"^算法标签\s*[:：]\s*(.+)$")
LUOGU = re.compile(r"([PBUT])(\d+)")
CURRENT_PROBLEM = re.compile(r"^(?:实际对应|原题现址)\s*[:：]")
PLATFORMS = {
    "CF": "Codeforces",
    "CFGYM": "Codeforces",
    "AT_": "AtCoder",
    "HDU": "HDU",
    "LC_": "LeetCode",
    "LOJ": "LibreOJ",
    "UOJ": "UOJ",
    "QOJ": "QOJ",
    "SP": "SPOJ",
    "SPOJ_": "SPOJ",
    "UVA": "UVa",
    "POJ": "POJ",
    "NC_": "牛客",
    "LQ": "蓝桥杯",
    "BZOJ": "DarkBZOJ",
    "LIGHTOJ": "LightOJ",
}


@dataclass
class Entry:
    source: str
    sha256: str
    destination: str | None = None
    platform: str | None = None
    problem: str | None = None
    link: str | None = None
    tags: tuple[str, ...] = ()
    review: str | None = None


def header_lines(data: bytes, is_python: bool) -> list[str]:
    try:
        text = data.decode("utf-8-sig")
    except UnicodeDecodeError:
        text = data.decode("gb18030", errors="replace")

    lines = []
    in_block = False
    for line in text.splitlines():
        line = line.lstrip()
        if is_python and line.startswith("#"):
            lines.append(line[1:].strip())
        elif not is_python and (in_block or line.startswith("/*")):
            comment = line if in_block else line[2:]
            comment, closer, tail = comment.partition("*/")
            lines.append(comment.strip().lstrip("*").strip())
            in_block = not closer
            if tail.strip() and not tail.lstrip().startswith("//"):
                break
        elif not is_python and line.startswith("//"):
            lines.append(line[2:].strip())
        elif line:
            break
    return lines


def header_problem(lines: list[str]) -> tuple[str | None, str | None, str | None]:
    found: dict[str, tuple[int, str]] = {}
    explicit = set()
    all_links = False
    for line in lines:
        for link in URL.findall(line):
            link = link.rstrip(".,;:)]")
            all_links = True
            result = parse_problem_url(link)
            if not result:
                continue
            problem, link, priority = result
            if problem not in found or priority < found[problem][0]:
                found[problem] = (priority, link)
            if CURRENT_PROBLEM.match(line):
                explicit.add(problem)

    candidates = explicit or set(found)
    if candidates == {"SP8791", "SPOJ_DYNALCA"}:
        candidates = {"SPOJ_DYNALCA"}
    if candidates == {"P3513", "LOJ2155"}:
        candidates = {"P3513"}
    if len(candidates) == 1:
        problem = next(iter(candidates))
        return problem, found[problem][1], None
    if candidates:
        return None, None, "有多个题号：" + "、".join(sorted(candidates))
    return None, None, "题目链接需复核" if all_links else "未找到题目链接"


def destination(problem: str, name: str) -> tuple[str, str]:
    match = LUOGU.fullmatch(problem)
    if match:
        prefix, number = match.groups()
        first = int(number) // 500 * 500
        bucket = f"{prefix}{first:04d}-{prefix}{first + 499:04d}"
        return "洛谷", f"洛谷/{bucket}/{name}"

    prefix = re.match(r"^[A-Z]+_?", problem)[0]
    platform = PLATFORMS[prefix]
    return platform, f"{platform}/{name}"


def scan_archive(archive: Path) -> list[Entry]:
    plan = []
    by_destination = defaultdict(list)
    for path in sorted(archive.rglob("*")):
        if not path.is_file() or path.is_symlink() or path.suffix.lower() not in CODE_EXTS:
            continue
        data = path.read_bytes()
        lines = header_lines(data, path.suffix.lower() == ".py")
        tags = [match[1] for line in lines if (match := TAG.fullmatch(line))]
        problem, link, review = header_problem(lines)
        entry = Entry(
            source=path.relative_to(archive).as_posix(),
            sha256=hashlib.sha256(data).hexdigest(),
            problem=problem,
            link=link,
            tags=tuple(dict.fromkeys(tag.strip() for tag in tags[0].split("、") if tag.strip())) if len(tags) == 1 else (),
            review=review,
        )
        if problem:
            entry.platform, entry.destination = destination(problem, path.name)
            by_destination[entry.destination.casefold()].append(entry)
        plan.append(entry)

    for entries in by_destination.values():
        if len(entries) > 1:
            for entry in entries:
                entry.review = "归档路径与其他源码重名"
                entry.destination = None
    return plan


def write_index(
    path: Path, archive: Path, plan: list[Entry], *, archived_only: bool = False
) -> tuple[int, int]:
    by_tag = defaultdict(lambda: defaultdict(list))
    problems = set()
    for entry in plan:
        if entry.review or (archived_only and entry.source != entry.destination):
            continue
        for tag in entry.tags:
            key = (entry.platform, entry.problem)
            by_tag[tag][key].append(entry)
            problems.add(key)

    lines = [
        "# 按算法标签练习",
        "",
        f"共 {len(by_tag)} 个标签，覆盖 {len(problems)} 道题。",
        "同题的多份实现合并展示。每个标签下仅列出使用该算法的版本。",
        "本页收录已归档、且有文件头算法标签的实现。" if archived_only else
        "此预览的源码链接指向文件当前所在的位置。",
        "",
    ]
    for tag, entries in sorted(by_tag.items(), key=lambda item: (-len(item[1]), item[0])):
        lines.extend((f"## {tag}（{len(entries)} 题）", ""))
        for (platform, problem), versions in sorted(
            entries.items(), key=lambda item: (item[0][0], problem_sort_key(item[0][1]))
        ):
            sources = []
            for entry in versions:
                local = Path(os.path.relpath(archive / entry.source, path.parent)).as_posix()
                name = PurePosixPath(entry.source).name.replace("[", "\\[").replace("]", "\\]")
                sources.append(f"[{name}]({quote(local, safe='/')})")
            lines.append(f"- {platform} [{problem}](<{versions[0].link}>) · " + "、".join(sources))
        lines.append("")
    path.write_text("\n".join(lines), encoding="utf-8")
    return len(by_tag), len(problems)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--archive", type=Path, default=ARCHIVE)
    output_type = parser.add_mutually_exclusive_group(required=True)
    output_type.add_argument("--output", type=Path, help="保存归档预演及题单的目录")
    output_type.add_argument("--index", type=Path, help="生成已归档题目的 Markdown 题单")
    args = parser.parse_args()
    archive = args.archive.resolve()
    output = (args.index or args.output).resolve()
    if not archive.is_dir():
        parser.error(f"找不到源码目录：{archive}")
    if output.is_relative_to(archive):
        parser.error("输出必须在源码目录外。")

    plan = scan_archive(archive)
    if args.index:
        if output.suffix.lower() != ".md":
            parser.error("题单的扩展名必须为 .md。")
        output.parent.mkdir(parents=True, exist_ok=True)
        labels, problems = write_index(output, archive, plan, archived_only=True)
        print(f"练习题单：{labels} 个算法标签，{problems} 道不同题目。")
        return

    output.mkdir(parents=True, exist_ok=True)
    (output / "归档预演.json").write_text(
        json.dumps([asdict(entry) for entry in plan], ensure_ascii=False, indent=2) + "\n",
        encoding="utf-8",
    )
    labels, problems = write_index(output / "按算法标签练习（预览）.md", archive, plan)
    platforms = Counter(entry.platform for entry in plan if entry.destination)
    print(f"源码 {len(plan)} 份，可归档 {sum(platforms.values())} 份，待复核 {sum(bool(entry.review) for entry in plan)} 份。")
    print("平台统计：" + "、".join(f"{name} {count}" for name, count in platforms.most_common()))
    print(f"练习题单：{labels} 个算法标签，{problems} 道不同题目。")


if __name__ == "__main__":
    main()
