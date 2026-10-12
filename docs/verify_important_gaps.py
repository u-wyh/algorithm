"""新补重要模板的小规模暴力对照与长链边界。"""

from itertools import permutations, product
from pathlib import Path
from tempfile import TemporaryDirectory
from collections import deque
import random
import subprocess

ROOT = Path(r"D:\algorithm\可打印算法模板")
SOURCES = {
    "bipartite": ROOT / "01_图论/二分图染色——判定与输出两侧.cpp",
    "km": ROOT / "01_图论/KM算法——最大权完美匹配.cpp",
    "flow": ROOT / "01_图论/上下界网络流——有源汇最大流.cpp",
    "difference": ROOT / "02_树上问题/树上点差分——路径加一后求最大点权.cpp",
    "diameter": ROOT / "02_树上问题/树的直径——允许负边的最大路径和.cpp",
    "quotients": ROOT / "05_数学数论/整除分块——除法下取整求和.cpp",
    "matrix": ROOT / "05_数学数论/矩阵快速幂——小阶方阵取模幂.cpp",
}
RNG = random.Random(20261012)


def run(exe: Path, data: str) -> str:
    return subprocess.check_output([str(exe)], input=data.encode(), timeout=10).decode().strip()


def tree_path(graph, start, target):
    parent = [-1] * len(graph)
    parent[start] = start
    que = deque([start])
    while que:
        u = que.popleft()
        if u == target:
            break
        for v, weight in graph[u]:
            if parent[v] == -1:
                parent[v] = u
                que.append(v)
    path = []
    u = target
    while u != start:
        path.append(u)
        u = parent[u]
    path.append(start)
    return path


def main() -> None:
    checks = 0
    with TemporaryDirectory() as tmp:
        exes = {}
        for key, source in SOURCES.items():
            exe = Path(tmp) / f"{key}.exe"
            subprocess.run(["g++", "-std=c++17", "-O2", str(source), "-o", str(exe)], check=True)
            exes[key] = exe

        for _ in range(160):
            n = RNG.randint(1, 8)
            edges = [(RNG.randrange(n), RNG.randrange(n)) for _ in range(RNG.randint(0, 12))]
            data = f"{n} {len(edges)}\n" + "".join(f"{u+1} {v+1}\n" for u, v in edges)
            lines = run(exes["bipartite"], data).splitlines()
            possible = any(all(colors[u] != colors[v] for u, v in edges)
                           for colors in product((1, 2), repeat=n))
            assert (lines[0] == "YES") == possible
            if possible:
                colors = list(map(int, lines[1].split()))
                assert len(colors) == n and all(colors[u] != colors[v] for u, v in edges)
            checks += 1

        for _ in range(150):
            n = RNG.randint(1, 7)
            weights = [[RNG.randint(-12, 12) for _ in range(n)] for _ in range(n)]
            data = str(n) + "\n" + "\n".join(" ".join(map(str, row)) for row in weights) + "\n"
            want = max(sum(weights[u][order[u]] for u in range(n)) for order in permutations(range(n)))
            assert int(run(exes["km"], data)) == want
            checks += 1

        for _ in range(180):
            n, m = RNG.randint(2, 5), RNG.randint(0, 6)
            source, sink = 0, n - 1
            edges = []
            for _ in range(m):
                u = RNG.randrange(n)
                v = RNG.choice([x for x in range(n) if x != u])
                upper = RNG.randint(0, 3)
                lower = RNG.randint(0, upper)
                edges.append((u, v, lower, upper))
            data = f"{n} {m} 1 {n}\n" + "".join(
                f"{u+1} {v+1} {lower} {upper}\n" for u, v, lower, upper in edges)
            want = -1
            for values in product(*(range(low, high + 1) for _, _, low, high in edges)):
                balance = [0] * n
                for (u, v, _, _), flow in zip(edges, values):
                    balance[u] -= flow
                    balance[v] += flow
                value = -balance[source]
                if value >= 0 and balance[sink] == value and all(
                        balance[v] == 0 for v in range(n) if v not in (source, sink)):
                    want = max(want, value)
            assert int(run(exes["flow"], data)) == want, (edges, want)
            checks += 1

        for _ in range(180):
            n, q = RNG.randint(1, 25), RNG.randint(0, 30)
            graph = [[] for _ in range(n)]
            edges = []
            for v in range(1, n):
                u = RNG.randrange(v)
                w = RNG.randint(-20, 20)
                edges.append((u, v, w))
                graph[u].append((v, w))
                graph[v].append((u, w))
            pairs = [(RNG.randrange(n), RNG.randrange(n)) for _ in range(q)]
            count = [0] * n
            for u, v in pairs:
                for x in tree_path(graph, u, v):
                    count[x] += 1
            data = f"{n} {q}\n" + "".join(f"{u+1} {v+1}\n" for u, v, _ in edges)
            data += "".join(f"{u+1} {v+1}\n" for u, v in pairs)
            assert int(run(exes["difference"], data)) == max(count)
            checks += 1

            diameter = 0 if n == 1 else -(10**18)
            for u in range(n):
                for v in range(u + 1, n):
                    path = tree_path(graph, u, v)
                    value = sum(next(w for x, w in graph[a] if x == b)
                                for a, b in zip(path, path[1:]))
                    diameter = max(diameter, value)
            data = f"{n}\n" + "".join(f"{u+1} {v+1} {w}\n" for u, v, w in edges)
            assert int(run(exes["diameter"], data)) == diameter
            checks += 1

        n = 50000
        chain = "".join(f"{u} {u+1}\n" for u in range(1, n))
        assert run(exes["difference"], f"{n} 1\n{chain}1 {n}\n") == "1"
        assert run(exes["diameter"], f"{n}\n" + "".join(
            f"{u} {u+1} -1\n" for u in range(1, n))) == "-1"
        checks += 2
        values = [RNG.randrange(0, 20001) for _ in range(300)]
        data = str(len(values)) + "\n" + "\n".join(map(str, values)) + "\n"
        got = list(map(int, run(exes["quotients"], data).split()))
        want = [sum(n // i for i in range(1, n + 1)) for n in values]
        assert got == want
        checks += len(values)
        for _ in range(200):
            k, exponent, mod = RNG.randint(1, 5), RNG.randint(0, 9), RNG.randint(1, 97)
            matrix = [[RNG.randint(-12, 12) for _ in range(k)] for _ in range(k)]
            answer = [[int(i == j) % mod for j in range(k)] for i in range(k)]
            for _ in range(exponent):
                answer = [[sum(answer[i][t] * matrix[t][j] for t in range(k)) % mod
                           for j in range(k)] for i in range(k)]
            data = f"{k} {exponent} {mod}\n" + "\n".join(
                " ".join(map(str, row)) for row in matrix) + "\n"
            got = [list(map(int, row.split())) for row in run(exes["matrix"], data).splitlines()]
            assert got == answer
            checks += 1
    print(f"compiled={len(exes)} functional_cases={checks}")


if __name__ == "__main__":
    main()
