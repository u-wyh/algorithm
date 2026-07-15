#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int min(int a,int b){
    return a<b?a:b;
}
/*
    想要求出最大的得分，那么最多可以输一局
    如果d >= n - 1  那么说明存在至少可以赢(n-1)局   也就是最多平一局或者输一局
        首先考虑赢得多
        如果(d - n + 1 > e)  表示即使赢了(n-1)局   依旧进的球比e大   说明还可以赢
        否则考虑(d - n + 1 == e)  表示最后一局可以平球  否则  就是输了一局
        其次考虑增加平局
        在这样的情况下  我们不得不考虑通过牺牲掉一局或者多局胜利来消除失败获取平局   比较一下得分
        (ans1 > (c + (ll)min(d - e, n - 1) * a + ((d - e < n - 1) ? (ll)(n - 1 - d + e) * c : 0)))
        其实min(d - e, n - 1)就是d-e   那么平局的数量就是(n-1)-(d-e)
    如果不满足d >= n - 1
        首先考虑赢得多
        那么最多可以赢d局  然后输一局  剩下的双方都是零分战平
        其次考虑增加平局
        如果说d>=e  那么才可以增加平局   否则免谈
        如果增加平局  那么必然是有e轮是增加的   否则还是会输一局并且赢的局数还会减少


    想要求出最小的得分，那么最多可以赢一局
    如果e >= n - 1 那么说明存在至少可以输(n-1)局   也就是最多平一局或者赢一局
        首先考虑输得多
        如果(e - n + 1 > d)  表示即使输了(n-1)局   依旧进的球比e小   说明还可以输
        否则考虑(e - n + 1 == d)  表示最后一局可以平球  否则  就是赢了一局
        其次考虑增加平局
        在这样的情况下  我们不得不考虑通过牺牲掉一局或者多局失败来消除胜利获取平局   比较一下得分
        (ans2 < (c + (ll)min(e - d, n - 1) * b + ((e - d < n - 1) ? (ll)(n - 1 - e + d) * c : 0)))
        其实min(e - d, n - 1)就是e-d   那么平局的数量就是(n-1)-(e-d)
    如果不满足e >= n - 1
        首先考虑输得多
        那么最多可以输e局  然后赢一局  剩下的双方都是零分战平
        其次考虑增加平局
        如果说e>=d  那么才可以增加平局   否则免谈
        如果增加平局  那么必然是有e轮是增加的   否则还是会赢一局并且输的局数还会减少
*/
int main() {
    int t, n, a, b, c, d, e;
    ll ans1, ans2;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d %d %d %d", &n, &a, &b, &c, &d, &e);

        if (d >= n - 1) {
            ans1 = (ll)(n - 1) * a + ((d - n + 1 > e) ? a : ((d - n + 1 == e) ? c : b));

            if (d - n + 1 < e && d >= e) {
                ans1 = (ans1 > (c + (ll)min(d - e, n - 1) * a + ((d - e < n - 1) ? (ll)(n - 1 - d + e) * c : 0))) ? ans1 : (c + (ll)min(d - e, n - 1) * a + ((d - e < n - 1) ? (ll)(n - 1 - d + e) * c : 0));
            }
        } else {
            ans1 = (ll)d * a + (ll)(n - d - 1) * c + b;
            if (e <= d) {
                ans1 = (ans1 > ((ll)e * c + (ll)(d - e) * a + (ll)(n - d) * c)) ? ans1 : ((ll)e * c + (ll)(d - e) * a + (ll)(n - d) * c);
            }
        }

        if (e >= n - 1) {
            ans2 = (ll)(n - 1) * b + ((e - n + 1 > d) ? b : ((e - n + 1 == d) ? c : a));
            if (e - n + 1 < d && e >= d) {
                ans2 = (ans2 < (c + (ll)(e - d) * b +(ll)(n - 1 - e + d) * c )) ? ans2 : (c + (ll)(e - d) * b +(ll)(n - 1 - e + d) * c );
        } else {
            ans2 = (ll)e * b + (ll)(n - e - 1) * c + a;
            if (d <= e) {
                ans2 = (ans2 < ((ll)d * c + (ll)(e - d) * b + (ll)(n - e) * c)) ? ans2 : ((ll)d * c + (ll)(e - d) * b + (ll)(n - e) * c);
            }
        }

        printf("%lld %lld\n", ans1, ans2);
    }
    return 0;
}
