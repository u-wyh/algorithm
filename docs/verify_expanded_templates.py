"""新增关键模板的随机差分与边界检验。"""

from functools import lru_cache
from pathlib import Path
from random import Random
from tempfile import TemporaryDirectory
import itertools
import heapq
import subprocess

ROOT = Path(r"D:\algorithm\可打印算法模板")
RNG = Random(20261012)
SOURCES = {
    "ac": ROOT / "03_字符串/AC自动机——多模式串匹配.cpp",
    "sa": ROOT / "03_字符串/后缀数组——后缀排序与排名.cpp",
    "ntt": ROOT / "05_数学数论/NTT——多项式卷积.cpp",
    "contour": ROOT / "06_动态规划/轮廓线DP——网格不相邻选格方案.cpp",
    "mask": ROOT / "06_动态规划/状压DP——CanIWin先手必胜.cpp",
    "zeroone": ROOT / "06_动态规划/01背包.cpp",
    "complete": ROOT / "06_动态规划/完全背包.cpp",
    "dsu": ROOT / "04_数据结构/并查集——路径压缩按大小合并.cpp",
    "kruskal": ROOT / "01_图论/Kruskal——最小生成树.cpp",
    "floyd": ROOT / "01_图论/Floyd——指定路线最短总路程.cpp",
    "zeroone_bfs": ROOT / "01_图论/0-1 BFS——网格最少清障.cpp",
    "monotone_stack": ROOT / "07_搜索与贪心/单调栈——两侧首个严格更小位置.cpp",
}


def build(path: Path, exe: Path) -> None:
    result = subprocess.run(
        ["g++", "-std=c++17", "-O2", str(path), "-o", str(exe)],
        capture_output=True, text=True, encoding="utf-8", errors="replace",
    )
    if result.returncode:
        raise RuntimeError(f"{path.name}: {result.stderr[:1200]}")


def run(exe: Path, data: str, timeout: int = 4) -> str:
    result = subprocess.run(
        [str(exe)], input=data, capture_output=True, text=True,
        encoding="utf-8", errors="replace", timeout=timeout,
    )
    if result.returncode:
        raise RuntimeError(f"{exe.name}: exit {result.returncode}: {result.stderr[:400]}")
    return result.stdout.strip()


