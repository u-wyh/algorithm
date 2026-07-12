#include<bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 20;
const int MAXS = 1 << MAXN;

int n;
long long m;

// 当前起点集合覆盖了多少个原串位置
int coverLen[MAXS];

// 当前起点集合产生的周期 gcd
// 0 表示暂时没有发生重叠
int periodGcd[MAXS];

// 状态中 1 的个数的奇偶性
unsigned char parityBit[MAXS];

long long powerM[MAXN + 1];

long long gcd(long long a,long long b){
    return b==0?a:gcd(b,a%b);
}

long long qpow(long long x, long long y){
    long long res = 1;

    while(y){
        if(y & 1){
            res = res * x % MOD;
        }

        x = x * x % MOD;
        y >>= 1;
    }

    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    powerM[0] = 1;

    for(int i = 1; i <= n; i++){
        powerM[i] = powerM[i - 1] * (m % MOD) % MOD;
    }

    int allLimit = 1 << n;

    for(int mask = 1; mask < allLimit; mask++){
        parityBit[mask] = parityBit[mask >> 1] ^ (mask & 1);
    }

    // 所有字符串的复杂度总和
    long long answerSum = 0;

    // 枚举子串长度
    for(int len = 1; len <= n; len++){
        int startCount = n - len + 1;
        int limit = 1 << startCount;

        // 枚举至少出现一次的位置集合
        for(int mask = 1; mask < limit; mask++){
            // 当前集合中最大的起点
            int highest = 31 - __builtin_clz(mask);

            // 删除最大的起点
            int previous = mask ^ (1 << highest);

            if(previous == 0){
                // 只有一个子串
                coverLen[mask] = len;
                periodGcd[mask] = 0;
            }
            else{
                // 原集合中第二大的起点
                int previousHighest = 31 - __builtin_clz(previous);

                // 两个相邻选中起点之间的距离
                int distance = highest - previousHighest;

                // 加入新区间后增加的覆盖长度
                coverLen[mask] =
                    coverLen[previous] + min(distance, len);

                periodGcd[mask] = periodGcd[previous];

                // 两个子串发生重叠
                if(distance < len){
                    if(periodGcd[mask] == 0){
                        periodGcd[mask] = distance;
                    }
                    else{
                        periodGcd[mask] =
                            gcd(periodGcd[mask], distance);
                    }
                }
            }

            // 模式串内部独立字符的数量
            int patternParts;

            if(periodGcd[mask] == 0){
                patternParts = len;
            }
            else{
                patternParts = periodGcd[mask];
            }

            // 未被覆盖的位置可以任取
            // 被覆盖部分由模式串的独立字符决定
            int componentCount =
                n - coverLen[mask] + patternParts;

            // 容斥
            if(parityBit[mask]){
                answerSum += powerM[componentCount];

                if(answerSum >= MOD){
                    answerSum -= MOD;
                }
            }
            else{
                answerSum -= powerM[componentCount];

                if(answerSum < 0){
                    answerSum += MOD;
                }
            }
        }
    }

    // 除以总字符串数量 m^n
    long long inverseTotal = qpow(powerM[n], MOD - 2);

    cout << answerSum * inverseTotal % MOD << '\n';

    return 0;
}