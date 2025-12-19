//顺序存储 求树的高度  叶子结点个数  最大度数
//输入的信息包括  节点总数  以及他们的父亲节点编号
//双亲表示法
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n;              //结点个数
int fa[MAXN];       //表示这个节点的父亲节点
int val[MAXN];      //表示这个节点存储的值

int degree[MAXN];   //表示这个节点的度
int high[MAXN];     //表示这个节点高度
int sz[MAXN];       //以这个节点为头的子树叶子结点个数

//链式前向星建图
int cnt=1;
int head[MAXN];
int nxt[MAXN];
int to[MAXN];

//链式前向星连边
void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u){
    bool flag=0;//判断是否有孩子
    for(int i=head[u];i;i=nxt[i]){
        degree[u]++;
        int v=to[i];
        dfs(v);
        flag=1;//表示有孩子 那么一定不是叶子结点
        high[u]=max(high[u],high[v]);//找到孩子节点中最大的高度
        sz[u]+=sz[v];//加上孩子的子树中的叶子结点个数
    }
    high[u]+=1;
    if(!flag){
        //表示是叶子结点
        sz[u]=1;
    }
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>fa[i];
    }
    int root=0;//表示整棵树的根节点
    for(int i=0;i<n;i++){
        if(fa[i]!=-1){
            addedge(fa[i],i);
        }
        else{
            root=i;
        }
    }
    dfs(root);//从根节点开始遍历
    for(int i=0;i<n;i++){
        cout<<head[i]<<' ';
    }
    cout<<endl;
    for(int i=1;i<=cnt;i++){
        cout<<nxt[i]<<' '<<to[i]<<endl;
    }
    cout<<endl;
    int ans=0;//统计最大度数
    for(int i=0;i<n;i++){
        ans=max(ans,degree[i]);
    }
    cout<<"叶子结点总数为： "<<sz[root]<<endl;
    cout<<"最大度数为： "<<ans<<endl;
    cout<<"树的高度为： "<<high[root]<<endl;
    return 0;
}
/*
14
-1 0 0 0 1 1 2 3 3 3 5 5 8 8
*/
