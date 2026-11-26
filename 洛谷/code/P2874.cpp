// https://www.luogu.com.cn/problem/P2874
// 题意：平面上 n 个两两曼哈顿距离 >= 2 的整点。
// 求到这 n 个点曼哈顿距离之和的最小值 D，以及不与给定点重合的最优整点个数 C。
// 一行输出 D 和 C。
// 数据范围：2 <= n <= 10^4，-10^4 <= x_i, y_i <= 10^4。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;

int n;
int x[MAXN];
int y[MAXN];
long long ans=0;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
    }
    sort(x+1,x+n+1);
    sort(y+1,y+n+1);
    if(n%2==1){
        int posx=x[n/2+1];
        int posy=y[n/2+1];
        for(int i=1;i<=n/2;i++){
            ans+=posx-x[i];
            ans+=posy-y[i];
        }
        for(int i=n/2+1;i<=n;i++){
            ans+=x[i]-posx;
            ans+=y[i]-posy;
        }
        cout<<ans<<' '<<1<<endl;
    }
    else{
        int minx=x[n/2],maxx=x[n/2+1];
        int miny=y[n/2],maxy=y[n/2+1];
        int lenx=maxx-minx+1,leny=maxy-miny+1;
        for(int i=1;i<=n/2;i++){
            ans+=minx-x[i];
            ans+=miny-y[i];
        }
        for(int i=n/2+1;i<=n;i++){
            ans+=x[i]-minx;
            ans+=y[i]-miny;
        }
        cout<<ans<<' '<<(1ll*lenx*leny)<<endl;
    }
    return 0;
}