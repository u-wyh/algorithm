import os
import tkinter as tk
from tkinter import filedialog, messagebox, ttk

class CodeCounter:
    def __init__(self, root):
        self.root = root
        self.root.title("代码行数统计工具")
        self.root.geometry("800x600")
        self.root.configure(bg="#ffffff")
        
        # 创建界面
        self.create_widgets()
        
    def create_widgets(self):
        # 标题
        title_label = tk.Label(self.root, text="代码行数统计工具", font=("Arial", 16, "bold"), bg="#f0f0f0", fg="#333")
        title_label.pack(pady=20)
        
        # 选择文件夹按钮
        self.select_button = tk.Button(self.root, text="选择文件夹", command=self.select_directory, 
                                      bg="#4CAF50", fg="white", font=("Arial", 12), padx=20, pady=10)
        self.select_button.pack(pady=10)
        
        # 文件夹路径显示
        self.path_label = tk.Label(self.root, text="未选择文件夹", font=("Arial", 10), bg="#f0f0f0", fg="#666")
        self.path_label.pack(pady=5)
        
        # 统计按钮
        self.count_button = tk.Button(self.root, text="开始统计", command=self.count_lines, 
                                     bg="#2196F3", fg="white", font=("Arial", 12), padx=20, pady=10, state="disabled")
        self.count_button.pack(pady=10)
        
        # 进度条
        self.progress = ttk.Progressbar(self.root, orient="horizontal", length=600, mode="determinate")
        self.progress.pack(pady=10)
        
        # 结果显示区域
        result_frame = tk.Frame(self.root, bg="#f0f0f0")
        result_frame.pack(pady=20, fill="both", expand=True, padx=20)
        
        # 创建表格样式的结果显示
        columns = ("文件类型", "文件数量", "总行数", "平均行数")
        self.tree = ttk.Treeview(result_frame, columns=columns, show="headings", height=8)
        
        for col in columns:
            self.tree.heading(col, text=col)
            self.tree.column(col, width=150, anchor="center")
        
        self.tree.pack(side="left", fill="both", expand=True)
        
        # 滚动条
        scrollbar = ttk.Scrollbar(result_frame, orient="vertical", command=self.tree.yview)
        scrollbar.pack(side="right", fill="y")
        self.tree.configure(yscrollcommand=scrollbar.set)
        
        # 总计信息
        self.total_label = tk.Label(self.root, text="", font=("Arial", 12, "bold"), bg="#f0f0f0", fg="#333")
        self.total_label.pack(pady=10)
        
    def select_directory(self):
        self.directory = filedialog.askdirectory(title="选择要统计的文件夹")
        if self.directory:
            self.path_label.config(text=self.directory)
            self.count_button.config(state="normal")
        
    def count_lines(self):
        if not hasattr(self, 'directory'):
            return
            
        # 重置进度条
        self.progress["value"] = 0
        
        # 定义要统计的文件扩展名
        extensions = ['.cpp', '.c', '.py']
        
        # 初始化统计结果
        results = {ext: {"count": 0, "lines": 0} for ext in extensions}
        
        # 获取所有文件
        all_files = []
        for root_dir, _, files in os.walk(self.directory):
            for file in files:
                if any(file.endswith(ext) for ext in extensions):
                    all_files.append(os.path.join(root_dir, file))
        
        total_files = len(all_files)
        if total_files == 0:
            messagebox.showinfo("结果", "未找到任何.cpp、.c或.py文件")
            return
            
        # 更新进度条
        self.progress["maximum"] = total_files
        
        # 清空树形视图
        for item in self.tree.get_children():
            self.tree.delete(item)
            
        # 统计每个文件的行数
        for i, file_path in enumerate(all_files):
            try:
                with open(file_path, 'r', encoding='utf-8') as f:
                    lines = sum(1 for _ in f)
            except:
                try:
                    with open(file_path, 'r', encoding='gbk') as f:
                        lines = sum(1 for _ in f)
                except:
                    lines = 0
                    
            # 更新对应扩展名的统计
            for ext in extensions:
                if file_path.endswith(ext):
                    results[ext]["count"] += 1
                    results[ext]["lines"] += lines
                    break
                    
            # 更新进度条
            self.progress["value"] = i + 1
            self.root.update_idletasks()
        
        # 计算总计
        total_count = sum(results[ext]["count"] for ext in extensions)
        total_lines = sum(results[ext]["lines"] for ext in extensions)
        
        # 显示结果
        for ext in extensions:
            if results[ext]["count"] > 0:
                avg_lines = results[ext]["lines"] / results[ext]["count"]
                self.tree.insert("", "end", values=(
                    ext, 
                    results[ext]["count"], 
                    results[ext]["lines"], 
                    f"{avg_lines:.1f}"
                ))
        
        # 显示总计信息
        self.total_label.config(text=f"文件总数: {total_count}  总代码行数: {total_lines}")

# 创建主窗口
root = tk.Tk()
app = CodeCounter(root)
root.mainloop()