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
// 算法标签：二分答案、前缀计数

#include <stdio.h>

typedef struct{
    int start, end, step;
} Sequence;

Sequence seq[200005];
int n;

long long count_up_to(int x){
    long long count = 0;
    for(int i = 0; i < n; ++i){
        int start = seq[i].start, step = seq[i].step;
        if(x < start){
            continue;
        }
        int end = x < seq[i].end ? x : seq[i].end;
        count += step == 0 ? 1 : (end - start) / step + 1;
    }
    return count;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        int left = 0, right = 0;
        for(int i = 0; i < n; ++i){
            scanf("%d%d%d", &seq[i].start, &seq[i].end, &seq[i].step);
            if(seq[i].end > right){
                right = seq[i].end;
            }
        }
        if(count_up_to(right) % 2 == 0){
            puts("There's no weakness.");
            continue;
        }
        while(left < right){
            int mid = left + (right - left) / 2;
            if(count_up_to(mid) % 2 != 0){
                right = mid;
            }else{
                left = mid + 1;
            }
        }
        printf("%d %lld\n", left, count_up_to(left) - count_up_to(left - 1));
    }
    return 0;
}
