"""新增高级专题的随机差分检验。"""

from pathlib import Path
from random import Random
from tempfile import TemporaryDirectory
import heapq
import subprocess

ROOT = Path(r"D:\algorithm\可打印算法模板")
RNG = Random(74073)
SOURCES = {
    "cactus": ROOT / "01_图论/圆方树——仙人掌两点最短路.cpp",
    "segment_graph": ROOT / "01_图论/线段树优化建图——区间连边最短路.cpp",
    "cycle_tree": ROOT / "02_树上问题/基环树——无环定向方案数.cpp",
    "edge_divide": ROOT / "02_树上问题/边分治——路径长度乘最小点权.cpp",
    "tree_of_tree": ROOT / "04_数据结构/树套树——动态区间排名与第k小.cpp",
    "dynamic_kd": ROOT / "04_数据结构/动态KD树——插点与矩形求和.cpp",
    "nearest_kd": ROOT / "04_数据结构/KD树——平面最近点对.cpp",
}


def build(path: Path, exe: Path) -> None:
    r = subprocess.run(["g++", "-std=c++17", "-O2", str(path), "-o", str(exe)], capture_output=True)
    if r.returncode:
        raise RuntimeError(f"{path.name}: {r.stderr[-900:]}")


def run(exe: Path, data: str, timeout: int = 5) -> str:
    r = subprocess.run([str(exe)], input=data, text=True, capture_output=True, timeout=timeout)
    if r.returncode:
        raise RuntimeError(f"{exe.name}: exit={r.returncode}, {r.stderr[-400:]}")
    return r.stdout.strip()


