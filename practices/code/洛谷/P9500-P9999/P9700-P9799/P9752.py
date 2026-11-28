# https://www.luogu.com.cn/problem/P9752
# 题意：密码锁有 5 个 0~9 循环拨圈。
# 从正确密码出发，
# 随机转动仅一次
# （以任意非零幅度单独转动 1 个拨圈，或以相同幅度同时转动 2 个相邻拨圈），
# 得到锁车状态。
# 给定 n 个互不为正确密码的锁车状态，
# 求有多少种可能的正确密码能各自通过一次上述操作得到全部 n 个状态。
# 题意：第一行输入 n，接下来 n 行每行 5 个 0~9 的整数；
# 输出一行一个整数。
# 数据范围：1 <= n <= 8。
# 难度评分：900（洛谷分级换算）
# 算法标签：枚举、集合求交
def main():
    n = int(input().strip())
    states = []
    for _ in range(n):
        data = tuple(map(int, input().split()))
        states.append(data)
    
    S = None
    
    for state in states:
        T = set()
        for i in range(5):
            for k in range(1, 10):
                lst = list(state)
                lst[i] = (lst[i] - k) % 10
                T.add(tuple(lst))
        for i in range(4):
            for k in range(1, 10):
                lst = list(state)
                lst[i] = (lst[i] - k) % 10
                lst[i+1] = (lst[i+1] - k) % 10
                T.add(tuple(lst))
        if S is None:
            S = T
        else:
            S = S.intersection(T)
    
    print(len(S) if S is not None else 0)

if __name__ == '__main__':
    main()