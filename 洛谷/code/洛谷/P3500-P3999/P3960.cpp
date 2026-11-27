// https://www.luogu.com.cn/problem/P3960
// 题意：第一行输入方阵行数 n、列数 m 和离队事件数 q；
// 初始第 i 行第 j 列学生编号为 (i-1)*m + j。
// 接下来 q 行每行输入 (x, y)，
// 表示第 x 行第 y 列的学生离队并输出其编号；
// 随后该行所有同学向左看齐填补空位
// （第 x 行 y+1..m 左移，空位到 (x, m)），
// 再第 m 列 x+1..n 上移，最后该学生回到 (n, m)。
// 按事件顺序每行输出离队学生的编号。
// 数据范围：对于 100% 的数据，
// 1 <= n, m, q <= 3 * 10^5，1 <= x <= n，
// 1 <= y <= m。
// 算法标签：动态开点线段树、线段树二分
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;
const int MAXT = MAXN*40;

int n,m,q,limit;

int root[MAXN];
int colroot;

int sz[MAXT];
int ls[MAXT];
int rs[MAXT];
int cntt;

vector<int>vec[MAXN];
vector<int>colvec;

int insert(int pos,int l,int r,int i){
    int rt=++cntt;
    ls[rt]=ls[i];
    rs[rt]=rs[i];
    sz[rt]=sz[i]+1;
    if(l<r){
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[rt]=insert(pos,l,mid,ls[rt]);
        }
        else{
            rs[rt]=insert(pos,mid+1,r,rs[rt]);
        }
    }
    return rt;
}

int query(int k,int l,int r,int i){
    if(l==r){
        return l;
    }
    else{
        int mid=(l+r)>>1;
        int ltlen=mid-l+1;
        if(ltlen-sz[ls[i]]>=k){
            return query(k,l,mid,ls[i]);
        }
        else{
            return query(k+sz[ls[i]]-ltlen,mid+1,r,rs[i]);
        }
    }
}

int removerow(int x,int y){
    int pos=query(y,1,limit,root[x]);
    int val;
    if(pos<m){
        val=(x-1)*m+pos;
    }
    else{
        val=vec[x][pos-m];
    }
    root[x]=insert(pos,1,limit,root[x]);
    return val;
}

int removecol(int x){
    int pos=query(x,1,limit,colroot);
    colroot=insert(pos,1,limit,colroot);
    if(pos<=n){
        return pos*m;
    }
    else{
        return colvec[pos-n-1];
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>q;
    limit=max(n,m)+q;
    for(int i=1;i<=q;i++){
        int x,y;
        cin>>x>>y;
        if(y<m){
            int ans=removerow(x,y);
            int tmp=removecol(x);
            vec[x].push_back(tmp);
            colvec.push_back(ans);
            cout<<ans<<endl;
        }
        else{
            int ans=removecol(x);
            colvec.push_back(ans);
            cout<<ans<<endl;
        }
    }

    return 0;
}