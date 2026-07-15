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