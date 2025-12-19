#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;

int n,m;
int nums[MAXN][MAXN];
int arr[MAXN][MAXN][4];
int val[MAXN][MAXN];
int walk[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
int color;
int cnt[2600];
int ans;
// char s[4]={'W','N','E','S'};

double help[4][2]={{0,-1},{-1,-0.5},{0,0},{0,-0.5}};

double x,y;
int pos;



void dfs(int x,int y,int col){
    for(int k=0;k<4;k++){
        if(arr[x][y][k]==0){
            int nx=x+walk[k][0];
            int ny=y+walk[k][1];
            if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&(val[nx][ny]==0)){
                val[nx][ny]=color;
                dfs(nx,ny,col);
            }
        }
    }
}

void check(double i,double j,int p,int val){
    if(val<ans){
        return ;
    }
    else if(val>ans){
        x=i,y=j,pos=p,ans=val;
        return ;
    }
    if(j>y){
        return ;
    }
    else if(j<y){
        x=i,y=j,pos=p;
        return ;
    }
    if(i<=x){
        return ;
    }
    else {
        x=i,pos=p;
        return ;
    }
}

int main()
{
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>nums[i][j];
            for(int k=0;k<4;k++){
                arr[i][j][k]=((nums[i][j]>>k)&1);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(val[i][j]==0){
                val[i][j]=++color;
                dfs(i,j,color);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cnt[val[i][j]]++;
        }
    }
    for(int i=1;i<=color;i++){
        ans=max(ans,cnt[i]);
        // cout<<cnt[i]<<' ';
    }
    // cout<<endl;
    cout<<color<<endl<<ans<<endl;
    ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=0;k<4;k++){
                if(arr[i][j][k]){
                    int nx=i+walk[k][0];
                    int ny=j+walk[k][1];
                    if(val[i][j]!=val[nx][ny]){
                        check(i+help[k][0],j+help[k][1],k,cnt[val[i][j]]+cnt[val[nx][ny]]);
                    }
                }
            }
        }
    }
    cout<<ans<<endl;
    int ansx,ansy;
    if(pos==0||pos==2){
        ansx=x,ansy=y;
        cout<<ansx<<' '<<ansy<<' '<<"E";
    }
    else{
        ansy=y+0.5;
        ansx=x+1;
        cout<<ansx<<' '<<ansy<<' '<<"N";
    }
    return 0;
}