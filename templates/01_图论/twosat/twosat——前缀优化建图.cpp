// https://www.luogu.com.cn/problem/CF1215F
// 需要注意的是 我的代码中 电台的真实值是从0下标开始的
#include<bits/stdc++.h>
using namespace std;
// 节点个数为(n+m)*2  即4e5*4
const int MAXN = 2e6+5;
// 边的数量为(q1*2)+(n*4)+(q2*2)
const int MAXM = 4e6+5;

int q1,q2,n,m;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt=1;

int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,dfncnt;
int col[MAXN];
bool instack[MAXN];

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

// 表示这个要求被满足的编号
inline int yes(int u){
    return u<<1;
}

// 表示这个要求不被满足的编号
inline int no(int u){
    return u<<1|1;
}

void tarjan(int x){
    dfn[x]=++dfncnt;
    low[x]=dfncnt;
    st[++top]=x;
    instack[x]=true;
    for(int i=head[x];i;i=nxt[i]){
        int v=to[i];
        if(!dfn[v]){
            //表示这个节点没有被访问过
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(instack[v]){
            //表示这个属于是回溯了 一定是同一个环上的
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        //将所有节点按照颜色分类  完成缩点
        while(st[top]!=x){
            //属于同一个强联通分量
            col[st[top]]=color;
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

bool compute(){
    // 标号为1~(n+m) 即2~2*(n+m)+1
    for(int i=2;i<=(n+m)*2+1;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n+m;i++){
        if(col[yes(i)]==col[no(i)]){
            return false;
        }
    }
    return true;
}

int main()
{
    q1=read(),n=read(),m=read(),q2=read();

    // 两者必须至少选其一的限制
    for(int i=1;i<=q1;i++){
        int u,v;
        u=read(),v=read();
        addedge(no(u),yes(v));
        addedge(no(v),yes(u));
    }

    // 电台本身功率的限制
    for(int i=1;i<=n;i++){
        int l,r;
        l=read(),r=read();
        if(l>1){
            // 注意这里要特判一下  因为l可能是1 那么就会导致0的出现 
            addedge(yes(i),no(n+l-1));
            addedge(yes(n+l-1),no(i));
        }
        addedge(yes(i),yes(n+r));
        addedge(no(n+r),no(i));
    }

    // 频率本身之间的限制
    for(int i=1;i<m;i++){
        // 表示<=i  那么一定<=i+1
        addedge(yes(n+i),yes(n+i+1));
        // 表示>i+1  那么一定>i
        addedge(no(n+i+1),no(n+i));
    }

    // 两者最多只能选其一的限制
    for(int i=1;i<=q2;i++){
        int u,v;
        u=read(),v=read();
        addedge(yes(u),no(v));
        addedge(yes(v),no(u));
    }

    if(compute()){
        int k=0;
        for(int i=1;i<=n;i++){
            if(col[yes(i)]<col[no(i)]){
                k++;
            }
        }
        for(int i=1;i<=m;i++){
            if(col[yes(n+i)]<col[no(n+i)]){
                printf("%d %d\n",k,i);
                break;
            }
        }
        for(int i=1;i<=n;i++){
            if(col[yes(i)]<col[no(i)]){
                printf("%d ",i);
            }
        }
    }
    else{
        printf("-1\n");
    }
    return 0;
}