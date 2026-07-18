# 仓库整体结构分析

- 仓库根目录：`D:/algorithm`
- 顶层目录：

  | 顶层目录 | 文件数 |
  | --- | --- |
  | `洛谷` | 3134 |
  | `templates` | 845 |
  | `README.md` | 1 |

## 1. 扩展名分布

| 扩展名 | 文件数 |
| --- | --- |
| `.cpp` | 3191 |
| `.c` | 715 |
| `.py` | 25 |
| `.pdf` | 21 |
| `.jpg` | 8 |
| `.exe` | 5 |
| `.zip` | 3 |
| `.bat` | 2 |
| `.docx` | 2 |
| `.md` | 2 |
| `.ofd` | 2 |
| `.txt` | 2 |
| `<no-ext>` | 2 |

## 2. `templates/` 子目录

| 子目录 | 文件数 | 主要扩展名 |
| --- | --- | --- |
| `动态规划` | 141 | `.cpp`=84, `.c`=57 |
| `数学` | 91 | `.cpp`=79, `.c`=12 |
| `其他` | 57 | `.c`=32, `.cpp`=25 |
| `分块 莫队` | 53 | `.cpp`=53 |
| `图论` | 48 | `.cpp`=48 |
| `线段树` | 39 | `.cpp`=39 |
| `树上问题` | 34 | `.cpp`=34 |
| `tarjan` | 30 | `.cpp`=30 |
| `平衡树` | 25 | `.cpp`=25 |
| `并查集` | 20 | `.cpp`=15, `.c`=5 |
| `点分治` | 20 | `.cpp`=20 |
| `贪心算法` | 18 | `.c`=17, `.cpp`=1 |
| `哈希` | 15 | `.cpp`=15 |
| `前缀树` | 14 | `.cpp`=14 |
| `树状数组` | 14 | `.cpp`=14 |
| `线段树分治` | 14 | `.cpp`=14 |
| `博弈论` | 13 | `.cpp`=10, `.c`=3 |
| `树链剖分` | 13 | `.cpp`=13 |
| `CDQ分治` | 12 | `.cpp`=12 |
| `单调队列单调栈` | 12 | `.cpp`=12 |
| `整体二分` | 12 | `.cpp`=12 |
| `KMP` | 11 | `.cpp`=11 |
| `搜索` | 11 | `.cpp`=6, `.c`=5 |
| `AC自动机` | 10 | `.cpp`=10 |
| `左偏树` | 10 | `.cpp`=10 |
| `Manacher` | 9 | `.cpp`=9 |
| `线段树合并与分裂` | 9 | `.cpp`=9 |
| `网络流` | 9 | `.cpp`=9 |
| `kruskal重构树` | 8 | `.cpp`=8 |
| `差分前缀和` | 8 | `.cpp`=8 |
| `树上启发式合并` | 7 | `.cpp`=7 |
| `树套树` | 7 | `.cpp`=7 |
| `twosat` | 6 | `.cpp`=6 |
| `倍增st表` | 6 | `.cpp`=6 |
| `扩展KMP` | 6 | `.cpp`=6 |
| `虚树` | 6 | `.cpp`=6 |
| `01分数规划` | 5 | `.cpp`=5 |
| `数论` | 5 | `.cpp`=5 |
| `二分图` | 4 | `.cpp`=4 |
| `欧拉回路` | 3 | `.cpp`=3 |
| `优化求LCA` | 2 | `.cpp`=2 |
| `后缀数组 后缀自动机` | 2 | `.cpp`=2 |
| `边分治` | 2 | `.cpp`=2 |
| `README.md` | 1 | `.md`=2 |
| `code.docx` | 1 | `.docx`=1 |
| `count.py` | 1 | `.py`=1 |
| `count_all.bat` | 1 | `.bat`=1 |

## 3. `templates/` 中含 `main` 的文件

