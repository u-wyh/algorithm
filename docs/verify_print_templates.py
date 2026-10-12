"""Compile and differentially check the printable C++ templates."""
from collections import Counter, deque
from concurrent.futures import ThreadPoolExecutor
from itertools import combinations
from math import gcd, lcm
from pathlib import Path
import bisect
import random
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1] / "可打印算法模板"
R = random.Random(20261012)
COUNTS = Counter()


def run(exes, name, data):
    proc = subprocess.run([str(exes[name])], input=data, text=True,
                          capture_output=True, timeout=12)
    assert proc.returncode == 0, (name, proc.returncode, proc.stderr[:300])
    COUNTS[name] += 1
    return proc.stdout.strip()


def ints(s):
    return list(map(int, s.split()))


def test_graph(ex):
    for _ in range(35):
        n = R.randrange(1, 9)
        m = R.randrange(0, 19)
        s = R.randrange(1, n + 1)
        edges = [(R.randrange(1, n + 1), R.randrange(1, n + 1), R.randrange(0, 30)) for _ in range(m)]
        d = [10**30] * (n + 1)
        d[s] = 0
        for _ in range(n - 1):
            for u, v, w in edges:
                d[v] = min(d[v], d[u] + w)
        want = [-1 if x == 10**30 else x for x in d[1:]]
        data = f"{n} {m} {s}\n" + "".join(f"{u} {v} {w}\n" for u, v, w in edges)
        assert ints(run(ex, "Dijkstra最短路", data)) == want

    for _ in range(35):
        n = R.randrange(1, 8)
        m = R.randrange(0, 18)
        edges = [(R.randrange(1, n + 1), R.randrange(1, n + 1), R.randrange(-5, 25)) for _ in range(m)]
        pa = list(range(n + 1))
        def find(x):
            while pa[x] != x:
                x = pa[x]
            return x
        ans, used = 0, 0
        for u, v, w in sorted(edges, key=lambda e: e[2]):
            a, b = find(u), find(v)
            if a != b:
                pa[a] = b
                ans += w
                used += 1
        want = str(ans) if used == n - 1 else "orz"
        data = f"{n} {m}\n" + "".join(f"{u} {v} {w}\n" for u, v, w in edges)
        assert run(ex, "Prim最小生成树", data) == want

    for _ in range(30):
        n = R.randrange(2, 8)
        m = R.randrange(0, 16)
        edges = [(R.randrange(1, n + 1), R.randrange(1, n + 1), R.randrange(0, 8)) for _ in range(m)]
        want = 10**30
        for mask in range(1 << (n - 2)):
            side = {1} | {v for v in range(2, n) if mask >> (v - 2) & 1}
            want = min(want, sum(w for u, v, w in edges if u in side and v not in side))
        data = f"{n} {m} 1 {n}\n" + "".join(f"{u} {v} {w}\n" for u, v, w in edges)
        assert ints(run(ex, "Dinic最大流", data)) == [want]

    for _ in range(30):
        n = R.randrange(1, 9)
        edges = [(u, v) for u in range(1, n + 1) for v in range(1, n + 1) if R.randrange(4) == 0]
        reach = [[False] * (n + 1) for _ in range(n + 1)]
        for i in range(1, n + 1): reach[i][i] = True
        for u, v in edges: reach[u][v] = True
        for k in range(1, n + 1):
            for i in range(1, n + 1):
                for j in range(1, n + 1):
                    reach[i][j] |= reach[i][k] and reach[k][j]
        groups = {frozenset(j for j in range(1, n + 1) if reach[i][j] and reach[j][i]) for i in range(1, n + 1)}
        data = f"{n} {len(edges)}\n" + "".join(f"{u} {v}\n" for u, v in edges)
        lines = run(ex, "Tarjan强连通分量", data).splitlines()
        assert int(lines[0]) == len(groups)
        assert {frozenset(ints(line)) for line in lines[1:]} == groups

    for _ in range(35):
        n = R.randrange(1, 9)
        edges = [(R.randrange(1, n + 1), R.randrange(1, n + 1)) for _ in range(R.randrange(0, 16))]
        def components(removed):
            g = [[] for _ in range(n + 1)]
            for u, v in edges:
                if u != removed and v != removed:
                    g[u].append(v); g[v].append(u)
            seen = set(); count = 0
            for v in range(1, n + 1):
                if v == removed or v in seen: continue
                count += 1; stack = [v]; seen.add(v)
                while stack:
                    for w in g[stack.pop()]:
                        if w not in seen: seen.add(w); stack.append(w)
            return count
        before = components(0)
        want = [v for v in range(1, n + 1) if components(v) > before]
        data = f"{n} {len(edges)}\n" + "".join(f"{u} {v}\n" for u, v in edges)
        got = ints(run(ex, "Tarjan割点", data))
        assert got == [len(want)] + want

    for _ in range(30):
        a, b = R.randrange(1, 7), R.randrange(1, 7)
        edges = [(u, v) for u in range(1, a + 1) for v in range(1, b + 1) if R.randrange(2)]
        adj = [[v for u, v in edges if u == x] for x in range(1, a + 1)]
        def best(i, used):
            if i == a: return 0
            return max([best(i + 1, used)] + [1 + best(i + 1, used | {v}) for v in adj[i] if v not in used])
        data = f"{a} {b} {len(edges)}\n" + "".join(f"{u} {v}\n" for u, v in edges)
        assert ints(run(ex, "HopcroftKarp二分图最大匹配", data)) == [best(0, set())]


