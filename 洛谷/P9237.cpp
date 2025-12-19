#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int a[15][15];
int n,m;
int ans[15][15];
bool flag=0;

int d[9][2]={-1,-1,-1,0,-1,1,0,-1,0,0,0,1,1,-1,1,0,1,1};

int cnt(int x,int y){
    int res=0;
    for(int i=0;i<9;i++){
        int dx=x+d[i][0],dy=y+d[i][1];
        res+=(ans[dx][dy]==1);
    }
    return res;
}

bool check(int x,int y){
    for(int i=1;i<=x-2;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]==-1)continue;
            if(cnt(i,j)!=a[i][j]){
                return 0;
            }
        }
    }
    if(x>=2)
    for(int j=1;j<=y-2;j++){
        if(a[x-1][j]==-1)continue;
        if(cnt(x-1,j)!=a[x-1][j])return 0;
    }
    return 1;
}

bool check2(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]==-1)continue;
            if(cnt(i,j)!=a[i][j]){
                return 0;
            }
        }
    }
    return 1;
}

void dfs(int x,int y){

    if(flag)return;

    if(x==n+1){
        if(check2()==0)return;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cout<<ans[i][j];
            }
            cout<<endl;
        }
        flag=1;
        return;
    }

    if(check(x,y)==0)return;

    if(y==m){
        ans[x][y]=1;
        dfs(x+1,1);
        ans[x][y]=0;
        dfs(x+1,1);
        return;
    }
    ans[x][y]=1;
    dfs(x,y+1);
    ans[x][y]=0;
    dfs(x,y+1);
    return;
}

void solve(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char ch;
            cin>>ch;
            if(ch=='_')a[i][j]=-1;
            else a[i][j]=ch-'0';
        }
    }
    dfs(1,1);
    return;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}

/*
6 8
_1__5_1_
1_4__42_
3__6__5_
___56___
_688___4
_____6__
*/
