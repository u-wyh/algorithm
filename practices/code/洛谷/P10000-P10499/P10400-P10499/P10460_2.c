// https://www.luogu.com.cn/problem/P10460
// 题意：每组给 N 个防具等差序列。
// 参数 S、E、D 表示从 S 起每次加 D，至多到 E。
// 最多只有一个位置的防具数为奇数。
// 输出：若有该位置，输出位置和防具数。
// 否则输出 There's no weakness.。
// 数据范围：1 <= T <= 5，N <= 2*10^5，S <= E。
// S、E、D 均在 [0, 2^31-1] 内。
// 防具总数不超过 10^8。
// 难度评分：1300（洛谷分级换算）
// 算法标签：枚举、异或

#include <stdio.h>

typedef struct{
    int start, end, step;
} Sequence;

Sequence seq[200005];

int main(void)
{
    int t;
    scanf("%d", &t);
    while(t--){
        int n, position = 0;
        scanf("%d", &n);
        for(int i = 0; i < n; ++i){
            int s, e, d;
            scanf("%d%d%d", &s, &e, &d);
            seq[i] = (Sequence){s, e, d};
            if(d == 0){
                position ^= s;
            }else{
                for(long long k = s; k <= e; k += d){
                    position ^= (int)k;
                }
            }
        }

        int count = 0;
        for(int i = 0; i < n; ++i){
            int s = seq[i].start, e = seq[i].end, d = seq[i].step;
            if(position >= s && position <= e &&
               (d == 0 ? position == s : (position - s) % d == 0)){
                ++count;
            }
        }
        if(count % 2 == 0){
            puts("There's no weakness.");
        }else{
            printf("%d %d\n", position, count);
        }
    }
    return 0;
}
