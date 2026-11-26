// https://www.luogu.com.cn/problem/P3850
// 题意：先输入初始书架上的书数 N 及 N 行书名，再输入新买书数 M 及 M 行（书名、插入位置）
// 最后输入询问数 Q 及 Q 个查询位置（位置均从 0 开始）。
// 按顺序将新书插入对应位置（原位置及之后的书依次后移一位）。
// 输出 Q 行，每行对应查询位置最终放置的书名。
// 数据范围：对于 100% 的数据，1 <= N <= 200，1 <= M <= 10^5，1 <= Q <= 10^4，书名不含空格且长度 <= 10
// 保证插入与查询位置合法。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+305;

int n,m;
int cnt;
int head=0;
string key[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
double priority[MAXN];

int ansi=-1;
string ans[MAXN];

void up(int i){
    sz[i]=sz[ls[i]]+sz[rs[i]]+1;
}

void split(int l, int r, int i, int rank) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        if (sz[ls[i]] + 1 <= rank) {
            rs[l] = i;
            split(i, r, rs[i], rank - sz[ls[i]] - 1);
        } else {
            ls[r] = i;
            split(l, i, ls[i], rank);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

void inorder(int i) {
    if (i != 0) {
        inorder(ls[i]);
        ans[++ansi] = key[i];
        inorder(rs[i]);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    srand(time(0));
    cin>>n;
    string s;
    for(int i=1;i<=n;i++){
        cin>>s;
        key[++cnt]=s;
        sz[cnt]=1;
        priority[cnt]=(double)rand()/RAND_MAX;
        head=merge(head,cnt);
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>s;
        int pos;
        cin>>pos;
        split(0,0,head,pos);
        int l=rs[0],r=ls[0];
        key[++cnt]=s;
        sz[cnt]=1;
        priority[cnt]=(double)rand()/RAND_MAX;
        l=merge(l,cnt);
        head=merge(l,r);
    }

    inorder(head);
    int q;
    cin>>q;
    for(int i=1;i<=q;i++){
        int u;
        cin>>u;
        cout<<ans[u]<<endl;
    }
    return 0;
}