"""复查数据结构模板的边界值、版本操作和随机操作序列。"""
from pathlib import Path
import random
import subprocess
import tempfile

BASE = Path(__file__).resolve().parents[1] / "可打印算法模板" / "04_数据结构"
R = random.Random(20261013)


def compile_run(name, td, data):
    exe = Path(td) / "test.exe"
    src = BASE / (name + ".cpp")
    result = subprocess.run(["g++", "-std=c++17", "-O2", str(src), "-o", str(exe)],
                            capture_output=True, text=True)
    assert result.returncode == 0, (name, result.stderr[:400])
    for case, want in data:
        result = subprocess.run([str(exe)], input=case, capture_output=True,
                                text=True, timeout=20)
        assert result.returncode == 0, (name, case[:300], result.stderr[:200])
        got = list(map(int, result.stdout.split()))
        assert got == want, (name, case[:500], got, want)
    print(name, len(data), "cases")


def test_beats(td):
    cases = []
    for _ in range(150):
        n, q = R.randint(1, 12), R.randint(1, 40)
        a = [R.randint(-100000, 10**9) for _ in range(n)]
        cur, ops, want = a[:], [], []
        for _ in range(q):
            op = R.randrange(3)
            l, r = sorted(R.sample(range(1, n+1), 2)) if n > 1 else (1, 1)
            if op == 0:
                v = R.randint(-100000, 10**9)
                ops.append(f"0 {l} {r} {v}")
                cur[l-1:r] = [min(x, v) for x in cur[l-1:r]]
            else:
                ops.append(f"{op} {l} {r}")
                want.append(max(cur[l-1:r]) if op == 1 else sum(cur[l-1:r]))
        cases.append((f"{n} {q}\n" + " ".join(map(str, a)) + "\n" + "\n".join(ops) + "\n", want))
    cases.append(("100000 1\n" + "1000000000 " * 100000 + "\n2 1 100000\n", [10**14]))
    compile_run("线段树Beats——区间取min与求和", td, cases)


def test_bit2d(td):
    cases = []
    for _ in range(150):
        n, m, q = R.randint(1, 5), R.randint(1, 5), R.randint(1, 35)
        a = [[R.randint(-100, 100) for _ in range(m)] for _ in range(n)]
        cur = [row[:] for row in a]
        ops, want = [], []
        for _ in range(q):
            if R.randrange(2):
                x, y, v = R.randrange(n), R.randrange(m), R.randint(-10**9, 10**9)
                cur[x][y] = v
                ops.append(f"1 {x} {y} {v}")
            else:
                x1, x2 = sorted((R.randrange(n), R.randrange(n)))
                y1, y2 = sorted((R.randrange(m), R.randrange(m)))
                ops.append(f"2 {x1} {y1} {x2} {y2}")
                want.append(sum(cur[x][y] for x in range(x1, x2+1) for y in range(y1, y2+1)))
        case = f"{n} {m}\n" + "\n".join(" ".join(map(str, row)) for row in a)
        cases.append((case + f"\n{q}\n" + "\n".join(ops) + "\n", want))
    compile_run("二维树状数组——单点赋值与矩形求和", td, cases)


def test_persistent_fhq(td):
    cases = []
    for _ in range(100):
        versions = [[]]
        ops, want = [], []
        for _ in range(80):
            v = R.randrange(len(versions))
            old = versions[v]
            allowed = [1, 3]
            if old:
                allowed += [2, 4]
            if len(old) > 1:
                allowed += [5, 6]
            op = R.choice(allowed)
            x = R.choice([-2**31, -10, -1, 0, 1, 10, 2**31-1])
            new = old[:]
            if op == 1:
                new.append(x)
                new.sort()
            elif op == 2:
                x = R.choice(old)
                new.remove(x)
            elif op == 3:
                want.append(sum(a < x for a in old) + 1)
            elif op == 4:
                x = R.randint(1, len(old))
                want.append(old[x-1])
            elif op == 5:
                x = R.choice(old[1:])
                if not any(a < x for a in old):
                    op = 3
                    want.append(sum(a < x for a in old) + 1)
                else:
                    want.append(max(a for a in old if a < x))
            else:
                x = R.choice(old[:-1])
                if not any(a > x for a in old):
                    op = 3
                    want.append(sum(a < x for a in old) + 1)
                else:
                    want.append(min(a for a in old if a > x))
            versions.append(new)
            ops.append(f"{v} {op} {x}")
        cases.append((f"{len(ops)}\n" + "\n".join(ops) + "\n", want))
    compile_run("可持久化FHQ_Treap——历史版本有序集合", td, cases)


def test_seg_split(td):
    cases = []
    for _ in range(100):
        n, q = R.randint(2, 12), 80
        initial = [R.randrange(4) for _ in range(n)]
        roots = [None, initial[:]]
        ops, want = [], []
        for _ in range(q):
            op = R.choice([0, 1, 2, 3, 4])
            x = R.randrange(1, len(roots))
            if op == 0:
                l, r = sorted((R.randint(1, n), R.randint(1, n)))
                new = [0] * n
                for i in range(l-1, r):
                    new[i], roots[x][i] = roots[x][i], 0
                roots.append(new)
                ops.append(f"0 {x} {l} {r}")
            elif op == 1 and len(roots) > 2:
                y = R.choice([i for i in range(1, len(roots)) if i != x])
                roots[x] = [a+b for a, b in zip(roots[x], roots[y])]
                roots[y] = [0] * n
                ops.append(f"1 {x} {y}")
            elif op == 2:
                y, z = R.randint(1, 3), R.randint(1, n)
                roots[x][z-1] += y
                ops.append(f"2 {x} {y} {z}")
            elif op == 3:
                l, r = sorted((R.randint(1, n), R.randint(1, n)))
                want.append(sum(roots[x][l-1:r]))
                ops.append(f"3 {x} {l} {r}")
            elif sum(roots[x]):
                k = R.randint(1, sum(roots[x]))
                acc = 0
                for i, value in enumerate(roots[x], 1):
                    acc += value
                    if acc >= k:
                        want.append(i)
                        break
                ops.append(f"4 {x} {k}")
        data = f"{n} {len(ops)}\n" + " ".join(map(str, initial)) + "\n" + "\n".join(ops) + "\n"
        cases.append((data, want))
    compile_run("线段树分裂——权值集合拆分合并", td, cases)


def test_dynamic_kd(td):
    cases = []
    for _ in range(100):
        points, ops, want = [], [], []
        last = 0
        for _ in range(80):
            if not points or R.randrange(2):
                x, y, v = R.randrange(25), R.randrange(25), R.randrange(100)
                points.append((x, y, v))
                ops.append(f"1 {x ^ last} {y ^ last} {v ^ last}")
            else:
                x1, x2 = sorted((R.randrange(25), R.randrange(25)))
                y1, y2 = sorted((R.randrange(25), R.randrange(25)))
                ops.append(f"2 {x1 ^ last} {y1 ^ last} {x2 ^ last} {y2 ^ last}")
                last = sum(v for x, y, v in points if x1 <= x <= x2 and y1 <= y <= y2)
                want.append(last)
        cases.append(("25\n" + "\n".join(ops) + "\n3\n", want))
    compile_run("动态KD树——插点与矩形求和", td, cases)


if __name__ == "__main__":
    with tempfile.TemporaryDirectory() as td:
        test_beats(td)
        test_bit2d(td)
        test_persistent_fhq(td)
        test_seg_split(td)
        test_dynamic_kd(td)
