import math

n, m = map(int, input().split())

sum_num = 0
sum_den = 1

for i in range(1, n + 1):
    denominator = 1
    for j in range(i, i + m):
        denominator *= j
    
    new_num = sum_num * denominator + sum_den
    new_den = sum_den * denominator
    
    common_divisor = math.gcd(new_num, new_den)
    sum_num = new_num // common_divisor
    sum_den = new_den // common_divisor

print(sum_num)
print(sum_den)