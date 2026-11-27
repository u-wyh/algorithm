// https://www.luogu.com.cn/problem/P5546
// 题意：给定 n 个仅由小写字母组成的单词，求它们的最长公共子串的长度。
// 输入 n 及 n 个字符串；输出最长公共子串长度。
// 数据范围：1 <= n <= 5，每个单词长度在 1 到 2000 之间。
// 算法标签：二分答案、字符串哈希
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2005;
const int BASE = 499;

int h[5][MAXN];
int power[MAXN];
string str[5];
int n,m;
map<long long,int>t;
map<long long,int>vis;

void build() {
    power[0] = 1;
    for (int j = 1; j < MAXN; ++j) {
        power[j] = power[j - 1] * BASE;
    }
}

// 范围是s[l,r)，左闭右开
long long getHash(int l, int r,int *hash_val) {
    long long ans = hash_val[r ];
    if (l > 0) {
        ans -= hash_val[l - 1] * power[r - l +1 ];
    }
    return ans;
}

void prepare(){
    for(int i=0;i<n;i++){
        h[i][0] = str[i][0] - 'a' + 1;
        for (int j = 1; j < str[i].length(); ++j) {
            h[i][j] = h[i][j - 1] * BASE + str[i][j] - 'a' + 1;
        }
    }
}

bool check(int limit){
    bool flag=false;
    for(int i=0;i<n;i++){
        int m=(int)str[i].length();
        for(int l=0;l+limit<=m;l++){
            int r=l+limit-1;
            long long tmp=getHash(l,r,h[i]);
            if(vis[tmp]!=i+1){
                t[tmp]++;
                vis[tmp]=i+1;
            }
            if(i==n-1&&t[tmp]==n){
                flag=true;
                break;
            }
        }
    }
    vis.clear();
    t.clear();
    return flag;
}

signed main() {
    cin >> n;
    build();
    m=2006;
    for(int i=0;i<n;i++){
        cin>>str[i];
        m=min((int)str[i].length(),m);
    }
    prepare();
    int l=0,r=m,ans=0;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    cout<<ans<<endl;
    return 0;
}

