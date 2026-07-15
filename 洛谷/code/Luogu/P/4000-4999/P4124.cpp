#include<bits/stdc++.h>
using namespace std;

long long dp[11][10][10][2][2][2][2];
//这是第几位  前两位和前一位是多少  是否已经有三个一样的了  是否保证值比要求的小   有没有4 和 8
//而且这些数字必须合法  即开头一定不能是0
int num[12];

long long compute(int pos,int a,int b,bool c,bool free,bool four,bool eight){
    /*
    pos表示当前来到第多少位
    a表示前两位 b表示前一位 c表示是否有了三位一样的
    free表示是否可以自由选择
    four表示有没有4  eight表示有没有8
    */
    if(four&&eight){
        return 0;
    }
    if(dp[pos][a][b][c][free][four][eight]){
        return dp[pos][a][b][c][free][four][eight];
    }
    if(pos==0){
        //来到0位置  说明全部结束 看一下是否有三个一样的  如果有4和8  那么一定无法来到这里
        return c;
    }
    long long ans=0;
    int limit=free?9:num[pos];
    for(int i=0;i<=limit;i++){
        ans+=compute(pos-1,b,i,c||(a==i&&a==b),free||(i<limit),four||(i==4),eight||(i==8));
    }
    dp[pos][a][b][c][free][four][eight]=ans;
    return ans;
}

long long calc(long long x){
    if(x<1e10){
        return 0;
    }
    memset(dp,0,sizeof(dp));
    int len;
    for(len=0;x;x/=10){
        num[++len]=x%10;
    }
    long long ans=0;
    for(int i=1;i<=num[len];i++){
        //第11位数字  一定不能是0
        ans+=compute(10,0,i,0,i<num[len],i==4,i==8);
    }
    return ans;
}

int main()
{
    long long l,r;
    cin>>l>>r;
    cout<<(calc(r)-calc(l-1));
    return 0;
}
