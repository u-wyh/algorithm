"""09 文件夹：二维差分和二维前缀和与直接模拟对照。"""

from pathlib import Path
from tempfile import TemporaryDirectory
import random
import subprocess

ROOT = Path(__file__).resolve().parents[1] / "可打印算法模板" / "09_基础技巧"


def compile_cpp(source: Path, exe: Path) -> None:
    subprocess.run(["g++", "-std=c++17", "-O2", str(source), "-o", str(exe)], check=True)


def run(exe: Path, data: str) -> list[int]:
    return [int(x) for x in subprocess.check_output([str(exe)], input=data.encode()).split()]


def main() -> None:
    rng = random.Random(9)
    with TemporaryDirectory() as temp:
        diff = Path(temp) / "diff.exe"
        pref = Path(temp) / "prefix.exe"
        compile_cpp(ROOT / "二维差分——矩形加值.cpp", diff)
        compile_cpp(ROOT / "二维前缀和——静态矩形求和.cpp", pref)

        for case in range(200):
            n = rng.randint(1, 10)
            count = rng.randint(0, 25)
            grid = [[0] * n for _ in range(n)]
            rectangles = []
            for _ in range(count):
                x1, x2 = sorted((rng.randint(1, n), rng.randint(1, n)))
                y1, y2 = sorted((rng.randint(1, n), rng.randint(1, n)))
                rectangles.append((x1, y1, x2, y2))
                for x in range(x1 - 1, x2):
                    for y in range(y1 - 1, y2):
                        grid[x][y] += 1
            data = f"{n} {count}\n" + "".join(" ".join(map(str, rect)) + "\n" for rect in rectangles)
            expected = [value for row in grid for value in row]
            assert run(diff, data) == expected, (case, rectangles)

        for case in range(200):
            n, m = rng.randint(1, 10), rng.randint(1, 10)
            grid = [[rng.randint(-10**9, 10**9) for _ in range(m)] for _ in range(n)]
            queries = []
            expected = []
            for _ in range(rng.randint(1, 25)):
                x1, x2 = sorted((rng.randint(1, n), rng.randint(1, n)))
                y1, y2 = sorted((rng.randint(1, m), rng.randint(1, m)))
                queries.append((x1, y1, x2, y2))
                expected.append(sum(grid[x][y] for x in range(x1 - 1, x2) for y in range(y1 - 1, y2)))
            data = f"{n} {m} {len(queries)}\n"
            data += "".join(" ".join(map(str, row)) + "\n" for row in grid)
            data += "".join(" ".join(map(str, query)) + "\n" for query in queries)
            assert run(pref, data) == expected, (case, grid, queries)
    print("basic_09_cases=400")


if __name__ == "__main__":
    main()