def test_tree(ex):
    for _ in range(35):
        n = R.randrange(1, 30); q = 40; root = R.randrange(1, n + 1)
        edges = [(v, R.randrange(1, v)) for v in range(2, n + 1)]
        g = [[] for _ in range(n + 1)]
        for u, v in edges: g[u].append(v); g[v].append(u)
        pa = [0] * (n + 1); dep = [0] * (n + 1); order = [root]; dep[root] = 1
        for u in order:
            for v in g[u]:
                if v != pa[u]: pa[v] = u; dep[v] = dep[u] + 1; order.append(v)
        pairs = [(R.randrange(1, n + 1), R.randrange(1, n + 1)) for _ in range(q)]
        want = []
        for a, b in pairs:
            while dep[a] > dep[b]: a = pa[a]
            while dep[b] > dep[a]: b = pa[b]
            while a != b: a = pa[a]; b = pa[b]
            want.append(a)
        data = f"{n} {q} {root}\n" + "".join(f"{u} {v}\n" for u, v in edges) + "".join(f"{u} {v}\n" for u, v in pairs)
        assert ints(run(ex, "树链剖分求LCA", data)) == want


def test_strings(ex):
    alphabet = "abc"
    for _ in range(45):
        s = "".join(R.choices(alphabet, k=R.randrange(1, 31)))
        p = "".join(R.choices(alphabet, k=R.randrange(1, 9)))
        nxt = [0] * len(p)
        for i in range(1, len(p)):
            nxt[i] = max([k for k in range(1, i + 1) if p[:k] == p[i-k+1:i+1]] or [0])
        occ = [i + 1 for i in range(len(s) - len(p) + 1) if s[i:i+len(p)] == p]
        assert ints(run(ex, "KMP字符串匹配", s + "\n" + p + "\n")) == occ + nxt
        want = max(j - i for i in range(len(s)) for j in range(i + 1, len(s) + 1) if s[i:j] == s[i:j][::-1])
        assert ints(run(ex, "Manacher最长回文子串", s + "\n")) == [want]
        z = [max(k for k in range(len(p) - i + 1) if p[:k] == p[i:i+k]) for i in range(len(p))]
        e = [max(k for k in range(min(len(p), len(s)-i) + 1) if p[:k] == s[i:i+k]) for i in range(len(s))]
        def xorval(values):
            x = 0
            for i, v in enumerate(values, 1): x ^= i * (v + 1)
            return x
        assert ints(run(ex, "Z算法扩展KMP", s + "\n" + p + "\n")) == [xorval(z), xorval(e)]


