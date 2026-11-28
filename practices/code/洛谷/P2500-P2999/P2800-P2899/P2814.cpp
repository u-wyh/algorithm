// https://www.luogu.com.cn/problem/P2814
// 题意：按 #father、+son 给出父子关系，
// ?name 查询某人的最早祖先，$ 结束。
// 对每次查询输出 本人名字 祖先名字。
// 数据范围：名字为 6 个字符且互异，父子关系 <= 10^3 组，
// 总人数 <= 5*10^4，不超过 30 代。
// 难度评分：1300（洛谷分级换算）
// 算法标签：并查集、map
#include<bits/stdc++.h>
using namespace std;
map<string,string>p;

string s,s1;

string find(string x)
{
    if(x!=p[x])
        p[x]=find(p[x]);
    return  p[x];
}

int main()
{
    char ch;
    cin>>ch;
    while(ch!='$'){
        cin>>s;
        if(ch=='#'){
            s1=s;
            if(p[s]=="")
                p[s]=s;
        }else if(ch=='+')
            p[s]=s1;
        else
            cout<<s<<' '<<find(s)<<endl;
        cin>>ch;
    }
    return 0;
}
