// https://www.luogu.com.cn/problem/P4562
// 题意：编号为 l 到 r 的办公室，
// 检查 i 号办公室时其所有倍数编号都会开始工作
// 对所有检查顺序排列 p 定义 t(p) 为使全部办公室都开始工作的最少检查次数，
// 求所有排列 t(p) 之和模 10^9+7。
// 数据范围：1 <= l <= r <= 10^7。
// 难度评分：1800（洛谷分级换算）
// 算法标签：埃氏筛、组合数学、快速幂
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 1e7+5;

int l,r;
int cnt;
bool vis[MAXN];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(a*ans)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

void prepare(){
    if(l<=r/2){
        for(int i=l;i<=r/2;i++){
            for(int j=2*i;j<=r;j+=i){
                vis[j]=true;
                // cout<<i<<' '<<j<<endl;
            }
        }
    }
    for(int i=l;i<=r;i++){
        if(!vis[i]){
            cnt++;
        }
    }
}

signed main()
{
    cin>>l>>r;
    prepare();
    // cout<<cnt<<endl;
    int ans=power(cnt+1,MOD-2);
    ans=(ans*cnt)%MOD;
    for(int i=1;i<=(r-l+2);i++){
        ans=(ans*i)%MOD;
    }
    cout<<ans<<endl;
    return 0;
}