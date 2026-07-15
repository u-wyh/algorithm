#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,m;
    map<int ,int >ds;
    cin>>n;
    int a,b;
    for(int i=1;i<=n;i++){
        cin>>a;
        ds[a]=i;
    }
    cin>>m;
    while(m--){
        cin>>b;
        if(ds.find(b)!=ds.end())
            cout<<ds[b]<<endl;
        else
            cout<<0<<endl;
    }
    return 0;
}
