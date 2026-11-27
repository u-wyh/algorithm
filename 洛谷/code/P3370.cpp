// https://www.luogu.com.cn/problem/P3370
// 题意：输入字符串个数 N，以及 N 个包含数字和大小写字母的字符串（大小写敏感）。
// 统计这 N 个字符串中互不相同的字符串共有多少个。
// 输出不同的字符串个数。
// 数据范围：N <= 10000，单串长度 M_i 约 1000、最大 M_max <= 1500。
#include<bits/stdc++.h>
// 算法标签：字符串哈希、排序
using namespace std;

const int MAXN = 10001;
const int BASE = 499;

vector<long long> nums(MAXN);
int n;

int v(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0' + 1;
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 11;
    } else {
        return c - 'a' + 37;
    }
}

long long value(const string& s) {
    long long ans = v(s[0]);
    for (size_t i = 1; i < s.length(); i++) {
        ans = ans * BASE + v(s[i]);
    }
    return ans;
}

// 数字 + 大写 + 小写
// '0' -> 1
// '1' -> 2
// ...
// '9' -> 10
// 'A' -> 11
// 'B' -> 12
// ...
// 'Z' -> 36
// 'a' -> 37
// ...
// 'z' -> 62

int cnt() {
    sort(nums.begin(), nums.begin() + n);
    int ans = 1;
    for (int i = 1; i < n; i++) {
        if (nums[i] != nums[i - 1]) {
            ans++;
        }
    }
    return ans;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        string line;
        cin >> line;
        nums[i] = value(line);
    }
    cout << cnt() << endl;
    return 0;
}
