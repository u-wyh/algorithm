#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

int n,m,q;

int val[MAXN];
int allsum[MAXN];
int cursum[MAXN];
int sum;
int target;

mt19937_64 rng(time(0));

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        val[i]=rng();
        target+=val[i];
    }

    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        allsum[v]+=val[u];
    }
    for(int i=1;i<=n;i++){
        cursum[i]=allsum[i];
        sum+=cursum[i];
    }

    cin>>q;
    for(int i=1;i<=q;i++){
        int op,u,v;
        cin>>op;
        if(op==1){
            cin>>u>>v;
            cursum[v]-=val[u];
            sum-=val[u];
        }
        else if(op==2){
            cin>>v;
            sum-=cursum[v];
            cursum[v]=0;
        }
        else if(op==3){
            cin>>u>>v;
            cursum[v]+=val[u];
            sum+=val[u];
        }
        else{
            cin>>v;
            sum-=cursum[v];
            cursum[v]=allsum[v];
            sum+=cursum[v];
        }

        if(sum==target){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}