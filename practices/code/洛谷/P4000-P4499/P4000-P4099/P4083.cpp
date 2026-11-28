// https://www.luogu.com.cn/problem/P4083
// 题意：第一行输入整数 N 和 D；
// 接下来 2N 行每行两个整数，
// 分别表示某个派在 Bessie 眼中的美味值和在 Elsie
// 眼中的美味值（前 N 个属 Bessie
// 后 N 个属 Elsie）。
// Bessie 先送出她的某只派，此后收到对方送来美味值为 v 的派的奶牛，
// 必须回赠一只自己尚未送出过、且在自己眼中美味值在 [v, v+D] 的派；
// 直到某人收到自己眼中美味值为 0 的派则高兴结束，若无法回赠则失败。
// 输出 N 行，对 Bessie 初始送出的每只派，
// 输出达成高兴结束所需赠送的最小总派数，否则输出 -1。
// 数据范围：1 <= N <= 10^5，0 <= D <= 10^9，
// 所有美味值均在 [0, 10^9] 内。
// 难度评分：2600（洛谷分级换算）
// 算法标签：广度优先搜索、平衡树
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,d;
pair<int,int>nums[MAXN<<1];
int dis[MAXN<<1];
set<pair<int,int>>st1,st2;
queue<int>q;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int main()
{
    n=read(),d=read();
    for(int i=1;i<=2*n;i++){
        nums[i].first=read();
        nums[i].second=read();
        dis[i]=-1;
    }

    for(int i=1;i<=2*n;i++){
        if(i<=n){
            st1.insert({nums[i].second,i});
        }
        else{
            st2.insert({nums[i].first,i});
        }
    }

    for(int i=1;i<=2*n;i++){
        if(i<=n){
            if(nums[i].second==0){
                q.push(i);
                dis[i]=1;
                st1.erase({nums[i].second,i});
            }
        }
        else{
            if(nums[i].first==0){
                q.push(i);
                dis[i]=1;
                st2.erase({nums[i].first,i});
            }
        }
    }

    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(u<=n){
            int val=nums[u].first;
            int l=val-d;
            int r=val;
            auto it=st2.lower_bound({l,0});
            vector<set<pair<int,int>>::iterator>del;
            while(it!=st2.end()&&it->first<=r){
                int v=it->second;
                dis[v]=dis[u]+1;
                q.push(v);
                del.push_back(it);
                it++;
            }
            for(auto &it:del){
                st2.erase(it);
            }
        }
        else{
            int val=nums[u].second;
            int l=val-d;
            int r=val;
            auto it=st1.lower_bound({l,0});
            vector<set<pair<int,int>>::iterator>del;
            while(it!=st1.end()&&it->first<=r){
                int v=it->second;
                dis[v]=dis[u]+1;
                q.push(v);
                del.push_back(it);
                it++;
            }
            for(auto &it:del){
                st1.erase(it);
            }
        }
    }

    for(int i=1;i<=n;i++){
        cout<<dis[i]<<endl;
    }
    return 0;
}