"""普通 BSGS 随机检验，exBSGS 穷举小模数，与直接枚举比较。"""
from pathlib import Path
import math
import random
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1] / "可打印算法模板" / "05_数学数论"


def brute(a, mod, b):
    seen, value, x = set(), 1 % mod, 0
    while value not in seen:
        if value == b:
            return x
        seen.add(value)
        value = value * a % mod
        x += 1
    return -1


def compile_cpp(name, td):
    exe = Path(td) / ("exbsgs.exe" if name.startswith("ex") else "bsgs.exe")
    result = subprocess.run(["g++", "-std=c++17", "-O2", str(ROOT / (name + ".cpp")),
                             "-o", str(exe)], capture_output=True, text=True)
    assert result.returncode == 0, result.stderr[:400]
    return exe


def main():
    with tempfile.TemporaryDirectory() as td:
        exe = compile_cpp("BSGS离散对数", td)
        rng = random.Random(34)
        cases = []
        for _ in range(200):
            mod = rng.randrange(2, 1000)
            a, b = rng.randrange(1, mod), rng.randrange(mod)
            if math.gcd(a, mod) == 1:
                cases.append((a, mod, b))
        for a, mod, b in cases:
            result = subprocess.run([str(exe)], input=f"{mod} {a} {b}\n",
                                    capture_output=True, text=True, timeout=5)
            assert result.returncode == 0
            got = -1 if result.stdout.strip() == "no solution" else int(result.stdout)
            assert got == brute(a, mod, b), (a, mod, b, got)
        print("BSGS", len(cases), "cases")

        exe = compile_cpp("exBSGS离散对数", td)
        cases = [(a, mod, b) for mod in range(1, 41)
                 for a in range(mod) for b in range(mod)]
        data = "\n".join(f"{a} {mod} {b}" for a, mod, b in cases) + "\n0 0 0\n"
        result = subprocess.run([str(exe)], input=data, capture_output=True,
                                text=True, timeout=60)
        assert result.returncode == 0, result.stderr[:300]
        got = [-1 if line == "No Solution" else int(line)
               for line in result.stdout.splitlines()]
        want = [brute(a, mod, b) for a, mod, b in cases]
        assert got == want, next((cases[i], got[i], want[i]) for i in range(len(cases))
                                 if got[i] != want[i])
        print("exBSGS", len(cases), "cases")


if __name__ == "__main__":
    main()
