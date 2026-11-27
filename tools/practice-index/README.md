# 题单生成工具

从仓库根目录运行下面的命令，即可用现有练习和模板重新生成 `docs` 里的题单。

```powershell
python tools/practice-index/_build_algorithm_practice_list.py
python tools/practice-index/_build_full_practice_index.py
python tools/practice-index/_preview_practice_archive.py --index "docs/按算法标签练习.md"
```

专题学习题单根据模板目录、题号和原题链接整理。全量清单读取题库标签快照，按算法标签练习则读取源码文件头中的标签。
