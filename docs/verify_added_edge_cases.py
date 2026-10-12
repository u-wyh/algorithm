"""检验高精度、二维树状数组和 2-SAT 的操作语义。"""

from pathlib import Path
from random import Random
from tempfile import TemporaryDirectory
from itertools import combinations
import subprocess

ROOT = Path(r"D:\algorithm\可打印算法模板")
RNG = Random(851031)


def build(source: Path, exe: Path) -> None:
    result = subprocess.run(["g++", "-std=c++17", "-O2", str(source), "-o", str(exe)], capture_output=True)
    if result.returncode:
        raise RuntimeError(result.stderr[-1000:])


def run(exe: Path, data: str) -> str:
    result = subprocess.run([str(exe)], input=data, text=True, capture_output=True, timeout=5)
    if result.returncode:
        raise RuntimeError(result.stderr[-500:])
    return result.stdout.strip()


def main() -> None:
    tests = 0
    with TemporaryDirectory() as directory:
        temp = Path(directory)
        high = ROOT / "05_数学数论/高精度——非负整数四则运算.cpp"
        high_harness = temp / "high.cpp"
        high_harness.write_text(
            '#define main old_main\n#include "' + high.as_posix() + '"\n#undef main\n'
            'int main(){std::string a,b;while(std::cin>>a>>b){auto x=strToNum(a),y=strToNum(b);'
            'std::cout<<numToStr(add(x,y))<<" "<<numToStr(mul(x,y))<<" "'
            '<<numToStr(div(x,y))<<"\\n";}}', encoding="utf-8"
        )
        high_exe = temp / "high.exe"
        build(high_harness, high_exe)
        for _ in range(45):
            a = RNG.randrange(10 ** RNG.randint(1, 25))
            b = RNG.randrange(1, 10 ** RNG.randint(1, 15))
            got = run(high_exe, f"{a} {b}\n").split()
            assert got == [str(a + b), str(a * b), str(a // b)]
            tests += 1

        bit = ROOT / "04_数据结构/二维树状数组——单点加矩形和.cpp"
        bit_harness = temp / "bit.cpp"
        bit_harness.write_text(
            '#define main old_main\n#include "' + bit.as_posix() + '"\n#undef main\n'
            'int main(){std::cin>>n>>m;int q;std::cin>>q;while(q--){int op;std::cin>>op;'
            'if(op==1){int x,y,v;std::cin>>x>>y>>v;update(x,y,v);}else{int a,b,c,d;'
            'std::cin>>a>>b>>c>>d;std::cout<<sumRegion(a,b,c,d)<<"\\n";}}}',
            encoding="utf-8"
        )
        bit_exe = temp / "bit.exe"
        build(bit_harness, bit_exe)
        for _ in range(35):
            n, m = RNG.randint(1, 7), RNG.randint(1, 7)
            mat = [[0] * m for _ in range(n)]
            ops, want = [], []
            for _ in range(40):
                if RNG.randrange(2):
                    x, y, val = RNG.randrange(n), RNG.randrange(m), RNG.randint(-100, 100)
                    mat[x][y] = val
                    ops.append(f"1 {x} {y} {val}")
                else:
                    a, c = sorted((RNG.randrange(n), RNG.randrange(n)))
                    b, d = sorted((RNG.randrange(m), RNG.randrange(m)))
                    want.append(sum(mat[x][y] for x in range(a, c + 1) for y in range(b, d + 1)))
                    ops.append(f"2 {a} {b} {c} {d}")
            data = f"{n} {m} {len(ops)}\n" + "\n".join(ops) + "\n"
            assert list(map(int, run(bit_exe, data).split())) == want
            tests += 1

        sat_exe = temp / "sat.exe"
        build(ROOT / "01_图论/2-SAT——可满足性判定.cpp", sat_exe)
        for _ in range(45):
            n = RNG.randint(1, 6)
            clauses = [(RNG.randrange(n), RNG.randrange(n), RNG.randrange(2), RNG.randrange(2)) for _ in range(RNG.randint(0, 15))]
            want = any(all(not (((mask >> a) & 1) == ca and ((mask >> b) & 1) == cb)
                           for a, b, ca, cb in clauses) for mask in range(1 << n))
            data = f"{n} {len(clauses)}\n" + "\n".join(" ".join(map(str, x)) for x in clauses) + "\n"
            assert run(sat_exe, data) == ("YES" if want else "NO")
            tests += 1

        fraction_exe = temp / "fraction.exe"
        build(ROOT / "05_数学数论/01分数规划——删k项最大化比值.cpp", fraction_exe)
        for _ in range(300):
            n = RNG.randint(1, 7)
            take = RNG.randint(1, n)
            numerators = [RNG.randint(0, 100) for _ in range(n)]
            denominators = [RNG.randint(1, 100) for _ in range(n)]
            best = max(sum(numerators[i] for i in selection) / sum(denominators[i] for i in selection)
                       for selection in combinations(range(n), take))
            data = f"{n} {n-take}\n" + " ".join(map(str, numerators)) + "\n"
            data += " ".join(map(str, denominators)) + "\n0 0\n"
            assert int(run(fraction_exe, data)) == int(100 * best + 0.5)
            tests += 1

    print(f"compiled=4 functional_cases={tests}")


if __name__ == "__main__":
    main()
