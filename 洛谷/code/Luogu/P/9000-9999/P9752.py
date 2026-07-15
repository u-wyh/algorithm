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