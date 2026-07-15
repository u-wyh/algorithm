#include<bits/stdc++.h>
using namespace std;

int n;
char a[110][200];  // 无效单词
char c1[200];
char c[200];
char all[200][200]; // 有效单词
int ma[26][200];    // 每个字母的有效位置
int tag[200];
int tag1[200];      // 两个标记
int cut[200];       // 单词的尾后位置
int sum[26];        // 出现的次数
int f[200][200];    // dp数组

int main() {
    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", a[i]);
    }
    scanf("%s", c1);
    
    while (1) {
        int word_count = 1;
        strcpy(c, c1);
        if (strcmp(c, "LAST") == 0) {
            scanf("%s", all[word_count++]);
            if (strcmp(all[word_count-1], "CASE") == 0) break;
        }
        
        while (cin >> all[word_count++]) {
            int j = 0;
            int len = strlen(all[word_count-1]);
            while (all[word_count-1][j] < 'a' && j < len) j++;
            if (j >= len) {
                strcpy(c1, all[word_count-1]);
                word_count--;
                break;
            } else {
                for (int i = 1; i <= n; i++) {
                    if (strcmp(a[i], all[word_count-1]) == 0) {
                        word_count--;
                        break;
                    }
                }
            }
        }
        word_count--;
        printf("%s ", c);
        int len = strlen(c);
        for (int i = 0; i < len; i++) {
            c[i] = c[i] + 32;
        }
        
        // 处理三种情况
        if (len < word_count) {
            puts("is not a valid abbreviation");
        } else if (len == word_count) {
            int ans = 1;
            for (int i = 0; i < len; i++) {
                int len2 = strlen(all[i+1]);
                int tmp = 0;
                for (int j = 0; j < len2; j++) {
                    if (all[i+1][j] == c[i]) tmp++;
                }
                if (tmp) {
                    ans *= tmp;
                } else {
                    puts("is not a valid abbreviation");
                    ans = 0;
                    break;
                }
            }
            if (ans) {
                printf("can be formed in %d ways\n", ans);
            }
        } else {
            memset(sum, 0, sizeof(sum));
            memset(f, 0, sizeof(f));
            memset(tag, 0, sizeof(tag));
            memset(cut, 0, sizeof(cut));
            memset(ma, 0, sizeof(ma));
            
            int total_len = strlen(all[1]);
            for (int i = 2; i <= word_count; i++) {
                strcpy(all[1] + total_len, all[i]);
                cut[i-1] = total_len;
                total_len = strlen(all[1]);
            }
            cut[word_count] = total_len;
            
            for (int i = 0; i < total_len; i++) {
                int j = all[1][i] - 'a';
                ma[j][++sum[j]] = i;
            }
            
            for (int k = 0; k < len; k++) {
                int id = c[k] - 'a';
                int ci = min(k+1, word_count);
                int ti = 1;
                
                for (int i = 0; i < total_len; i++) {
                    tag1[i] = tag[i];
                }
                
                for (int i = 1; i <= sum[id] && ma[id][i] < cut[ci]; i++) {
                    while (ma[id][i] >= cut[ti]) ti++;
                    if (word_count - ti > len - k - 1) continue;
                    
                    if (k == 0) {
                        tag1[ma[id][i]] = 0;
                        f[k][i] = 1;
                    } else {
                        int t = c[k-1] - 'a';
                        for (int j = 1; j <= sum[t]; j++) {
                            if (ma[t][j] < ma[id][i] && ma[t][j] >= cut[ti-2] && tag[ma[t][j]] == k-1) {
                                f[k][i] += f[k-1][j];
                                tag1[ma[id][i]] = k;
                            }
                        }
                    }
                }
                
                for (int i = 0; i < total_len; i++) {
                    tag[i] = tag1[i];
                }
            }
            
            int ans = 0;
            for (int i = 1; i <= sum[c[len-1]-'a']; i++) {
                ans += f[len-1][i];
            }
            
            if (ans) {
                printf("can be formed in %d ways\n", ans);
            } else {
                puts("is not a valid abbreviation");
            }
        }
    }
    return 0;
}