#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXC = 11;
const int MOD = 987654321;

int n,m,c;
long long f[MAXN][MAXC];
bool used[MAXN][MAXC];//表示是否可以选择这种颜色
bool same[MAXN];

void compute(){
    for(int i=2;i<=n+1;i++){
		if(same[i]){
			for(int j=1;j<=c;j++){
				if(used[i][j]){
                    f[i][j]=f[i-1][j];
				}
			}
		}
		else{
			long long sum=0;
			for(int j=1;j<=c;j++){
				sum=(sum+f[i-1][j])%MOD;
			}
			for(int j=1;j<=c;j++){
				if(used[i][j]){
					f[i][j]=(sum-f[i-1][j]+MOD)%MOD;
				}
			}
		}
    }
	return;
}

int work(){
    long long ans=0;
    for(int i=1;i<=c;i++){
        if(used[1][i]){
            for(int j=1;j<=n;j++){
                for(int k=1;k<=c;k++){
                    f[j][k]=0;
                }
            }
            f[1][i]=1;
            compute();
            ans=(ans+f[n+1][i])%MOD;
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>c;
    for(int i=1;i<=n+1;i++){
        for(int j=1;j<=c;j++){
            used[i][j]=true;
        }
    }
    for(int i=1;i<=m;i++){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            if(used[x][y]==false){
                cout<<0<<endl;
                return 0;
            }
            for(int j=1;j<=c;j++){
                used[x][j]=false;
            }
            used[x][y]=true;
        }
        else if(op==2){
            used[x][y]=false;
        }
        else{
            same[max(x,y)]=true;
        }
    }
    cout<<work()<<endl;
    return 0;
}
