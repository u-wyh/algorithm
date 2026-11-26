// https://www.luogu.com.cn/problem/P3643
// 题意：输入学校数量 N，以及第 1..N 所学校若派出划艇时可派出的数量区间 [a_i, b_i]。
// 每所学校可选择不派或派出区间内数量的划艇（不同学校颜色不同），要求所有派出的学校按编号从 1 到 N 的派出数量严格递增，且至少有一所学校派出。
// 输出合法派出方案数对 1,000,000,007 取模的结果。
// 数据范围：1 <= N <= 500，1 <= a_i <= b_i <= 10^9。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 505;

int n;
int cnt,m;
int nums[MAXN*3];
int inv[MAXN];
int comb[MAXN];
int l[MAXN];
int r[MAXN];
int g[MAXN*3];

int find(int val){
    int l=1,r=m,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(nums[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>l[i]>>r[i];
        nums[++cnt]=l[i];
        nums[++cnt]=r[i];
        nums[++cnt]=r[i]+1;
    }
    sort(nums+1,nums+cnt+1);
    m=1;
    for(int i=2;i<=cnt;i++){
        if(nums[i]!=nums[i-1]){
            nums[++m]=nums[i];
        }
    }

    inv[1]=1;
    for(int i=2;i<=n;i++){
        inv[i]=(MOD-inv[MOD%i]*(MOD/i)%MOD+MOD)%MOD;
    }

    for(int i=1;i<=n;i++){
        l[i]=find(l[i]);
        r[i]=find(r[i]);
    }

    g[0]=1;
    for(int j=1;j<m;j++){

        int len=nums[j+1]-nums[j];
        comb[0]=1;
        for(int i=1;i<=n;i++){
            comb[i]=((comb[i-1]*inv[i])%MOD)*(len+i-1)%MOD;
        }

        for(int i=n;i>=1;i--){
            if(j>=l[i]&&j<=r[i]){
                int f=0,m=1,c=comb[1];
                for(int p=i-1;p>=0;p--){
                    f=(f+c*g[p]%MOD)%MOD;
                    if(l[p]<=j&&r[p]>=j){
                        c=comb[++m];
                    }
                }
                g[i]=(g[i]+f)%MOD;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=(ans+g[i])%MOD;
    }
    cout<<ans<<endl;
    return 0;
}