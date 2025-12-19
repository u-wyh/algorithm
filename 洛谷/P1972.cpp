#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
int arr[MAXN];
struct Query{
    int l,r,subsrcipt;
}query[MAXN];
int ans[MAXN];
int Map[MAXN];
int tree[MAXN];
int n, m;

int lowbit(int i) {
    return i & -i;
}

void add(int i, int v) {
    while (i <= n) {
        tree[i] += v;
        i += lowbit(i);
    }
}

int sum(int i) {
    int ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

int range(int l, int r) {
	return sum(r) - sum(l - 1);
}

bool cmp(Query a,Query b){
    return a.r<b.r;
}

void compute() {
    sort(query+1,query+ m + 1,cmp);
    for (int s = 1, q = 1, l, r, i; q <= m; q++) {
        r = query[q].r;
        for (; s <= r; s++) {
            int color = arr[s];
            if (Map[color] != 0) {
                add(Map[color], -1);
            }
            add(s, 1);
            Map[color] = s;
        }
        l = query[q].l;
        i = query[q].subsrcipt;
        ans[i] = range(l, r);
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>query[i].l>>query[i].r;
        query[i].subsrcipt=i;
    }
    compute();
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}

