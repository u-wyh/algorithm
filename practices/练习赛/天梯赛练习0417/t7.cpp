#include<bits/stdc++.h>
using namespace std;

bool col[500005];
bool row[500005];

int main()
{
    int a=0,b=0,n,m,k;
    cin>>n>>m>>k;
    for(int i=1;i<=k;i++){
        int u,v;
        cin>>u>>v;
        if(u==0){
            if(!col[v])
                a++;
            col[v]=1;
        }
        else{
            if(!row[v])
                b++;
            row[v]=1;
        }
    }
    int ans=n*m+a*b-a*m-b*n;
    cout<<ans<<endl;
    return 0;
}