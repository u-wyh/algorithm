// https://www.luogu.com.cn/problem/P8643
// 题意：输入 n, m, k 和 n 个仅含 A, G, C, T 的非空 DNA 字符串（下标从 1 开始，长度可不同）；
// 统计满足 1 <= i_1 < i_2 < ... < i_m <= n 且各串从 p_1, ..., p_m 起长为 k 的子串完全相等的 2m 元组 (i_1, p_1, ..., i_m, p_m) 数量（任一位置不同视为不同）
// 输出对 10^9+7 取模的结果。
// 数据范围：n <= 5，m <= 5，1 <= k <= L <= 10^5（L 为所有字符串总长）。
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
const int BASE = 499;
const int MAXN = 1e5+5;

map<long long,int>graph;
map<long long,int>last;
string str[5];
int n,m,k;
long long p[MAXN];
long long h[5][MAXN];
int c[5]={0,5,10,10,5,1};
vector<long long>vec;
map<pair<int,long long>,int>rec;

void prepare(){
    p[0]=1;
    for(int i=1;i<=MAXN;i++){
        p[i]=p[i-1]*BASE;
    }
}

inline long long gethash(int i,int l,int r){
    long long ans=h[i][r];
    if(l>0){
        ans-=h[i][l-1]*p[r-l+1];
    }
    return ans;
}

int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        cin>>str[i-1];
    }
    for(int i=0;i<n;i++){
        h[i][0]=str[i][0]-'A'+1;
        for(int j=0;j<str[i].length();j++){
            h[i][j]=h[i][j-1]*BASE+str[j]-'A'+1;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<=str[i].length()-k;j++){
            long long val=gethash(i,j,j+k-1);
            if(last[val]!=i+1){
                graph[val]++;
                last[val]=i+1;
                rec[make_pair(i,val)]++;
                if(graph[val]>=m){
                    ans.push_back(val);
                }
            }
        }
    }
    return 0;
}
