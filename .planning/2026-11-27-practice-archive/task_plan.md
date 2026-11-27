# Task Plan: 练习代码归档

## Goal
按原题平台归档练习源码，洛谷按每 500 个题号分段，生成按标签可查的练习题单。

## Next Step
分类和题单已完成。后续可根据用户安排核查 19 份无链接文件或配置收件自动化。

## Current Phase
Phase 5

## Phases

### Phase 1: Requirements & Discovery
- [ ] Understand user intent
- [ ] Identify constraints
- [ ] Document in findings.md
- **Status:** complete

### Phase 2: Planning & Structure
- [ ] Define approach
- [ ] Create project structure
- **Status:** complete

### Phase 3: Implementation
- [ ] Execute the plan
- [ ] Write to files before executing
- **Status:** complete

### Phase 4: Testing & Verification
- [ ] Verify requirements met
- [ ] Document test results
- **Status:** complete

### Phase 5: Delivery
- [ ] Review outputs
- [ ] Deliver to user
- **Status:** complete

## Decisions Made
| Decision | Rationale |
|----------|-----------|
| 当前阶段只读源码 | Gemini 仍在改文件头，先生成预演与说明，待其结束再迁移。 |
| 洛谷每 500 个题号一段 | 例如 P2000-P2499，题号前缀不同则分开。 |
| 先迁移洛谷 | 用户另开进程补其他 OJ 的注释和标签，本轮保持其他 OJ 的源路径。 |

## Errors Encountered
| Error | Resolution |
|-------|------------|
| Codeforces 比赛题的标准链接此前只识别部分路径。 | 在预演里兼容 `/contest/编号/problem/题号` 并通过镜像回归检查。 |
| 第二阶段预演后，另一个进程补写了 37 份源码。 | 移动前按哈希拦截，待批量写入结束后按最新源码重建清单。 |
| 全量题单生成器还引用旧变量 `archive_paths`。 | 改为据最新条目构造预期路径集合，并验证生成结果。 |
