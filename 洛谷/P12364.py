def exgcd(a, b):
    if b == 0:
        return (a, 1, 0)
    else:
        d, x1, y1 = exgcd(b, a % b)
        x = y1
        y = x1 - (a // b) * y1
        return (d, x, y)

def multiply(a, b, mod):
    a = a % mod
    if a < 0:
        a += mod
    b = b % mod
    if b < 0:
        b += mod
    ans = 0
    while b > 0:
        if b % 2 == 1:
            ans = (ans + a) % mod
        a = (a * 2) % mod
        b = b // 2
    return ans

def excrt(n, m, r):
    tail = 0
    lcm = 1
    for i in range(1, n + 1):
        b = m[i]
        current_r = r[i]
        c = (current_r - tail) % b
        if c < 0:
            c += b
        # 求解方程：lcm * x + b * y = c
        d, x, y = exgcd(lcm, b)
        if c % d != 0:
            return -1
        mod = b // d
        x0 = multiply(x, c // d, mod)
        tmp = lcm * mod
        tail = (tail + multiply(x0, lcm, tmp)) % tmp
        lcm = tmp
        # Debug print
        # print(f"Step {i}: tail={tail}, lcm={lcm}")
    return tail

def main():
    m = [0] * 50  # m[1..48]
    r = [0,1,2,1,4,5,4,1,2,9,0,5,10,11,14,9,0,11,18,9,11,11,15,17,9,23,20,25,
         16,29,27,25,11,17,4,29,22,37,23,9,1,11,11,33,29,15,5,41,46]  # r[1..48]
    
    # 初始化m数组，m[i] = i+1 for 1<=i<=48
    for i in range(1, 49):
        m[i] = i + 1
    for i in range(2,49):
        result = excrt(i, m, r)
        print(i,result)

if __name__ == "__main__":
    main()