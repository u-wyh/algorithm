# templates 目标路径冲突报告 (v2)

本报告记录 `docs/_analyze_templates.py` 在为每个文件生成 `proposed_path` 时遇到的目标路径冲突，以及如何消解。

## 1. 验证数据

| 指标 | 值 |
| --- | ---: |
| `current_path` 唯一数 | 841 / 841 |
| `proposed_path` 唯一数 | 841 / 841 |
| `proposed_path` 冲突数（修复后） | 0 |
| 实际遇到冲突的源文件数 | 4 |
| 实际遇到冲突的源文件数 | 4 |
| `collision_status=resolved`（不同 SHA） | 4 |
| `collision_status=duplicate_review`（相同 SHA） | 0 |

## 2. 冲突消解规则

1. **检测**：遍历 841 个文件，按 `proposed_path` 分组，找到组内文件数 ≥ 2 的分组
2. **后缀来源**：
   - 若文件含 Luogu problem URL，取 `Pxxxx` 作为后缀（形如 `[P4450]`）
   - 否则取注释块前 30 行中第一条「干净的」标题（无数学符号 / 无 URL / 非纯数字），截断到 ≤ 16 字符作为后缀
   - 若仍无法确定，使用 SHA-256 前 6 位（形如 `[54e95b]`）
3. **冲突状态判定**：
   - 同组所有文件 SHA-256 相同 → `duplicate_review`（**重复文件，未删除**）
   - SHA-256 不同 → `resolved`（按内容重命名以区分）
4. **不删除原则**：v2 不删除任何文件。即使两个 `圆方树——模板.cpp` 的内容看起来几乎一致（P4320 同题），本次也仅添加后缀、保留两者。

## 3. 实际遇到的冲突组

### 冲突 1: `templates/图论/Tarjan/圆方树/圆方树——模板.cpp`

- 冲突文件数：**2**
- SHA-256 不同：是
- 冲突状态：`resolved`

| 源路径 | 建议新路径 | SHA-256 | 后缀来源 |
| --- | --- | --- | --- |
| `templates/tarjan/圆方树——模板.cpp` | `templates/图论/Tarjan/圆方树/圆方树——模板[54e95b].cpp` | `54e95b35e1f75426…` | `[54e95b]` |
| `templates/tarjan/点双/圆方树——模板.cpp` | `templates/图论/Tarjan/圆方树/圆方树——模板[ea1445].cpp` | `ea1445b2ddeb6eda…` | `[ea1445]` |

### 冲突 2: `templates/数学/数论/莫比乌斯反演/莫比乌斯函数——模板.cpp`

- 冲突文件数：**2**
- SHA-256 不同：是
- 冲突状态：`resolved`

| 源路径 | 建议新路径 | SHA-256 | 后缀来源 |
| --- | --- | --- | --- |
| `templates/数学/莫比乌斯函数——模板.cpp` | `templates/数学/数论/莫比乌斯反演/莫比乌斯函数——模板[P4450].cpp` | `a3b5cda179916af4…` | `[P4450]` |
| `templates/数论/莫比乌斯函数——模板.cpp` | `templates/数学/数论/莫比乌斯反演/莫比乌斯函数——模板[否则是-1].cpp` | `01656440cdd8abf9…` | `[否则是-1]` |

## 4. 已知但未发现冲突的源文件

`templates/` 内部 SHA-256 一致的 3 组文件（仅记录，未删除，未触发冲突）：

| 哈希 | 文件 1 | 文件 2 |
| --- | --- | --- |
| `a92504590c1d3b4a…` | `templates/欧拉回路/temp.cpp` | `templates/欧拉回路/欧拉路径——有向图.cpp` |
| `e3260fda0a8ae3f8…` | `templates/tarjan/边双/temp.cpp` | `templates/tarjan/边双/边双——边差分.cpp` |
| `f3fbfe13168cc9c3…` | `templates/其他/高精度——加法.c` | `templates/其他/高精度——除法（高对高）.c` |

## 5. 后续建议

- `resolved` 冲突的两组（圆方树 × 2、莫比乌斯函数 × 2）已用内容后缀自动区分。**重构阶段请人工选择保留哪一份**（一般建议保留较新 / 注释更详细 / 与现有目录一致的版本）。
- `duplicate_review` 状态本次未触发（v2 没有新增）。
- 任何仍产生冲突的 `proposed_path` 都已在 v2 解决；如未来再新增同名文件，脚本会自动按相同规则追加后缀。