def test_structures(ex):
    for _ in range(35):
        n = R.randrange(1, 35); initial = [R.randrange(-30, 31) for _ in range(n)]
        ops = []; want = []; arr = initial[:]
        for _ in range(60):
            l = R.randrange(1, n + 1); r = R.randrange(l, n + 1)
            if R.randrange(2):
                v = R.randrange(-30, 31); ops.append(f"1 {l} {v}"); arr[l-1] += v
            else:
                ops.append(f"2 {l} {r}"); want.append(sum(arr[l-1:r]))
        data = f"{n} {len(ops)}\n" + " ".join(map(str, initial)) + "\n" + "\n".join(ops) + "\n"
        assert ints(run(ex, "树状数组单点加区间和", data)) == want

        arr = initial[:]; ops = []; want = []
        for _ in range(60):
            l = R.randrange(1, n + 1); r = R.randrange(l, n + 1)
            if R.randrange(2):
                v = R.randrange(-30, 31); ops.append(f"1 {l} {r} {v}")
                for i in range(l-1, r): arr[i] += v
            else:
                ops.append(f"2 {l} {r}"); want.append(sum(arr[l-1:r]))
        data = f"{n} {len(ops)}\n" + " ".join(map(str, initial)) + "\n" + "\n".join(ops) + "\n"
        assert ints(run(ex, "线段树区间加区间和", data)) == want

        mod = R.randrange(1, 100); arr = [x % mod for x in initial]; ops = []; want = []
        for _ in range(60):
            l = R.randrange(1, n + 1); r = R.randrange(l, n + 1); op = R.randrange(1, 4)
            if op < 3:
                v = R.randrange(0, 100); ops.append(f"{op} {l} {r} {v}")
                for i in range(l-1, r): arr[i] = (arr[i] * v if op == 1 else arr[i] + v) % mod
            else:
                ops.append(f"3 {l} {r}"); want.append(sum(arr[l-1:r]) % mod)
        data = f"{n} {len(ops)} {mod}\n" + " ".join(map(str, initial)) + "\n" + "\n".join(ops) + "\n"
        assert ints(run(ex, "线段树区间乘加区间和", data)) == want

        positive = [R.randrange(1, 1000) for _ in range(n)]
        pairs = [(R.randrange(1, n + 1), R.randrange(1, n + 1)) for _ in range(30)]
        pairs = [(min(a,b), max(a,b)) for a,b in pairs]
        want = []
        for l, r in pairs:
            x = 0
            for v in positive[l-1:r]: x = gcd(x, v)
            want.append(x)
        data = f"{n} {len(pairs)}\n" + " ".join(map(str, positive)) + "\n" + "\n".join(f"{l} {r}" for l,r in pairs) + "\n"
        assert ints(run(ex, "ST表区间GCD", data)) == want


def test_others(ex):
    for _ in range(35):
        a = R.randrange(-10**12, 10**12); b = R.randrange(0, 10000); mod = R.randrange(1, 10**12)
        got = run(ex, "快速幂取模", f"{a} {b} {mod}\n")
        assert int(got.split("=")[-1]) == pow(a, b, mod)

    for n in list(range(1, 80)) + [1000, 10000]:
        got = run(ex, "线性筛质数", f"{n}\n")
        vals = ints(got.replace(":", " "))
        want = sum(x >= 2 and all(x % d for d in range(2, int(x**0.5) + 1)) for x in range(1, n + 1))
        assert vals == [n, want, want, want]

    for _ in range(35):
        n = R.randrange(1, 35); a = R.sample(range(1, n+1), n); b = R.sample(range(1, n+1), n)
        dp = [0] * (n + 1)
        for x in a:
            new = [0] * (n + 1)
            for j, y in enumerate(b, 1): new[j] = dp[j-1] + 1 if x == y else max(dp[j], new[j-1])
            dp = new
        data = f"{n}\n" + " ".join(map(str,a)) + "\n" + " ".join(map(str,b)) + "\n"
        assert ints(run(ex, "排列LCS转LIS", data)) == [dp[n]]

        arr = [R.randrange(-50,51) for _ in range(n)]
        pairs = [(R.randrange(1,n+1), R.randrange(1,n+1)) for _ in range(30)]
        pairs = [(min(l,r), max(l,r)) for l,r in pairs]
        want = [len(set(arr[l-1:r])) for l,r in pairs]
        # SPOJ DQUERY limits values to positive integers.
        positive = [x + 51 for x in arr]
        data = f"{n}\n" + " ".join(map(str,positive)) + f"\n{len(pairs)}\n" + "\n".join(f"{l} {r}" for l,r in pairs) + "\n"
        assert ints(run(ex, "莫队区间不同数", data)) == want

        changes = [(R.randrange(1,n+1), R.randrange(1,n+1), R.randrange(-30,31)) for _ in range(30)]
        changes = [(min(l,r), max(l,r),v) for l,r,v in changes]
        diff = [0]*n
        for l,r,v in changes:
            for i in range(l-1,r): diff[i] += v
        data = f"{n} {len(changes)}\n" + "\n".join(f"{l} {r} {v}" for l,r,v in changes) + "\n"
        assert ints(run(ex, "一维差分区间加", data)) == diff

        rows, cols = R.randrange(1,9), R.randrange(1,9)
        grid = [[R.randrange(3)==0 for _ in range(cols)] for _ in range(rows)]
        sources = [(i,j) for i in range(rows) for j in range(cols) if grid[i][j]]
        want = [min((abs(i-x)+abs(j-y) for x,y in sources), default=-1) for i in range(rows) for j in range(cols)]
        data = f"{rows} {cols}\n" + "\n".join(" ".join(str(int(x)) for x in row) for row in grid) + "\n"
        assert ints(run(ex, "网格多源BFS", data)) == want


