"""检验 AC fail 树词频与随机权重集合哈希。"""
from collections import Counter
from pathlib import Path
import random
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1] / "可打印算法模板"
R = random.Random(20261015)


def compile_cpp(source, exe):
    result = subprocess.run(["g++", "-std=c++17", "-O2", str(source), "-o", str(exe)],
                            capture_output=True, text=True)
    assert result.returncode == 0, result.stderr[:500]


def run(exe, data, timeout=15):
    result = subprocess.run([str(exe)], input=data, capture_output=True,
                            text=True, timeout=timeout)
    assert result.returncode == 0, (data[:200], result.stderr[:300])
    return result.stdout.split()


def test_fail_tree(td):
    exe = Path(td) / "failtree.exe"
    compile_cpp(ROOT / "03_字符串" / "AC自动机Fail树——打印文本中的模式串出现次数.cpp", exe)
    for _ in range(200):
        current, words, operations = "", [], []
        for _ in range(R.randint(2, 45)):
            choice = R.randrange(4)
            if choice <= 1 or not current:
                ch = R.choice("abc")
                current += ch
                operations.append(ch)
            elif choice == 2:
                current = current[:-1]
                operations.append("B")
            else:
                words.append(current)
                operations.append("P")
        if not words:
            if not current:
                current = "a"
                operations.append("a")
            words.append(current)
            operations.append("P")
        questions = [(R.randint(1, len(words)), R.randint(1, len(words)))
                     for _ in range(R.randint(1, 30))]
        want = []
        for x, y in questions:
            pattern, text = words[x-1], words[y-1]
            want.append(sum(text[i:i+len(pattern)] == pattern
                            for i in range(len(text)-len(pattern)+1)))
        data = "".join(operations) + f"\n{len(questions)}\n"
        data += "".join(f"{x} {y}\n" for x, y in questions)
        assert list(map(int, run(exe, data))) == want, (data, want)
    n = 100000
    data = "a" * n + "P\n1\n1 1\n"
    assert run(exe, data, timeout=35) == ["1"]
    print("AC fail tree: 200 random + 100000-chain")


def test_random_hash(td):
    exe = Path(td) / "randomhash.exe"
    compile_cpp(ROOT / "05_数学数论" / "随机权重集合哈希——区间频次整除判定.cpp", exe)
    for _ in range(150):
        n, q = R.randint(1, 10), R.randint(1, 35)
        initial = [R.randint(-3, 5) for _ in range(n)]
        current, lines, want = initial[:], [], []
        for _ in range(q):
            if R.randrange(3) == 0:
                pos, value = R.randint(1, n), R.randint(-3, 5)
                current[pos-1] = value
                lines.append(f"1 {pos} {value}")
            else:
                left, right = sorted((R.randint(1, n), R.randint(1, n)))
                k = R.randint(1, 5)
                freq = Counter(current[left-1:right])
                want.append("YES" if all(v % k == 0 for v in freq.values()) else "NO")
                lines.append(f"2 {left} {right} {k}")
        data = f"{n} {q}\n" + " ".join(map(str, initial)) + "\n"
        data += "\n".join(lines) + "\n"
        assert run(exe, data) == want, (data, want)
    print("random weight hash: 150 random")


def test_substring_hash(td):
    exe = Path(td) / "substringhash.exe"
    compile_cpp(ROOT / "03_字符串" / "字符串哈希——任意子串相等查询.cpp", exe)
    for _ in range(200):
        n = R.randint(1, 60)
        s = "".join(R.choices("abcde", k=n))
        questions, want = [], []
        for _ in range(30):
            l1, r1 = sorted((R.randint(1, n), R.randint(1, n)))
            l2, r2 = sorted((R.randint(1, n), R.randint(1, n)))
            questions.append(f"{l1} {r1} {l2} {r2}")
            want.append("YES" if s[l1-1:r1] == s[l2-1:r2] else "NO")
        data = s + "\n" + str(len(questions)) + "\n" + "\n".join(questions) + "\n"
        assert run(exe, data) == want, (data, want)
    n = 1000000
    data = "a" * n + "\n2\n1 999999 2 1000000\n1 1 1 2\n"
    assert run(exe, data, timeout=25) == ["YES", "NO"]
    print("substring hash: 200 random + 1000000-length")


if __name__ == "__main__":
    with tempfile.TemporaryDirectory() as td:
        test_fail_tree(td)
        test_random_hash(td)
        test_substring_hash(td)
