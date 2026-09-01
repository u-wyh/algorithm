#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e3+5;

int n,m;
int val[MAXN][MAXN];
int d[MAXN][MAXN];
int t[MAXN][MAXN];
int maxval;

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    if(!(cin>>T)) return 0;
    while(T--){
        cin>>n>>m;
        maxval=-1e9;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>val[i][j];
                maxval=max(maxval,val[i][j]);
            }
        }

        if(m==1||n==1){
            bool flag=false;
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    if(val[i][j]!=maxval){
                        flag=true;
                        break;
                    }
                }
            }

            if(flag){
                cout<<-1<<endl;
            }
            else{
                cout<<0<<endl;
            }
            continue;
        }

        int delta=-(2ll*val[1][1]-val[1][2]-val[2][1]);
        int all=delta+val[1][1];

        if(delta<0||val[1][1]!=val[n][m]){
            cout<<-1<<endl;
            continue;
        }

        bool flag=false;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                d[i][j]=all-val[i][j];
                t[i][j]=d[i][j];
                if(d[i][j]<0){
                    flag=true;
                    break;
                }
            }
        }

        for(int sum=3;sum<=(n+m)&&!flag;sum++){
            for(int r=1;r<=n;r++){
                int c=sum-r;

                if(c>=1&&c<=m){
                    int upr=r-1,upc=c;
                    int ltr=r,ltc=c-1;

                    if(upr>=1){
                        d[r][c]-=t[upr][upc];
                        t[upr][upc]=0;
                        if(d[r][c]<0){
                            flag=true;
                        }
                    }

                    if(ltc>=1){
                        t[ltr][ltc]-=d[r][c];
                        d[r][c]=0;
                        if(t[ltr][ltc]<0){
                            flag=true;
                        }
                    }

                    if(d[r][c]){
                        flag=true;
                        break;
                    }
                }
            }    
        }
        if(flag){
            cout<<-1<<endl;
        }
        else{
            cout<<delta<<endl;
        }
    }
    return 0;
}
