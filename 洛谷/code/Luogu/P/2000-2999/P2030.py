import sys
import bisect

def main():
    data = sys.stdin.read().splitlines()
    if not data: 
        return
    
    n, m = map(int, data[0].split())
    names = []
    index = 1
    for i in range(n):
        names.append(data[index].strip())
        index += 1
        
    # 对车辆名字进行排序（区分大小写）
    names.sort()
    
    # 第一部分：使用二分查找处理前缀匹配
    count = 0
    for i in range(m):
        s = data[index].strip()
        index += 1
        
        # 使用bisect_left找到第一个大于等于s的字符串位置
        pos = bisect.bisect_left(names, s)
        
        # 检查找到的字符串是否以s为前缀
        if pos < len(names) and names[pos].startswith(s):
            count += 1
            
    print(count)
    
    # 第二部分：计算排列方案数（斐波那契数列）
    if n == 1:
        print(1)
    elif n == 2:
        print(2)
    else:
        a, b = 1, 2  # f(1)=1, f(2)=2
        for i in range(3, n+1):
            a, b = b, a + b
        print(b)

if __name__ == '__main__':
    main()