// 用途：查找由给定等长单词各用一次、连续拼接而成的所有子串起点。
// 时间：O(n+L)，n 为文本长、L 为所有单词总长；哈希表操作按均摊 O(1) 计。
// 空间：O(n+L)。
// 注意：文本长≤10000，单词非空且等长；64 位哈希仍有碰撞概率。
// 例题：https://leetcode.cn/problems/substring-with-concatenation-of-all-words/
// 题意：找出由给定单词各用一次、紧挨拼成的所有子串起点。
// 思路：将等长单词及文本块哈希，按起点模单词长度分组滑动计数。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10001;
const int BASE = 499;
using u64 = unsigned long long; // 无符号溢出等价于模 2^64，行为有定义。

u64 power[MAXN];
u64 hash_val[MAXN];

void build(const string& str) {
    power[0] = 1;
    for (int j = 1; j <= (int)str.length(); ++j) {
        power[j] = power[j - 1] * BASE;
    }
    hash_val[0] = str[0] - 'a' + 1;
    for (int j = 1; j < str.length(); ++j) {
        hash_val[j] = hash_val[j - 1] * BASE + str[j] - 'a' + 1;
    }
}

// 如下代码是字符串哈希的原理和模版
// 比如，base = 499, 也就是课上说的选择的质数进制
// 再比如字符串s如下
// " c a b e f "
//   0 1 2 3 4
// hash[0] = 3 * base的0次方
// hash[1] = 3 * base的1次方 + 1 * base的0次方
// hash[2] = 3 * base的2次方 + 1 * base的1次方 + 2 * base的0次方
// hash[3] = 3 * base的3次方 + 1 * base的2次方 + 2 * base的1次方 + 5 * base的0次方
// hash[4] = 3 * base的4次方 + 1 * base的3次方 + 2 * base的2次方 + 5 * base的1次方 + 6 *
// base的0次方
// hash[i] = hash[i-1] * base + s[i] - 'a' + 1，就是上面说的意思
// 想计算子串"be"的哈希值 -> 2 * base的1次方 + 5 * base的0次方
// 子串"be"的哈希值 = hash[3] - hash[1] * base的2次方(子串"be"的长度次方)
// hash[1] = 3 * base的1次方 + 1 * base的0次方
// hash[1] * base的2次方 = 3 * base的3次方 + 1 * base的2次方
// hash[3] = 3 * base的3次方 + 1 * base的2次方 + 2 * base的1次方 + 5 * base的0次方
// hash[3] - hash[1] * base的2次方 = 2 * base的1次方 + 5 * base的0次方
// 这样就得到子串"be"的哈希值了
// 子串s[l...r]的哈希值 = hash[r] - hash[l-1] * base的(r-l+1)次方，就是上面说的意思

// 范围是s[l,r)，左闭右开
u64 getHash(int l, int r) {
    u64 ans = hash_val[r - 1];
    if (l > 0) {
        ans -= hash_val[l - 1] * power[r - l];
    }
    return ans;
}

// 计算一个字符串的哈希值
u64 hashString(const string& str) {
    if (str.empty()) {
        return 0;
    }
    int n = str.length();
    u64 ans = str[0] - 'a' + 1;
    for (int j = 1; j < n; ++j) {
        ans = ans * BASE + str[j] - 'a' + 1;
    }
    return ans;
}

vector<int> findSubstring(const string& s, const vector<string>& words) {
    vector<int> ans;
    if (s.empty() || words.empty()) {
        return ans;
    }
    // words的词频表
    unordered_map<u64, int> map;
    for (const string& key : words) {
        u64 v = hashString(key);
        map[v]++;
    }
    build(s);
    int n = s.length();
    int wordLen = words[0].length();
    int wordNum = words.size();
    int allLen = wordLen * wordNum;
    // 窗口的词频表
    unordered_map<u64, int> window;
    for (int init = 0; init < wordLen && init + allLen <= n; ++init) { // 同余分组
        // init是当前组的首个开头
        int debt = wordNum;
        // 建立起窗口
        for (int l = init, r = init + wordLen, part = 0; part < wordNum; l += wordLen, r += wordLen, ++part) {
            u64 cur = getHash(l, r);
            window[cur]++;
            if (window[cur] <= map[cur]) {
                debt--;
            }
        }
        if (debt == 0) {
            ans.push_back(init);
        }
        // 接下来窗口进一个、出一个
        for (int l1 = init, r1 = init + wordLen, l2 = init + allLen,
             r2 = init + allLen + wordLen; r2 <= n; l1 += wordLen, r1 += wordLen, l2 += wordLen, r2 += wordLen) {
            u64 out = getHash(l1, r1);
            u64 in = getHash(l2, r2);
            window[out]--;
            if (window[out] < map[out]) {
                debt++;
            }
            window[in]++;
            if (window[in] <= map[in]) {
                debt--;
            }
            if (debt == 0) {
                ans.push_back(r1);
            }
        }
        window.clear();
    }
    return ans;
}

int main() {
    string s ;
    int n;
    cin>>s>>n;
    vector<string> words;
    for(int i=0;i<n;i++){
        string str;
        cin >>str;
        words.push_back(str);
    }
    vector<int> result = findSubstring(s, words);
    for (int index : result) {
        cout << index << " ";
    }
    cout << endl;
    return 0;
}
// 如果s的长度为n，words里所有单词的总长度为m
// 时间复杂度O(n + m)，最优解的时间复杂度与单词个数、单词长度是无关的
// 所有题解都没有做到这个复杂度的
// 虽然这个做法打败比例没有到100%，但那是因为测试数据量不够大
// 所以最优解的时间复杂度优势没有体现出来
// 这个方法绝对是最优解，只有同余分组 + 字符串哈希，时间复杂度才能到最优
/*
barfoothefoobarman
2
foo
bar

barfoofoobarthefoobarman
3
bar
foo
the

wordgoodgoodgoodbestword
4
word
best
good
word
*/
