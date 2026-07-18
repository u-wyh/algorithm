// 计数质数
// 给定整数n，返回小于非负整数n的质数的数量
// 测试链接 : https://leetcode.cn/problems/count-primes/
//这里介绍两种质数筛：埃氏筛 欧拉筛
//埃氏筛很容易理解
//欧拉筛的扩展功能很强  可以记录每个数字的最小质因子
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

bool visit[MAXN];//用于埃氏筛统计是否是质数

int prime[MAXN];//欧拉筛中用于收集质数的数组
int num[MAXN];//记录每个数字的最小质因子

// 埃氏筛统计0 ~ n范围内的质数个数
// 时间复杂度O(n * log(logn))
int ehrlich(int n) {
    memset(visit,0,sizeof(visit));
    // 初始时认为0~n所有数都是质数，但0和1不是质数
    for(int i=2;i*i<=n;i++){
        if(!visit[i]){
            for(int j=i*i;j<=n;j+=i){
                visit[j]=true;
            }
        }
    }

    int cnt=0;
    for(int i=2;i<=n;i++){
        if(!visit[i]){
            cnt++;
        }
    }
    return cnt;
}

// 欧拉筛统计0 ~ n范围内的质数个数
// 时间复杂度O(n)
//欧拉筛还可以设置每个数字的最小质因子
int euler(int n){
    int cnt=0;
    memset(num,0,sizeof(num));
    for(int i=2;i<=n;i++){
        if(num[i]==0){
            prime[++cnt]=i;
        }

        //无论是不是质数  都要进行下面的过程
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            num[i*prime[j]]=prime[j];
            if(i%prime[j]==0){
                //如果i可以整除prime[j]说明一定含有这个质因子
                //那么如果继续的话  就是将接下来的数字的按照下一个质数作为他的最小质因子排除的
                //而不是被最小质因子排除的  所以不能继续  要立即跳出
                break; // 每个合数只被其最小的质因数筛去一次
            }
        }
    }
    return cnt;
}

// 改进版埃氏筛，仅计数
int ehrlich2(int n) {
    if (n <= 1) {
        return 0;
    }
    // visit[i] = true，代表i是合数
	// visit[i] = false，代表i是质数
	// 初始时认为0~n所有数都是质数
    memset(visit,0,sizeof(visit));
    // 先把所有的偶数去掉，但是算上2
	// 估计的质数数量，如果发现更多合数，那么cnt--
    int cnt = (n + 1) / 2;
    //从此之后 不在有任何偶数参与判断了
    for (int i = 3; i * i <= n; i += 2) {
		if (!visit[i]) {
			for (int j = i * i; j <= n; j += 2 * i) {
				if (!visit[j]) {
					visit[j] = true;
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