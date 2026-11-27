// https://www.luogu.com.cn/problem/P3592
// 题意：输入洗车店数量 n 和顾客数量 m，以及每个顾客的区间 [a_i, b_i] 和价格上限 c_i。
// 需为每家洗车店设定正整数价格 p_i（1 <= p_i <= 5*10^5）；
// 第 i 个顾客会在第 a_i 到 b_i 家店中选择价格最便宜的一家消费，若最低价大于 c_i 则不消费。
// 求所有顾客消费总额的最大值，第一行输出最大总额，第二行输出任意一组对应的 n 个店铺价格 p_i。
// 数据范围：1 <= n <= 50，1 <= m <= 4000，1 <= a_i <= b_i <= n，1 <= c_i <= 5*10^5。
#include<bits/stdc++.h>
// 算法标签：区间动态规划、二维前缀和、离散化
using namespace std;
const int MAXN = 55;
const int MAXM = 4e3+5;

int n,m;

int a[MAXM];
int b[MAXM];
int c[MAXM];

int val[MAXM];
int cntt;

int head[MAXM];
int nxt[MAXM];
int to[MAXM];
int cntg=1;

int cnt[MAXN][MAXN];
int sum[MAXN][MAXN];
int dp1[MAXN][MAXN];
int dp2[MAXN][MAXN];
int choice[MAXN][MAXN][MAXM];
int ans[MAXN];

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int find(int v){
    int l=1,r=cntt,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(val[mid]>=v){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void prepare(){
    sort(val+1,val+m+1);
    cntt=1;
    for(int i=2;i<=m;i++){
        if(val[i]!=val[i-1]){
            val[++cntt]=val[i];
        }
    }

    for(int i=1;i<=m;i++){
        int k=find(c[i]);
        addedge(k,i);
    }
}

void add(int k){
    for(int i=head[k];i;i=nxt[i]){
        int v=to[i];
        ++cnt[a[v]][b[v]];
    }
}

void build(){
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            sum[i][j]=0;
        }
    }

    for(int l=1;l<=n;l++){
        for(int r=1;r<=n;r++){
            sum[l][r]=cnt[l][r]+sum[l-1][r]+sum[l][r-1]-sum[l-1][r-1];
        }
    }
}

int query(int l,int r,int p){
    return sum[p][r]-sum[l-1][r]-sum[p][p-1]+sum[l-1][p-1];
}

void restore(int l,int r,int k){
    if(l>r||k>cntt){
        return ;
    }
    if(choice[l][r][k]==0){
        restore(l,r,k+1);
        return ;
    }
    int p=choice[l][r][k];
    ans[p]=val[k];
    restore(l,p-1,k+1);
    restore(p+1,r,k);
}

void compute(){
    for(int k=cntt;k>=1;k--){
        add(k);
        build();

        for(int len=1;len<=n;len++){
            for(int l=1;l+len-1<=n;l++){
                int r=l+len-1;

                dp2[l][r]=dp1[l][r];
                choice[l][r][k]=0;

                for(int p=l;p<=r;p++){
                    int lt=p==l?0:dp1[l][p-1];
                    int rt=p==r?0:dp2[p+1][r];
                    int now=lt+rt+val[k]*query(l,r,p);
                    if(now>dp2[l][r]){
                        dp2[l][r]=now;
                        choice[l][r][k]=p;
                    }
                }
            }
        }

        for(int l=1;l<=n;l++){
            for(int r=l;r<=n;r++){
                dp1[l][r]=dp2[l][r];
            }
        }
    }

    restore(1,n,1);
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i]>>b[i]>>c[i];
        val[i]=c[i];
    }

    prepare();
    compute();

    cout<<dp1[1][n]<<endl;
    for(int i=1;i<=n;i++){
        if(ans[i]==0){
            ans[i]=5e5;
        }
        cout<<ans[i]<<' ';
    }

    return 0;
}