- 模板目录共 **845** 个文件，其中带 `main` 的有 **785** 个。
- 严格意义上的“算法模板”通常不写 `main` 也不读入整段样例。下面这些文件被识别为带 `main`，疑似是题目代码混入模板区，需要进一步人工确认：

  - `templates/01分数规划/01分数规划——模板.cpp`
  - `templates/01分数规划/01分数规划——模板4.cpp`
  - `templates/01分数规划/01分数规划——模板5.cpp`
  - `templates/01分数规划/01分数规划——结合最小生成树.cpp`
  - `templates/01分数规划/01分数规划——部分参数有限制.cpp`
  - `templates/AC自动机/AC自动机——01分数规划.cpp`
  - `templates/AC自动机/AC自动机——fail树.cpp`
  - `templates/AC自动机/AC自动机——fail树上差分.cpp`
  - `templates/AC自动机/AC自动机——出现统计.cpp`
  - `templates/AC自动机/AC自动机——完备状态.cpp`
  - `templates/AC自动机/AC自动机——应用.cpp`
  - `templates/AC自动机/AC自动机——模板.cpp`
  - `templates/AC自动机/AC自动机——综合应用.cpp`
  - `templates/AC自动机/AC自动机——警报标记.cpp`
  - `templates/AC自动机/基于AC自动机实现的文章词频检测.cpp`
  - `templates/CDQ分治/CDQ分治——三维偏序.cpp`
  - `templates/CDQ分治/CDQ分治——二维空间计数.cpp`
  - `templates/CDQ分治/CDQ分治——优化dp模板.cpp`
  - `templates/CDQ分治/CDQ分治——优化动态规划.cpp`
  - `templates/CDQ分治/CDQ分治——加速计算.cpp`
  - `templates/CDQ分治/CDQ分治——动态逆序对.cpp`
  - `templates/CDQ分治/CDQ分治——四维偏序.cpp`
  - `templates/CDQ分治/CDQ分治——四维偏序优化dp.cpp`
  - `templates/CDQ分治/CDQ分治——坐标变换.cpp`
  - `templates/CDQ分治/CDQ分治——添加和查询.cpp`
  - `templates/CDQ分治/CDQ分治——范围窗口.cpp`
  - `templates/CDQ分治/CDQ分治——静态二维空间.cpp`
  - `templates/KMP/KMP算法——1based.cpp`
  - `templates/KMP/KMP算法——next数组优化.cpp`
  - `templates/KMP/KMP算法——删除s2.cpp`
  - `templates/KMP/KMP算法——数位dp.cpp`
  - `templates/KMP/KMP算法——最短循环节.cpp`
  - `templates/KMP/KMP算法——树上匹配.cpp`
  - `templates/KMP/KMP算法——模板.cpp`
  - `templates/KMP/失配树——1based模板.cpp`
  - `templates/KMP/失配树——应用.cpp`
  - `templates/KMP/失配树——模板.cpp`
  - `templates/kruskal重构树/kruskal重构树——dfn序st表.cpp`
  - `templates/kruskal重构树/kruskal重构树——到达z个不同点.cpp`
  - `templates/kruskal重构树/kruskal重构树——可持久化线段树.cpp`
  - `templates/kruskal重构树/kruskal重构树——最大树.cpp`
  - `templates/kruskal重构树/kruskal重构树——最小生成树.cpp`
  - `templates/kruskal重构树/kruskal重构树——模板.cpp`
  - `templates/kruskal重构树/kruskal重构树——线段树.cpp`
  - `templates/kruskal重构树/kruskal重构树——结合dijkstra.cpp`
  - `templates/Manacher/Manacher算法——划分子串.cpp`
  - `templates/Manacher/Manacher算法——前k乘积.cpp`
  - `templates/Manacher/Manacher算法——双回文子串.cpp`
  - `templates/Manacher/Manacher算法——反演.cpp`
  - `templates/Manacher/Manacher算法——回文串数量.cpp`
  - `templates/Manacher/Manacher算法——模板.cpp`
  - `templates/Manacher/回文自动机——fail指针.cpp`
  - `templates/Manacher/回文自动机——模板.cpp`
  - `templates/tarjan/tarjan——LCA应用.cpp`
  - `templates/tarjan/tarjan——LCA模板.cpp`
  - `templates/tarjan/tarjan——割点模板.cpp`
  - `templates/tarjan/tarjan——并查集.cpp`
  - `templates/tarjan/tarjan——桥模板.cpp`
  - `templates/tarjan/tarjan——点双连通分量.cpp`
  - `templates/tarjan/tarjan——线段树优化建边.cpp`
  - `templates/tarjan/tarjan——缩点.cpp`
  - `templates/tarjan/tarjan——边双缩点.cpp`
  - `templates/tarjan/tarjan——边双连通分量.cpp`
  - `templates/tarjan/圆方树——模板.cpp`
  - `templates/tarjan/强连通分量/强连通分量——出入度.cpp`
  - `templates/tarjan/强连通分量/强连通分量——动态规划.cpp`
  - `templates/tarjan/强连通分量/强连通分量——模板.cpp`
  - `templates/tarjan/点双/割点——应用.cpp`
  - `templates/tarjan/点双/割点——模板.cpp`
  - `templates/tarjan/点双/圆方树——模板.cpp`
  - `templates/tarjan/点双/圆方树——虚树.cpp`
  - `templates/tarjan/点双/圆方树——重链剖分.cpp`
  - `templates/tarjan/点双/点双——圆桌.cpp`
  - `templates/tarjan/点双/点双——模板.cpp`
  - `templates/tarjan/边双/temp.cpp`
  - `templates/tarjan/边双/割边——应用.cpp`
  - `templates/tarjan/边双/割边——模板.cpp`
  - `templates/tarjan/边双/边双——trail.cpp`
  - `templates/tarjan/边双/边双——并查集.cpp`
  - `templates/tarjan/边双/边双——树的直径.cpp`
  - `templates/tarjan/边双/边双——模板.cpp`
  - `templates/tarjan/边双/边双——边差分.cpp`
  - `templates/twosat/twosat——前缀优化建图.cpp`
  - `templates/twosat/twosat——模板.cpp`
  - `templates/twosat/twosat——经典.cpp`
  - `templates/twosat/twosat——输出方案.cpp`
  - `templates/twosat/twosat——输出方案模板.cpp`
  - `templates/twosat/twosat——输出方案模板2.cpp`
  - `templates/二分图/二分图——HK算法.cpp`
  - `templates/二分图/二分图——匈牙利算法.cpp`
  - `templates/二分图/二分图——最大匹配.cpp`
  - `templates/二分图/匈牙利算法.cpp`
  - `templates/优化求LCA/优化LCA——dfn序.cpp`
  - `templates/优化求LCA/优化LCA——欧拉序.cpp`
  - `templates/倍增st表/倍增和st表——前缀差分.cpp`
  - `templates/倍增st表/倍增和st表——基础.cpp`
  - `templates/倍增st表/倍增和st表——并查集.cpp`
  - `templates/倍增st表/倍增和st表——最大公约数.cpp`
  - `templates/倍增st表/倍增和st表——查询最值.cpp`
  - `templates/倍增st表/倍增和st表——模板.cpp`
  - `templates/其他/dfn序——综合应用.cpp`
  - `templates/其他/KM算法——指派问题.cpp`
  - `templates/其他/LCA——三节点.cpp`
  - `templates/其他/ODT树——应用.cpp`
  - `templates/其他/tsp结合三进制状压.cpp`
  - `templates/其他/三分——模板.cpp`
  - `templates/其他/二分图——染色法判断.cpp`
  - `templates/其他/二分法——吃香蕉.c`
  - `templates/其他/二分法——找到最左大于一个数的数字.c`
  - `templates/其他/二分法——找峰值.c`
  - `templates/其他/二分法——最小数对距离.c`
  - `templates/其他/二分法——机器人跳跃.c`
  - `templates/其他/二分法——杀死怪物.c`
  - `templates/其他/二分法——水温.c`
  - `templates/其他/二分法——电脑充电.c`
  - `templates/其他/二分法——画匠问题.c`
  - `templates/其他/二分法——等待时间.c`
  - `templates/其他/二分法——结合树上问题.cpp`
  - `templates/其他/二叉树.c`
  - `templates/其他/二叉树——前中后遍历.c`
  - `templates/其他/二进位制打印.c`
  - `templates/其他/位图——模板.cpp`
  - `templates/其他/位图——状态压缩.cpp`
  - `templates/其他/位运算的加减乘除.c`
  - `templates/其他/位运算的神奇操作.c`
  - `templates/其他/前缀信息——最长和值.cpp`
  - `templates/其他/双指针——奇偶数位.cpp`
  - `templates/其他/双指针——快慢指针.cpp`
  - `templates/其他/启发式合并.cpp`
  - `templates/其他/带权二分——应用.cpp`
  - `templates/其他/带权二分——恰好k个.cpp`
  - `templates/其他/带权二分——模板.cpp`
  - `templates/其他/异或的神奇操作.c`
  - `templates/其他/归并分治.c`
  - `templates/其他/归并排序.c`
  - `templates/其他/扫描线——区间长度.cpp`
  - `templates/其他/扫描线——天际线.cpp`
  - `templates/其他/扫描线——天际线2.cpp`
  - `templates/其他/排序——三傻排序.c`
  - `templates/其他/排序——三大高级排序.c`
  - `templates/其他/排序——基数排序.c`
  - `templates/其他/排序——堆排序.c`
  - `templates/其他/排序——随机快速排序.c`
  - `templates/其他/排序——随机快速排序2.c`
  - `templates/其他/搜索——n皇后.c`
  - `templates/其他/极大化思想最大子矩阵.cpp`
  - `templates/其他/枚举子集——卡常.cpp`
  - `templates/其他/社会基尼系数.c`
  - `templates/其他/线段最小覆盖问题.cpp`
  - `templates/其他/递归函数.c`
  - `templates/其他/高精度——乘法.c`
  - `templates/其他/高精度——减法.c`
  - `templates/其他/高精度——加法.c`
  - `templates/其他/高精度——除法（高对低）.c`
  - `templates/其他/高精度——除法（高对高）.c`
  - `templates/分块 莫队/分块/分块——bfs.cpp`
  - `templates/分块 莫队/分块/分块——块长优化.cpp`
  - `templates/分块 莫队/分块/分块——并查集.cpp`
  - `templates/分块 莫队/分块/分块——序列结合树上.cpp`
  - `templates/分块 莫队/分块/分块——散整块讨论.cpp`
  - `templates/分块 莫队/分块/分块——节点分块.cpp`
  - `templates/分块 莫队/分块/双层分块——基数排序.cpp`
  - `templates/分块 莫队/分块/双层分块——模板.cpp`
  - `templates/分块 莫队/分块/块状链表——模板.cpp`
  - `templates/分块 莫队/分块/并查集分块——可撤销并查集.cpp`
  - `templates/分块 莫队/分块/并查集分块——可撤销并查集2.cpp`
  - `templates/分块 莫队/分块/并查集分块——并查集块分析.cpp`
  - `templates/分块 莫队/分块/时间分块——序列.cpp`
  - `templates/分块 莫队/分块/普通分块——众数.cpp`
  - `templates/分块 莫队/分块/普通分块——众数优化.cpp`
  - `templates/分块 莫队/分块/普通分块——区间增加.cpp`
  - `templates/分块 莫队/分块/普通分块——单点修改.cpp`
  - `templates/分块 莫队/分块/普通分块——频率偶数个数.cpp`
  - `templates/分块 莫队/分块/树上分块——重链序列分块.cpp`
  - `templates/分块 莫队/分块/树上分块——随机撒点.cpp`
  - `templates/分块 莫队/分块/根号分治——二分.cpp`
  - `templates/分块 莫队/分块/根号分治——分块.cpp`
  - `templates/分块 莫队/分块/根号分治——动态规划.cpp`
  - `templates/分块 莫队/分块/根号分治——最短路.cpp`
  - `templates/分块 莫队/分块/根号分治——树形dp.cpp`
  - `templates/分块 莫队/分块/根号分治——模板.cpp`
  - `templates/分块 莫队/分块/根号分治——等差数列.cpp`
  - `templates/分块 莫队/分块/根号分治——轻重点.cpp`
  - `templates/分块 莫队/分块/根号分治——长链剖分.cpp`
  - `templates/分块 莫队/莫队/只删回滚莫队——模板.cpp`
  - `templates/分块 莫队/莫队/只删回滚莫队——链表.cpp`
  - `templates/分块 莫队/莫队/只增回滚莫队——前缀和.cpp`
  - `templates/分块 莫队/莫队/只增回滚莫队——区间距离.cpp`
  - `templates/分块 莫队/莫队/只增回滚莫队——模板.cpp`
  - `templates/分块 莫队/莫队/带修莫队——mex.cpp`
  - `templates/分块 莫队/莫队/带修莫队——模板.cpp`
  - `templates/分块 莫队/莫队/带修莫队——词频.cpp`
  - `templates/分块 莫队/莫队/树上莫队——带修莫队.cpp`
  - `templates/分块 莫队/莫队/树上莫队——模板.cpp`
  - `templates/分块 莫队/莫队/莫队——众数次数.cpp`
  - `templates/分块 莫队/莫队/莫队——位图.cpp`
  - `templates/分块 莫队/莫队/莫队——哈希.cpp`
  - `templates/分块 莫队/莫队/莫队——根号分治.cpp`
  - `templates/分块 莫队/莫队/莫队——模板.cpp`
  - `templates/分块 莫队/莫队/莫队——线段树.cpp`
  - `templates/分块 莫队/莫队/莫队——链表.cpp`
  - `templates/分块 莫队/莫队/莫队二次离线——分块.cpp`
  - `templates/分块 莫队/莫队/莫队二次离线——方式二.cpp`
  - `templates/分块 莫队/莫队/莫队二次离线——根号分治.cpp`
  - `templates/分块 莫队/莫队/莫队二次离线——模板.cpp`
  - `templates/前缀树/前缀树——前k大异或值之和.cpp`
  - `templates/前缀树/前缀树——异或最大值.cpp`
  - `templates/前缀树/前缀树——搜索字符(2).cpp`
  - `templates/前缀树/前缀树——搜索字符.cpp`
  - `templates/前缀树/前缀树——树形dp.cpp`
  - `templates/前缀树/前缀树——模板.cpp`
  - `templates/前缀树/前缀树——贪心.cpp`
  - `templates/前缀树/前缀树——通配符.cpp`
  - `templates/前缀树/可持久化前缀树——01trie.cpp`
  - `templates/前缀树/可持久化前缀树——dfn序.cpp`
  - `templates/前缀树/可持久化前缀树——trie模版.cpp`
  - `templates/前缀树/可持久化前缀树——二维异或值第k大.cpp`
  - `templates/前缀树/可持久化前缀树——次大值的异或.cpp`
  - `templates/前缀树/可持久化前缀树——结合可持久化线段树.cpp`
  - `templates/动态规划/三进制状压dp.cpp`
  - `templates/动态规划/三进制状压dp2.cpp`
  - `templates/动态规划/动态规划——01背包.c`
  - `templates/动态规划/动态规划——一和零.c`
  - `templates/动态规划/动态规划——三角形之积最小.c`
  - `templates/动态规划/动态规划——不相邻元素最大累加和.c`
  - `templates/动态规划/动态规划——中括号和小括号.c`
  - `templates/动态规划/动态规划——主附件.c`
  - `templates/动态规划/动态规划——二叉树结构.c`
  - `templates/动态规划/动态规划——优惠与预期.c`
  - `templates/动态规划/动态规划——俄罗斯套娃信封.c`
  - `templates/动态规划/动态规划——俄罗斯套娃信封2.c`
  - `templates/动态规划/动态规划——切棍子.c`
  - `templates/动态规划/动态规划——卖股票获利.c`
  - `templates/动态规划/动态规划——反转后的最大累加和.c`
  - `templates/动态规划/动态规划——合并石头.c`
  - `templates/动态规划/动态规划——回文串数量.c`
  - `templates/动态规划/动态规划——处理后效性.cpp`
  - `templates/动态规划/动态规划——多重背包.c`
  - `templates/动态规划/动态规划——多重背包.cpp`
  - `templates/动态规划/动态规划——子序列问题.c`
  - `templates/动态规划/动态规划——字典序最小的递增子序列.c`
  - `templates/动态规划/动态规划——完全背包.c`
  - `templates/动态规划/动态规划——寻找单词.c`
  - `templates/动态规划/动态规划——干草问题.c`
  - `templates/动态规划/动态规划——快速最长递增子序列.cpp`
  - `templates/动态规划/动态规划——悬线法.cpp`
  - `templates/动态规划/动态规划——戳气球.c`
  - `templates/动态规划/动态规划——拼合字符.c`
  - `templates/动态规划/动态规划——插入字符形成回文串.c`
  - `templates/动态规划/动态规划——数位dp——windy数.c`
  - `templates/动态规划/动态规划——数位dp——丑数.c`
  - `templates/动态规划/动态规划——数位dp——丑数优化.c`
  - `templates/动态规划/动态规划——数位dp——互不相同的数字.c`
  - `templates/动态规划/动态规划——数位dp——分配重复数字.c`
  - `templates/动态规划/动态规划——数位dp——合成不超过n的数字.c`
  - `templates/动态规划/动态规划——数位dp——非连续1.c`
  - `templates/动态规划/动态规划——数码个数.c`
  - `templates/动态规划/动态规划——无重叠三个最大子数组之和.c`
  - `templates/动态规划/动态规划——最低票价.c`
  - `templates/动态规划/动态规划——最大字符串长度.c`
  - `templates/动态规划/动态规划——最大环形两段和.cpp`
  - `templates/动态规划/动态规划——最小路径和.c`
  - `templates/动态规划/动态规划——最长公共子序列.c`
  - `templates/动态规划/动态规划——最长公共子序列.cpp`
  - `templates/动态规划/动态规划——最长有效括号长度.c`
  - `templates/动态规划/动态规划——最长递增子序列长度.c`
  - `templates/动态规划/动态规划——最长递增数字串长度.c`
  - `templates/动态规划/动态规划——树形dp  bst.cpp`
  - `templates/动态规划/动态规划——树形dp  bst求和.cpp`
  - `templates/动态规划/动态规划——树形dp  dfn序.cpp`
  - `templates/动态规划/动态规划——树形dp  区间和.cpp`
  - `templates/动态规划/动态规划——树形dp  字符.cpp`
  - `templates/动态规划/动态规划——树形dp  油耗.cpp`
  - `templates/动态规划/动态规划——树形dp  监视.cpp`
  - `templates/动态规划/动态规划——树形dp  直径.cpp`
  - `templates/动态规划/动态规划——树形dp  移金币.cpp`
  - `templates/动态规划/动态规划——树形dp  舞会.cpp`
  - `templates/动态规划/动态规划——树形dp  选课.cpp`
  - `templates/动态规划/动态规划——树形dp  高度.cpp`
  - `templates/动态规划/动态规划——求余除7.c`
  - `templates/动态规划/动态规划——涂木板.c`
  - `templates/动态规划/动态规划——状压dp.cpp`
  - `templates/动态规划/动态规划——状压dp——tsp问题.c`
  - `templates/动态规划/动态规划——状压dp——拼火柴.c`
  - `templates/动态规划/动态规划——状态压缩——好子集.c`
  - `templates/动态规划/动态规划——相邻元素最大乘积.c`
  - `templates/动态规划/动态规划——相邻元素最大累加和.c`
  - `templates/动态规划/动态规划——累加和接近一半.c`
  - `templates/动态规划/动态规划——组合数字小于n.c`
  - `templates/动态规划/动态规划——统计整数.c`
  - `templates/动态规划/动态规划——编辑距离.c`
  - `templates/动态规划/动态规划——股票交易（k次交易）.c`
  - `templates/动态规划/动态规划——股票交易（两次交易）.c`
  - `templates/动态规划/动态规划——股票交易（手续费）.c`
  - `templates/动态规划/动态规划——解码方法.c`
  - `templates/动态规划/动态规划——超长最长公共子序列.cpp`
  - `templates/动态规划/动态规划——选择数字.c`
  - `templates/动态规划/动态规划——重复利用结合dfs.cpp`
  - `templates/动态规划/动态规划——预测赢家.c`
  - `templates/动态规划/动态规划优化.cpp`
  - `templates/动态规划/动态规划优化——优化转移方程.cpp`
  - `templates/动态规划/动态规划优化——倍增优化.cpp`
  - `templates/动态规划/动态规划优化——公共字符串.cpp`
  - `templates/动态规划/动态规划优化——单调sumsum.cpp`
  - `templates/动态规划/动态规划优化——单调刷木板.cpp`
  - `templates/动态规划/动态规划优化——单调收集能量.cpp`
  - `templates/动态规划/动态规划优化——单调求和.cpp`
  - `templates/动态规划/动态规划优化——单调移动.cpp`
  - `templates/动态规划/动态规划优化——单调跳跃.cpp`
  - `templates/动态规划/动态规划优化——单调运货.cpp`
  - `templates/动态规划/动态规划优化——开会.cpp`
  - `templates/动态规划/动态规划优化——扔鸡蛋.cpp`
  - `templates/动态规划/动态规划优化——放珠子.cpp`
  - `templates/动态规划/动态规划优化——放盘子.cpp`
  - `templates/动态规划/动态规划优化——最近与次近.cpp`
  - `templates/动态规划/动态规划优化——来回多次变一次.cpp`
  - `templates/动态规划/动态规划优化——枚举二进制位.cpp`
  - `templates/动态规划/动态规划优化——树二维.cpp`
  - `templates/动态规划/动态规划优化——树数字和.cpp`
  - `templates/动态规划/动态规划优化——树求和.cpp`
  - `templates/动态规划/动态规划优化——树相邻字符.cpp`
  - `templates/动态规划/动态规划优化——苹果盘子.cpp`
  - `templates/动态规划/动态规划优化——重复次数.cpp`
  - `templates/动态规划/动态规划优化——预处理——开会时间.cpp`
  - `templates/动态规划/动态规划优化——预处理——枚举状态.cpp`
  - `templates/动态规划/动态规划优化——预处理——结构转换.cpp`
  - `templates/动态规划/动态规划优化——预处理——还原.cpp`
  - `templates/动态规划/区间dp——断环为链.cpp`
  - `templates/动态规划/区间dp——释放囚犯.cpp`
  - `templates/动态规划/多重背包——单调队列优化.cpp`
  - `templates/动态规划/数位dp——不连续的1.cpp`
  - `templates/动态规划/数位dp——数码统计.cpp`
  - `templates/动态规划/数位dp——模板.cpp`
  - `templates/动态规划/数位dp——模板2.cpp`
  - `templates/动态规划/数位dp——没有重复数字.cpp`
  - `templates/动态规划/数位dp——统计整数.cpp`
  - `templates/动态规划/数位dp——萌数.cpp`
  - `templates/动态规划/树形dp——最低覆盖.cpp`
  - `templates/动态规划/树的直径——树形dp.cpp`
  - `templates/动态规划/状压dp——tsp问题.cpp`
  - `templates/动态规划/状压dp——分配.cpp`
  - `templates/动态规划/状压dp——分配喜欢的帽子.cpp`
  - `templates/动态规划/状压dp——划分成k个组.cpp`
  - `templates/动态规划/状压dp——模板.cpp`
  - `templates/动态规划/状压dp——火柴拼接正方形.cpp`
  - `templates/动态规划/状压dp——账单.cpp`
  - `templates/动态规划/轮廓线dp——国王.cpp`
  - `templates/动态规划/轮廓线dp——模板.cpp`
  - `templates/动态规划/轮廓线dp——贴瓷砖.cpp`
  - `templates/动态规划/轮廓线dp——贴瓷砖空间压缩.cpp`
  - `templates/动态规划/轮廓线dp——颜色.cpp`
  - `templates/动态规划/轮廓线dp——颜色空间压缩.cpp`
  - `templates/单调队列单调栈/单调栈——区间最小值之和.cpp`
  - `templates/单调队列单调栈/单调栈——大鱼吃小鱼.cpp`
  - `templates/单调队列单调栈/单调栈——字典序最小.cpp`
  - `templates/单调队列单调栈/单调栈——底层分析.cpp`
  - `templates/单调队列单调栈/单调栈——底层分析矩形个数.cpp`
  - `templates/单调队列单调栈/单调栈——最大矩形面积.cpp`
  - `templates/单调队列单调栈/单调栈——模板.cpp`
  - `templates/单调队列单调栈/单调队列——不等式最大值.cpp`
  - `templates/单调队列单调栈/单调队列——二分结合贪心.cpp`
  - `templates/单调队列单调栈/单调队列——二维.cpp`
  - `templates/单调队列单调栈/单调队列——模板.cpp`
  - `templates/单调队列单调栈/单调队列——限制值.cpp`
  - `templates/博弈论/博弈论——ED游戏.c`
  - `templates/博弈论/博弈论——sg两堆巴什博奕.cpp`
  - `templates/博弈论/博弈论——sg函数.cpp`
  - `templates/博弈论/博弈论——sg函数打表找规律.cpp`
  - `templates/博弈论/博弈论——三堆石头斐波那契.c`
  - `templates/博弈论/博弈论——二维博弈论.c`
  - `templates/博弈论/博弈论——反常游戏.cpp`
  - `templates/博弈论/博弈论——威佐夫博弈.cpp`
  - `templates/博弈论/博弈论——尼姆博弈.cpp`
  - `templates/博弈论/博弈论——巴什博奕扩展.cpp`
  - `templates/博弈论/博弈论——斐波那契博弈.cpp`
  - `templates/后缀数组 后缀自动机/后缀数组——模板.cpp`
  - `templates/后缀数组 后缀自动机/后缀自动机——模板.cpp`
  - `templates/哈希/哈希——字符串哈希值.cpp`
  - `templates/哈希/哈希——循环节.cpp`
  - `templates/哈希/哈希——算法模板.cpp`
  - `templates/哈希/哈希——通配符.cpp`
  - `templates/哈希/哈希——重叠检验子串.cpp`
  - `templates/哈希/哈希——随机权值.cpp`
  - `templates/哈希/随机化——异或.cpp`
  - `templates/图论/01bfs——模板.cpp`
  - `templates/图论/01bfs——模板升级.cpp`
  - `templates/图论/DJ算法——分层最短路.cpp`
  - `templates/图论/DJ算法——分层最短路模板.cpp`
  - `templates/图论/DJ算法——分层最短路类似状压.cpp`
  - `templates/图论/DJ算法——多源最短路.cpp`
  - `templates/图论/DJ算法——最小化路径最大值.cpp`
  - `templates/图论/DJ算法——最短路模版.cpp`
  - `templates/图论/DJ算法——次短路问题.cpp`
  - `templates/图论/floyd算法——修改边权.cpp`
  - `templates/图论/floyd算法——更新点.cpp`
  - `templates/图论/floyd算法——本质应用.cpp`
  - `templates/图论/floyd算法——模板.cpp`
  - `templates/图论/分层最短路.cpp`
  - `templates/图论/分层最短路——01bfs.cpp`
  - `templates/图论/分层最短路——层际连边.cpp`
  - `templates/图论/同余最短路——01bfs.cpp`
  - `templates/图论/同余最短路——DJ算法.cpp`
  - `templates/图论/同余最短路——DJ算法2.cpp`
  - `templates/图论/同余最短路——二次转圈法.cpp`
  - `templates/图论/同余最短路——二次转圈结合背包.cpp`
  - `templates/图论/图——邻接表.cpp`
  - `templates/图论/图论——Astar.cpp`
  - `templates/图论/图论——A星展示.cpp`
  - `templates/图论/图论——A星（k短路）模板.cpp`
  - `templates/图论/图论——bellman(SPFA).cpp`
  - `templates/图论/图论——bellman2  必须k次.cpp`
  - `templates/图论/图论——IDA星应用.cpp`
  - `templates/图论/图论——IDA星模板.cpp`
  - `templates/图论/图论——IDA星（进阶）.cpp`
  - `templates/图论/图论——spfa模板.cpp`
  - `templates/图论/差分约束——两种形式综合.cpp`
  - `templates/图论/差分约束——模板形式一.cpp`
  - `templates/图论/差分约束——模板形式二.cpp`
  - `templates/图论/差分约束——结合floyd.cpp`
  - `templates/图论/差分约束——限制性超级源点.cpp`
  - `templates/图论/拓扑排序——最多员工数量.cpp`
  - `templates/图论/拓扑排序——求最长公共路径.cpp`
  - `templates/图论/拓扑排序——结合前缀树.cpp`
  - `templates/图论/树上换根——最短路.cpp`
  - `templates/图论/欧拉图——应用.cpp`
  - `templates/图论/欧拉图——欧拉路径模板.cpp`
  - `templates/图论/欧拉图——欧拉路径模板（无向图）.cpp`
  - `templates/图论/线段树优化建图——模板.cpp`
  - `templates/图论/线段树优化建图——虚点.cpp`
  - `templates/左偏树/k短路——左偏树.cpp`
  - `templates/左偏树/可持久化左偏树.cpp`
  - `templates/左偏树/可持久化左偏树2.cpp`
  - `templates/左偏树/左偏树——删除任意节点模板.cpp`
  - `templates/左偏树/左偏树——单调栈.cpp`
  - `templates/左偏树/左偏树——合并堆.cpp`
  - `templates/左偏树/左偏树——启发式合并.cpp`
  - `templates/左偏树/左偏树——大根堆.cpp`
  - `templates/左偏树/左偏树——懒更新.cpp`
  - `templates/左偏树/左偏树——模板.cpp`
  - `templates/差分前缀和/前缀和——01正方形.cpp`
  - `templates/差分前缀和/前缀和——二维前缀和.cpp`
  - `templates/差分前缀和/差分——一维模板.cpp`
  - `templates/差分前缀和/差分——二维应用.cpp`
  - `templates/差分前缀和/差分——二维模板.cpp`
  - `templates/差分前缀和/差分——求和.cpp`
  - `templates/差分前缀和/差分——等差数列.cpp`
  - `templates/差分前缀和/差分——等差数列升级.cpp`
  - `templates/平衡树/AVL树——模板.cpp`
  - `templates/平衡树/FHQ treap——区间移动.cpp`
  - `templates/平衡树/FHQ treap——区间翻转.cpp`
  - `templates/平衡树/FHQ treap——可持久化平衡树.cpp`
  - `templates/平衡树/FHQ treap——可持久化线段树.cpp`
  - `templates/平衡树/FHQ treap——有序表.cpp`
  - `templates/平衡树/FHQ treap——词频不压缩版.cpp`
  - `templates/平衡树/FHQ treap——词频压缩版.cpp`
  - `templates/平衡树/splay树——全局变量辅助.cpp`
  - `templates/平衡树/splay树——区间移动.cpp`
  - `templates/平衡树/splay树——区间翻转.cpp`
  - `templates/平衡树/splay树——展示.cpp`
  - `templates/平衡树/splay树——有序表.cpp`
  - `templates/平衡树/splay树——模板.cpp`
  - `templates/平衡树/splay树——线段树.cpp`
  - `templates/平衡树/Treap树——模板.cpp`
  - `templates/平衡树/有序表——替罪羊树.cpp`
  - `templates/平衡树/有序表——替罪羊树重构因子测试.cpp`
  - `templates/平衡树/有序表——跳表.cpp`
  - `templates/平衡树/笛卡尔树——方案计数.cpp`
  - `templates/平衡树/笛卡尔树——树的序.cpp`
  - `templates/平衡树/笛卡尔树——模板.cpp`
  - `templates/并查集/可持久化并查集——模板.cpp`
  - `templates/并查集/可撤销并查集——最小生成树.cpp`
  - `templates/并查集/可撤销并查集——模板.cpp`
  - `templates/并查集/可撤销并查集——类似二分图.cpp`
  - `templates/并查集/带权并查集——乘除关系.cpp`
  - `templates/并查集/带权并查集——加减关系.cpp`
  - `templates/并查集/带权并查集——异或关系.cpp`
  - `templates/并查集/带权并查集——模板.cpp`
  - `templates/并查集/带权并查集——模板合理性检验.cpp`
  - `templates/并查集/带权并查集——模板合理性统计.cpp`
  - `templates/并查集/带权并查集——种类关系.cpp`
  - `templates/并查集/并查集——寻找岛屿.c`
  - `templates/并查集/并查集——情侣牵手问题.c`
  - `templates/并查集/并查集——模板.c`
  - `templates/并查集/并查集——模板2.c`
  - `templates/并查集/并查集——正反集.cpp`
  - `templates/并查集/并查集——正反集延伸.cpp`
  - `templates/并查集/并查集——相似字符串.c`
  - `templates/并查集/并查集——结合生成树.cpp`
  - `templates/并查集/并查集——维护序列连通性.cpp`
  - `templates/扩展KMP/扩展KMP(Z算法)——e数组应用.cpp`
  - `templates/扩展KMP/扩展KMP(Z算法)——Z数组应用.cpp`
  - `templates/扩展KMP/扩展KMP(Z算法)——应用.cpp`
  - `templates/扩展KMP/扩展KMP(Z算法)——循环节.cpp`
  - `templates/扩展KMP/扩展KMP(Z算法)——循环节个数.cpp`
  - `templates/扩展KMP/扩展KMP(Z算法)——模板.cpp`
  - `templates/搜索/dfs——结合模拟 等分面积.cpp`
  - `templates/搜索/搜索——dfs经典.cpp`
  - `templates/搜索/搜索——双向广搜.cpp`
  - `templates/搜索/搜索——双向广搜差值绝对值最少.cpp`
  - `templates/搜索/搜索——双向广搜模板.cpp`
  - `templates/搜索/搜索——多源bfs.cpp`
  - `templates/搜索/搜索——数独.c`
  - `templates/搜索/搜索——数独2.c`
  - `templates/搜索/洪水填充——包围的01.c`
  - `templates/搜索/洪水填充——岛屿数量.c`
  - `templates/搜索/洪水填充——最大的岛屿.c`
  - `templates/数学/中国剩余定理——扩展加推理.cpp`
  - `templates/数学/中国剩余定理——扩展模板.cpp`
  - `templates/数学/中国剩余定理——模板.cpp`
  - `templates/数学/中国剩余定理——转换.cpp`
  - `templates/数学/二项式反演——钦定系列结合树上问题.cpp`
  - `templates/数学/二项式反演——钦定系列结合背包.cpp`
  - `templates/数学/二项式反演——错排问题.cpp`
  - `templates/数学/二项式反演——集合计数.cpp`
  - `templates/数学/二项式定理——分割的方法.cpp`
  - `templates/数学/二项式定理——杨辉三角.cpp`
  - `templates/数学/二项式定理——系数.cpp`
  - `templates/数学/二项式定理——组合数.cpp`
  - `templates/数学/卡特兰数——二叉树应用.cpp`
  - `templates/数学/卡特兰数——公式4.cpp`
  - `templates/数学/卡特兰数——因子计数法.cpp`
  - `templates/数学/卡特兰数——左右相乘.cpp`
  - `templates/数学/卡特兰数——模板.cpp`
  - `templates/数学/卡特兰数——路径计数模板.cpp`
  - `templates/数学/卡特兰数——路径选择.cpp`
  - `templates/数学/卢卡斯定理——模板.cpp`
  - `templates/数学/原根——模板.cpp`
  - `templates/数学/康拓展开——阶乘进制 逆过程 树状数组.cpp`
  - `templates/数学/康拓展开——阶乘进制 逆过程 线段树.cpp`
  - `templates/数学/快速幂——乘法快速幂.cpp`
  - `templates/数学/快速幂——元音字母.c`
  - `templates/数学/快速幂——取模.c`
  - `templates/数学/快速幂——多米洛和拓米洛.c`
  - `templates/数学/快速幂——斐波那契数列.c`
  - `templates/数学/快速幂——斐波那契数列2.c`
  - `templates/数学/快速幂——泰波那契数.c`
  - `templates/数学/快速幂——爬楼梯.c`
  - `templates/数学/快速幂——矩阵乘法.c`
  - `templates/数学/快速幂——矩阵乘法展示.cpp`
  - `templates/数学/快速幂——矩阵快速幂.cpp`
  - `templates/数学/快速幂——考勤表.c`
  - `templates/数学/扩展欧几里得——一元二次方程.cpp`
  - `templates/数学/扩展欧几里得——区域.cpp`
  - `templates/数学/扩展欧几里得——格点.cpp`
  - `templates/数学/扩展欧几里得——模板.cpp`
  - `templates/数学/扩展欧几里得——洗牌.cpp`
  - `templates/数学/扩展欧几里得——环形.cpp`
  - `templates/数学/扩展欧几里得——算法展示.cpp`
  - `templates/数学/扩展欧几里得——组成.cpp`
  - `templates/数学/扩展欧拉定理——模板.cpp`
  - `templates/数学/数论——全家桶.cpp`
  - `templates/数学/欧拉函数——线性递推欧拉筛.cpp`
  - `templates/数学/矩阵乘法——线段树操作.cpp`
  - `templates/数学/矩阵乘法——经典.cpp`
  - `templates/数学/矩阵乘法——结合图论.cpp`
  - `templates/数学/约瑟夫环.cpp`
  - `templates/数学/约瑟夫环加强.cpp`
  - `templates/数学/线性基——向量模板.cpp`
  - `templates/数学/线性基——向量模板4.cpp`
  - `templates/数学/线性基——向量结合树上倍增.cpp`
  - `templates/数学/线性基——向量结合线段树.cpp`
  - `templates/数学/线性基——异或所有结果个数.cpp`
  - `templates/数学/线性基——异或普通消元法.cpp`
  - `templates/数学/线性基——异或过程展示.cpp`
  - `templates/数学/线性基——异或运算应用.cpp`
  - `templates/数学/线性基——异或高斯消元法.cpp`
  - `templates/数学/莫比乌斯函数——模板.cpp`
  - `templates/数学/裴蜀定理——模板.cpp`
  - `templates/数学/裴蜀定理——类似博弈论.cpp`
  - `templates/数学/质数——Miller-Rabin素数测试.c`
  - `templates/数学/质数——结合数论.cpp`
  - `templates/数学/质数——质数并查集.c`
  - `templates/数学/质数——质数筛.cpp`
  - `templates/数学/质数——较小的数字.c`
  - `templates/数学/逆元——单个除数求逆元.cpp`
  - `templates/数学/逆元——模板.cpp`
  - `templates/数学/逆元——连续数字逆元.cpp`
  - `templates/数学/逆元——连续数字阶乘的逆元.cpp`
  - `templates/数学/高斯消元——加法判断解的情况.cpp`
  - `templates/数学/高斯消元——加法提炼矩阵.cpp`
  - `templates/数学/高斯消元——加法检测错误数据.cpp`
  - `templates/数学/高斯消元——加法模板.cpp`
  - `templates/数学/高斯消元——加法运算展示.cpp`
  - `templates/数学/高斯消元——同余模板.cpp`
  - `templates/数学/高斯消元——同余模板2.cpp`
  - `templates/数学/高斯消元——同余运算展示.cpp`
  - `templates/数学/高斯消元——异或主元与自由元.cpp`
  - `templates/数学/高斯消元——异或模板.cpp`
  - `templates/数学/高斯消元——异或结合位图.cpp`
  - `templates/数学/高斯消元——异或运算展示.cpp`
  - `templates/数学/高精度——模板.cpp`
  - `templates/数论/FFT——迭代版模板.cpp`
  - `templates/数论/FFT——递归版模板.cpp`
  - `templates/整体二分/整体二分——二维1.cpp`
  - `templates/整体二分/整体二分——二维2.cpp`
  - `templates/整体二分/整体二分——带修改.cpp`
  - `templates/整体二分/整体二分——扫描线.cpp`
  - `templates/整体二分/整体二分——最小瓶颈.cpp`
  - `templates/整体二分/整体二分——树上操作.cpp`
  - `templates/整体二分/整体二分——模板1.cpp`
  - `templates/整体二分/整体二分——模板2.cpp`
  - `templates/整体二分/整体二分——破环为链1.cpp`
  - `templates/整体二分/整体二分——破环为链2.cpp`
  - `templates/整体二分/整体二分——线性基.cpp`
  - `templates/整体二分/整体二分——线段树.cpp`
  - `templates/树上启发式合并/树上启发式合并——倍增st表.cpp`
  - `templates/树上启发式合并/树上启发式合并——出现次数信息.cpp`
  - `templates/树上启发式合并/树上启发式合并——向下k层.cpp`
  - `templates/树上启发式合并/树上启发式合并——回文转异或.cpp`
  - `templates/树上启发式合并/树上启发式合并——模板.cpp`
  - `templates/树上启发式合并/树上启发式合并——结合主席树.cpp`
  - `templates/树上启发式合并/树上启发式合并——统计最大次数.cpp`
  - `templates/树上问题/prufer序——堆模板.cpp`
  - `templates/树上问题/prufer序——线性模板.cpp`
  - `templates/树上问题/最小树形图——朱刘算法.cpp`
  - `templates/树上问题/树上倍增——LCA.cpp`
  - `templates/树上问题/树上倍增——LCA迭代.cpp`
  - `templates/树上问题/树上倍增——卡车.cpp`
  - `templates/树上问题/树上倍增——回文.cpp`
  - `templates/树上问题/树上差分——tarjan求lca.cpp`
  - `templates/树上问题/树上差分——倍增求lca.cpp`
  - `templates/树上问题/树上差分——变形应用.cpp`
  - `templates/树上问题/树上差分——点差分模版.cpp`
  - `templates/树上问题/树上差分——边差分.cpp`
  - `templates/树上问题/树上差分——边差分模板.cpp`
  - `templates/树上问题/树上换根——换根.cpp`
  - `templates/树上问题/树上换根——换根2.cpp`
  - `templates/树上问题/树上换根——换根3.cpp`
  - `templates/树上问题/树上换根——距离为k点权和.cpp`
  - `templates/树上问题/树上换根——边权.cpp`
  - `templates/树上问题/树上问题——唯一重心.cpp`
  - `templates/树上问题/树上问题——边权点权求重心.cpp`
  - `templates/树上问题/树上问题——重心.cpp`
  - `templates/树上问题/树上问题——重心1.cpp`
  - `templates/树上问题/树上问题——重心2.cpp`
  - `templates/树上问题/树的直径——两次dfs.cpp`
  - `templates/树上问题/树的直径——加边.cpp`
  - `templates/树上问题/树的直径——区间.cpp`
  - `templates/树上问题/树的直径——并查集.cpp`
  - `templates/树上问题/树的直径——直径公共部分.cpp`
  - `templates/树上问题/生成树——prim算法优化.cpp`
  - `templates/树上问题/生成树——最小生成树k算法.cpp`
  - `templates/树上问题/生成树——最小生成树p算法.cpp`
  - `templates/树上问题/生成树——水井.cpp`
  - `templates/树上问题/生成树——瓶颈数.cpp`
  - `templates/树上问题/生成树倍增LCA.cpp`
  - `templates/树套树/树套树——树状数组套线段树.cpp`
  - `templates/树套树/树套树——树状数组套线段树2.cpp`
  - `templates/树套树/树套树——树状数组套线段树dfn差分.cpp`
  - `templates/树套树/树套树——树状数组套线段树逆序对.cpp`
  - `templates/树套树/树套树——线段树套平衡树.cpp`
  - `templates/树套树/树套树——线段树套开点线段树.cpp`
  - `templates/树套树/树套树——线段树套线段树.cpp`
  - `templates/树状数组/树状数组——二维数组.cpp`
  - `templates/树状数组/树状数组——二维数组模版.cpp`
  - `templates/树状数组/树状数组——区间种类查询.cpp`
  - `templates/树状数组/树状数组——升序三元组.cpp`
  - `templates/树状数组/树状数组——带修改最长不降子序列.cpp`
  - `templates/树状数组/树状数组——最长递增子序列的个数.cpp`
  - `templates/树状数组/树状数组——结合set.cpp`
  - `templates/树状数组/树状数组——范围增加单点查询.cpp`
  - `templates/树状数组/树状数组——范围增加范围查询.cpp`
  - `templates/树状数组/树状数组——范围查询单点增加.cpp`
  - `templates/树状数组/树状数组——进阶逆序对.cpp`
  - `templates/树状数组/树状数组——逆序对数量.cpp`
  - `templates/树链剖分/树链剖分——LCA.cpp`
  - `templates/树链剖分/树链剖分——变换根.cpp`
  - `templates/树链剖分/树链剖分——存在优先级的线段树.cpp`
  - `templates/树链剖分/树链剖分——懒更新.cpp`
  - `templates/树链剖分/树链剖分——模板.cpp`
  - `templates/树链剖分/树链剖分——路径拼接.cpp`
  - `templates/树链剖分/树链剖分——路径查询.cpp`
  - `templates/树链剖分/树链剖分——路径组合.cpp`
  - `templates/树链剖分/树链剖分——边权化点权.cpp`
  - `templates/树链剖分/树链剖分——边权模板.cpp`
  - `templates/树链剖分/长链剖分——动态规划.cpp`
  - `templates/树链剖分/长链剖分——动态规划优化.cpp`
  - `templates/树链剖分/长链剖分——模板.cpp`
  - `templates/欧拉回路/temp.cpp`
  - `templates/欧拉回路/欧拉路径——无向图.cpp`
  - `templates/欧拉回路/欧拉路径——有向图.cpp`
  - `templates/点分治/点分树——二分.cpp`
  - `templates/点分治/点分树——前缀和.cpp`
  - `templates/点分治/点分树——树上开关.cpp`
  - `templates/点分治/点分树——树状数组.cpp`
  - `templates/点分治/点分树——模板.cpp`
  - `templates/点分治/点分树——模板2.cpp`
  - `templates/点分治/点分树——重心移动.cpp`
  - `templates/点分治/点分治——01背包.cpp`
  - `templates/点分治/点分治——bfs.cpp`
  - `templates/点分治/点分治——二分.cpp`
  - `templates/点分治/点分治——单调栈.cpp`
  - `templates/点分治/点分治——哈希前后缀.cpp`
  - `templates/点分治/点分治——树上二分.cpp`
  - `templates/点分治/点分治——线段树.cpp`
  - `templates/点分治/静态点分治——容斥树状数组.cpp`
  - `templates/点分治/静态点分治——容斥模板.cpp`
  - `templates/点分治/静态点分治——树形容斥.cpp`
  - `templates/点分治/静态点分治——模板.cpp`
  - `templates/点分治/静态点分治——距离为k.cpp`
  - `templates/点分治/静态点分治——边数最少.cpp`
  - `templates/线段树/可持久化线段树——上中位数.cpp`
  - `templates/线段树/可持久化线段树——单点修改模板.cpp`
  - `templates/线段树/可持久化线段树——最小自然数.cpp`
  - `templates/线段树/可持久化线段树——查询第k小.cpp`
  - `templates/线段树/可持久化线段树——标记永久化.cpp`
  - `templates/线段树/可持久化线段树——树上dfn.cpp`
  - `templates/线段树/可持久化线段树——树上问题.cpp`
  - `templates/线段树/可持久化线段树——第一次出现.cpp`
  - `templates/线段树/可持久化线段树——范围修改加标记永久化.cpp`
  - `templates/线段树/可持久化线段树——范围修改模板.cpp`
  - `templates/线段树/线段树——二维.cpp`
  - `templates/线段树/线段树——交替子串.cpp`
  - `templates/线段树/线段树——俄罗斯方块.cpp`
  - `templates/线段树/线段树——加和更新操作.cpp`
  - `templates/线段树/线段树——加操作求和.cpp`
  - `templates/线段树/线段树——加操作求最大值.cpp`
  - `templates/线段树/线段树——势能分析.cpp`
  - `templates/线段树/线段树——区间合并.cpp`
  - `templates/线段树/线段树——区间组合查询.cpp`
  - `templates/线段树/线段树——单点修改.cpp`
  - `templates/线段树/线段树——吉如一线段树.cpp`
  - `templates/线段树/线段树——开点线段树.cpp`
  - `templates/线段树/线段树——异或和修改操作.cpp`
  - `templates/线段树/线段树——扫描线——矩形周长并.cpp`
  - `templates/线段树/线段树——扫描线——矩形面积并.cpp`
  - `templates/线段树/线段树——旅馆问题.cpp`
  - `templates/线段树/线段树——更新操作求和.cpp`
  - `templates/线段树/线段树——更新操作求最大值.cpp`
  - `templates/线段树/线段树——最大与次大.cpp`
  - `templates/线段树/线段树——最大与次大2.cpp`
  - `templates/线段树/线段树——等差数列.cpp`
  - `templates/线段树/线段树——结合拓扑排序.cpp`
  - `templates/线段树/线段树——花瓶里的花.cpp`
  - `templates/线段树分治/线段树分治——二分图.cpp`
  - `templates/线段树分治/线段树分治——位图线性基.cpp`
  - `templates/线段树分治/线段树分治——位置轴背包.cpp`
  - `templates/线段树分治/线段树分治——反面教材.cpp`
  - `templates/线段树分治/线段树分治——可持久化前缀树.cpp`
  - `templates/线段树分治/线段树分治——并查集线性基.cpp`
  - `templates/线段树分治/线段树分治——操作排序.cpp`
  - `templates/线段树分治/线段树分治——模板.cpp`
  - `templates/线段树分治/线段树分治——答案贡献.cpp`
  - `templates/线段树分治/线段树分治——答案轴.cpp`
  - `templates/线段树分治/线段树分治——结合01背包.cpp`
  - `templates/线段树分治/线段树分治——继承操作.cpp`
  - `templates/线段树分治/线段树分治——背包递推.cpp`
  - `templates/线段树分治/线段树分治——连通图.cpp`
  - `templates/线段树合并与分裂/线段树分裂——合并与分裂.cpp`
  - `templates/线段树合并与分裂/线段树分裂——模板.cpp`
  - `templates/线段树合并与分裂/线段树合并——dp前后缀.cpp`
  - `templates/线段树合并与分裂/线段树合并——动态规划.cpp`
  - `templates/线段树合并与分裂/线段树合并——差分分析.cpp`
  - `templates/线段树合并与分裂/线段树合并——并查集.cpp`
  - `templates/线段树合并与分裂/线段树合并——树上差分.cpp`
  - `templates/线段树合并与分裂/线段树合并——模板.cpp`
  - `templates/线段树合并与分裂/线段树合并——逆序对.cpp`
  - `templates/网络流/上下界网络流——无源汇可行流.cpp`
  - `templates/网络流/上下界网络流——有源汇最大流.cpp`
  - `templates/网络流/最小费用最大流——spfa.cpp`
  - `templates/虚树/虚树——dijkstra.cpp`
  - `templates/虚树/虚树——倍增.cpp`
  - `templates/虚树/虚树——最小联通树.cpp`
  - `templates/虚树/虚树——树形dp.cpp`
  - `templates/虚树/虚树——模板.cpp`
  - `templates/虚树/虚树——进阶树形dp.cpp`
  - `templates/贪心算法/贪心算法——一天会议.c`
  - `templates/贪心算法/贪心算法——两地调度.c`
  - `templates/贪心算法/贪心算法——修课程.c`
  - `templates/贪心算法/贪心算法——吃橘子.c`
  - `templates/贪心算法/贪心算法——哈夫曼编码.c`
  - `templates/贪心算法/贪心算法——哈夫曼编码2.c`
  - `templates/贪心算法/贪心算法——回文数字.c`
  - `templates/贪心算法/贪心算法——子数组升序.c`
  - `templates/贪心算法/贪心算法——字符转换.c`
  - `templates/贪心算法/贪心算法——最大平均分.c`
  - `templates/贪心算法/贪心算法——水龙头.c`
  - `templates/贪心算法/贪心算法——砍树.c`
  - `templates/贪心算法/贪心算法——组团买票.c`
  - `templates/贪心算法/贪心算法——组队.c`
  - `templates/贪心算法/贪心算法——缩小偏移量.c`
  - `templates/贪心算法/贪心算法——跳跃游戏.c`
  - `templates/贪心算法/贪心算法——过河.c`
  - `templates/边分治/边分治——容斥.cpp`
  - `templates/边分治/边分治——模板.cpp`

