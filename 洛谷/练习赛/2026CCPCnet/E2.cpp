#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int val[3][MAXN];
int pos[3][MAXN];
bool okay[MAXN];

void compute(int a,int b){
    int maxx=0;
    for(int i=1;i<n;i++){
        maxx=max(maxx,pos[b][val[a][i]]);
        if(maxx==i){
            okay[i]=true;
        }
    }
}

void solve(){
    cin>>n;
    for(int i=0;i<3;i++){
        for(int j=1;j<=n;j++){
            cin>>val[i][j];
            pos[i][val[i][j]]=j;
        }
    }
    for(int i=1;i<=n;i++){
        okay[i]=false;
    }

    compute(1,2);
    compute(0,2);
    compute(1,0);

    int ans=1;
    for(int i=1;i<n;i++){
        if(okay[i]){
            ans++;
        }
    }
    cout<<ans<<endl;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}