def test_math_extra(ex):
    for _ in range(60):
        a = R.randrange(-100000, 100001); mod = R.randrange(1, 10001)
        want = pow(a, -1, mod) if gcd(a, mod) == 1 else -1
        assert ints(run(ex, "扩展欧几里得", f"{a} {mod}\n")) == [want]

    for _ in range(45):
        mods = R.sample([2,3,5,7,11,13], R.randrange(1,5))
        residues = [R.randrange(m) for m in mods]
        limit = 1
        for m in mods: limit *= m
        want = next(x for x in range(limit) if all(x % m == r for m,r in zip(mods,residues)))
        data = str(len(mods)) + "\n" + "".join(f"{m} {r}\n" for m,r in zip(mods,residues))
        assert ints(run(ex, "CRT中国剩余定理", data)) == [want]

    for _ in range(65):
        mods = [R.randrange(1,21) for _ in range(R.randrange(1,6))]
        residues = [R.randrange(m) for m in mods]
        limit = 1
        for m in mods: limit = lcm(limit,m)
        want = next((x for x in range(limit) if all(x%m==r for m,r in zip(mods,residues))),-1)
        data = str(len(mods)) + "\n" + "".join(f"{m} {r}\n" for m,r in zip(mods,residues))
        assert ints(run(ex, "exCRT扩展中国剩余定理", data)) == [want]

    primes = [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47]
    for _ in range(65):
        p = R.choice(primes); a = R.randrange(1,p); b = R.randrange(p)
        want = next((x for x in range(p) if pow(a,x,p)==b),None)
        got = run(ex, "BSGS离散对数", f"{p} {a} {b}\n")
        assert got == (str(want) if want is not None else "no solution")

    cases=[]; want=[]
    for _ in range(140):
        p=R.randrange(2,100); a=R.randrange(p); b=R.randrange(p)
        seen=set(); val=1%p; answer=-1
        for x in range(p+2):
            if val==b: answer=x; break
            if val in seen: break
            seen.add(val); val=val*a%p
        cases.append((a,p,b)); want.append(answer)
    data="".join(f"{a} {p} {b}\n" for a,p,b in cases)+"0 0 0\n"
    got=run(ex,"exBSGS离散对数",data).splitlines()
    assert [(-1 if x=="No Solution" else int(x)) for x in got]==want

    nums=list(range(1,121))+[1000,9999]
    data=str(len(nums))+"\n"+"\n".join(map(str,nums))+"\n"
    want=[sum(gcd(i,n)==1 for i in range(1,n+1)) for n in nums]
    assert ints(run(ex,"欧拉函数",data))==want

    cases=[(R.randrange(1,31),R.randrange(1,31),R.randrange(1,11)) for _ in range(80)]
    data=str(len(cases))+"\n"+"".join(f"{a} {b} {d}\n" for a,b,d in cases)
    want=[sum(gcd(x,y)==d for x in range(1,a+1) for y in range(1,b+1)) for a,b,d in cases]
    assert ints(run(ex,"莫比乌斯反演_互质数对",data))==want

    for _ in range(45):
        n=R.randrange(0,9); m=R.randrange(0,9)
        a=[R.randrange(-10,11) for _ in range(n+1)]
        b=[R.randrange(-10,11) for _ in range(m+1)]
        want=[sum(a[i]*b[k-i] for i in range(n+1) if 0<=k-i<=m) for k in range(n+m+1)]
        data=f"{n} {m}\n"+" ".join(map(str,a))+"\n"+" ".join(map(str,b))+"\n"
        assert ints(run(ex,"FFT多项式乘法",data))==want


