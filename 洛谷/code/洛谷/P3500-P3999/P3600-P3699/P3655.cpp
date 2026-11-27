// https://www.luogu.com.cn/problem/P3655
// 题意：输入成员下标上限 N（共 N+1 人，A_0=0 固定）、修改次数
// Q、常数 S 和 T，初始唱功 A_0..A_N
// 以及 Q 次区间加值操作 (X, Y, Z)。
// 每次操作将 A_X..A_Y 均加上 Z；
// 设魅力值 B 为从 i=1..N 累加：
// 若 A_{i-1} < A_i 则减 S*(A_i - A_{i-1})
// 若 A_{i-1} > A_i 则加 T*(A_{i-1} - A_i)。
// 每次操作后输出当前队伍的魅力值 B。
// 数据范围：N, Q <= 200000，
// 1 <= S, T, A_i <= 10^6（A_0=0），
// |Z| <= 10^6
// 1 <= X <= Y <= N。
// 算法标签：差分
#include<bits/stdc++.h>
using namespace std;

long n,m,s,t,ans=0;
long long nums[200005],d[200005];

long long read(){
	long long a=0,k=1;char c=getchar();
	while (!isdigit(c)){if (c=='-')k=-1;c=getchar();}
	while (isdigit(c)){a=a*10+c-'0';c=getchar();}
	return a*k;
}

int main()
{
    n=read(),m=read(),s=read(),t=read();
    for(int i=0;i<=n;i++){
        nums[i]=read();
    }
    for(int i=1;i<=n;i++){
        d[i]=nums[i-1]-nums[i];
        if(d[i]<0)
            ans+=d[i]*s;
        else
            ans+=d[i]*t;
        //printf("%3d",d[i]);
    }
    //printf("\n");
    //cout<<ans<<endl;
    while(m--){
        //for(int i=1;i<=n;i++){
            //printf("%3d",d[i]);
        //}
        //printf("\n");
        long long a,b,c;
        a=read(),b=read(),c=read();
        if(d[a]<=0&&(d[a]-c)<=0)
            ans-=c*s;
        else if(d[a]>=0&&(d[a]-c)>=0)
            ans-=t*c;
        else if(d[a]>=0&&(d[a]-c)<=0)
            ans+=(d[a]-c)*s-d[a]*t;
        else
            ans+=(d[a]-c)*t-d[a]*s;
        d[a]-=c;
        if(b==n){
            cout<<ans<<endl;
            continue;
        }
        if(d[b+1]<=0&&(d[b+1]+c)<=0)
            ans+=c*s;
        else if(d[b+1]>=0&&(d[b+1]+c)>=0)
            ans+=t*s;
        else if(d[b+1]>=0&&(d[b+1]+c)<=0)
            ans+=(d[b+1]+c)*s-d[b+1]*t;
        else
            ans+=(d[b+1]+c)*t-d[b+1]*s;
        d[b+1]+=c;
        cout<<ans<<endl;
    }
    //for(int i=1;i<=n;i++){
        //printf("%3d",d[i]);
    //}
    //printf("\n");
    return 0;
}
