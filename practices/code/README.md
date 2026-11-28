# 练习代码归档

日常练习按平台和题号归档。想集中练一个知识点，可以打开[算法题单](../../docs/按算法标签练习.md)，再到源码文件头查看难度。

| 平台 | 目录 |
| --- | --- |
| 洛谷 | [洛谷](洛谷/) |
| Codeforces、AtCoder | [Codeforces](Codeforces/) · [AtCoder](AtCoder/) |
| HDU、SPOJ、UVa、LeetCode | [HDU](HDU/) · [SPOJ](SPOJ/) · [UVa](UVa/) · [LeetCode](LeetCode/) |
| LibreOJ、QOJ、UOJ | [LibreOJ](LibreOJ/) · [QOJ](QOJ/) · [UOJ](UOJ/) |

洛谷先按 500 个题号分段，每段下再按 100 个题号分目录。例如 P2153 在 [P2000-P2499 / P2100-P2199](洛谷/P2000-P2499/P2100-P2199/) 下。P、B、U、T 各自分段，其他平台的镜像题归到原平台。

文件一般用题号或原题标识命名。同题的独立实现用 `_2`、`_3` 等后缀区分。文件头依次记录原题链接、题意、满分数据范围、难度评分和该版本实际使用的算法。

## 难度评分

评分行写作 `难度评分：分数（来源）`，放在算法标签上一行。同题各版本共用一个分数，算法标签按各自实现填写。

有 Codeforces 官方 rating 的题保留原值。其余题的评分用于跨平台选题，范围为 800–3500，每 100 分一档。

| 文件头中的来源 | 评分方式 |
| --- | --- |
| CF 官方 | 直接使用 [Codeforces 的题目 rating](https://codeforces.com/apiHelp/objects#Problem)。 |
| 洛谷分级换算 | 以[洛谷官方难度](https://help.luogu.com.cn/manual/luogu/problem/difficulty)定档，结合同题源码的算法标签在档内微调。 |
| AtCoder Problems 换算 | 将 [AtCoder Problems 的第三方评级](https://github.com/kenkoooo/AtCoderProblems/blob/main/doc/api.md)分段映射到同一尺度。 |
| LeetCode 分级参考 | 结合 LeetCode 原题的官方难度和解法逐题估分。 |
| 估算 | 根据题意、关键思路和实现难度逐题估分。 |

例如，[CF1706E](Codeforces/CF1706E.cpp) 的 2300 分来自 Codeforces，[QOJ22916](QOJ/QOJ22916.cpp) 的 2200 分是估分。
