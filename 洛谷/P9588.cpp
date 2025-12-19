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
