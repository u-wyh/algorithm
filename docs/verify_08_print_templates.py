"""08 文件夹新增模板的小数据穷举对拍；直接运行本脚本。"""
from pathlib import Path
import random
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1] / "可打印算法模板" / "08_离线分治"
R = random.Random(20261013)
CASES = {}


def run(exes, name, data):
    result = subprocess.run([str(exes[name])], input=data, text=True,
                            capture_output=True, timeout=10)
    assert result.returncode == 0, (name, data[:400], result.stderr[:300])
    CASES[name] = CASES.get(name, 0) + 1
    return result.stdout.split()


def chain(points):
    """所选四维点按字典序排列后必须在每一维都不下降。"""
    points = sorted(points)
    return all(all(a[d] <= b[d] for d in range(4))
               for a, b in zip(points, points[1:]))


def main():
    names = [
        "CDQ四维偏序——宝藏链最大收益及方案数",
        "CDQ四维偏序——含负权怪兽链最大收益",
        "CDQ优化DP——导弹最长拦截与入选概率",
        "CDQ优化DP——任意单点变值仍不下降的最长子序列",
        "时间分块——位置值达到阈值的历史时刻数",
        "树上分块——多路径点权并集与mex",
        "整体二分——单点修改区间第k小",
        "根号分治——模下标求和与单点修改",
        "普通莫队——静态区间不同数计数",
    ]
    with tempfile.TemporaryDirectory() as td:
        exes = {}
        for i, name in enumerate(names):
            exe = Path(td) / f"test{i}.exe"
            p = subprocess.run(["g++", "-std=c++17", "-O2", str(ROOT / (name + ".cpp")),
                                "-o", str(exe)], capture_output=True, text=True)
            assert p.returncode == 0, (name, p.stderr[:500])
            exes[name] = exe

        for _ in range(140):
            n = R.randint(1, 8)
            rows = [tuple(R.randint(1, 3) for _ in range(4)) + (R.randint(1, 9),)
                    for _ in range(n)]
            groups = {}
            for row in rows:
                groups[row[:4]] = groups.get(row[:4], 0) + row[4]
            items = list(groups.items())
            best, ways = 0, 0
            for mask in range(1, 1 << len(items)):
                chosen = [items[i] for i in range(len(items)) if mask >> i & 1]
                if chain([p for p, _ in chosen]):
                    value = sum(v for _, v in chosen)
                    if value > best:
                        best, ways = value, 1
                    elif value == best:
                        ways += 1
            data = f"{n} {n}\n" + "".join(" ".join(map(str, row)) + "\n" for row in rows)
            got = list(map(int, run(exes, names[0], data)))
            assert got == [best, ways], (data, got, [best, ways])

        for _ in range(140):
            n = R.randint(1, 8)
            rows = [tuple(R.randint(-2, 2) for _ in range(4)) + (R.randint(-8, 8),)
                    for _ in range(n)]
            best = -10**20
            for mask in range(1, 1 << n):
                chosen = [rows[i] for i in range(n) if mask >> i & 1]
                if chain([row[:4] for row in chosen]):
                    best = max(best, sum(row[4] for row in chosen))
            data = f"{n}\n" + "".join(" ".join(map(str, row)) + "\n" for row in rows)
            got = int(run(exes, names[1], data)[0])
            assert got == best, (data, got, best)

        for _ in range(160):
            n = R.randint(1, 9)
            rows = [(R.randint(1, 5), R.randint(1, 5)) for _ in range(n)]
            best, optimal = 0, []
            for mask in range(1, 1 << n):
                seq = [rows[i] for i in range(n) if mask >> i & 1]
                if all(a[0] >= b[0] and a[1] >= b[1] for a, b in zip(seq, seq[1:])):
                    if len(seq) > best:
                        best, optimal = len(seq), [mask]
                    elif len(seq) == best:
                        optimal.append(mask)
            data = f"{n}\n" + "".join(f"{h} {v}\n" for h, v in rows)
            out = run(exes, names[2], data)
            assert int(out[0]) == best, (data, out, best)
            for i, got in enumerate(map(float, out[1:])):
                want = sum(bool(mask >> i & 1) for mask in optimal) / len(optimal)
                assert abs(got - want) < 1e-4, (data, i, got, want)

        # 每层两点互不可比，1200 层形成 2^1200 条最长方案，原 double 计数会溢出。
        groups = 1200
        rows = []
        for level in range(groups, 0, -1):
            base = 3 * level
            rows.extend(((base, base + 1), (base + 1, base)))
        data = f"{len(rows)}\n" + "".join(f"{h} {v}\n" for h, v in rows)
        out = run(exes, names[2], data)
        assert int(out[0]) == groups and all(abs(float(x)-.5) < 1e-4 for x in out[1:])

        for _ in range(160):
            n, m = R.randint(1, 9), R.randint(0, 8)
            values = [R.randint(1, 6) for _ in range(n)]
            changes = [(R.randrange(n), R.randint(1, 6)) for _ in range(m)]
            candidates = [values[:]]
            for i, val in changes:
                changed = values[:]
                changed[i] = val
                candidates.append(changed)
            best = 0
            for mask in range(1, 1 << n):
                idx = [i for i in range(n) if mask >> i & 1]
                if all(all(a[i] <= a[j] for i, j in zip(idx, idx[1:]))
                       for a in candidates):
                    best = max(best, len(idx))
            data = f"{n} {m}\n" + " ".join(map(str, values)) + "\n"
            data += "".join(f"{i+1} {v}\n" for i, v in changes)
            got = int(run(exes, names[3], data)[0])
            assert got == best, (data, got, best)

        for _ in range(150):
            n, m = R.randint(2, 8), R.randint(2, 20)
            arr = [R.randint(-10, 10) for _ in range(n)]
            now, history = arr[:], [arr[:]]
            ops, expected = [], []
            for _ in range(m):
                if R.random() < .55:
                    l = R.randrange(n)
                    r = R.randrange(l, n)
                    v = R.randint(-10, 10)
                    ops.append(f"1 {l+1} {r+1} {v}")
                    for i in range(l, r+1):
                        now[i] += v
                else:
                    x, threshold = R.randrange(n), R.randint(-20, 20)
                    ops.append(f"2 {x+1} {threshold}")
                    expected.append(sum(state[x] >= threshold for state in history))
                history.append(now[:])
            data = f"{n} {m}\n" + " ".join(map(str, arr)) + "\n" + "\n".join(ops) + "\n"
            got = list(map(int, run(exes, names[4], data)))
            assert got == expected, (data, got, expected)

        for _ in range(120):
            n, m = R.randint(1, 12), R.randint(1, 12)
            values = [R.randint(0, 8) for _ in range(n)]
            edges = [(i, R.randrange(i)) for i in range(1, n)]
            graph = [[] for _ in range(n)]
            for x, y in edges:
                graph[x].append(y)
                graph[y].append(x)
            f, last = R.randint(0, 1), 0
            ops, expected = [], []
            for _ in range(m):
                pairs = [(R.randrange(n), R.randrange(n)) for _ in range(R.randint(1, 4))]
                op = [str(len(pairs))]
                seen = set()
                for x, y in pairs:
                    op.append(f"{(x+1)^last if f else x+1} {(y+1)^last if f else y+1}")
                    queue = [x]
                    parent = {x: -1}
                    for u in queue:
                        if u == y:
                            break
                        for v in graph[u]:
                            if v not in parent:
                                parent[v] = u
                                queue.append(v)
                    u = y
                    while u != -1:
                        seen.add(values[u])
                        u = parent[u]
                mex = next(v for v in range(n+1) if v not in seen)
                expected.extend((len(seen), mex))
                last = len(seen) + mex
                ops.append(" ".join(op))
            data = f"{n} {m} {f}\n" + " ".join(map(str, values)) + "\n"
            data += "".join(f"{x+1} {y+1}\n" for x, y in edges)
            data += "\n".join(ops) + "\n"
            got = list(map(int, run(exes, names[5], data)))
            assert got == expected, (data, got, expected)

        for _ in range(160):
            n, m = R.randint(1, 10), R.randint(1, 20)
            arr = [R.randint(1, 12) for _ in range(n)]
            current, ops, expected = arr[:], [], []
            for _ in range(m):
                if R.random() < .5:
                    i, val = R.randrange(n), R.randint(1, 12)
                    ops.append(f"C {i+1} {val}")
                    current[i] = val
                else:
                    l = R.randrange(n)
                    r = R.randrange(l, n)
                    k = R.randint(1, r-l+1)
                    ops.append(f"Q {l+1} {r+1} {k}")
                    expected.append(sorted(current[l:r+1])[k-1])
            data = f"{n} {m}\n" + " ".join(map(str, arr)) + "\n" + "\n".join(ops) + "\n"
            got = list(map(int, run(exes, names[6], data)))
            assert got == expected, (data, got, expected)

        for _ in range(120):
            n, m = R.randint(1, 30), R.randint(1, 25)
            arr = [R.randint(-10, 10) for _ in range(n)]
            current, ops, expected = arr[:], [], []
            for _ in range(m):
                if R.random() < .5:
                    x = R.randint(1, n)
                    y = R.randrange(x)
                    ops.append(f"A {x} {y}")
                    expected.append(sum(current[i-1] for i in range(1, n+1) if i%x == y))
                else:
                    i, val = R.randrange(n), R.randint(-10, 10)
                    ops.append(f"B {i+1} {val}")
                    current[i] = val
            data = f"{n} {m}\n" + " ".join(map(str, arr)) + "\n" + "\n".join(ops) + "\n"
            got = list(map(int, run(exes, names[7], data)))
            assert got == expected, (data, got, expected)

        for _ in range(100):
            n, q = R.randint(1, 30), R.randint(1, 30)
            arr = [R.randint(1, 10) for _ in range(n)]
            intervals = []
            for _ in range(q):
                l = R.randint(1, n)
                intervals.append((l, R.randint(l, n)))
            expected = [len(set(arr[l-1:r])) for l, r in intervals]
            data = f"{n}\n" + " ".join(map(str, arr)) + f"\n{q}\n"
            data += "".join(f"{l} {r}\n" for l, r in intervals)
            got = list(map(int, run(exes, names[8], data)))
            assert got == expected, (data, got, expected)

        # 链树达到题目上限，用来查递归 DFS 是否栈溢出。
        n = 100000
        data = f"{n} 1 0\n" + "0 " * n + "\n"
        data += "".join(f"{i} {i+1}\n" for i in range(1, n)) + f"1 1 {n}\n"
        assert run(exes, names[5], data) == ["1", "1"]
    print(f"08 differential cases={sum(CASES.values())}; " +
          ", ".join(f"{key}:{value}" for key, value in CASES.items()))


if __name__ == "__main__":
    main()
