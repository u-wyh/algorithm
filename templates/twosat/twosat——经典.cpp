// https://www.luogu.com.cn/problem/P6378
//这道题是一道twosat的经典应用  我们最初的想法是将一个点分成两个部分
//要么是关键点(2*i-1)  要么不是关键点(2*i)   不能既是又是
//所以这个问题就可以调用twosat模型来解决  即tarjan缩点判断
//那么问题就是如何连边   
//根据题目要求一条边的两个顶点必须至少有一个是关键点  那么我们可以得出如果： a不是->b一定是   b不是->a一定是   连边
//对于一个小组  只有一个可以是  如果a是 那么剩余的都不能是  暴力连边
//但是这会导致MLE TLE    所以我们必须简化组内连边方式
//我们将每个点的关键部分添加一个影子节点 称为前缀点    非关键部分也添加一个  称之为后缀点
//那么简化的方式就是   每一个关键点->前缀点   每一个后缀点->非关键点
//除了最后一个以外  每个前缀点->下一个前缀点
//除了第一个以外  每个后缀点->前一个后缀点
//除了最后一个以外  每个前缀点->下一个非关键点
//除了第一个以外  每个关键点->前一个后缀点
// 这道题也是前缀后缀优化建图的一道典题
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e6+5;
const int MAXM = 1e7+5;

int n,m,k;
int nums[MAXN];

int dfn[MAXN];
int low[MAXN];
int dfncnt;
int color;
int st[MAXN];
bool instack[MAXN];
int top;
int col[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt=1;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    st[++top]=u;
    instack[u]=true;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(instack[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u]){
        col[u]=++color;
        instack[u]=false;
        while(st[top]!=u){
            instack[st[top]]=false;
            col[st[top--]]=color;
        }
        top--;
    }
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u*2,v*2-1);
        addedge(v*2,u*2-1);
    }

    while(k--){
        //非常卓越的想法  简化连边同时保持性质不变
        int t=read();
        for(int i=1;i<=t;i++){
            nums[i]=read();
            addedge(nums[i]*2-1,2*n+nums[i]*2-1);
            addedge(nums[i]*2+2*n,nums[i]*2);
        }
        for(int i=1;i<t;i++){
            addedge(nums[i]*2-1+2*n,nums[i+1]*2-1+2*n);
            addedge(nums[i]*2-1+2*n,nums[i+1]*2);
        }
        for(int i=1;i<t;i++){
            addedge(nums[i+1]*2+2*n,nums[i]*2+2*n);
            addedge(nums[i+1]*2-1,nums[i]*2+2*n);
        }
    }

    for(int i=1;i<=4*n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }

    bool flag=false;
    for(int i=1;i<=n;i++){
        if(col[i*2-1]==col[2*i]){
            flag=true;
            break;
        }
    }
    if(flag){
        cout<<"NIE"<<endl;
    }
    else{
        cout<<"TAK"<<endl;
    }
    return 0;
}