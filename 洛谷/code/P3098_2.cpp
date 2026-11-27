// https://www.luogu.com.cn/problem/P3098
// 题意：输入牌总数 N、A 类洗牌窗口大小 M、询问数 Q，排列 P_1..P_M，以及 Q 个查询位置 q_i。
// 初始牌堆从上到下为 1..N；
// 每次将顶部 M 张按「第 i 张放到位置 P_i」洗牌，然后把最上面 1 张移到临时堆顶部；
// 不足 M 张时直接依次把顶部牌移到临时堆顶部。
// 求操作结束后临时堆从上到下第 q_i 个位置的牌编号。
// 输出 Q 行，每行一个整数表示对应位置的牌编号。
// 数据范围：2 <= M <= 10^5，M <= N <= 10^9，1 <= Q <= min(N, 5000)，1 <= P_i <= M
// 1 <= q_i <= N。
#include<bits/stdc++.h>
// 算法标签：倍增
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXH = 33;

int n,m,p,q;
int f[MAXN][MAXH];
int pre[MAXN];

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

int compute(int k){
    int all=min(n-m+1,n-k+1);//总共洗牌次数
    int st=max(1ll,m-k+1);//最后一次洗牌之后的位置 即最终位置
    int u=st,step=all-1,j=0;
    while(step){
        if(step&1){
            u=f[u][j];
        }
        j++;
        step>>=1;
    }
    if(u!=m+1){
        u=pre[u];
        return u;
    }
    int res=0;
    for(int i=p;i>=0;i--){
        if(f[st][i]<m+1){
            st=f[st][i];
            res+=1ll<<i;
        }
    }
    res+=1;
    return all-res+m;
}

signed main()
{
    n=read(),m=read(),q=read();
    p=log2(n)+1;
    for(int i=1;i<=m;i++){
        int u=read();
        pre[u]=i;
    }
    pre[m+1]=m+1;
    for(int i=1;i<=m+1;i++){
        f[i][0]=min(pre[i]+1,m+1);
    }
    for(int i=1;i<=p;i++){
        for(int j=1;j<=m+1;j++){
            f[j][i]=f[f[j][i-1]][i-1];
        }
    }
    while(q--){
        int u=read();
        cout<<compute(u)<<endl;
    }
    return 0;
}