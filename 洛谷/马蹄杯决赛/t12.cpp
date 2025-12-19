#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;
const int MAXM = 105;
const int MAXK = 1e4+5;

int n,m,q;
char s[MAXM][MAXM];
int val[MAXN][MAXN];
int dx[5][MAXK];
int dy[5][MAXK];

int main()
{
    scanf("%d %d %d",&n,&m,&q);
    for(int i=1;i<=m;i++){
        scanf("%s",s[i]+1);
    }

    int all=0;
    for(int k=1;k<=4;k++){
        int cnt=0;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=m;j++){
                if(s[i][j]=='#'){
                    ++cnt;
                    if(k==1){
                        dx[k][cnt]=i-1;
                        dy[k][cnt]=j-1;
                    }
                    else if(k==2){
                        dx[k][cnt]=j-1;
                        dy[k][cnt]=m-i;
                    }
                    else if(k==3){
                        dx[k][cnt]=m-i;
                        dy[k][cnt]=m-j;
                    }
                    else{
                        dx[k][cnt]=m-j;
                        dy[k][cnt]=i-1;
                    }
                }
            }
        }
        all=cnt;
    }

    // for(int k=1;k<=4;k++){
    //     for(int i=1;i<=all;i++){
    //         cout<<k<<":  "<<dx[k][i]<<' '<<dy[k][i]<<endl;
    //     }
    // }

    int now=1;
    for(int i=1;i<=q;i++){
        int op,x,y;
        cin>>op;
        if(op==1){
            now=(now%4+1);
        }
        else{
            cin>>x>>y;
            for(int j=1;j<=all;j++){
                val[x+dx[now][j]][y+dy[now][j]]++;
            }
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<val[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}