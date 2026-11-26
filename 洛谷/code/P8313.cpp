// https://www.luogu.com.cn/problem/P8313
// 题意：给定长为 n 的序列 a_1..a_n
// 求有多少对 (l, r) (1 <= l <= r <= n) 使得区间 [l, r] 内存在严格出现次数超过区间长度一半的数（即绝对众数）。
// 数据范围：100% 数据满足 1 <= l <= r <= n <= 2*10^5，1 <= a_i <= 10^9。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n;
int val[MAXN];
int sorted[MAXN];
int len;
int B;

int cnt[MAXN];
int tag[MAXN];
int tim[MAXN];

int bucket[MAXN<<1];

int find(int x){
    int l=1,r=len,ans=len;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]>=x){
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
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        sorted[i]=val[i];
    }
    sort(sorted+1,sorted+n+1);
    len=1;
    for(int i=2;i<=n;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++len]=sorted[i];
        }
    }
    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
    }

    for(int i=1;i<=n;i++){
        cnt[val[i]]++;
    }

    int ans=0;
    int T=sqrt(n);
    B=2*T;

    for(int l=1;l<=n;l++){
        int mx=0;
        int major=0;
        for(int r=l;r<l+B&&r<=n;r++){
            int x=val[r];
            if(tag[x]!=l){
                tag[x]=l;
                tim[x]=0;
            }
            tim[x]++;
            if(tim[x]>mx){
                mx=tim[x];
                major=x;
            }
            if(2*mx>(r-l+1)&&cnt[major]<=T){
                ans++;
            }
        }
    }

    for(int x=1;x<=len;x++){
        if(cnt[x]<=T){
            continue;
        }
        int s=n;
        int less=0;
        for(int j=0;j<=2*n;j++){
            bucket[j]=0;
        }
        bucket[s]=1;

        for(int i=1;i<=n;i++){
            if(val[i]==x){
                less+=bucket[s];
                s++;
            }
            else{
                s--;
                less-=bucket[s];
            }
            ans+=less;
            bucket[s]++;
        }
    }

    cout<<ans<<endl;
    return 0;
}