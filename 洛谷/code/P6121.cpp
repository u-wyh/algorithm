#include<iostream>
#include<cstdio>
using namespace std;
struct _edge{
    int from;
    int to;
    int next;
}e[400010];
int tot,head[200010],k;
bool vis[200010];                        //判断农场是否开着
inline void add_edge(int from,int to){   //链式前向星存图
    e[++tot].from=from;
    e[tot].to=to;
    e[tot].next=head[from];
    head[from]=tot;
}
int n,m,u,v,t[200010],ans[200010],f[200010];
inline int _find(int x){            //查询+路径压缩
    while(x!=f[x]) x=f[x]=f[f[x]];
    return x;
}
inline void init(){                 //并查集初始化
    for(register int i=1;i<=n;i++)
        f[i]=i;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(register int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        add_edge(u,v);              //无向图双向存边
        add_edge(v,u);
    }
    for(register int i=1;i<=n;i++)
        scanf("%d",&t[i]);          //农场关的时间，反着看就是开的时间
    init();                         //定义了函数……记得用
    vis[t[n]]=1;                    //t_n时开了农场 t[n]，标记
    ans[n]=1;                       //只开了一个时图必定是联通的
    for(register int i=n-1;i>=1;i--) //反着搜，第i 时刻开了农场t[i]
    {
        vis[t[i]]=1;                //标记
        for(register int j=head[t[i]];j;j=e[j].next)
        {
            if(vis[e[j].to]==1)      //如果该边终点农场也开了，执行如下语句
            {
                int fx=_find(t[i]),fy=_find(e[j].to);//并查集查询
                if(fx!=fy)     //不在同一个集合的话
                {
                    ++k;       //合并次数 +1
                    f[fx]=fy;  //合并两个集合
                }
            }
        }
        if(k==n-i) ans[i]=1;   //当前开了n-（i-1）个农场，判断是否连通，储存答案
        else ans[i]=0;
    }
    for(register int i=1;i<=n;i++)
    {
        if(ans[i]==1) printf("YES\n");  //打印答案
        else printf("NO\n");
    }
    return 0;
}
