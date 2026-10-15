"""全目录复查时的定向回归：Tarjan、线性基、区间建图、数论边界。"""
from collections import deque
from pathlib import Path
import heapq
import math
import random
import subprocess
import tempfile

BASE = Path(__file__).resolve().parents[1]
PRINT = BASE / "可打印算法模板"
R = random.Random(20261014)


def compile_cpp(src, exe):
    p = subprocess.run(["g++", "-std=c++17", "-O2", str(src), "-o", str(exe)],
                       capture_output=True, text=True)
    assert p.returncode == 0, (src, p.stderr[:400])


def run(exe, data, timeout=15):
    p = subprocess.run([str(exe)], input=data, capture_output=True,
                       text=True, timeout=timeout)
    assert p.returncode == 0, (exe.name, data[:250], p.stderr[:250], p.returncode)
    return p.stdout


def components(output):
    nums = list(map(int, output.split()))
    count, pos = nums[0], 1
    result = []
    for _ in range(count):
        size = nums[pos]
        pos += 1
        result.append(tuple(sorted(nums[pos:pos+size])))
        pos += size
    assert pos == len(nums)
    return sorted(result)


def test_tarjan(td):
    for name in ("Tarjan——边双连通分量", "Tarjan——点双连通分量"):
        rel = f"可打印算法模板/01_图论/{name}.cpp"
        current = PRINT / "01_图论" / (name + ".cpp")
        old_source = Path(td) / "old.cpp"
        p = subprocess.run(["git", "show", f"HEAD:{rel}"], cwd=BASE,
                           capture_output=True)
        assert p.returncode == 0, p.stderr[:200]
        old_source.write_bytes(p.stdout)
        old, new = Path(td) / "old.exe", Path(td) / "new.exe"
        compile_cpp(old_source, old)
        compile_cpp(current, new)
        for _ in range(250):
            n, m = R.randint(1, 12), R.randint(0, 25)
            edges = [(R.randint(1, n), R.randint(1, n)) for _ in range(m)]
            data = f"{n} {m}\n" + "".join(f"{u} {v}\n" for u, v in edges)
            assert components(run(new, data)) == components(run(old, data)), (name, data)
        n = 500000
        data = f"{n} {n-1}\n" + "".join(f"{i} {i+1}\n" for i in range(1, n))
        answer = run(new, data, timeout=45).split("\n", 1)[0]
        assert int(answer) == (n if "边双" in name else n-1), (name, answer)
        print(name, "250 random + 500000-chain")


def test_basis(td):
    name = "线性基——图路径最大异或和"
    exe = Path(td) / "basis.exe"
    compile_cpp(PRINT / "05_数学数论" / (name + ".cpp"), exe)
    for _ in range(300):
        n = R.randint(2, 8)
        edges = [(i, R.randrange(1, i), R.randrange(16)) for i in range(2, n+1)]
        edges += [(R.randint(1, n), R.randint(1, n), R.randrange(16))
                  for _ in range(R.randint(0, 12))]
        graph = [[] for _ in range(n+1)]
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))
        reachable = {(1, 0)}
        queue = deque([(1, 0)])
        while queue:
            u, x = queue.popleft()
            for v, w in graph[u]:
                state = (v, x ^ w)
                if state not in reachable:
                    reachable.add(state)
                    queue.append(state)
        want = max(x for u, x in reachable if u == n)
        data = f"{n} {len(edges)}\n" + "".join(f"{u} {v} {w}\n" for u, v, w in edges)
        assert int(run(exe, data)) == want, data
    huge = 10**18
    data = f"3 3\n1 2 {huge}\n2 3 1\n1 3 0\n"
    assert int(run(exe, data)) == huge+1
    n = 50000
    data = f"{n} {n-1}\n" + "".join(f"{i} {i+1} 1\n" for i in range(1, n))
    assert int(run(exe, data, timeout=20)) == ((n-1) & 1)
    print("linear basis", "300 random + 64-bit + 50000-chain")


def test_interval_graph(td):
    exe = Path(td) / "interval.exe"
    compile_cpp(PRINT / "01_图论" / "线段树优化建图——区间连边最短路.cpp", exe)
    for _ in range(220):
        n = R.randint(1, 8)
        q = R.randint(1, 20)
        start = R.randint(1, n)
        ops, graph = [], [[] for _ in range(n+1)]
        for _ in range(q):
            kind = R.randint(1, 3)
            v, w = R.randint(1, n), R.randint(0, 20)
            if kind == 1:
                u = R.randint(1, n)
                ops.append(f"1 {v} {u} {w}")
                graph[v].append((u, w))
            else:
                l = R.randint(1, n)
                r = R.randint(l, n)
                ops.append(f"{kind} {v} {l} {r} {w}")
                for u in range(l, r+1):
                    graph[v if kind == 2 else u].append((u if kind == 2 else v, w))
        dist = [10**20] * (n+1)
        dist[start] = 0
        heap = [(0, start)]
        while heap:
            d, u = heapq.heappop(heap)
            if d != dist[u]:
                continue
            for v, w in graph[u]:
                if d+w < dist[v]:
                    dist[v] = d+w
                    heapq.heappush(heap, (d+w, v))
        want = [-1 if x == 10**20 else x for x in dist[1:]]
        data = f"{n} {q} {start}\n" + "\n".join(ops) + "\n"
        assert list(map(int, run(exe, data).split())) == want, data
    print("interval graph", "220 random")


