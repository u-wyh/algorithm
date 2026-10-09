#include<bits/stdc++.h>
using namespace std;
#define int long long

int all;
int val[7];
int ans[7];

// 表示现在来到了第now个  已经赢了win局   还可以选择res
bool dfs(int now,int win,int res){
    if(now==1){
        if(res>=0&&win>=19){
            return true;
        }
        else{
            return false;
        }
    }

    if(res<now-1){
        return false;
    }

    for(int i=0;i<=6;i++){
        if(dfs(now-1,win+i,res-val[i]-1)){
            ans[now-1]=val[i]+1;
            return true;
        }
    }
    return false;
}

signed main()
{
    for(int i=1;i<=6;i++){
        cin>>val[i];
    }
    cin>>all;
    sort(val+1,val+7);

    if(dfs(7,0,all)){
        cout<<"YES"<<endl;
        int res=all;
        for(int i=1;i<=6;i++){
            res-=ans[i];
        }
        ans[1]+=res;
        for(int i=1;i<=6;i++){
            cout<<ans[i]<<' ';
        }
    }
    else{
        cout<<"NO"<<endl;
    }
    return 0;
}