// https://www.luogu.com.cn/problem/P9410
// 题意：有 n 个城市初始互不连通且人口为 0，共 m 个操作：
// 1 x y 在 x, y 间开通双向航班；
// 2 l r a 将编号在 [l, r] 内所有城市人口加上 a；
// 3 x 询问当前所有能连通到达城市 x 的城市（含自身）的人口总和。
// 题意：第一行输入 n, m，接下来 m 行每行一个操作；
// 对每个操作 3 输出一行答案。
// 数据范围：1 <= n, m <= 2 * 10^5，
// 0 <= a <= 10^9，保证答案在 64 位有符号整数范围内。
// 难度评分：2500（洛谷分级换算）
// 算法标签：分块、启发式合并
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXB = 500;

int n,m;

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int sz[MAXN];
int bel[MAXN];

int tmp[MAXB];

long long sum[MAXN];
long long tag[MAXN];

vector<int>vec[MAXN];
vector<pair<int,int>>block[MAXN];

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

void prepare(){
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }
    for(int i=1;i<=n;i++){
        bel[i]=i;
        sz[i]=1;
        vec[i].push_back(i);
        block[i].push_back({bi[i],1});
    }
}

int main()
{
    n=read(),m=read();
    prepare();
    while(m--){
        int op=read();
        if(op==1){
            int x,y;
            x=read(),y=read();
            int fx=bel[x],fy=bel[y];
            if(fx==fy){
                continue;
            }
            if(sz[fx]<sz[fy]){
                swap(fx,fy);
            }
            for(int i=0;i<(int)vec[fy].size();i++){
                int v=vec[fy][i];
                bel[v]=fx;
                vec[fx].push_back(v);
            }
            sum[fx]+=sum[fy];
            sz[fx]+=sz[fy];

            for(int i=0;i<(int)block[fy].size();i++){
                pair<int,int>t=block[fy][i];
                tmp[t.first]+=t.second;
            }
            for(int i=0;i<(int)block[fx].size();i++){
                pair<int,int>t=block[fx][i];
                tmp[t.first]+=t.second;
            }
            block[fx].clear();
            for(int i=1;i<=bnum;i++){
                if(tmp[i]){
                    block[fx].push_back({i,tmp[i]});
                    tmp[i]=0;
                }
            }
        }
        else if(op==2){
            int l,r,v;
            l=read(),r=read(),v=read();
            if(bi[l]==bi[r]){
                for(int i=l;i<=r;i++){
                    sum[bel[i]]+=v;
                }
            }
            else{
                for(int i=l;i<=br[bi[l]];i++){
                    sum[bel[i]]+=v;
                }
                for(int i=bl[bi[r]];i<=r;i++){
                    sum[bel[i]]+=v;
                }
                for(int i=bi[l]+1;i<bi[r];i++){
                    tag[i]+=v;
                }
            }
        }
        else{
            int x=read();
            int fx=bel[x];
            long long ans=sum[fx];
            for(int i=0;i<(int)block[fx].size();i++){
                pair<int,int>t=block[fx][i];
                ans+=tag[t.first]*t.second;
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}