def test_structures_extra(ex):
    for _ in range(35):
        arr=[]; ops=[]; want=[]
        for _ in range(90):
            op=R.randrange(1,7)
            if op in (2,4) and not arr: op=1
            x=R.randrange(-20,21)
            if op==1: bisect.insort(arr,x)
            elif op==2:
                x=R.choice(arr); arr.pop(bisect.bisect_left(arr,x))
            elif op==3: want.append(bisect.bisect_left(arr,x)+1)
            elif op==4: x=R.randrange(1,len(arr)+1); want.append(arr[x-1])
            elif op==5:
                i=bisect.bisect_left(arr,x); want.append(arr[i-1] if i else -2147483648)
            else:
                i=bisect.bisect_right(arr,x); want.append(arr[i] if i<len(arr) else 2147483647)
            ops.append((op,x))
        data=str(len(ops))+"\n"+"".join(f"{op} {x}\n" for op,x in ops)
        assert ints(run(ex,"FHQ_Treap普通平衡树",data))==want

    for _ in range(35):
        n=R.randrange(1,14); values=[R.randrange(0,20) for _ in range(n)]
        group=list(range(n)); active=[True]*n; ops=[]; want=[]
        for _ in range(80):
            if R.randrange(2):
                x=R.randrange(n); y=R.randrange(n); ops.append(f"1 {x+1} {y+1}")
                if active[x] and active[y] and group[x]!=group[y]:
                    old,new=group[y],group[x]
                    group=[new if g==old else g for g in group]
            else:
                x=R.randrange(n); ops.append(f"2 {x+1}")
                if not active[x]: want.append(-1)
                else:
                    candidates=[i for i in range(n) if active[i] and group[i]==group[x]]
                    minimum=min(candidates,key=lambda i:(values[i],i))
                    want.append(values[minimum]); active[minimum]=False
        data=f"{n} {len(ops)}\n"+" ".join(map(str,values))+"\n"+"\n".join(ops)+"\n"
        assert ints(run(ex,"左偏树可并堆",data))==want

    for _ in range(35):
        n=R.randrange(1,21); values=[R.randrange(-5,6) for _ in range(n)]
        left=[0]*(n+1); right=[0]*(n+1)
        def build(l,r):
            if l>r: return 0
            root=min(range(l,r+1),key=lambda i:(values[i-1],i))
            left[root]=build(l,root-1); right[root]=build(root+1,r)
            return root
        build(1,n)
        want=[0,0]
        for i in range(1,n+1):
            want[0]^=i*(left[i]+1); want[1]^=i*(right[i]+1)
        data=str(n)+"\n"+" ".join(map(str,values))+"\n"
        assert ints(run(ex,"笛卡尔树",data))==want


