#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int BASE = 499;

vector<int>h[MAXN];
int power[MAXN];
int len[MAXN];
string str[MAXN];
int n,m;
map<long long>pre;
map<long long>suf;

void build() {
    power[0] = 1;
    for (int j = 1; j < MAXN; ++j) {
        power[j] = power[j - 1] * BASE;
    }
}

long long getHash(int l, int r,vector<int> hash_val) {
    long long ans = hash_val[r ];
    if (l > 0) {
        ans -= hash_val[l - 1] * power[r - l +1 ];
    }
    return ans;
}

// 计算一个字符串的哈希值
long long hashString(const string& str) {
    if (str.empty()) {
        return 0;
    }
    int n = str.length();
    long long ans = str[0] - 'a' + 1;
    for (int j = 1; j < n; ++j) {
        ans = ans * BASE + str[j] - 'a' + 1;
    }
    return ans;
}

void prepare(){
    for(int i=0;i<n;i++){
        h[i].push_back( str[i][0] - 'a' + 1);
        for (int j = 1; j < str[i].length(); ++j) {
            h[i].push_back(h[i][j - 1] * BASE + str[i][j] - 'a' + 1);
        }
    }
}

signed main() {
    cin >> n >>m;
    build();
    for(int i=0;i<n;i++){
        cin>>str[i];
        len[i]=(int)str[i].length();
    }
    prepare();
    for(int i=0;i<n;i++){
        for(int r=0;r<len[i];r++){
            pre[getHash(0,r,h[i])]++;
        }

        for(int l=0;l<len[i];r++){
            suf[getHash(l,len[i],h[i])]++;
        }
    }
    for(int i=1;i<=m;i++){
        int ans=0;
        string pre,suf;
        cin>>pre>>suf;
    }
    return 0;
}


