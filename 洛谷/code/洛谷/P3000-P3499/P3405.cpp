// https://www.luogu.com.cn/problem/P3405
// 题意：输入城市数量 N，
// 接下来每行给出城市名（2 到 10 个大写字母）和所在州代码（2 个大写字母），
// 同州无同名城市。
// 若两座城市来自不同州，且城市名前两个字母互为对方所在州代码，则称作一对特殊城市。
// 输出特殊的城市对数。
// 数据范围：1 <= N <= 2*10^5，城市名长度不超过 10。
// 算法标签：哈希表
#include<iostream>
#include<vector>
#define mod 233333
using namespace std;
int n;
char a[12],b[12];
long long ans;
vector<pair<int ,int>>linker[mod+2];

inline int gethash(char a[],char b[]){
    return (a[0]-'A')+(a[1]-'A')*26+(b[0]-'A')*26*26+(b[1]-'A')*26*26*26;
}
inline void insert(int x){
    for(int i=0;i<linker[x%mod].size();i++)
        if(linker[x%mod][i].first==x){
            linker[x%mod][i].second++;
            break;
        }
    linker[x%mod].push_back(pair<int ,int >(x,1));
}

inline int find(int x){
    for(int i=0;i<linker[x%mod].size();i++){
        if(linker[x%mod][i].first==x)
            return linker[x%mod][i].second;
    }
    return 0;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a>>b;
        a[2]=0;
        if(a[0]!=b[0]||a[1]!=b[1])
            ans+=find(gethash(b,a));
        insert(gethash(a,b));
    }
    cout<<ans<<endl;
    return 0;
}
