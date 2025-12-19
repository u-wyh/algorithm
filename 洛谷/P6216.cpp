#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e6+5;
const int BASE = 499;

int n,m,N;
string s1,s2;
char ss[MAXN<<1];
int arr[MAXN];
int R[MAXN<<1];
long long p[MAXN];
long long h[MAXN];

void build(const string& str) {
    p[0] = 1;
    for (int j = 1; j < MAXN; ++j) {
        p[j] = p[j - 1] * BASE;
    }
    h[0] = str[0] - 'a' + 1;
    for (int j = 1; j <(int) str.length(); ++j) {
        h[j] = h[j - 1] * BASE + str[j] - 'a' + 1;
    }
}

long long getHash(int l, int r) {
    long long ans = h[r];
    if (l > 0) {
        ans -= h[l - 1] * p[r - l +1];
    }
    return ans;
}

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

void manacherss() {
    N = n * 2 + 1;
    for (int i = 0, j = 0; i < N; i++) {
        ss[i] = (i & 1) == 0 ? '#' : s1[j++];
    }
    printf("%s\n",ss);
}

void manacher() {
    manacherss();
    int maxans = 0;
    for (int i = 0, c = 0, r = 0, len; i < N; i++) {
        len = r > i ? min(R[2 * c - i], r - i) : 1;
        while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        maxans = max(maxans, len);
        R[i] = len;
    }
}

int main() {
    cin>>n>>m;
    cin>>s1>>s2;
    build(s1);
    long long val=hashString(s2);
    for(int i=0;i<n;i++){
        if(val==getHash(i,i+m-1)){
            arr[i]++;
        }
    }
    for(int i=0;i<n;i++){
        arr[i]+=arr[i-1];
    }
    manacher();
    for(int i=0;i<n;i++){
        R[i]=R[2*i+1];
        cout<<R[i]<<endl;
    }
    return 0;
}