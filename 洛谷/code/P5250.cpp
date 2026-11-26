// https://www.luogu.com.cn/problem/P5250
// 题意：维护一个无重复长度的木材集合，支持 m 次操作：1 L 插入长度为 L 的木材（已存在则输出 Already Exist）。
// 2 L 取出长度为 L 的木材，若无恰好长度则取最接近的（相同时取较短的）并输出长度，仓库为空输出 Empty。
// 数据范围：操作次数 m <= 10^5，木材长度 L 不超过 10^9。
#include<bits/stdc++.h>
using namespace std;

int n,opt,length;
set<int >ds;
int main()
{
    cin>>n;
    while(n--){
        cin>>opt>>length;
        if(opt==1)
            if(ds.find(length)!=ds.end())
                cout<<"Already Exist"<<endl;
            else
                ds.insert(length);
        else if(ds.empty())
            cout<<"Empty"<<endl;
        else{
            auto i=ds.lower_bound(length),j=i;
            if(j!=ds.begin())
                --j;
            if(i!=ds.end()&&length-(*j)>(*i)-length)
                j=i;
            cout<<(*j)<<endl,ds.erase(j);
        }
    }
    return 0;
}
