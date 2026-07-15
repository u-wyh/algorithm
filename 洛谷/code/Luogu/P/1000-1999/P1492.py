import sys
import math

def prepare(n):
    num = [0] * (n+1)
    prime = []
    cnt = 0
    for i in range(2, n+1):
        if num[i] == 0:
            cnt += 1
            prime.append(i)
            num[i] = i
        j = 0
        while j < cnt and prime[j] * i <= n:
            num[prime[j]*i] = prime[j]
            if i % prime[j] == 0:
                break
            j += 1
    return prime, num

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    m = int(data[1])
    total = n + m
    if n > m:
        n, m = m, n
    
    if total == 0:
        s = '1'.zfill(100)
        for i in range(0, 100, 10):
            print(s[i:i+10])
        return
    
    # 计算组合数C(total, n) = (total)! / (n! * m!)
    primes, num_list = prepare(total)
    
    # 初始化计数数组
    counts = [0] * (total+1)
    for i in range(2, n+1):
        counts[i] -= 1
    for i in range(m+1, total+1):
        counts[i] += 1
    
    # 分解质因数并合并
    for i in range(total, 1, -1):
        if num_list[i] != i:  # 如果是合数
            p = num_list[i]
            q = i // p
            counts[p] += counts[i]
            counts[q] += counts[i]
            counts[i] = 0
    
    # 计算最终结果（只保留后100位）
    M = 10**100  # 用于保留最后100位
    result = 1
    
    # 计算因子2和5的指数
    exp2 = 0
    exp5 = 0
    for p in primes:
        exp = counts[p]
        if exp > 0:
            if p == 2:
                exp2 = exp
            elif p == 5:
                exp5 = exp
    
    # 计算末尾0的个数
    t = min(exp2, exp5)
    if t >= 100:
        for _ in range(10):
            print('0' * 10)
        return
    
    # 计算组合数（去除因子2和5）
    for p in primes:
        exp = counts[p]
        if exp > 0:
            if p == 2:
                exp -= t
            elif p == 5:
                exp -= t
            # 使用快速幂模M计算p^exp
            result = (result * pow(p, exp, M)) % M
    
    # 恢复末尾的0
    result = (result * pow(10, t, M)) % M
    
    # 格式化为100位字符串
    s = str(result)
    if len(s) < 100:
        s = '0' * (100 - len(s)) + s
    else:
        s = s[-100:]
    
    # 每行10位输出
    for i in range(0, 100, 10):
        print(s[i:i+10])

if __name__ == '__main__':
    main()