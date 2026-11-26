// https://www.luogu.com.cn/problem/P3534
// 题意：输入正整数个数 n、操作次数上限 m，以及序列 x_1..x_n。
// 最多进行 m 次操作，每次将某个正整数 x_i 减 1，要求操作后至少存在一个位置 k 满足 x_k = 0
// 并最小化 z = max_{1<=i<=n-1} |x_i - x_{i+1}|。
// 输出任一组最优解对应的位置 k 和最小值 z。
// 数据范围：1 <= n <= 10^6，1 <= m <= 10^18，1 <= x_i <= 10^9。
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 1e6+5;

int n,m;
int val[MAXN];
int tmp[MAXN];
int sum[MAXN];

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

int check(int limit){
    int now=m;
    for(int i=1;i<=n;i++){
        tmp[i]=val[i];
    }
    for(int i=n-1;i>=1;i--){
        if(tmp[i]-tmp[i+1]>limit){
            int delta=tmp[i]-tmp[i+1]-limit;
            tmp[i]-=delta;
            now-=delta;
        }
    }
    for(int i=2;i<=n;i++){
        if(tmp[i]-tmp[i-1]>limit){
            int delta=tmp[i]-tmp[i-1]-limit;
            tmp[i]-=delta;
            now-=delta;
        }
    }
    if(now<0){
        return 0;
    }

    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+tmp[i];
    }
    int l=1,r=1;
    for(int i=1;i<=n;i++){
        while(l<i&&tmp[l]<limit*(i-l)){
            l++;
        }
        while(r+1<=n&&tmp[r+1]>=limit*(r+1-i)){
            r++;
        }
        int all=limit*((i-l)*(i-l+1)+(r-i)*(r-i+1))/2;
        if(sum[r]-sum[l-1]-now<=all){
            return i;
        }
    }
    return 0;
}

signed main()
{
    n=read(),m=read();
    int l=0,r=0,ans=0;
    for(int i=1;i<=n;i++){
        val[i]=read();
        r=max(r,val[i]);
    }
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    int pos=check(ans);
    cout<<pos<<' '<<ans<<endl;
    return 0;
}