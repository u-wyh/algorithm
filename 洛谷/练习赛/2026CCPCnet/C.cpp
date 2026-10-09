
#include<bits/stdc++.h>
using namespace std;
#define int long long

const long double INF=1e100L;

// op=0：从左端点通过
// op=1：从右端点通过
long double calc(int x,int op,int yc,int u,int v){
    int A=v*v-u*u;
    int B=-2*x*u;
    int C=-(x*x+yc*yc);

    long double t0=(long double)yc/v;
    long double ans=INF;

    // 判断求出的根是否合法
    auto upd=[&](long double t){
        if(t<t0-1e-12L) return;

        // t 时刻端点的横坐标
        long double pos=(long double)x+u*t;

        // 从左边绕过，接触点应位于 x<=0 一侧
        if(op==0&&pos>1e-8L) return;

        // 从右边绕过，接触点应位于 x>=0 一侧
        if(op==1&&pos<-1e-8L) return;

        ans=min(ans,t);
    };

    if(A==0){
        // 退化为一次方程
        if(B!=0){
            upd(-(long double)C/B);
        }
    }
    else{
        // 判别式可能超过 long long，使用 __int128
        __int128 D=(__int128)B*B-4*(__int128)A*C;

        if(D>=0){
            long double delta=sqrtl((long double)D);

            // 枚举两个实数根
            upd((-(long double)B-delta)/(2.0L*A));
            upd((-(long double)B+delta)/(2.0L*A));
        }
    }

    return ans;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin>>T;

    cout<<fixed<<setprecision(12);

    while(T--){
        int w,x1,x2,yc,u,v;
        cin>>w>>x1>>x2>>yc>>u>>v;

        // 可以直接竖直过马路
        // 交叉相乘，避免浮点误差
        if(x1*v+u*yc>=0 || x2*v+u*yc<=0){
            cout<<(long double)w/v<<'\n';
            continue;
        }

        // 分别考虑从左右两个端点通过
        long double t1=calc(x1,0,yc,u,v);
        long double t2=calc(x2,1,yc,u,v);

        long double t=min(t1,t2);

        // 穿过车所在直线后，竖直向上
        long double ans=t+(long double)(w-yc)/v;

        cout<<ans<<'\n';
    }

    return 0;
}
