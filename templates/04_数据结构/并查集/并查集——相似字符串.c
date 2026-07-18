// 相似字符串组
// 如果交换字符串 X 中的两个不同位置的字母，使得它和字符串 Y 相等
// 那么称 X 和 Y 两个字符串相似
// 如果这两个字符串本身是相等的，那它们也是相似的
// 例如，"tars" 和 "rats" 是相似的 (交换 0 与 2 的位置)；
// "rats" 和 "arts" 也是相似的，但是 "star" 不与 "tars"，"rats"，或 "arts" 相似
// 总之，它们通过相似性形成了两个关联组：{"tars", "rats", "arts"} 和 {"star"}
// 注意，"tars" 和 "arts" 是在同一组中，即使它们并不相似
// 形式上，对每个组而言，要确定一个单词在组中，只需要这个词和该组中至少一个单词相似。
// 给你一个字符串列表 strs列表中的每个字符串都是 strs 中其它所有字符串的一个字母异位词。
// 返回 strs 中有多少字符串组
// 测试链接 : https://leetcode.cn/problems/similar-string-groups/
#include <stdio.h>
#include <string.h>

#define MAXN 301

int father[MAXN];
int sets;

void build(int n) {
    for (int i = 0; i < n; i++) {
        father[i] = i;
    }
    sets = n;
}

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

void union_sets(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) {
        father[fx] = fy;
        sets--;
    }
}

int numSimilarGroups(char* strs[], int n) {
    int m = strlen(strs[0]); // 假设所有字符串长度相同
    build(n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (find(i) != find(j)) {
                int diff = 0;
                for (int k = 0; k < m && diff < 3; k++) {
                    if (strs[i][k] != strs[j][k]) {
                        diff++;
                    }
                }
                if (diff == 0 || diff == 2) {
                    union_sets(i, j);
                }
            }
        }
    }

    return sets;
}

int main() {
    char* strs[] = {"star", "sart", "atsr", "asbt", "aart"};
    int n = sizeof(strs) / sizeof(strs[0]);
    int result = numSimilarGroups(strs, n);
    printf("Number of similar groups: %d\n", result);
    return 0;
}