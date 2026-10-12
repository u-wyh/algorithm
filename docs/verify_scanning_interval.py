"""扫描线最短覆盖区间：随机小例与暴力枚举对照。"""

from pathlib import Path
from tempfile import TemporaryDirectory
import random
import subprocess

SOURCE = Path(r"D:\algorithm\可打印算法模板\09_基础技巧\扫描线——查询点的最短覆盖区间.cpp")


def main() -> None:
    rng = random.Random(17)
    with TemporaryDirectory() as tmp:
        exe = Path(tmp) / "scan.exe"
        subprocess.run(["g++", "-std=c++17", "-O2", str(SOURCE), "-o", str(exe)], check=True)
        for case in range(300):
            n, m = rng.randrange(17), rng.randrange(1, 18)
            segments = []
            for _ in range(n):
                left = rng.randrange(-20, 21)
                segments.append((left, rng.randrange(left, 22)))
            queries = [rng.randrange(-22, 23) for _ in range(m)]
            data = f"{n} {m}\n"
            data += "".join(f"{l} {r}\n" for l, r in segments)
            data += "".join(f"{x}\n" for x in queries)
            got = list(map(int, subprocess.check_output([str(exe)], input=data.encode()).split()))
            want = [min((r - l + 1 for l, r in segments if l <= x <= r), default=-1) for x in queries]
            assert got == want, (case, segments, queries, got, want)
    print("scan_cases=300")


if __name__ == "__main__":
    main()
