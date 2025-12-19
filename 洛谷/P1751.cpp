//P1751
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const int MAXM = 1005;
const int MAXT = 505;

int n,m,tt;

int cnt=1;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];

int pos[MAXM];//每个贪吃虫所在位置
int nums[MAXN];//每个节点上为哪条贪吃虫，0表示没有贪吃虫
int arr[MAXT];//每一次食物出现的地方
int eat[MAXM];//每条贪吃虫吃的食物数

//这两个数组是dfs过程中用到的变量
int t[MAXN];   // 占领每个节点的时间
int o[MAXN];   // 每个节点被占据的贪吃虫编号

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

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    if(nums[u]){
        //如果这个节点本来就有虫子
        //那么接下来即使有虫子也不用走了  因为他们距离远
        t[u]=0,o[u]=nums[u];

        pos[nums[u]]=u;//其实这个不填也不影响  以前也是这个值
        return ;
    }
    //接下来就是这个节点没有虫子 那么必然会有一个虫子经过这里
    //还有一种情况  就是他的下面有没有虫子  那么他的t o数组就是mp mt
    int mp=1e9,mt=1e9;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);//去孩子节点统计信息
        if(o[v]==1e9){
            continue;//说明这个孩子没有虫子
        }
        if((t[v] + 1) < mt || ((t[v] + 1) == mt && o[v] < mp)){
            mt = t[v] + 1;
            mp = o[v];
        }
    }
    t[u] = mt;
    o[u] = mp;//如果他的子树上没有虫子  那么的值就是1e9
    if(mp!=1e9){
        //如果这个值是1e9  那么说明下面根本没有虫子
        //否则pos暂时先填上  如果这个虫子还可以继续向上走  那么会有上面的节点覆盖
        //这个其实就是覆盖
        nums[pos[mp]]=0;
        pos[mp]=u;
        nums[u]=mp;//更新b p数组
    }
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v),addedge(v,u);
    }

    m=read();
    for(int i=1;i<=m;i++){
        int u;
        u=read();
        pos[i]=u,nums[u]=i;//修改相应信息
    }

    tt=read();
    for(int i=1;i<=tt;i++){
        arr[i]=read();
    }

    for(int i=1;i<=tt;i++){
        //每次查询  都相当于换根
        memset(t, 0, sizeof(t));
        memset(o, 0, sizeof(o));
        dfs(arr[i], 0);
        eat[o[arr[i]]]++;
    }

    for(int i=1;i<=m;i++){
        cout<<pos[i]<<' '<<eat[i]<<endl;
    }
    return 0;
}
/*
9
1 2 2 3 3 4 1 5 5 6 5 7 7 8 7 9
4
2 4 5 9
3
1 3 6
*/