def test_lct(ex):
    for _ in range(35):
        n=R.randrange(2,10); initial=[0]+[R.randrange(0,64) for _ in range(n)]
        values=initial[:]; g=[set() for _ in range(n+1)]; ops=[]; want=[]
        def path(a,b):
            todo=deque([a]); parent={a:0}
            while todo:
                u=todo.popleft()
                if u==b: break
                for v in g[u]:
                    if v not in parent: parent[v]=u; todo.append(v)
            if b not in parent: return None
            result=[]
            while b: result.append(b); b=parent[b]
            return result
        for _ in range(90):
            x=R.randrange(1,n+1); y=R.randrange(1,n+1); op=R.randrange(4)
            if op==0:
                p=path(x,y)
                if p is not None:
                    acc=0
                    for v in p: acc^=values[v]
                    ops.append((0,x,y)); want.append(acc); continue
                op=1
            if op==1:
                ops.append((1,x,y))
                if path(x,y) is None: g[x].add(y); g[y].add(x)
            elif op==2:
                ops.append((2,x,y))
                if y in g[x]: g[x].remove(y); g[y].remove(x)
            else:
                y=R.randrange(0,64); ops.append((3,x,y)); values[x]=y
        data=f"{n} {len(ops)}\n"+" ".join(map(str,initial[1:]))+"\n"+"".join(f"{op} {x} {y}\n" for op,x,y in ops)
        assert ints(run(ex,"LCT动态森林",data))==want


def test_trie(tmp):
    source=(ROOT / "03_字符串" / "Trie前缀树.cpp").resolve().as_posix()
    harness=tmp / "trie_harness.cpp"
    harness.write_text('#define main template_main\n#include "'+source+'"\n#undef main\n'
                       '#include <iostream>\nint main(){int op; std::string s;'
                       'while(std::cin>>op){if(op==5){clear();continue;}'
                       'std::cin>>s;if(op==1)insert(s);else if(op==2)std::cout<<search(s)<<"\\n";'
                       'else if(op==3)std::cout<<preword(s)<<"\\n";else erase(s);}}\n',encoding='utf-8')
    exe=tmp / "trie_harness.exe"
    p=subprocess.run(["g++","-std=c++17","-O2",str(harness),"-o",str(exe)],capture_output=True)
    assert p.returncode==0,repr(p.stderr[-500:])
    for _ in range(30):
        state=Counter(); ops=[]; want=[]
        for _ in range(150):
            word="".join(R.choices("abc",k=R.randrange(1,6)))
            op=R.randrange(1,6)
            if op==1: state[word]+=1
            elif op==2: want.append(state[word])
            elif op==3: want.append(sum(v for k,v in state.items() if k.startswith(word)))
            elif op==4:
                if state[word]: state[word]-=1
            else: state.clear()
            ops.append(str(op)+(f" {word}" if op!=5 else ""))
        proc=subprocess.run([str(exe)],input="\n".join(ops)+"\n",text=True,capture_output=True,timeout=10)
        assert proc.returncode==0
        assert ints(proc.stdout)==want
        COUNTS["Trie前缀树"]+=1


def main():
    files = sorted(ROOT.rglob("*.cpp"))
    assert len(files) >= 34
    with tempfile.TemporaryDirectory() as tmp:
        out = Path(tmp)
        def compile_one(item):
            i, path = item
            exe = out / f"test_{i}.exe"
            p = subprocess.run(["g++", "-std=c++17", "-O2", "-Wall", "-Wextra", str(path), "-o", str(exe)], capture_output=True, text=True, encoding="utf-8", errors="replace")
            assert p.returncode == 0, (path.name, p.stderr[-1500:])
            return path.stem, exe
        with ThreadPoolExecutor(max_workers=4) as pool:
            ex = dict(pool.map(compile_one, enumerate(files)))
        test_graph(ex); test_tree(ex); test_strings(ex); test_structures(ex); test_others(ex)
        test_math_extra(ex); test_structures_extra(ex); test_lct(ex); test_trie(out)
        # Long-chain tests catch recursive DFS stack overflow.
        n = 20000
        data = f"{n} {n-1}\n" + "".join(f"{i} {i+1}\n" for i in range(1,n))
        got = ints(run(ex, "Tarjan割点", data))
        assert got[0] == n-2 and got[1] == 2 and got[-1] == n-1
        n = 500000
        data = f"{n} 2 1\n" + "".join(f"{i} {i+1}\n" for i in range(1,n)) + f"1 {n}\n{n-1} {n}\n"
        assert ints(run(ex, "树链剖分求LCA", data)) == [1,n-1]
        print("compiled", len(files), "templates; baseline differential/stress cases", sum(COUNTS.values()))
        for name, count in sorted(COUNTS.items()): print(name, count)


if __name__ == "__main__":
    main()
