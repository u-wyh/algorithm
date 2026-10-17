"""把用户已确认要打印的 C++ 文件排版为一份合订 PDF。"""

from pathlib import Path

from pypdf import PdfReader, PdfWriter

from render_cpp_print_preview import render


ROOT = Path(r"D:\algorithm")
PRINT = ROOT / "可打印算法模板"
OLD = Path(r"C:\Users\wyh15\Documents\code\C++\打印的模板")
TEMP = ROOT / "tmp" / "pdfs" / "selected_booklet_work"
DESTINATION = ROOT / "output" / "pdf" / "已选算法模板——合订打印.pdf"

# 每项是（首页左侧所属系列、右上角算法名、原样排版的 .cpp）。
SELECTED = [
    ("分块", "时间分块——历史时刻数", PRINT / "08_离线分治" / "时间分块——位置值达到阈值的历史时刻数.cpp"),
    ("分块", "根号分治——模下标求和与修改", PRINT / "08_离线分治" / "根号分治——模下标求和与单点修改.cpp"),
    ("莫队", "树上莫队——路径不同数", PRINT / "08_离线分治" / "树上莫队——路径不同数计数.cpp"),
    ("字符串", "随机权重集合哈希——频次整除", PRINT / "05_数学数论" / "随机权重集合哈希——区间频次整除判定.cpp"),
    ("数学数论", "扩展欧拉定理——大指数模幂", PRINT / "05_数学数论" / "扩展欧拉定理——大指数模幂.cpp"),
    ("数学数论", "exBSGS——离散对数", PRINT / "05_数学数论" / "exBSGS离散对数.cpp"),
    ("数学数论", "高斯消元——实数方程组", PRINT / "05_数学数论" / "高斯消元——实数方程组.cpp"),
    ("数学数论", "线性基——路径最大异或和", PRINT / "05_数学数论" / "线性基——图路径最大异或和.cpp"),
    ("数学数论", "双变量整除分块——互质数对（原版 P3455）", OLD / "莫比乌斯" / "莫比乌斯函数——模板.cpp"),
    ("数学数论", "NTT——多模数卷积（原版 P4245）", OLD / "NTT" / "NTT——多模数.cpp"),
    ("数学数论", "NTT——多项式求逆（原版 P4238）", OLD / "NTT" / "NTT——多项式求逆.cpp"),
    ("数学数论", "康托展开——排列排名", PRINT / "05_数学数论" / "康托展开——排列排名.cpp"),
    ("数学数论", "SG 函数——分糖豆博弈", PRINT / "05_数学数论" / "SG函数——分糖豆博弈.cpp"),
    ("数学数论", "0/1 分数规划——删 k 项", PRINT / "05_数学数论" / "01分数规划——删k项最大化比值.cpp"),
    ("点分治", "点分治——是否存在指定距离点对", PRINT / "02_树上问题" / "点分治——查询是否存在指定距离的点对.cpp"),
    ("点分治", "点分治——距离不超过 K 的点对", PRINT / "02_树上问题" / "点分治——统计距离不超过K的点对.cpp"),
    ("点分治", "点分树——修改点权与距离内求和", PRINT / "02_树上问题" / "点分树——点权修改与距离内求和.cpp"),
    ("线段树分治", "时间线段树分治——动态连通性", PRINT / "08_离线分治" / "时间线段树分治——动态连通性.cpp"),
    ("网络流", "Dinic 最大流", PRINT / "01_图论" / "Dinic最大流.cpp"),
    ("网络流", "最小费用最大流——Dijkstra 增广", PRINT / "01_图论" / "最小费用最大流——Dijkstra增广.cpp"),
    ("网络流", "上下界网络流——有源汇最大流", PRINT / "01_图论" / "上下界网络流——有源汇最大流.cpp"),
    ("网络流", "上下界网络流——无源汇可行流", PRINT / "01_图论" / "上下界网络流——无源汇可行流及各边流量.cpp"),
    ("网络流", "最小割——最少删除顶点", PRINT / "01_图论" / "最小割——拆点求最少删除顶点.cpp"),
    ("Tarjan", "强连通分量（B3609）", PRINT / "01_图论" / "Tarjan强连通分量.cpp"),
    ("Tarjan", "边双连通分量（原版 P8436）", ROOT / "templates" / "01_图论" / "tarjan" / "边双" / "P8436.cpp"),
    ("Tarjan", "点双连通分量（原版 P8435）", ROOT / "templates" / "01_图论" / "tarjan" / "点双" / "P8435.cpp"),
]


def main() -> None:
    assert len(SELECTED) == 26
    assert len({source.resolve() for _, _, source in SELECTED}) == len(SELECTED)
    for _, _, source in SELECTED:
        assert source.is_file() and source.suffix.lower() == ".cpp", source
    TEMP.mkdir(parents=True, exist_ok=True)
    DESTINATION.parent.mkdir(parents=True, exist_ok=True)
    writer = PdfWriter()
    temporary_pdfs = []
    total_pages = 0
    for i, (series, title, source) in enumerate(SELECTED, 1):
        temporary = TEMP / f"section_{i:02d}.pdf"
        pages = render(source, temporary, series, title)
        temporary_pdfs.append(temporary)
        writer.append(str(temporary))
        writer.add_outline_item(f"{i:02d} {series}｜{title}", total_pages)
        total_pages += pages
        print(f"{i:02d}\t{pages} pages\t{source}")
    with DESTINATION.open("wb") as stream:
        writer.write(stream)
    assert len(PdfReader(str(DESTINATION)).pages) == total_pages
    for temporary in temporary_pdfs:
        temporary.unlink()
    TEMP.rmdir()
    print(f"TOTAL\t{len(SELECTED)} files\t{total_pages} pages\t{DESTINATION}")


if __name__ == "__main__":
    main()
