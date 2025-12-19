#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = MAXN * 23;

int root[MAXT];
int ls[MAXT];
int rs[MAXT];
int sum[MAXT];
char s[MAXT];
int cnt;
int n;

int build(int l,int r){
    int rt = ++cnt;
    if (l == r) {
        sum[rt] = 0;
    } else {
        int mid = (l + r) >> 1;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
    }
    return rt;
}

int add(int jobi,char c,int l,int r,int i){
    int rt = ++cnt;//新建一个节点（沿途节点）
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    sum[rt] = sum[i]+1;
    s[rt]=s[i];
    //拷贝原有信息
    if (l == r) {
        //cout<<l<<' '<<r<<' '<<c<<endl;
        //到达了要修改的节点位置
        s[rt] = c;
    } else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            ls[rt] = add(jobi, c, l, mid, ls[rt]);
        } else {
            rs[rt] = add(jobi, c, mid + 1, r, rs[rt]);
        }
    }
    return rt;
}

char query(int k,int l,int r,int i){
    if(l==r){
        //cout<<l<<' '<<r<<endl;
        return s[i];
    }
    int mid=(l+r)/2;
    int lsize=sum[ls[i]];
    if(lsize>=k){
        return query(k,l,mid,ls[i]);
    }
    else{
        return query(k-lsize,mid+1,r,rs[i]);
    }
}

int main()
{
    cin>>n;
    root[0]=build(1,n);
    for(int i=1,t=0;i<=n;i++){
        char op;
        cin>>op;
        if(op=='T'){
            char c;
            cin>>c;
            //cout<<' '<<t<<' '<<sum[root[t]]+1<<endl;
            root[t+1]=add(sum[root[t]]+1,c,1,n,root[t]);
            t++;
            //cout<<' '<<t<<' '<<sum[root[t]]<<endl;
            //cout<<' '<<t<<' '<<root[t]<<endl;
        }
        else if(op=='U'){
            int u;
            cin>>u;
            //cout<<t+1<<' '<<t-u<<endl;
            root[t+1]=root[t-u];
            t++;
            //cout<<' '<<t<<' '<<root[t]<<endl;
        }
        else{
            int u;
            cin>>u;
            //cout<<t<<' '<<root[t]<<endl;
            cout<<query(u,1,n,root[t])<<endl;
        }
    }
    return 0;
}
/*
9
T a
T b
T c
U 2
Q 1
T d
T e
U 3
Q 3
*/