def main() -> None:
    checks = 0
    with TemporaryDirectory() as directory:
        temp = Path(directory)
        exes = {}
        for key, source in SOURCES.items():
            exes[key] = temp / f"{key}.exe"
            build(source, exes[key])

        for _ in range(35):
            n, m = RNG.randint(1, 3), RNG.randint(1, 3)
            grid = [[RNG.randrange(2) for _ in range(m)] for _ in range(n)]
            want = 0
            for mask in range(1 << (n * m)):
                okay = True
                for i in range(n):
                    for j in range(m):
                        if mask >> (i * m + j) & 1:
                            if not grid[i][j] or (j and mask >> (i * m + j - 1) & 1) or (i and mask >> ((i - 1) * m + j) & 1):
                                okay = False
                want += okay
            data = f"{n} {m}\n" + "\n".join(" ".join(map(str, row)) for row in grid) + "\n"
            assert int(run(exes["contour"], data)) == want
            checks += 1

        for _ in range(75):
            n, m = RNG.randint(1, 6), RNG.randint(1, 6)
            grid = [[RNG.randrange(2) for _ in range(m)] for _ in range(n)]
            dist = [[10 ** 9] * m for _ in range(n)]
            dist[0][0] = 0
            heap = [(0, 0, 0)]
            while heap:
                d, x, y = heapq.heappop(heap)
                if d != dist[x][y]:continue
                for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                    xx, yy = x + dx, y + dy
                    if 0 <= xx < n and 0 <= yy < m and d + grid[xx][yy] < dist[xx][yy]:
                        dist[xx][yy] = d + grid[xx][yy]
                        heapq.heappush(heap, (dist[xx][yy], xx, yy))
            data = f"{n} {m}\n" + "\n".join(" ".join(map(str, row)) for row in grid) + "\n"
            assert int(run(exes["zeroone_bfs"], data)) == dist[-1][-1]
            checks += 1

        for _ in range(100):
            values = [RNG.randint(-3, 5) for _ in range(RNG.randint(1, 30))]
            want = []
            for i, value in enumerate(values):
                left = next((j for j in range(i - 1, -1, -1) if values[j] < value), -1)
                right = next((j for j in range(i + 1, len(values)) if values[j] < value), -1)
                want.extend((left, right))
            data = str(len(values)) + "\n" + " ".join(map(str, values)) + "\n"
            assert list(map(int, run(exes["monotone_stack"], data).split())) == want
            checks += 1

        for _ in range(35):
            n = RNG.randint(1, 9)
            target = RNG.randint(0, n * (n + 1) // 2 + 3)
            @lru_cache(None)
            def win(used: int, rest: int) -> bool:
                if rest <= 0:
                    return False
                return any(not win(used | 1 << i, rest - i) for i in range(1, n + 1) if not used >> i & 1)
            want = target == 0 or (n * (n + 1) // 2 >= target and win(0, target))
            assert (run(exes["mask"], f"{n} {target}\n") == "yes") == want
            checks += 1

        for _ in range(40):
            s = "".join(RNG.choice("abc") for _ in range(RNG.randint(1, 15)))
            want = sorted(range(1, len(s) + 1), key=lambda i: s[i - 1:])
            assert list(map(int, run(exes["sa"], s + "\n").split())) == want
            checks += 1

        for _ in range(30):
            patterns = ["".join(RNG.choice("abc") for _ in range(RNG.randint(1, 5))) for _ in range(RNG.randint(1, 6))]
            text = "".join(RNG.choice("abc") for _ in range(RNG.randint(1, 20)))
            want = [sum(text[i:i + len(p)] == p for i in range(len(text) - len(p) + 1)) for p in patterns]
            data = str(len(patterns)) + "\n" + "\n".join(patterns) + "\n" + text + "\n"
            assert list(map(int, run(exes["ac"], data).split())) == want
            checks += 1
        long_pattern = "a" * 100000
        assert run(exes["ac"], f"1\n{long_pattern}\n{long_pattern}\n", 8) == "1"
        checks += 1

        mod = 998244353
        for _ in range(30):
            a = [RNG.randint(-20, 20) for _ in range(RNG.randint(1, 8))]
            b = [RNG.randint(-20, 20) for _ in range(RNG.randint(1, 8))]
            want = [sum(a[i] * b[k - i] for i in range(len(a)) if 0 <= k - i < len(b)) % mod for k in range(len(a) + len(b) - 1)]
            data = f"{len(a)-1} {len(b)-1}\n" + " ".join(map(str, a)) + "\n" + " ".join(map(str, b)) + "\n"
            assert list(map(int, run(exes["ntt"], data).split())) == want
            checks += 1

        for _ in range(40):
            n, cap = RNG.randint(1, 8), RNG.randint(1, 20)
            items = [(RNG.randint(1, 7), RNG.randint(0, 15)) for _ in range(n)]
            data = f"{n} {cap}\n" + "\n".join(f"{w} {v}" for w, v in items) + "\n"
            want = max((sum(items[i][1] for i in range(n) if mask >> i & 1)
                        for mask in range(1 << n) if sum(items[i][0] for i in range(n) if mask >> i & 1) <= cap), default=0)
            assert int(run(exes["zeroone"], data)) == want
            dp = [0] * (cap + 1)
            for w, v in items:
                for c in range(w, cap + 1):
                    dp[c] = max(dp[c], dp[c - w] + v)
            assert int(run(exes["complete"], data)) == dp[cap]
            checks += 2

        for _ in range(30):
            n = RNG.randint(2, 12)
            groups = [{i} for i in range(n)]
            ops, want = [], []
            for _ in range(25):
                typ, u, v = RNG.choice([1, 1, 2]), RNG.randrange(n), RNG.randrange(n)
                ops.append((typ, u + 1, v + 1))
                if typ == 1:
                    groups[u] |= groups[v]
                    for x in groups[u]: groups[x] = groups[u]
                else:
                    want.append("Yes" if v in groups[u] else "No")
            data = f"{n} {len(ops)}\n" + "\n".join(" ".join(map(str, x)) for x in ops) + "\n"
            assert run(exes["dsu"], data).splitlines() == want
            checks += 1

        for _ in range(30):
            n = RNG.randint(2, 9)
            edges = [(u, v, RNG.randint(-10, 25)) for u in range(n) for v in range(u + 1, n) if RNG.randrange(3)]
            groups = list(range(n))
            def root(x):
                while groups[x] != x: x = groups[x]
                return x
            total = count = 0
            for u, v, w in sorted(edges, key=lambda x: x[2]):
                a, b = root(u), root(v)
                if a != b:
                    groups[a] = b
                    total += w
                    count += 1
            want = str(total) if count == n - 1 else "orz"
            data = f"{n} {len(edges)}\n" + "\n".join(f"{u+1} {v+1} {w}" for u, v, w in edges) + "\n"
            assert run(exes["kruskal"], data) == want
            checks += 1

        for _ in range(30):
            n = RNG.randint(2, 7)
            path = [RNG.randrange(n) for _ in range(RNG.randint(2, 10))]
            dist = [[0 if i == j else RNG.randint(1, 20) for j in range(n)] for i in range(n)]
            d = [row[:] for row in dist]
            for k in range(n):
                for i in range(n):
                    for j in range(n):d[i][j] = min(d[i][j], d[i][k] + d[k][j])
            want = sum(d[path[i]][path[i + 1]] for i in range(len(path) - 1))
            data = f"{n} {len(path)}\n" + " ".join(str(x + 1) for x in path) + "\n" + "\n".join(" ".join(map(str, row)) for row in dist) + "\n"
            assert int(run(exes["floyd"], data)) == want
            checks += 1

        print(f"compiled={len(exes)} functional_cases={checks}")


if __name__ == "__main__":
    main()
