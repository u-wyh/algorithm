#include<bits/stdc++.h>
using namespace std;

int n;
int ans[105];
double val[105];
double sum=0;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    int u,v;
    while(cin>>u){
        cin>>v;
        // cout<<' '<<u<<' '<<v<<endl;
        if(u==0){
            break;
        }
        ans[u]+=v;
    }
    for(int i=1;i<=n;i++){
        sum+=ans[i]*val[i];
        cout<<ans[i]<<endl;
    }
    printf("%.2lf",sum);
    return 0;
}