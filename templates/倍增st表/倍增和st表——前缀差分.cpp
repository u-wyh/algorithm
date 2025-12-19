// https://www.luogu.com.cn/problem/P9019
// 这道题的第一问查询最短路径其实也不是很简单  也需要使用倍增算法
// 关键是第二问  难度很大
// 首先令d(u,v)为u到v的最短路径长度 那么在保持最短的路径长度不变的情况下  有哪些点可能被经过呢
// 这里的经过不是跨过 必须是停留在这个节点上才能算的上是经过
// 必须要满足条件  d(u,x)+d(x,v)==d(u,v)
// 除此之外  我们可以发现一个性质  就是在u v之间的所有点x  都满足d(u,v)<=d(u,x)+d(x,v)<=d(u,v)+1
// 不过这个性质我们没有使用到
// 根据uv的最短长度ans  我们可以枚举从u走多少步  从v走多少步
// cnt(a,a)+cnt(b,b)+ (i=1~ans-1) cnt(g(b,ans−i),f(a,i))  cnt表示这个区间中的特殊位置的个数
// 解释一下这个式子  我们可以假设从u走了i步  从v走了ans-i步  但是这可能会形成一个区间  因为这并不一定是恰好走到了一个节点上
// 那么这个区间中的特殊的位置个数全部可以统计进来  并且所有的区间一定是不相交的
// 把这个式子展开就是  v左走ans-1步的点~u右走1步最远的点这个区间  v左走ans-2步的点~u右走2步最远的点这个区间  ………  v左走1步的点~u右走ans-1步最远的点这个区间  
// 区间统计使用前缀和  但是这个式子好像不好统计  我们变个形
// 1~u右走1步最远的点 + 1~u右走2步最远的点 …… 1~u右走ans-1步最远的点 - 1~v左走1步的点前一个点 - 1~v左走2步的点前一个点
// 为什么是枚举到ans-1  因为ans-1的各个二进制位是独特的  最后的一个1可以单独计算端点  不然的话 可能很麻烦 比如11111+1  位数超了
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXH = 18;

int n,q;
char s[MAXN<<1];
char t[MAXN];
int l[MAXN][MAXH];
int r[MAXN][MAXH];
int sum[MAXN];
// 这两个数组特别奇妙很厉害 
// sl[i][j]的意思是从i左走1步 左走2步  左走3步  左走2的j步前一个点的这些点的前缀和之和
// sr[i][j]的意思是从i走1步  走2步  走3步 走2的j步这些点的前缀和之和
// 通过这样算可以很轻松的得到我们想要的信息
int sl[MAXN][MAXH];
int sr[MAXN][MAXH];

int query(int u,int v){
    if(u==v){
        return 0;
    }
    int ans=0;
    for(int i=MAXH-1;i>=0;i--){
        if(r[u][i]>=v){
            continue;
        }
        ans+=(1<<i);
        u=r[u][i];
    }
    ans++;
    return ans;
}

int main()
{
    scanf("%d %d",&n,&q);
    scanf("%s",s+1);
    scanf("%s",t+1);
    int cnt=0,now=1;
    for(int i=1;i<=2*n;i++){
        if(s[i]=='L'){
            cnt++;
        }
        else{
            r[now][0]=cnt;
            now++;
        }
    }
    cnt=n+1,now=n;
    for(int i=2*n;i>=1;i--){
        if(s[i]=='R'){
            cnt--;
        }
        else{
            l[now][0]=cnt;
            now--;
        }
    }

    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+t[i]-'0';
    }
    for(int i=1;i<=n;i++){
        sr[i][0]=sum[r[i][0]];
        sl[i][0]=sum[l[i][0]-1];
    }

    for(int k=1;k<MAXH;k++){
        for(int i=1;i<=n;i++){
            l[i][k]=l[l[i][k-1]][k-1];
            r[i][k]=r[r[i][k-1]][k-1];
            sr[i][k]=sr[i][k-1]+sr[r[i][k-1]][k-1];
            sl[i][k]=sl[i][k-1]+sl[l[i][k-1]][k-1];
        }
    }

    while(q--){
        int u,v;
        scanf("%d %d",&u,&v);
        int ans1=query(u,v);
        long long ans2=t[u]-'0'+t[v]-'0';
        int steps=ans1-1;
        for(int i=MAXH-1;i>=0;i--){
            if(steps&(1<<i)){
                ans2+=sr[u][i];
                u=r[u][i];
            }
        }
        for(int i=MAXH-1;i>=0;i--){
            if(steps&(1<<i)){
                ans2-=sl[v][i];
                v=l[v][i];
            }
        }
        cout<<ans1<<' '<<ans2<<endl;
    }
    return 0;
}