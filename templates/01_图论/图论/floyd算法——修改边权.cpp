//P6464
//这道题是可以修改一条边权  然后求全局联通最小值
//如果修改一条边就跑一遍floyd  那么时间复杂度不允许
//所以我们在枚举修改哪两个点之间的边的时候 
//如果有两个节点之间的距离变小  那么说明这枚举的两个点中一定有一个是后来这两个点的中转点
//所以我们可以认为这外层的枚举点就是floyd算法中的bridge  然后考察哪些点之间可以被减少
#include<bits/stdc++.h>
using namespace std;

int n,m;
int F[105][105];
int f[105][105];

void floyd() {
    for (int bridge = 1; bridge <= n; bridge++) { // 跳板
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (f[i][bridge] != INT_MAX && f[bridge][j] != INT_MAX && f[i][j] > f[i][bridge] + f[bridge][j]) {
                    f[i][j] = f[i][bridge] + f[bridge][j];
                }
            }
        }
    }
}

inline void restore(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            F[i][j]=f[i][j];
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            f[i][j]=INT_MAX;
            F[i][j]=INT_MAX;
        }
        f[i][i]=0;
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        f[u][v]=w;
        f[v][u]=w;
    }
    floyd();
    long long ans=LLONG_MAX;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            restore();
            F[i][j]=F[j][i]=0;
            for(int x=1;x<=n;x++){
                for(int y=1;y<=n;y++){
                    if(F[x][y]>F[x][i]+F[i][y]){
                        F[x][y]=F[x][i]+F[i][y];
                    }
                    if(F[x][y]>F[x][j]+F[j][y]){
                        F[x][y]=F[x][j]+F[j][y];
                    }
                }
            }
            long long res=0;
            for(int i=1;i<=n;i++){
                for(int j=i+1;j<=n;j++){
                    res+=F[i][j];
                }
            }
            ans=min(ans,res);
        }
    }
    cout<<ans<<endl;
    return 0;
}
