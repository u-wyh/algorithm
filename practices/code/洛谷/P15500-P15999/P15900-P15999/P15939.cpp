// https://www.luogu.com.cn/problem/P15939
// 题意：游程编码的甜辣团子串，多次问区间分成若干口使每口甜-辣>=K的最多次数。
// 输入：首行 N, Q, K，次行段长 A_1..A_N，
// 后 Q 行计划 (L_j, R_j)。
// 规则：奇数段甜偶数段辣；
// 吃第 L_j..R_j 段对应团子，顺序分段使尽量多口满足甜-辣>=K。
// 输出：输出 Q 行，表示每个计划最多能感到的满足次数。
// 数据范围：1 <= N, Q <= 5*10^5，
// 1 <= K <= 10^14，1 <= A_i <= 10^9
// 1 <= L_j <= R_j <= N。
// 算法标签：倍增、有序集合
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int MAXH = 20;

int n,m,k;
int p;

int val[MAXN];
int pre[MAXN];
int f[MAXN];

int up[MAXH][MAXN];
int sum[MAXH][MAXN];

set<pair<long long,int>>st;

int MOD(int x){
    x%=k;
    if(x<0){
        x+=k;
    }
    return x;
}

void compute(int l,int r,int pos){
    auto it=st.lower_bound({l,-1});

    vector<pair<long long,int>>vec;
    while(it!=st.end()&&it->first<=r){
        vec.push_back(*it);
        it++;
    }
    for(auto p:vec){
        st.erase(p);
        f[p.second]=pos;
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<=n;i++){
        if(i&1){
            pre[i]=pre[i-1]+val[i];
        }
        else{
            pre[i]=pre[i-1]-val[i];
        }
    }

    for(int i=1;i<=n+1;i++){
        f[i]=n+1;
    }

    for(int i=1;i<=n;i++){
        if(i&1){
            st.insert({MOD(pre[i-1]),i});
        }
        else{
            f[i]=i;
            int high=MOD(pre[i-1]);

            if(val[i]>=k-1){
                compute(0,k-1,i);
            }
            else{
                int low=MOD(high-val[i]);
                if(low<high){
                    compute(low,high,i);
                }
                else{
                    compute(low,k-1,i);
                    compute(0,high,i);
                }
            }
        }
    }

    for(int i=1;i<=n;i++){
        if(f[i]<=n){
            up[0][i]=f[i]+1;
            sum[0][i]=(pre[f[i]-1]-pre[i-1])/k;
        }
        else{
            up[0][i]=n+2;
        }
    }

    p=log2(n);
    for(int k=1;k<=p;k++){
        for(int i=1;i<=n;i++){
            int mid=up[k-1][i];
            if(mid<=n){
                up[k][i]=up[k-1][mid];
                sum[k][i]=sum[k-1][i]+sum[k-1][mid];
            }
            else{
                up[k][i]=n+2;
                sum[k][i]=sum[k-1][i];
            }
        }
    }

    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;

        int ans=0;
        int cur=l;
        for(int k=p;k>=0;k--){
            if(cur<=n&&up[k][cur]<=r+1){
                ans+=sum[k][cur];
                cur=up[k][cur];
            }
        }
        if(cur<=r){
            ans+=(pre[r]-pre[cur-1])/k;
        }
        cout<<ans<<endl;
    }
    return 0;
}