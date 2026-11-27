#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,m;
int val[MAXN];

bool cmp(int a,int b){
    return a>b;
}

signed main()
{
    int op;
    cin>>op;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }

    if(op==1){
        for(int i=1;i<=n;i++){
            val[i]=val[i]/m;
        }
        sort(val+1,val+n+1,cmp);
        for(int i=1;i<=n;i++){
            cout<<val[i]<<' ';
        }
    }
    else{
        int ans=0;
        for(int i=1;i<=n;i++){
            ans+=val[i];
            if(ans>=m){
                cout<<i<<endl;
                return 0;
            }
        }
        cout<<-1<<endl;
    }
    return 0;
}