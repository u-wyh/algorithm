@echo off
cd /d "C:\Luogu"  rem 改用英文路径
set total=0
set count=0

for /r %%i in (*.cpp *.c *.py) do (
    set /a count+=1
    for /f "delims=" %%j in ('type "%%i" 2^>nul ^| find /c /v ""') do (
        set /a total+=%%j
        echo [%%~ni] Lines: %%j
    )
)

echo.
echo ==========================
echo Total files: %count%
echo Total lines: %total%
echo ==========================
pause