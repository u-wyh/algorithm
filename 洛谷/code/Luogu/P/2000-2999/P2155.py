import sys

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    T = int(data[0])
    R_val = int(data[1])
    max_n = 10000000
    is_prime = [True] * (max_n + 1)
    is_prime[0] = is_prime[1] = False
    for i in range(2, int(max_n**0.5) + 1):
        if is_prime[i]:
            for j in range(i * i, max_n + 1, i):
                is_prime[j] = False

    fact = [1] * (max_n + 1)
    fact_without_R = [1] * (max_n + 1)
    primorial = [1] * (max_n + 1)
    primorial_without_R = [1] * (max_n + 1)
    product_minus = [1] * (max_n + 1)

    for i in range(1, max_n + 1):
        fact[i] = fact[i - 1] * i % R_val
        if i == R_val:
            fact_without_R[i] = fact_without_R[i - 1]
        else:
            fact_without_R[i] = fact_without_R[i - 1] * i % R_val

        primorial[i] = primorial[i - 1]
        primorial_without_R[i] = primorial_without_R[i - 1]
        product_minus[i] = product_minus[i - 1]

        if is_prime[i]:
            primorial[i] = primorial[i] * i % R_val
            if i != R_val:
                primorial_without_R[i] = primorial_without_R[i] * i % R_val
            product_minus[i] = product_minus[i] * (i - 1) % R_val

    def mod_inv(a, mod):
        return pow(a, mod - 2, mod)

    index = 2
    out_lines = []
    for _ in range(T):
        N = int(data[index])
        M = int(data[index + 1])
        index += 2
        if R_val > M:
            A = fact[N]
            B = product_minus[M]
            C = primorial[M]
            invC = mod_inv(C, R_val)
            ans = A * B % R_val * invC % R_val
            out_lines.append(str(ans))
        else:
            v = 0
            temp = R_val
            while temp <= N:
                v += N // temp
                if temp > N // R_val:
                    break
                temp *= R_val
            if v >= 2:
                out_lines.append("0")
            else:
                A = fact_without_R[N]
                B = product_minus[M]
                C = primorial_without_R[M]
                invC = mod_inv(C, R_val)
                ans = A * B % R_val * invC % R_val
                out_lines.append(str(ans))
    
    sys.stdout.write("\n".join(out_lines) + "\n")

if __name__ == "__main__":
    main()