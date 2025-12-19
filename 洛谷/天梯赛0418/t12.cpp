#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 1e5+5;

int n,m;
vector<int>vec[MAXN];

int st[MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        for(int j=1;j<=k;j++){
            int v;
            cin>>v;
            vec[i].push_back(v);
        }
    }
    int now=1;
    for(int i=1;i<=m;i++){
        int op,u;
        cin>>op>>u;
        if(op==1){
            cout<<now<<endl;
            st[u]=now;
        }
        else if(op==2){
            now=st[u];
        }
        else{
            u--;
            now=vec[now][u];
        }
    }
    cout<<now<<endl;
    return 0;
}