#include<bits/stdc++.h>
using namespace std;

int n,m;
map<int,int>per;
int ans[1005];
int cnt;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int val;
        char op;
        cin>>val>>op;
        per[val]=(op=='i')?1:2;
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        int k;
        cin>>k;
        int all=0;
        for(int j=1;j<=k;j++){
            int val;
            cin>>val;
            all+=per[val];
        }
        if(all==k){
            ans[++cnt]=i;
        }
    }
    if(cnt==0){
        cout<<"None"<<endl;
        return 0;
    }
    for(int i=1;i<cnt;i++){
        cout<<ans[i]<<' ';
    }
    cout<<ans[cnt]<<endl;
    return 0;
}