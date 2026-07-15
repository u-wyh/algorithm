#include<bits/stdc++.h>
using namespace std;

int T,n,dx[110],dy[110];
bool v[2100][2100];

bool solve(){
    queue <int>qx,qy;
    qx.push(100),qy.push(100);
    v[100][100]=1;
    int sum=0;
    while(!qx.empty()){
        int x=qx.front(),y=qy.front();
        qx.pop();qy.pop();
        sum++;
        for(int i=1;i<=n;i++){
            int nx=x+dx[i],ny=y+dy[i];
            if(nx>=0&&nx<=200&&ny>=0&&ny<=200&&!v[nx][ny]){
                v[nx][ny]=1;
                qx.push(nx),qy.push(ny);
            }
            if(v[101][100]&&v[100][101]&&v[99][100]&&v[100][99]){
                return true;
            }
        }
    }
    if(v[101][100]&&v[100][101]&&v[99][100]&&v[100][99]){
        return true;
    }
    return false;
}

signed main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<=200;i++){
            for(int j=0;j<=200;j++){
                v[i][j]=0;
            }
        }
        for(int i=1;i<=n;i++){
            scanf("%d%d",&dx[i],&dy[i]);
        }
        if(n>1){
            int g=__gcd(abs(dx[1]),abs(dx[2]));
            for(int i=3;i<=n;i++){
                g=__gcd(g,abs(dx[i]));
            }
            if(g>1){
                puts("NIE");
                continue;
            }
            g=__gcd(abs(dy[1]),abs(dy[2]));
            for(int i=3;i<=n;i++){
                g=__gcd(g,abs(dy[i]));
            }
            if(g>1){
                puts("NIE");
                continue;
            }
        }
        if(solve()){
            puts("TAK");
        }
        else{
            puts("NIE");
        }
    }
    return 0;
}
