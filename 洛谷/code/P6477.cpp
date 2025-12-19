#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int MOD = 1e9+7;

int n;
int arr[MAXN];
int temp[MAXN];
int last[MAXN];//表示上一个arr[i]的位置 没有就是0
int d[MAXN];
int tree1[MAXN];
int tree2[MAXN];
int tree[MAXN];

int lowbit(int i){
    return i&-i;
}

int sum(int x) {
    int res = 0;
    for (int i = x; i > 0; i -= i & -i) {
        res += tree1[i] * (x + 1) - tree2[i];
    }
    return res;
}

void add(int x, int d) {
    for (int i = x; i <= n; i += i & -i) {
        tree1[i] += d;
        tree2[i] += d * x;
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        temp[i]=arr[i];
    }
    sort(temp+1,temp+n+1);
    int m = unique(temp, temp + n) - temp;
    for (int i = 1; i <= n; i++) {
        arr[i] = lower_bound(temp, temp + m, arr[i]) - temp;
        last[i] = d[arr[i]];
        d[arr[i]] = i;
    }
    int now=0,ans=0;
    for(int i=1;i<=n;i++){
        now+=i-last[i]+2*(sum(i)-sum(last[i]));
        //每次加上的都是g(i)-g(i-1)
        //sum(r)求的是  l  从last[r]到r  的f(l,r)的值
        now%=MOD;
        //cout<<now<<' '<<last[i]<<endl;
        //现在的now是g(i)的值
        ans+=now;
        ans%=MOD;
        add(i+1,-1);
        add(last[i]+1,1);
    }
    cout<<ans<<endl;
    return 0;
}