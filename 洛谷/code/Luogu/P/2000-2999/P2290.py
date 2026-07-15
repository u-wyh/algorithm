def main():
    n = int(input().strip())
    degs = list(map(int, input().split()))
    
    # 单节点特判
    if n == 1:
        print(1 if degs[0] == 0 else 0)
        return
    
    # 验证节点度数和合法性
    total_deg = sum(degs)
    if total_deg != 2 * (n - 1) or any(d == 0 for d in degs):
        print(0)
        return
    
    # 生成150以内的质数列表
    primes = []
    is_prime = [True] * 151
    is_prime[0] = is_prime[1] = False
    for i in range(2, 151):
        if is_prime[i]:
            primes.append(i)
            for j in range(i*i, 151, i):
                is_prime[j] = False
    
    # 计算阶乘中质因数的指数
    def calc_exponent(x, p):
        cnt = 0
        power = p
        while power <= x:
            cnt += x // power
            power *= p
        return cnt
    
    # 分子：(n-2)! 的质因数指数
    numerator_exp = {p: calc_exponent(n-2, p) for p in primes}
    
    # 分母：∏(d_i-1)! 的质因数指数
    denominator_exp = {p: 0 for p in primes}
    for d in degs:
        x = d - 1
        for p in primes:
            if p > x:
                break
            denominator_exp[p] += calc_exponent(x, p)
    
    # 计算最终结果
    result = 1
    for p in primes:
        exp = numerator_exp[p] - denominator_exp[p]
        if exp < 0:
            print(0)
            return
        
        for _ in range(exp):
            result *= p
    
    print(result)

if __name__ == "__main__":
    main()