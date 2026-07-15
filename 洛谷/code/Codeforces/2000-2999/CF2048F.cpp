#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int INF = 1e18;

int n;
int nums[MAXN];
int val[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];
int f[MAXN][64];

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

void build() {
    int top = 0;
    for (int i = 1; i <= n; i++) {
        int pos = top;

        while (pos > 0 && val[sta[pos]] > val[i]) {
            //单调栈  弹出不符合的元素
            pos--;
        }

        // 插入一个元素 它是连接在哪个节点的右孩子上的   哪些节点连接到它的左孩子
        if (pos > 0) {
            //那么就是没有弹干净   那么当前节点就会成为栈顶节点的右孩子
            rs[sta[pos]] = i;
        }

        if (pos < top) {
            //表示有元素弹出 那么一定是当前节点的左孩子节点
            ls[i] = sta[pos + 1];
        }

        sta[++pos] = i;//加入栈中
        top = pos;
    }
}

void dfs(int u){
    if(ls[u]==0&&rs[u]==0){
        f[u][0]=nums[u];
        for(int i=1;i<=63;i++){
            f[u][i]=f[u][i-1]/val[u];
        }
        return ;
    }
    if(!ls[u]||!rs[u]){
        int v=ls[u]+rs[u];
        dfs(v);
        for(int i=0;i<=63;i++){
            f[u][i]=max(f[v][i],nums[u]);
        }
        for(int i=1;i<=63;i++){
            f[u][i]=min(f[u][i],f[u][i-1]/val[u]);
        }
        return;
    }
    dfs(ls[u]);
    dfs(rs[u]);
    for(int i=0;i<=63;i++){
        for(int j=0;j<=i;j++){
            f[u][i]=min(f[u][i],max(nums[u],max(f[ls[u]][j],f[rs[u]][i-j])));
        }
    }
    for(int i=1;i<=63;i++){
        f[u][i]=min(f[u][i],f[u][i-1]/val[u]);
    }
}

signed main()
{
    int T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            ls[i]=0;
            rs[i]=0;
        }
        for(int i=1;i<=n;i++){
            nums[i]=read();
            nums[i]--;
        }
        for(int i=1;i<=n;i++){
            val[i]=read();
        }
        build();
        for(int i=1;i<=n;i++){
            for(int j=0;j<=63;j++){
                f[i][j]=INF;
            }
        }
        dfs(sta[1]);
        for(int i=0;i<=63;i++){
            if(!f[sta[1]][i]){
                cout<<i<<endl;
                break;
            }
        }
    }
    return 0;
}