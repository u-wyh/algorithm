// https://www.luogu.com.cn/problem/P3594
// 题意：输入序列长度 n、和上限 p、覆盖长度上限 d，
// 以及正整数序列 w_1..w_n。
// 你有一次机会选一段长度不超过 d 的连续子段并将其中所有数清零，
// 之后再选一段连续子段使其元素和不超过 p。
// 输出修改后能找到的合法连续子段的最大长度。
// 数据范围：1 <= d <= n <= 2*10^6，
// 0 <= p <= 10^16，1 <= w_i <= 10^9。
// 算法标签：双指针、单调队列、前缀和
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e6+5;

int n,m,d;
int arr[MAXN];
int sum[MAXN];
int q[MAXN],head,tail;

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

signed main()
{
    n=read(),m=read(),d=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
        sum[i]=sum[i-1]+arr[i];
    }
    int ans=d;
    int l=1;
    head=0,tail=1;
    q[head]=d;
    for(int r=d+1;r<=n;r++){
        while(head<tail&&sum[r]-sum[r-d]>sum[q[tail-1]]-sum[q[tail-1]-d]){
            tail--;
        }
        q[tail++]=r;
        while(head<tail&&sum[r]-sum[l-1]-sum[q[head]]+sum[q[head]-d]>m){
            l++;
            while(head<tail&&q[head]-d+1<l){
                head++;
            }
        }
        ans=max(ans,r-l+1);
    }
    cout<<ans<<endl;
    return 0;
}
