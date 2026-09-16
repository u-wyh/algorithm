#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int change_num(char p) {
    switch (p) {
        case 'A': return 1;
        case 'T': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        default: return p - '0';
    }
}

int n, ans;
int color_count[14][4]; // 假设有4种花色，记录每种牌型的每种花色数量
int cnt[14]; // 存储每个牌点的数量，无视花色

int main() {
    // freopen("xinxin.in", "r", stdin);
    // freopen("xinxin.out", "w", stdout);
    char a, b;
    scanf("%d", &n);
    memset(cnt, 0, sizeof(cnt));
    memset(color_count, 0, sizeof(color_count));

    for (int i = 0; i < n; i++) {
        scanf(" %c%c", &a, &b);
        int t = change_num(b);
        cnt[t]++; // 该牌点的数量增加

        // 假设'S', 'H', 'D', 'C' 分别代表四种花色
        switch (a) {
            case 'S': color_count[t][0]++; break;
            case 'H': color_count[t][1]++; break;
            case 'D': color_count[t][2]++; break;
            case 'C': color_count[t][3]++; break;
        }
    }

    for (int i = 1; i <= 13; i++) {
        if (cnt[i] == 5) ans++; // 5张1对
        else if (cnt[i] >= 6) ans += 2; // 6,7,8张2对
        else if (cnt[i] >= 3 && cnt[i] <= 4) {
            int unique_colors = 0;
            for (int j = 0; j < 4; j++) {
                if (color_count[i][j] > 0) unique_colors++;
            }
            // 如果是3,4张，则看总花色数
            // 如果3张牌共有3个不同的花色 或 4张牌共有不同的4个花色，肯定不能组成“小昕昕”
            if (unique_colors == cnt[i]) ans++;
        }
    }

    printf("%d\n", ans);
    return 0;
}
