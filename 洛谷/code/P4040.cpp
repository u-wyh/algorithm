#include<bits/stdc++.h>
using namespace std;

const int MAXN = 205;

// 食物种类数
int n;

// 总预算、每次叫外卖的外送费
long long m, f;

// 按保质期从小到大排序后的价格和保质期
long long p[MAXN];
long long s[MAXN];

// bestp[i]表示第i种及其后面所有食物中的最低价格
long long bestp[MAXN];

// 一次外卖连续覆盖days天时，食物的最低费用
__int128 blockCost(long long days){
    __int128 ans = 0;

    // 上一个保质期，初始为-1
    long long last = -1;

    for(int i = 1; i <= n && days > 0; i++){
        // 偏移量last+1到s[i]的天数
        long long len = s[i] - last;
        long long take = min(days, len);

        ans += (__int128)take * bestp[i];

        days -= take;
        last = s[i];
    }

    return ans;
}

// 宅days天，并且恰好叫k次外卖时的最低费用
__int128 planCost(long long days, long long k){
    long long q = days / k;
    long long r = days % k;

    __int128 costq = blockCost(q);

    // 先令所有k段长度都是q
    __int128 ans = (__int128)k * f;
    ans += (__int128)k * costq;

    // 再把其中r段增加一天
    if(r > 0){
        ans += (__int128)r * (blockCost(q + 1) - costq);
    }

    return ans;
}

// 判断预算是否足够宅days天
bool check(long long days){
    if(days == 0) return true;

    // 一次外卖最多能够覆盖的天数
    long long maxlen = s[n] + 1;

    // 至少需要叫这么多次外卖
    long long left = (days - 1) / maxlen + 1;

    // 最多每天叫一次
    long long right = days;

    // planCost关于叫外卖次数是单峰函数
    while(right - left > 8){
        long long d = (right - left) / 3;

        long long mid1 = left + d;
        long long mid2 = right - d;

        if(planCost(days, mid1) <= planCost(days, mid2)){
            right = mid2 - 1;
        }
        else{
            left = mid1 + 1;
        }
    }

    __int128 best = (__int128)m + 1;

    for(long long k = left; k <= right; k++){
        best = min(best, planCost(days, k));
    }

    return best <= m;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> f >> n;

    long long minp = LLONG_MAX;

    for(int i = 1; i <= n; i++){
        cin >> p[i] >> s[i];
        minp = min(minp, p[i]);
    }

    // n最大只有200，直接按保质期排序
    for(int i = 1; i <= n; i++){
        for(int j = i + 1; j <= n; j++){
            if(s[i] > s[j]){
                long long temp = s[i];
                s[i] = s[j];
                s[j] = temp;

                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // 预处理后缀最低价格
    bestp[n] = p[n];

    for(int i = n - 1; i >= 1; i--){
        bestp[i] = min(p[i], bestp[i + 1]);
    }

    // 每天至少需要购买一份食物
    long long left = 0;
    long long right = m / minp;

    while(left < right){
        long long mid = left + (right - left + 1) / 2;

        if(check(mid)){
            left = mid;
        }
        else{
            right = mid - 1;
        }
    }

    cout << left << '\n';

    return 0;
}