## 4. `洛谷/` 子目录

| 子目录 | 文件数 | 主要扩展名 |
| --- | --- | --- |
| `code` | 2773 | `.cpp`=2172, `.c`=584, `.py`=17 |
| `练习赛` | 358 | `.cpp`=308, `.pdf`=21, `.jpg`=8, `.py`=7, `.exe`=5 |
| `.gitattributes` | 1 | `<no-ext>`=1 |
| `count_all.bat` | 1 | `.bat`=1 |
| `temp.cpp` | 1 | `.cpp`=1 |

## 5. 不应提交到 Git 的文件

判断规则：扩展名属于编译产物/缓存/备份/临时文件，或文件名是常见产物名（`a.out`、`core`、`nul` 等）。

共发现 **5** 个疑似遗留产物/临时文件。

| 路径 | 大小 (字节) | 扩展名 |
| --- | --- | --- |
| `洛谷/练习赛/20250628/output/t1.exe` | 210164 | `.exe` |
| `洛谷/练习赛/20250628/output/t3.exe` | 248342 | `.exe` |
| `洛谷/练习赛/20250628/output/t4.exe` | 214653 | `.exe` |
| `洛谷/练习赛/20250628/output/t5.exe` | 247555 | `.exe` |
| `洛谷/练习赛/20250628/output/t7.exe` | 424572 | `.exe` |

