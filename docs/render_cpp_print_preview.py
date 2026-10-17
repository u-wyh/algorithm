"""把指定 C++ 模板排成黑白 A4 预览 PDF；原代码保持逐行顺序。"""

from pathlib import Path

from reportlab.lib import colors
from reportlab.lib.pagesizes import A4
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.pdfgen import canvas


ROOT = Path(r"D:\algorithm")
SOURCE_DIR = ROOT / "可打印算法模板" / "01_图论"
OUTPUT_DIR = ROOT / "output" / "pdf"
FONT_DIR = Path(r"C:\Windows\Fonts")

FONT_ASCII = "CascadiaMonoPrint"
FONT_CJK = "SimHeiPrint"
pdfmetrics.registerFont(TTFont(FONT_ASCII, str(FONT_DIR / "CascadiaMono.ttf")))
pdfmetrics.registerFont(TTFont(FONT_CJK, str(FONT_DIR / "simhei.ttf")))

PAGE_WIDTH, PAGE_HEIGHT = A4
CODE_X = 82
NUMBER_X = 49
RIGHT_MARGIN = 34
CODE_SIZE = 8.5
LINE_HEIGHT = 11.1
BOTTOM = 48


def font_for(char: str) -> str:
    return FONT_ASCII if ord(char) < 128 else FONT_CJK


def width_of(char: str, size: float = CODE_SIZE) -> float:
    return pdfmetrics.stringWidth(char, font_for(char), size)


def wrap_line(line: str) -> list[str]:
    line = line.expandtabs(4)
    limit = PAGE_WIDTH - CODE_X - RIGHT_MARGIN
    if not line:
        return [""]
    pieces: list[str] = []
    current = ""
    width = 0.0
    for char in line:
        char_width = width_of(char)
        if current and width + char_width > limit:
            pieces.append(current)
            current = "    " + char
            width = 4 * width_of(" ") + char_width
        else:
            current += char
            width += char_width
    pieces.append(current)
    return pieces


def draw_mixed(c: canvas.Canvas, x: float, y: float, value: str, size: float) -> None:
    if not value:
        return
    run = value[0]
    font = font_for(value[0])
    for char in value[1:]:
        next_font = font_for(char)
        if next_font == font:
            run += char
        else:
            c.setFont(font, size)
            c.drawString(x, y, run)
            x += pdfmetrics.stringWidth(run, font, size)
            run = char
            font = next_font
    c.setFont(font, size)
    c.drawString(x, y, run)


def page_heading(c: canvas.Canvas, series: str, title: str, page: int) -> float:
    c.setFillColor(colors.black)
    if page == 1:
        draw_mixed(c, 49, PAGE_HEIGHT - 39, series, 18)
    label = f"算法：{title}"
    title_size = 10
    title_width = sum(width_of(char, title_size) for char in label)
    draw_mixed(c, PAGE_WIDTH - 33 - title_width, PAGE_HEIGHT - 39, label, title_size)
    c.setStrokeColor(colors.HexColor("#b8b8b8"))
    c.setLineWidth(0.5)
    c.line(49, PAGE_HEIGHT - 53, PAGE_WIDTH - 33, PAGE_HEIGHT - 53)
    c.line(49, 39, PAGE_WIDTH - 33, 39)
    c.setFillColor(colors.HexColor("#555555"))
    c.setFont(FONT_ASCII, 7)
    c.drawString(49, 26, "C++17  |  A4")
    c.drawRightString(PAGE_WIDTH - 33, 26, str(page))
    return PAGE_HEIGHT - 70


def render(source: Path, destination: Path, series: str, title: str | None = None) -> int:
    lines = source.read_text(encoding="utf-8").splitlines()
    display_title = title or source.stem
    c = canvas.Canvas(str(destination), pagesize=A4, pageCompression=1)
    c.setTitle(display_title)
    c.setAuthor("Code template print preview")
    page = 1
    y = page_heading(c, series, display_title, page)
    for number, line in enumerate(lines, 1):
        for part_index, part in enumerate(wrap_line(line)):
            if y < BOTTOM:
                c.showPage()
                page += 1
                y = page_heading(c, series, display_title, page)
            if part_index == 0:
                c.setFillColor(colors.HexColor("#777777"))
                c.setFont(FONT_ASCII, 7)
                c.drawRightString(NUMBER_X + 21, y, str(number))
            c.setFillColor(colors.HexColor("#202020"))
            draw_mixed(c, CODE_X, y, part, CODE_SIZE)
            y -= LINE_HEIGHT
    c.save()
    return page


def main() -> None:
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
    names = [
        "上下界网络流——无源汇可行流及各边流量.cpp",
        "最小割——拆点求最少删除顶点.cpp",
    ]
    for name in names:
        source = SOURCE_DIR / name
        destination = OUTPUT_DIR / f"{source.stem}.pdf"
        pages = render(source, destination, "网络流")
        print(f"{destination}\t{pages} pages\t{len(source.read_text(encoding='utf-8').splitlines())} lines")


if __name__ == "__main__":
    main()
