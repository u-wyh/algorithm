#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxtot = 20005;
const int maxm = 4e6 + 5;
const int base = 131;

string S[maxtot], T[maxtot];
int totalS, totalT, n, m;
int mid; // 前后串的长度
int Pow[2005]; // 预计算的幂
unordered_map<int, int> hashT; // 存储T的所有字符串

// 快速幂计算
int qmi(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

// 一次性哈希函数
int make_hash(const string& s, int len) {
    int res = 0;
    for (int i = 0; i < len; i++) {
        res = res * base + s[i];
    }
    return res;
}

// 计算字符串所有旋转的哈希值（去重版本）
vector<int> get_rotation_hashes(const string& str) {
    int len = str.length();
    string doubled = str + str;
    unordered_set<int> unique_hashes;
    
    // 预计算哈希数组
    vector<int> hash_arr(len * 2 + 1, 0);
    for (int i = 1; i <= len * 2; i++) {
        hash_arr[i] = hash_arr[i - 1] * base + doubled[i - 1];
    }
    
    // 获取所有旋转的哈希值并去重
    for (int i = 0; i < len; i++) {
        int h = hash_arr[i + len] - hash_arr[i] * Pow[len];
        unique_hashes.insert(h);
    }
    
    // 转换为向量返回
    vector<int> hashes(unique_hashes.begin(), unique_hashes.end());
    return hashes;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> totalS >> totalT >> n >> m;
    for (int i = 0; i < totalS; i++) {
        cin >> S[i];
    }
    for (int i = 0; i < totalT; i++) {
        cin >> T[i];
    }
    
    mid = (n + m) / 2;
    
    // 预计算我们需要的幂
    Pow[0] = 1;
    for (int i = 1; i <= 2000; i++) {
        Pow[i] = Pow[i - 1] * base;
    }
    
    // 对T中的所有字符串哈希并计数
    for (int i = 0; i < totalT; i++) {
        int h = make_hash(T[i], m);
        hashT[h]++;
    }
    
    long long ans = 0;
    
    for (int i = 0; i < totalS; i++) {
        string U = S[i].substr(0, mid);
        string V_prefix = S[i].substr(mid, n - mid);
        
        vector<int> rotation_hashes = get_rotation_hashes(U);
        
        int hash_V_prefix = make_hash(V_prefix, n - mid);
        
        for (int rot_hash : rotation_hashes) {
            int required_T_hash = rot_hash - hash_V_prefix * Pow[m];
            
            if (hashT.find(required_T_hash) != hashT.end()) {
                ans += hashT[required_T_hash];
            }
        }
    }
    
    cout << ans << endl;
    return 0;
}