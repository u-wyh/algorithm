//https://www.luogu.com.cn/problem/P4397
//数论知识： 一个数字可以可以表示为质数的次方乘积 N=P1^a1​​∗P2^a2​​∗…∗Pn^an​​，
//并且他所有的因子之和为 (1+p1+p1^2+…+p1^a1)*(1+p2+p2^2+…+p2^a2)*…*(1+pn+pn^2+…+pn^an)
//这道题要求数字满足他的因子之和等于固定值
//那么可以枚举质因子p1 p2 p3 pn
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;//因为数字最大是1e9  那么质因子最大不会超过1e5

int prime[MAXN],cnt;//填上1e5以内的质数
bool visit[MAXN];
int n;
int ans[MAXN],tot;//用于统计答案

void euler(int n) {
    for (int i = 2; i <= n; i++) {
        if (!visit[i]) {
            prime[++cnt] = i;
        }

        for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
            //每一次从最小的质数开始
            visit[i * prime[j]] = 1; // 标记为合数
            if (i % prime[j] == 0) {
                //如果i可以整除prime[j]说明一定含有这个质因子
                //那么如果继续的话  就是将接下来的数字的按照下一个质数作为他的最小质因子排除的
                //不是最小质因子排除的  所以不能继续  要立即跳出
                break; // 每个合数只被其最小的质因数筛去一次
            }
        }
    }
}

bool isprime(int x) {
    if (x == 1)
        return false;
    for (int i = 1; i<=cnt&&prime[i]*prime[i]<=x; i++) {
        if (x % prime[i] == 0)
            return false;
    }
    return true;
}

void dfs(int rest,int u,int now){
    //表示现在开始判断第u个质数能否成为p
    //rest的意思是已经选择过的质数的(1+p1+p1^2+…+p1^a1)*(1+p2+p2^2+…+p2^a2)  被除过后还有多少要完成
    //now表示经过前面选择的质数 P1^a1​​∗P2^a2​​ 到目前是now
    if(rest==1){
        //如果这个rest=1  说明now的所有因子之和就是要求的  那么记录答案
        ans[++tot]=now;
        return ;
    }
    if (isprime(rest - 1) && rest > prime[u]) {
        ans[++tot] = now * (rest - 1);//这个要特判 即1+pi 这种只有两项的
    }
    for(int i=u;prime[i]*prime[i]<=rest;i++){
        int t=prime[i];//t表示的选择的质数的次方代表
        int sum=prime[i]+1;//sum表示的是因子和代表
        while(sum<=rest){
            if(rest%sum==0){
                //只有可以整除才行  因为整除后的结果表示的是(1+p2+p2^2+…+p2^a2)*…*(1+pn+pn^2+…+pn^an)
                dfs(rest/sum,i+1,now*t);
                //表示的是如今的这个质数的(1+pn+pn^2+…+pn^an)是sum
                //选择的数字目前是now*t（t是这个质数的次方）
            }
            t*=prime[i];//表示阶数增加一个
            sum+=t;//sum要累加 表示1+p1+p1^2+…+p1^a1
        }
    }
}

int main()
{
    //准备好质数数组
    euler(100000);
    while(cin>>n){
        tot=0;
        dfs(n,1,1);
        sort(ans + 1, ans + tot + 1);
        cout<<tot<<endl;
        for (int i = 1; i <= tot; i++) {
            cout<<ans[i]<<' ';
        }
        if (tot)
            cout<<endl;
    }
    return 0;
}