def test_euler(td):
    exe = Path(td) / "euler.exe"
    compile_cpp(PRINT / "05_数学数论" / "扩展欧拉定理——大指数模幂.cpp", exe)
    for _ in range(200):
        a, mod = R.randint(0, 10**9), R.randint(1, 10**6)
        exponent = int("".join(str(R.randrange(10)) for _ in range(R.randint(1, 60))))
        data = f"{a} {mod} {exponent}\n"
        assert int(run(exe, data)) == pow(a, exponent, mod), data
    print("extended Euler", "200 random")


def test_bitset(td):
    exe = Path(td) / "bitset.exe"
    compile_cpp(PRINT / "04_数据结构" / "位图——布尔值域集合.cpp", exe)
    for _ in range(160):
        n = R.choice((33, 64, 100, 1000000))
        present, ops, want = set(), [], []
        for _ in range(100):
            op = R.randint(1, 4)
            x = R.choice((0, 31, 32, n-1, R.randrange(n)))
            ops.append(f"{op} {x}")
            if op == 1:
                present.add(x)
            elif op == 2:
                present.discard(x)
            elif op == 3:
                if x in present:
                    present.remove(x)
                else:
                    present.add(x)
            else:
                want.append(int(x in present))
        data = f"{n} {len(ops)}\n" + "\n".join(ops) + "\n"
        assert list(map(int, run(exe, data).split())) == want
    print("bitset", "160 random")


def test_segment_mul_add(td):
    exe = Path(td) / "segment.exe"
    compile_cpp(PRINT / "04_数据结构" / "线段树区间乘加区间和.cpp", exe)
    for _ in range(180):
        n, q = R.randint(1, 20), R.randint(1, 100)
        mod = R.choice((1, 2, 101, 1000000007))
        arr = [R.randint(-10, 10) for _ in range(n)]
        current, ops, want = arr[:], [], []
        for _ in range(q):
            kind = R.randint(1, 3)
            l = R.randint(1, n)
            r = R.randint(l, n)
            if kind == 1:
                val = R.randint(-3, 3)
                ops.append(f"1 {l} {r} {val}")
                for i in range(l-1, r):
                    current[i] = current[i] * val % mod
            elif kind == 2:
                val = R.randint(-10, 10)
                ops.append(f"2 {l} {r} {val}")
                for i in range(l-1, r):
                    current[i] = (current[i] + val) % mod
            else:
                ops.append(f"3 {l} {r}")
                want.append(sum(current[l-1:r]) % mod)
        data = f"{n} {q} {mod}\n" + " ".join(map(str, arr)) + "\n" + "\n".join(ops) + "\n"
        assert list(map(int, run(exe, data).split())) == want, data[:300]
    print("segment multiply/add", "180 random")


def test_inverse(td):
    original = PRINT / "05_数学数论" / "逆元——整数与阶乘逆元预处理.cpp"
    source = Path(td) / "inverse_harness.cpp"
    source.write_text(f'''#define main template_main
#include "{original.as_posix()}"
#undef main
int main() {{
  cin >> n >> mod;
  build(n); build();
  for (int i=1;i<=n;i++) cout << inv[i] << ' ' << fac[i] << ' ' << facinv[i] << '\\n';
}}
''', encoding="utf-8")
    exe = Path(td) / "inverse.exe"
    compile_cpp(source, exe)
    for _ in range(100):
        mod = R.choice((101, 1009, 10007, 1000000007))
        n = R.randint(1, min(100, mod-1))
        got = list(map(int, run(exe, f"{n} {mod}\n").split()))
        fac = 1
        for i in range(1, n+1):
            fac = fac * i % mod
            want = [pow(i, -1, mod), fac, pow(fac, -1, mod)]
            assert got[3*(i-1):3*i] == want, (n, mod, i, got[3*(i-1):3*i], want)
    print("inverse tables", "100 random")


