//https://www.luogu.com.cn/problem/P2391
//这道题借用了并查集的思想
//fa数组记录的是节点i之前第一个可以染色的节点的位置
//当然也可以改成后面第一个可以染色的位置
//由于后来的颜色会覆盖之前的颜色
//所以这道题需要倒序枚举
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m,p,q;
int fa[MAXN];
int col[MAXN];

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int main()
{
    cin>>n>>m>>p>>q;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=m;i>=1;i--){
        //倒序枚举
        int l=(i*p+q)%n+1;
        int r=(i*q+p)%n+1;
        if(l>r){
            swap(l,r);
        }
        for(int j=find(r);j>=l;j=find(j-1)){
            //表示这个节点可以染色
            col[j]=i;
            fa[j]=j-1;
        }
    }
    for(int i=1;i<=n;i++){
        cout<<col[i]<<endl;
    }
    return 0;
}