"""逐份检查原模板源文件的 C++17 语法，并记录来源线索。"""

from concurrent.futures import ThreadPoolExecutor, as_completed
from hashlib import sha256
from pathlib import Path
import json
import re
import subprocess

REPO = Path(r"D:\algorithm\templates")
PRINT = Path(r"C:\Users\wyh15\Documents\code\C++\打印的模板")
OUTPUT = Path(r"D:\algorithm\docs\模板源文件审计.json")


def inspect(path: Path) -> dict:
    data = path.read_bytes()
    source = data.decode("utf-8", errors="replace")
    first = "\n".join(source.splitlines()[:45])
    links = re.findall(r"https?://[^\s\*]+", first)
    try:
        result = subprocess.run(
            ["g++", "-std=gnu++17", "-fsyntax-only", "-w", str(path)],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            encoding="utf-8",
            errors="replace",
            timeout=30,
        )
        error = "" if result.returncode == 0 else result.stderr[:1600]
        valid = result.returncode == 0
    except subprocess.TimeoutExpired:
        valid, error = False, "编译超时（30 秒）"
    return {
        "path": str(path),
        "source": "templates" if REPO in path.parents else "旧打印",
        "sha256": sha256(data).hexdigest(),
        "lines": source.count("\n") + 1,
        "has_main": bool(re.search(r"\bmain\s*\(", source)),
        "links": links,
        "has_time_comment": bool(re.search(r"时间复杂度|//\s*时间[：:]", first)),
        "has_space_comment": bool(re.search(r"空间复杂度|//\s*空间[：:]", first)),
        "syntax_ok": valid,
        "error": error,
    }


def main() -> None:
    paths = sorted((*REPO.rglob("*.cpp"), *PRINT.rglob("*.cpp")))
    records = []
    with ThreadPoolExecutor(max_workers=6) as pool:
        for future in as_completed(pool.submit(inspect, path) for path in paths):
            records.append(future.result())
    records.sort(key=lambda item: item["path"])
    OUTPUT.write_text(json.dumps(records, ensure_ascii=False, indent=2), encoding="utf-8")
    failures = [item for item in records if not item["syntax_ok"]]
    print(f"sources={len(records)} syntax_ok={len(records)-len(failures)} failed={len(failures)}")
    for item in failures:
        print(item["path"])
        print(item["error"].splitlines()[:3])


if __name__ == "__main__":
    main()
