"""P2619 带权二分：小图枚举生成树，对照恰好 need 条白边的最优值。"""

from itertools import combinations
from pathlib import Path
from tempfile import TemporaryDirectory
import random
import subprocess

SOURCE = Path(__file__).resolve().parents[1] / "可打印算法模板" / "09_基础技巧" / "带权二分——恰选k条特殊边最小生成树.cpp"


def exact_answers(n: int, edges: list[tuple[int, int, int, int]]) -> dict[int, int]:
    best = {}
    for selected in combinations(edges, n - 1):
        parent = list(range(n))

        def find(x: int) -> int:
            while parent[x] != x:
                x = parent[x]
            return x

        valid = True
        for u, v, _, _ in selected:
            a, b = find(u), find(v)
            if a == b:
                valid = False
                break
            parent[a] = b
        if not valid:
            continue
        white = sum(color == 0 for _, _, _, color in selected)
        cost = sum(weight for _, _, weight, _ in selected)
        best[white] = min(best.get(white, cost), cost)
    return best


def main() -> None:
    rng = random.Random(2619)
    with TemporaryDirectory() as temp:
        exe = Path(temp) / "weighted_binary.exe"
        subprocess.run(["g++", "-std=c++17", "-O2", str(SOURCE), "-o", str(exe)], check=True)
        for case in range(300):
            n = rng.randint(2, 6)
            pairs = []
            # 先构造一棵树，确保图连通。
            for v in range(1, n):
                pairs.append((rng.randrange(v), v))
            candidates = [(u, v) for u in range(n) for v in range(u + 1, n) if (u, v) not in pairs]
            rng.shuffle(candidates)
            pairs += candidates[:rng.randint(0, min(5, len(candidates)))]
            edges = [(u, v, rng.choice([1, 2, 3, 99, 100, rng.randint(1, 100)]), rng.randrange(2)) for u, v in pairs]
            best = exact_answers(n, edges)
            need = rng.choice(list(best))  # 原题保证该数量可实现。
            data = f"{n} {len(edges)} {need}\n" + "".join(f"{u} {v} {w} {color}\n" for u, v, w, color in edges)
            got = int(subprocess.check_output([str(exe)], input=data.encode()).strip())
            assert got == best[need], (case, edges, need, got, best[need])
        # 最大规模长链：检查数组边界、并查集深度和总权值。
        n = 50000
        data = f"{n} {n-1} {n-1}\n" + "".join(f"{v-1} {v} 100 0\n" for v in range(1, n))
        got = int(subprocess.check_output([str(exe)], input=data.encode(), timeout=20).strip())
        assert got == 100 * (n - 1), got
    print("weighted_binary_cases=301")


if __name__ == "__main__":
    main()
