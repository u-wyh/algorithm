"""对两份容易在边界处出错的模板做小规模暴力对拍。"""

from collections import Counter
from functools import reduce
from itertools import product
from math import gcd
from pathlib import Path
import random
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1] / "可打印算法模板"


def compile_cpp(source: Path, executable: Path) -> None:
    subprocess.run(["g++", "-std=c++17", "-O2", str(source), "-o", str(executable)], check=True)


def run(executable: Path, data: str) -> str:
    return subprocess.run(
        [str(executable)], input=data, text=True, capture_output=True, check=True
    ).stdout.strip()


def main() -> None:
    with tempfile.TemporaryDirectory() as temp:
        work = Path(temp)
        mobius = work / "mobius.exe"
        hashing = work / "hash.exe"
        compile_cpp(ROOT / "05_数学数论" / "莫比乌斯反演——N元组最大公约数.cpp", mobius)
        compile_cpp(ROOT / "03_字符串" / "字符串哈希——子串比较.cpp", hashing)

        rng = random.Random(3172)
        for _ in range(100):
            n = rng.randint(1, 4)
            k = rng.randint(1, 5)
            left = rng.randint(1, 8)
            right = rng.randint(left, 10)
            expected = sum(
                reduce(gcd, values) == k
                for values in product(range(left, right + 1), repeat=n)
            )
            got = int(run(mobius, f"{n} {k} {left} {right}\n"))
            assert got == expected, (n, k, left, right, expected, got)

        rng = random.Random(499)
        for _ in range(200):
            s = "".join(rng.choices("abc", k=rng.randint(1, 24)))
            width = rng.randint(1, 3)
            words = [
                "".join(rng.choices("abc", k=width))
                for _ in range(rng.randint(1, 5))
            ]
            total = width * len(words)
            expected = [
                i
                for i in range(len(s) - total + 1)
                if Counter(s[j:j + width] for j in range(i, i + total, width))
                == Counter(words)
            ]
            data = f"{s} {len(words)}\n" + "\n".join(words) + "\n"
            got = [int(x) for x in run(hashing, data).split()]
            assert got == expected, (s, words, expected, got)
    print("compiled=2 functional_cases=300")


if __name__ == "__main__":
    main()
