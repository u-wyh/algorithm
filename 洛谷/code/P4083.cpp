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