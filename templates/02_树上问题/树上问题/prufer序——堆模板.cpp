// https://www.luogu.com.cn/problem/P6086   
// 时间复杂度为O(n*log(n))
//对于一棵n(n>=2)个节点的标定树（节点带编号），其Prufer序列是一个长度为n-2，值域为n的整数序列。
//每棵树必定存在Prufer序列且唯一，每个Prufer序列对应的树也必定存在且唯一，即二者为双射关系。
//Prufer序列是这样从树转化的：
//1、从树上选择编号最小的叶子节点，序列的下一位为其父节点的编号。
//2、删去该叶子节点。
//3、重复 1 和 2 ，直到树只剩下两个节点，此时序列的长度刚好为 n-2
//那么解码就是逆过程：
//1、选择编号最小的叶子节点（即未出现在序列中的节点），其父节点就是序列的第i（i初始为1）个元素。
//2、由性质可得，其父节点的度数为其出现次数+1。将该叶子节点删去，其父节点度数-1。若度数变成1，则父节点也成为叶子节点。
//3、将i加一，然后重复1和2，直到序列的每一个元素都使用完毕。
//cayley公式 ：n个顶点的图中，可以构造出n^(n-2)中无根带有编号的树   因为可以有n^(n-2)中序列  每种序列对应一种独特的树
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e6+5;

int n,op;
int d[MAXN];
int nums[MAXN];
int ans[MAXN];
bool vis[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

priority_queue<int,vector<int>,greater<int>>heap;//小根堆

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

void dfs(int u,int f){
    if(u!=n){
        ans[u]=f;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==f){
            continue;
        }
        dfs(v,u);
    }
}

int main()
{
    n=read(),op=read();
    if(op==1){
        for(int i=1;i<n;i++){
            int u=read();
            addedge(i,u);
            addedge(u,i);
            d[u]++,d[i]++;
        }
        for(int i=1;i<=n;i++){
            if(d[i]==1){
                heap.push(i);
            }
        }
        int tot=0;
        while(tot<n-2){
            int u=heap.top();
            heap.pop();
            vis[u]=true;
            for(int i=head[u];i;i=nxt[i]){
                int v=to[i];
                if(vis[v]){
                    continue;
                }
                ans[++tot]=v;
                d[v]--;
                if(d[v]==1){
                    heap.push(v);
                }
                break;
            }
        }
        long long res=0;
        for(int i=1;i<=n-2;i++){
            res=(res^(1ll*i*ans[i]));
        }
        cout<<res<<endl;
    }
    else{
        for(int i=1;i<=n-2;i++){
            nums[i]=read();
            d[nums[i]]++;
        }
        for(int i=1;i<=n;i++){
            if(d[i]==0){
                heap.push(i);
            }
        }
        for(int i=1;i<=n-2;i++){
            int u=heap.top();
            heap.pop();
            vis[u]=true;
            addedge(nums[i],u);
            addedge(u,nums[i]);
            d[nums[i]]--;
            if(d[nums[i]]==0){
                heap.push(nums[i]);
            }
        }
        int u=0,v=0;
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                if(u==0){
                    u=i;
                }
                else{
                    v=i;
                    break;
                }
            }
        }
        addedge(u,v);
        addedge(v,u);
        dfs(n,0);
        long long res=0;
        for(int i=1;i<=n-1;i++){
            res=(res^(1ll*i*ans[i]));
        }
        cout<<res<<endl;
    }
    return 0;
}