## 6. `templates/` 分类规范性观察

- 多数子目录以中文算法名命名（`线段树`、`网络流` 等），便于人类阅读；少数使用英文（`KMP`、`Manacher`、`AC自动机`、`CDQ分治`、`tarjan`、`twosat`、`kruskal重构树`）。
- 个别目录存在轻微大小写或合并写法问题（如 `tarjan` 与 `点分治` 在不同分支、AC 自动机未使用全角空格），如需统一可在重构阶段处理。
- 顶部存在非源码文件：
  - `templates/code.docx`（约 1.4 MB，文档，建议确认是否仍需要）
  - `templates/count.py`、`templates/count_all.bat`
  - `洛谷/count_all.bat`、`洛谷/.gitattributes`、`洛谷/temp.cpp`
- 这些文件不影响功能，但说明历史上有人在仓库根直接放工具脚本，后续可在重构时归类到 `scripts/`。

## 7. 命名/结构观察（仅记录，不处理）

- `洛谷/code/` 与 `洛谷/练习赛/` 是练习题的两条主要入口。
- `洛谷/temp.cpp` 位于 `洛谷/` 顶层，命名上不属于任何一类练习题，可考虑归类为草稿或删除候选。
- 模板与练习的目录层级最深约 2 级，多数文件直接落在子目录根下，重命名空间干净。
- 跨平台问题：仓库中存在 `templates/count.py` 与 `洛谷/count_all.bat`、根 `count_all.bat` 等 Windows/跨平台脚本；脚本本身不参与题解逻辑，无需重写。

## 8. 后续建议（仅供参考，未执行）

- 在 `templates/` 子目录内补充 `README.md`，说明每类模板的用途和典型调用方式。
- 对疑似混入模板目录的题目文件，可在确认后迁回 `洛谷/` 或归档到 `templates/examples/`。
- 对带版本后缀的文件，建议保留一份主版本、其余归档到 `_archive/` 或在文件名中标注提交者/日期。
- 若确认 `templates/code.docx` 不再需要，可在重构阶段删除（本次扫描不会删除任何文件）。
