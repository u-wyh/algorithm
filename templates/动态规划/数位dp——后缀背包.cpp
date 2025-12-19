// https://www.luogu.com.cn/problem/P2481
// 做法是完全重组了这道题 角度非常独特  很厉害
// 我们可以知道  11234444668999  可以写成不同的后缀111111 相加的形式
// 后缀的长度不同  说明数字发生了变化  这个地方不理解的话 可以将数字拆开看看
// 那么其实这个长度最多有9种  因为1~9只有9个数字  每种长度数量可以有很多  但种类撑死就是9种
// 由于n的大小很大  但是p比较小  那么其实1111111   %p的值会形成一个循环
// 我们先收集出不同长度%p的余数相同的个数  按照%p的余数分类
// 我们使用背包  按照集合动态规划
// 因为不能有前导零  所以至少会有一个长度  那么也就说我们动态规划枚举的时候只需要枚举0~8
// 我认为这个思路的美妙就像哈希对于kmp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 999911659;
const int MAXN = 505;

int n,p;
// 记录每个余数的后缀1出现数量
int cnt[MAXN];
// 记录循环节长度
int cyclelen;
// 循环节开始的数字  这里也可以记录位置   我使用的是位置
int cyclestpos;
// 记录循环节的内容
int cycle[MAXN];
// 记录循环节中每个位置出现的数字
int firstpos[MAXN];
// dp[i][j][k]表示当前完成了前i个集合  已经选择了j个数字  余数为k的方案数
int dp[MAXN][10][MAXN];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

// 这里的b是小于等于8的   a是特别大的  所以这里是暴力计算

int comb(int a, int b) {
    if (b == 0) return 1;
    int x = 1, y = 1;
    for (int i = 0; i < b; i++) {
        x = x * (a - i) % MOD;
        y = y * (i + 1) % MOD;
    }
    return x * power(y, MOD - 2) % MOD;
}

signed main()
{
    cin>>n>>p;

    int base=0;//这个适用于记录全部都是1的余数  这个是必选的  因为没有前导零

    // 长度为1的后缀  其实就是1
    cycle[1]=1%p;
    firstpos[1%p]=1;
    // 一直循环直到遇见已经出现过的数字 即循环节出现
    for(int i=2;;i++){
        cycle[i]=(cycle[i-1]*10+1)%p;

        // 遇到了已经访问过的数字
        if(firstpos[cycle[i]]){
            // 记录循环节之前的  并且不能超过n  其实这里包含了第一个循环节
            for(int j=1;j<i&&j<=n;j++){
                cnt[cycle[j]]++;
                base=cycle[j];
            }
            n-=i-1;//没有处理的部分
            cyclestpos=firstpos[cycle[i]];
            cyclelen=i-firstpos[cycle[i]];
            break;
        }
        else{
            firstpos[cycle[i]]=i;
        }
    }

    n=max(n,0ll);
    int times=n/cyclelen;
    int rest=n%cyclelen;

    // 处理完整循环节
    for(int i=0;i<cyclelen;i++){
        cnt[cycle[i+cyclestpos]]+=times;
        cnt[cycle[i+cyclestpos]]%=MOD;
    }

    for(int i=0;i<rest;i++){
        cnt[cycle[i+cyclestpos]]++;
        base=cycle[i+cyclestpos];
    }

    // cout<<cyclestpos<<' '<<cyclelen<<' '<<base<<endl;

    // 这个地方不减最好  因为这个长度本身就可以不止一个 比如开头就是大于1的
    // 在这种情况下 如果你还想继续选择一个全都是1的  那么你剩余可以选的就不是9了  所以这个不能减去
    // 你选择了k个全都铺满的  那么你可以选的就剩下9-k  这里也很巧妙  设置成8
    // cnt[base]--;//这个一定会选  

    // 因为长度为n的必选要选 所以我们这个设置为默认值 可以选择的就只有8个了
    dp[0][0][base]=1;
        
    // 目前来到的集合是%p余数为i的集合
    for(int i=0;i<p;i++){
        // 这个集合以及之前已经使用过的量  注意这里是i+1  因为0被用过了
        for(int j=0;j<=8;j++){
            // 这个集合使用的量
            for(int k=0;k<=j;k++){
                int tmp=comb(cnt[i]+k-1,k);
                for(int d=0;d<p;d++){
                    // 这个以及之前的集合之后的余数
                    dp[i+1][j][d]=(dp[i+1][j][d]+tmp*dp[i][j-k][((d-k*i)%p+p)%p]%MOD)%MOD;
                }
            }
        }
    }

    int ans=0;
    for(int i=0;i<=8;i++){
        ans=(ans+dp[p][i][0])%MOD;
    }
    cout<<ans<<endl;
    return 0;
}