def test_coin_change(td):
    exe = Path(td) / "coins.exe"
    compile_cpp(PRINT / "06_动态规划" / "多重背包——限量硬币最少张数及选取数量.cpp", exe)
    for _ in range(220):
        n, amount = R.randint(1, 6), R.randint(0, 35)
        value = [R.randint(1, 12) for _ in range(n)]
        limit = [R.randint(0, 5) for _ in range(n)]
        dp = [10**9] * (amount + 1)
        dp[0] = 0
        for v, c in zip(value, limit):
            old = dp[:]
            dp = [min((old[s-k*v]+k for k in range(c+1) if k*v <= s), default=10**9)
                  for s in range(amount+1)]
        data = f"{n}\n" + " ".join(map(str, value)) + "\n"
        data += " ".join(map(str, limit)) + f"\n{amount}\n"
        got = list(map(int, run(exe, data).split()))
        if dp[amount] == 10**9:
            assert got == [-1], (data, got)
        else:
            counts = got[1:]
            assert got[0] == dp[amount] and len(counts) == n, (data, got, dp[amount])
            assert all(0 <= counts[i] <= limit[i] for i in range(n)), (data, got)
            assert sum(a*b for a, b in zip(value, counts)) == amount
            assert sum(counts) == got[0]
    n, amount = 1, 20000
    assert run(exe, f"{n}\n1\n20000\n{amount}\n").split() == ["20000", "20000"]
    print("bounded coin change", "220 random + max queue")


def test_lucas(td):
    exe = Path(td) / "lucas.exe"
    compile_cpp(PRINT / "05_数学数论" / "Lucas定理——求C(n+m,m)模质数.cpp", exe)
    cases = [(R.randint(0, 100), R.randint(0, 100), R.choice((2, 3, 5, 7, 101)))
             for _ in range(220)]
    data = f"{len(cases)}\n" + "".join(f"{n} {m} {p}\n" for n, m, p in cases)
    got = list(map(int, run(exe, data).split()))
    want = [math.comb(n+m, m) % p for n, m, p in cases]
    assert got == want, next((cases[i], got[i], want[i]) for i in range(len(cases)) if got[i] != want[i])
    print("Lucas", "220 random")


def test_subset_count(td):
    exe = Path(td) / "subset.exe"
    compile_cpp(PRINT / "07_搜索与贪心" / "折半搜索——限重子集计数.cpp", exe)
    for _ in range(100):
        n = R.randint(1, 16)
        arr = [R.randint(0, 20) for _ in range(n)]
        limit = R.randint(0, sum(arr))
        want = sum(sum(arr[i] for i in range(n) if mask >> i & 1) <= limit
                   for mask in range(1 << n))
        data = f"{n} {limit}\n" + " ".join(map(str, arr)) + "\n"
        assert int(run(exe, data)) == want, data
    assert int(run(exe, "40 40\n" + "1 " * 40 + "\n")) == 1 << 40
    print("meet-in-middle subset", "100 random + 2^40 answer")


def test_lct_edge(td):
    exe = Path(td) / "lctedge.exe"
    compile_cpp(PRINT / "02_树上问题" / "LCT——删边后最小生成树瓶颈查询.cpp", exe)
    for _ in range(140):
        n = R.randint(2, 8)
        edges = [(i, R.randrange(1, i), R.randint(1, 30)) for i in range(2, n+1)]
        used = {tuple(sorted((u, v))) for u, v, _ in edges}
        extra = []
        pairs = [(u, v) for u in range(1, n+1) for v in range(u+1, n+1)
                 if (u, v) not in used]
        R.shuffle(pairs)
        for u, v in pairs[:R.randint(0, min(8, len(pairs)))]:
            extra.append((u, v, R.randint(1, 30)))
        edges += extra
        current = {tuple(sorted((u, v))): w for u, v, w in edges}
        deletable = [tuple(sorted((u, v))) for u, v, _ in extra]
        ops, want = [], []
        for _ in range(R.randint(1, 18)):
            if deletable and R.random() < .4:
                pair = deletable.pop(R.randrange(len(deletable)))
                ops.append(f"2 {pair[0]} {pair[1]}")
                del current[pair]
            else:
                x, y = R.sample(range(1, n+1), 2)
                ops.append(f"1 {x} {y}")
                dist = [10**9] * (n+1)
                dist[x] = 0
                for _ in range(n-1):
                    for (u, v), w in current.items():
                        dist[u] = min(dist[u], max(dist[v], w))
                        dist[v] = min(dist[v], max(dist[u], w))
                want.append(dist[y])
        data = f"{n} {len(edges)} {len(ops)}\n"
        data += "".join(f"{u} {v} {w}\n" for u, v, w in edges)
        data += "\n".join(ops) + "\n"
        assert list(map(int, run(exe, data).split())) == want, (data, want)
    print("LCT edge MST bottleneck", "140 random")


def main():
    with tempfile.TemporaryDirectory() as td:
        test_tarjan(td)
        test_basis(td)
        test_interval_graph(td)
        test_euler(td)
        test_bitset(td)
        test_segment_mul_add(td)
        test_inverse(td)
        test_coin_change(td)
        test_lucas(td)
        test_subset_count(td)
        test_lct_edge(td)


if __name__ == "__main__":
    main()