def main() -> None:
    checks = 0
    with TemporaryDirectory() as directory:
        temp = Path(directory)
        exes = {}
        for key, source in SOURCES.items():
            exes[key] = temp / (key + ".exe")
            build(source, exes[key])

        for _ in range(35):
            n = RNG.randint(2, 7)
            edges = [(i, RNG.randrange(i), RNG.randint(1, 15)) for i in range(1, n)]
            pairs = {(min(u, v), max(u, v)) for u, v, _ in edges}
            extras = [(u, v) for u in range(n) for v in range(u + 1, n) if (u, v) not in pairs]
            if extras and RNG.randrange(2):
                u, v = RNG.choice(extras)
                edges.append((u, v, RNG.randint(1, 15)))
            dist = [[0 if i == j else 10 ** 9 for j in range(n)] for i in range(n)]
            for u, v, w in edges:dist[u][v] = dist[v][u] = w
            for k in range(n):
                for i in range(n):
                    for j in range(n):dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
            pairs_query = [(RNG.randrange(n), RNG.randrange(n)) for _ in range(12)]
            data = f"{n} {len(edges)} {len(pairs_query)}\n" + "\n".join(f"{u+1} {v+1} {w}" for u, v, w in edges) + "\n"
            data += "\n".join(f"{u+1} {v+1}" for u, v in pairs_query) + "\n"
            assert list(map(int, run(exes["cactus"], data).split())) == [dist[u][v] for u, v in pairs_query]
            checks += 1

        for _ in range(35):
            n, s = RNG.randint(2, 7), 0
            edges, ops = [], []
            for _ in range(RNG.randint(1, 16)):
                typ = RNG.randint(1, 3)
                u, w = RNG.randrange(n), RNG.randint(0, 20)
                if typ == 1:
                    v = RNG.randrange(n)
                    ops.append(f"1 {u+1} {v+1} {w}")
                    edges.append((u, v, w))
                else:
                    a, b = sorted((RNG.randrange(n), RNG.randrange(n)))
                    ops.append(f"{typ} {u+1} {a+1} {b+1} {w}")
                    for v in range(a, b + 1):edges.append((u, v, w) if typ == 2 else (v, u, w))
            graph = [[] for _ in range(n)]
            for u, v, w in edges:graph[u].append((v, w))
            dist = [10 ** 15] * n
            dist[s] = 0
            pq = [(0, s)]
            while pq:
                d, u = heapq.heappop(pq)
                if d != dist[u]:continue
                for v, w in graph[u]:
                    if d + w < dist[v]:dist[v] = d + w;heapq.heappush(pq, (dist[v], v))
            want = [x if x < 10 ** 15 else -1 for x in dist]
            data = f"{n} {len(ops)} 1\n" + "\n".join(ops) + "\n"
            assert list(map(int, run(exes["segment_graph"], data).split())) == want
            checks += 1

        for _ in range(35):
            n = RNG.randint(2, 8)
            f = [RNG.randrange(n) for _ in range(n)]
            want = 0
            for orientations in range(1 << n):
                graph = [[] for _ in range(n)]
                for i, v in enumerate(f):
                    u, w = (i, v) if orientations >> i & 1 else (v, i)
                    graph[u].append(w)
                state = [0] * n
                def cycle(u):
                    if state[u] == 1:return True
                    if state[u] == 2:return False
                    state[u] = 1
                    if any(cycle(v) for v in graph[u]):return True
                    state[u] = 2
                    return False
                if not any(cycle(i) for i in range(n) if state[i] == 0):want += 1
            data = str(n) + "\n" + " ".join(str(x + 1) for x in f) + "\n"
            got = int(run(exes["cycle_tree"], data))
            assert got == want, (f, got, want)
            checks += 1

        for _ in range(30):
            n = RNG.randint(2, 9)
            weights = [RNG.randint(1, 20) for _ in range(n)]
            edges = [(i, RNG.randrange(i)) for i in range(1, n)]
            graph = [[] for _ in range(n)]
            for u, v in edges:graph[u].append(v);graph[v].append(u)
            want = 0
            for start in range(n):
                stack = [(start, -1, 1, weights[start])]
                while stack:
                    u, parent, length, low = stack.pop()
                    if length >= 2:
                        want = max(want, length * low)
                    for v in graph[u]:
                        if v != parent:stack.append((v, u, length + 1, min(low, weights[v])))
            data = str(n) + "\n" + " ".join(map(str, weights)) + "\n" + "\n".join(f"{u+1} {v+1}" for u, v in edges) + "\n"
            got = int(run(exes["edge_divide"], data))
            assert got == want, (n, weights, edges, got, want)
            checks += 1

        for _ in range(20):
            n = RNG.randint(2, 9)
            values = [RNG.randint(0, 30) for _ in range(n)]
            current = values[:]
            ops, want = [], []
            for _ in range(25):
                typ = RNG.choice([1, 2, 3])
                if typ == 3:
                    pos, val = RNG.randrange(n), RNG.randint(0, 30)
                    current[pos] = val
                    ops.append(f"3 {pos+1} {val}")
                else:
                    left, right = sorted((RNG.randrange(n), RNG.randrange(n)))
                    interval = sorted(current[left:right + 1])
                    if typ == 1:
                        val = RNG.randint(0, 30)
                        want.append(1 + sum(x < val for x in interval))
                    else:
                        val = RNG.randint(1, len(interval))
                        want.append(interval[val - 1])
                    ops.append(f"{typ} {left+1} {right+1} {val}")
            data = f"{n} {len(ops)}\n" + " ".join(map(str, values)) + "\n" + "\n".join(ops) + "\n"
            assert list(map(int, run(exes["tree_of_tree"], data).split())) == want
            checks += 1

        for _ in range(25):
            points = []
            lines, want = ["100"], []
            last = 0
            for _ in range(25):
                if RNG.randrange(3) or not points:
                    x, y, value = RNG.randint(0, 20), RNG.randint(0, 20), RNG.randint(0, 15)
                    points.append((x, y, value))
                    lines.append(f"1 {x ^ last} {y ^ last} {value ^ last}")
                else:
                    x1, x2 = sorted((RNG.randint(0, 20), RNG.randint(0, 20)))
                    y1, y2 = sorted((RNG.randint(0, 20), RNG.randint(0, 20)))
                    answer = sum(v for x, y, v in points if x1 <= x <= x2 and y1 <= y <= y2)
                    lines.append(f"2 {x1 ^ last} {y1 ^ last} {x2 ^ last} {y2 ^ last}")
                    want.append(answer)
                    last = answer
            lines.append("3")
            assert list(map(int, run(exes["dynamic_kd"], "\n".join(lines) + "\n").split())) == want
            checks += 1

        for _ in range(25):
            n = RNG.randint(2, 18)
            points = [(RNG.randint(-20, 20), RNG.randint(-20, 20)) for _ in range(n)]
            squared = min((points[i][0] - points[j][0]) ** 2 + (points[i][1] - points[j][1]) ** 2
                          for i in range(n) for j in range(i + 1, n))
            data = str(n) + "\n" + "\n".join(f"{x} {y}" for x, y in points) + "\n"
            assert abs(float(run(exes["nearest_kd"], data)) - squared ** 0.5) < 0.00011
            checks += 1

        print(f"compiled={len(exes)} functional_cases={checks}")


if __name__ == "__main__":
    main()
