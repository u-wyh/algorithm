# https://www.luogu.com.cn/problem/P2152
# 题意：给定两个正整数 a 和 b，求它们的最大公约数。
# 输出最大公约数。
# 数据范围：0 < a, b <= 10^10000。
# 算法标签：Stein算法
g=0
result=0

def compute(a,b):
    if a==0 or b==0:
        result=a+b
        return 
    while a % 2 == 0 and b % 2 == 0:
        a //= 2
        b //= 2
        g += 1
        
    while a % 2 == 0:
        a //= 2
        
    while b % 2 == 0:
        b //= 2
        
    while a != 0 and b != 0:
        if a > b:
            a = a - b
            while a % 2 == 0:
                a //= 2
        else:
            b = b - a
            while b % 2 == 0:
                b //= 2
    compute(a,b)
                

def main():
    a = int(input())
    b = int(input())
        
    compute(a,b)
                
    result = result * (2 ** g)
    print(result)

if __name__ == '__main__':
    main()