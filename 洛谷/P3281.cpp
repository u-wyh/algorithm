#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 20130427;
const int MAXN = 1e5+5;

int ans;
int len,k;
int nums[MAXN];

int sum[MAXN];
int sumcnt[MAXN][2];
int sumval[MAXN][2];
int sumsuf[MAXN][2];
int sumlen[MAXN][2];

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

int compute(){
    if(len==1&&nums[1]==0){
        return 0;
    }
    int s=0,q=0,l=0;
    for(int i=len;i>=1;i--){
        s=(k*s+(l+1)*nums[i])%MOD;
        q=(q+s)%MOD;
        l=l+1;
    }
    return q%MOD;
}

int solve(){
    memset(sumcnt,0,sizeof(sumcnt));
    memset(sumval,0,sizeof(sumval));
    memset(sumsuf,0,sizeof(sumsuf));
    memset(sumlen,0,sizeof(sumlen));

    sumcnt[len+1][0]=1;
    for(int i=len;i>=1;i--){
        int c=(i==len)?0:k;//这个就仅仅只是针对最高位的  类似于一个特判形式
        // 每个公式的c-1表示的是前面什么都没有  从这里开始填数字的  但是一定不是0  否则不就是前导0吗

        sumcnt[i][0]=sumcnt[i+1][0];
        sumcnt[i][1]=((c-1)+(sumcnt[i+1][1]*k%MOD)+(sumcnt[i+1][0]*nums[i]%MOD))%MOD;

        sumlen[i][0]=(sumlen[i+1][0]+sumcnt[i+1][0])%MOD;
        sumlen[i][1]=((c-1)+(sumlen[i][0]*nums[i]%MOD)+((sumlen[i+1][1]+sumcnt[i+1][1])*k%MOD))%MOD;

        sumsuf[i][0]=((sumsuf[i+1][0]*k%MOD)+(sumlen[i][0]*nums[i]%MOD))%MOD;
        sumsuf[i][1]=(sum[c]+((sumsuf[i+1][0]*k%MOD)*nums[i])%MOD+
                      (sum[nums[i]]*sumlen[i][0]%MOD)+(sumsuf[i+1][1]*k%MOD*k%MOD)
                     +(sum[k]*(sumlen[i+1][1]+sumcnt[i+1][1])%MOD))%MOD;
        
        sumval[i][0]=(sumval[i+1][0]+sumsuf[i][0])%MOD;
        sumval[i][1]=((sumval[i+1][0]*nums[i])%MOD+(sumval[i+1][1]*k)%MOD+sumsuf[i][1])%MOD;
    }

    return (sumval[1][0]+sumval[1][1])%MOD;
} 

signed main()
{
    k=read(),len=read();
    sum[0]=0;
    for(int i=0;i<k;i++){
        sum[i+1]=(sum[i]+i)%MOD;
    }
    for(int i=1;i<=len;i++){
        nums[len-i+1]=read();
    }
    ans=compute();
    ans=(ans-solve()+MOD)%MOD;

    len=read();
    for(int i=1;i<=len;i++){
        nums[len-i+1]=read();
    }
    ans=(ans+solve())%MOD;
    ans=(ans%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}