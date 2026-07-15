import sys

def main():
    data = sys.stdin.read().split()
    n = int(data[0])
    m = int(data[1])
    d = float(data[2])
    a1 = float(data[3])
    an = float(data[4])

    if(m==0):
        print("0.000")
        return 
    
    # 如果a1等于d，直接输出d
    if abs(a1 - d) < 1e-9:
        print(f"{d:.3f}")
        return
    
    # 初始化f数组，大小为n（至少需要索引n-1）
    f = [0] * (n + 1)
    f[0] = 0
    f[1] = 1
    
    # 计算f[2]到f[n-1]
    for i in range(2, n):
        f[i] = 2 * f[i-1] + f[i-2]
    
    # 计算中间变量
    an_val = (an - d) / (a1 - d)
    
    a = f[n-2]
    b = f[n-1]
    
    # 根据n的奇偶性计算k
    if n % 2 == 0:
        k = (an_val + a) / b
    else:
        k = (a - an_val) / b
    
    a = f[m-2]
    b = f[m-1]
    
    # 根据m的奇偶性计算kk
    if m % 2 == 0:
        kk = k * b - a
    else:
        kk = a - k * b
    
    # 计算最终结果
    ans = (a1 - d) * kk + d
    print(f"{ans:.3f}")

if __name__ == "__main__":
    main()