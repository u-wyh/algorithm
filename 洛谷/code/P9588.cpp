// https://www.luogu.com.cn/problem/P9588
// 题意：维护一个初始为空的队列，共 q 次操作：1 x 在队尾依次插入 1, 2, ..., x；
// 2 y 从队头弹出前 y 个元素；
// 3 z 查询当前队列第 z 个元素；
// 4 查询当前队列所有元素的最大值。
// 题意：第一行输入测试点编号 c 及 q，接下来 q 行每行一个操作；对每个操作 3 和 4 输出一行一个整数。
// 数据范围：1 <= q <= 2 * 10^5，1 <= x, y, z <= 10^9
// sum(x) <= 2 * 10^14（保证每次操作合法且不越界）。
// 算法标签：前缀和、二分查找、multiset
#include<bits/stdc++.h>
using namespace std;
int a[200005], s[200005], n;
multiset<int> ms;

void push(int w)
{
    a[++n] = w;
    s[n] = s[n - 1] + w;
    ms.insert(w);
}
signed main()
{
    int res = 0, id = 1;
    int q;
    cin>>q;
    cin>>q;
    while (q--)
    {
        int op;
        cin>>op;
        if (op == 1)
        {
            int x ;
            cin>>x;
            push(x);
        }
        if (op == 2)
        {
            int y;
            cin>>y;
            res += y;
            while(s[id] <= res && id <= n) {
                ms.erase(ms.find(a[id]));
                id++;
            }
        }
        if (op == 3)
        {
            int z ;
            cin>>z;
            z+=res;
            int pos = lower_bound(s + 1, s + n + 1, z) - s - 1;
            cout << z - s[pos] << endl;
        }
        if(op == 4)
        {
            cout << *ms.rbegin() << endl;
        }
    }
    return 0;
}
