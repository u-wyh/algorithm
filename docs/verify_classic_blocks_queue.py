"""经典序列分块与单调队列的随机暴力对照。"""

from pathlib import Path
from random import Random
from tempfile import TemporaryDirectory
import subprocess

ROOT = Path(r"D:\algorithm\可打印算法模板")
SOURCES = {
    "sum": ROOT / "08_离线分治/分块——区间加与区间求和.cpp",
    "count": ROOT / "08_离线分治/分块——区间加与阈值计数.cpp",
    "queue": ROOT / "07_搜索与贪心/单调队列——窗口最小值与最大值.cpp",
}
RNG = Random(20261013)


def run(exe: Path, data: str) -> list[str]:
    return subprocess.check_output([str(exe)], input=data.encode(), timeout=15).decode().splitlines()


def main() -> None:
    checks = 0
    with TemporaryDirectory() as tmp:
        exes = {}
        for key, source in SOURCES.items():
            exe = Path(tmp) / f"{key}.exe"
            subprocess.run(["g++", "-std=c++17", "-O2", "-Wall", "-Wextra",
                            str(source), "-o", str(exe)], check=True)
            exes[key] = exe

        for _ in range(220):
            n, q = RNG.randint(1, 70), RNG.randint(1, 80)
            original = [RNG.randint(-30, 30) for _ in range(n)]
            current = original[:]
            operations, expected = [], []
            for _ in range(q):
                left, right = sorted((RNG.randrange(n), RNG.randrange(n)))
                if RNG.randrange(2):
                    delta = RNG.randint(-20, 20)
                    operations.append(f"1 {left+1} {right+1} {delta}")
                    for i in range(left, right + 1):
                        current[i] += delta
                else:
                    operations.append(f"2 {left+1} {right+1}")
                    expected.append(sum(current[left:right + 1]))
            data = f"{n} {q}\n" + " ".join(map(str, original)) + "\n"
            data += "\n".join(operations) + "\n"
            assert list(map(int, run(exes["sum"], data))) == expected
            checks += 1

        for _ in range(220):
            n, q = RNG.randint(1, 70), RNG.randint(1, 80)
            original = [RNG.randint(-30, 30) for _ in range(n)]
            current = original[:]
            operations, expected = [], []
            for _ in range(q):
                left, right = sorted((RNG.randrange(n), RNG.randrange(n)))
                value = RNG.randint(-40, 40)
                if RNG.randrange(2):
                    operations.append(f"M {left+1} {right+1} {value}")
                    for i in range(left, right + 1):
                        current[i] += value
                else:
                    operations.append(f"A {left+1} {right+1} {value}")
                    expected.append(sum(x >= value for x in current[left:right + 1]))
            data = f"{n} {q}\n" + " ".join(map(str, original)) + "\n"
            data += "\n".join(operations) + "\n"
            assert list(map(int, run(exes["count"], data))) == expected
            checks += 1

        for _ in range(300):
            n = RNG.randint(1, 100)
            k = RNG.randint(1, n)
            values = [RNG.randint(-100, 100) for _ in range(n)]
            data = f"{n} {k}\n" + " ".join(map(str, values)) + "\n"
            lines = run(exes["queue"], data)
            assert len(lines) == 2
            assert list(map(int, lines[0].split())) == [min(values[i:i + k]) for i in range(n - k + 1)]
            assert list(map(int, lines[1].split())) == [max(values[i:i + k]) for i in range(n - k + 1)]
            checks += 1

        n = 200000
        data = f"{n} 3\n" + "0 " * n + f"\n1 1 {n} 7\n1 2 {n-1} -3\n2 1 {n}\n"
        assert run(exes["sum"], data) == [str(7 * n - 3 * (n - 2))]
        checks += 1
    print(f"compiled=3 functional_cases={checks}")


if __name__ == "__main__":
    main()
