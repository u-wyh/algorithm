// https://www.luogu.com.cn/problem/P2256
// 题意：有 N 名选手，给出 M 组同组关系（具有传递性），随后 K 次询问。
// 每次询问两名选手是否属于同一组。
// 对每次询问输出 Yes. 或 No.。
// 数据范围：2 <= N <= 2*10^4，1 <= M, K <= 10^6，
// 名字长度 <= 20。
// 难度评分：1300（洛谷分级换算）
// 算法标签：并查集
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;

map<string ,string >father;
int n,k;

string find(string s){
    if(s!=father[s])
        father[s]=find(father[s]);
    return father[s];
}

void un(string u,string v){
    father[find(u)]=find(v);
}

bool issameset(string u,string v){
    return find(u)==find(v);
}

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        father[s]=s;
    }
    for(int i=1;i<=k;i++){
        string a,b;
        cin>>a>>b;
        un(a,b);
    }
    int m;
    cin>>m;
    for(int i=1;i<=m;i++){
        string u,v;
        cin>>u>>v;
        if(issameset(u,v)){
            cout<<"Yes.\n";
        }
        else
            cout<<"No.\n";
    }
    return 0;
}
