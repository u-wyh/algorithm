// https://www.luogu.com.cn/problem/P3745
// 题意：输入三种不愉快度参数 A, B, C、学生数 n 和课程数 m
// 以及每位学生期望最晚出分天数 t_1..t_n 和每门课程原定出分天数
// b_1..b_m。
// 若所有课程最晚出分天数大于 t_i，第 i 位学生每多等一天产生 C 不愉快度；
// 可多次执行两类调整：1) 将课程 X 的部分老师调到 Y，
// 使 X 推迟 1 天、Y 提前 1 天，花费 A；
// 2) 给课程 Z 增加老师使其提前 1 天，花费 B。
// 输出最小的总不愉快度之和。
// 数据范围：1 <= n, m, t_i, b_i <= 10^5，
// 0 <= A, B <= 10^5；
// 测试点 13-14 中 C = 10^16，
// 其余 100% 范围内 0 <= C <= 10^5。
// 难度评分：1300（洛谷分级换算）
// 算法标签：枚举、前缀和、贪心
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
const int MAXN = 1e5+5;
typedef unsigned long long ll;
const ll INF = 100000000000000000ll;

int n,m,k,p=INT_MAX;
long long A,B,C;
int t[MAXN],b[MAXN];
int cntt[MAXN];
long long sumt[MAXN];
int cntb[MAXN];
long long sumb[MAXN];

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
    scanf("%lld %lld %lld",&A,&B,&C);
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&t[i]);
        p=min(p,t[i]);//p代表的是要求难度最高的
        cntt[t[i]]++;
    }
    for(int i=1;i<=m;i++){
        scanf("%d",&b[i]);
        cntb[b[i]]++;
        k=max(k,b[i]);
    }
    if(p>=k){
        cout<<0<<endl;
        return 0;
    }
    for(int i=1;i<=k;i++){
        sumt[i]=cntt[i]*i;
        cntt[i]+=cntt[i-1];
    }
    for(int i=1;i<=k;i++){
        sumt[i]+=sumt[i-1];
    }
    for(int i=1;i<=k;i++){
        sumb[i]=cntb[i]*i;
        cntb[i]+=cntb[i-1];
    }
    for(int i=1;i<=k;i++){
        sumb[i]+=sumb[i-1];
    }
    // for(int i=1;i<=k;i++){
    //     cout<<i<<": "<<cntt[i]<<' '<<sumt[i]<<' '<<cntb[i]<<' '<<sumb[i]<<endl;
    // }
    ll ans=INF;
    for(int i=1;i<=k;i++){
        // cout<<i<<": ";
        ll tmp=0;
        if(A<B){
            long long tmp1=sumb[k]-sumb[i]-(m-cntb[i])*i;
            long long tmp2=cntb[i]*i-sumb[i];
            if(tmp2>=tmp1){
                tmp+=tmp1*A;
            }
            else{
                tmp+=tmp2*A;
                tmp+=(tmp1-tmp2)*B;
            }
            // cout<<tmp1<<' '<<tmp2<<' ';
        }
        else{
            tmp+=B*(sumb[k]-sumb[i]);
        }
        tmp+=C*(cntt[i-1]*i-sumt[i-1]);
        // cout<<tmp<<endl;
        ans=min(ans,tmp);
    }
    cout<<ans<<endl;
    return 0;
}