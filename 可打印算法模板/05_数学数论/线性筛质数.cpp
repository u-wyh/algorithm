// 用途：展示埃氏筛与欧拉线性筛的质数计数。
// 时间：欧拉筛 O(n)，埃氏筛 O(n log log n)。
// 空间：O(n)。
// 注意：输入 n<=1e6；输出三种计数互相核对；例题须改输入输出。
// 例题：https://leetcode.cn/problems/count-primes/
// 题意：统计小于 n 的质数个数。
// 思路：筛去合数；线性筛让每个合数只由其最小质因子处理一次。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

bool composite[MAXN];//用于埃氏筛统计是否是质数

int prime[MAXN];//欧拉筛中用于收集质数的数组
int num[MAXN];//记录每个数字的最小质因子

int ehrlich(int n) {
    memset(composite,0,sizeof(composite));
    for(int i=2;i*i<=n;i++){
        if(!composite[i]){
            for(int j=i*i;j<=n;j+=i){
                composite[j]=true;
            }
        }
    }

    int cnt=0;
    for(int i=2;i<=n;i++){
        if(!composite[i]){
            cnt++;
        }
    }
    return cnt;
}

// 每个合数仅由其最小质因子对应的步骤筛掉一次。
int euler(int n){
    int cnt=0;
    memset(num,0,sizeof(num));
    for(int i=2;i<=n;i++){
        if(num[i]==0){
            prime[++cnt]=i;
        }

        for(int j=1;j<=cnt&&1LL*i*prime[j]<=n;j++){
            num[i*prime[j]]=prime[j];
            if(i%prime[j]==0){
                break; // 每个合数只被其最小的质因数筛去一次
            }
        }
    }
    return cnt;
}

int ehrlich2(int n) {
    if (n <= 1) {
        return 0;
    }
    memset(composite,0,sizeof(composite));
    int cnt = (n + 1) / 2;
    for (int i = 3; i * i <= n; i += 2) {
		if (!composite[i]) {
			for (int j = i * i; j <= n; j += 2 * i) {
				if (!composite[j]) {
					composite[j] = true;
					cnt--;
				}
			}
		}
	}
	return cnt;
}

int main()
{
    int n;
    while(cin>>n){
        cout<<n<<": "<<ehrlich(n)<<' '<<euler(n)<<' '<<ehrlich2(n)<<endl;
    }
    return 0;
}
