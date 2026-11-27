#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;

int n;
int val[MAXN][MAXN];
int arr[MAXN][MAXN];
int tmp[MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    string s;
    cin>>s>>n;
    if(s=="first"){
        for(int i=1;i<=n;i++){
            cin>>tmp[i];
            val[1][i]=tmp[i];
        }
        swap(tmp[1],tmp[2]);

        for(int i=2;i<=n;i++){
            for(int j=1;j<n;j++){
                val[i][j]=tmp[j+1];
            }
            val[i][n]=tmp[1];

            for(int j=1;j<=n;j++){
                tmp[j]=val[i][j];
            }
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                cout<<val[i][j]<<' ';
            }
            cout<<endl;
        }
    }
    else{
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                cin>>val[i][j];
                arr[i][j]=val[i][j];
            }
        }

        for(int i=1;i<=n;i++){
            int pos=1;
            for(int j=1;j<=n;j++){
                if(val[i][j]==1){
                    pos=j;
                    break;
                }
            }

            int len=0;
            for(int j=pos;j<=n;j++){
                tmp[++len]=val[i][j];
            }
            for(int j=1;j<pos;j++){
                tmp[++len]=val[i][j];
            }

            for(int j=1;j<=n;j++){
                val[i][j]=tmp[j];
            }
        }

        int ans=0;
        for(int j=1;j<=n;j++){
            if(ans){
                break;
            }
            int v=val[1][j];
            if(v==val[2][j]){

            }
            else{
                v=val[3][j];
            }

            for(int i=1;i<=n;i++){
                if(val[i][j]!=v){
                    ans=i;
                    break;
                }
            }
        }

        for(int i=1;i<=n;i++){
            cout<<arr[ans][i]<<' ';
        }
    }
    return 0;
}