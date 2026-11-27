#include<bits/stdc++.h>
using namespace std;

const double PI=acos(-1.0);
const double EPS=1e-12;

double sx,sy;
double len;

double calc(double theta){
    double x=len*cos(theta);
    double y=len*sin(theta);

    return fabs(x-sx*y/sy);
}

void solve(){
    double ax,ay,bx,by;
    cin>>sx>>sy>>ax>>ay>>bx>>by;

    len=hypot(ax,ay);

    double alpha=atan2(sy,sx);
    double thetaA=atan2(ay,ax);
    double thetaB=atan2(by,bx);

    double mn=min(calc(thetaA),calc(thetaB));
    double mx=max(calc(thetaA),calc(thetaB));

    // 检查一个特殊角度是否在杆允许转动的范围内
    auto check=[&](double theta){
        if(theta+EPS<thetaA||theta-EPS>thetaB){
            return;
        }

        double val=calc(theta);
        mn=min(mn,val);
        mx=max(mx,val);
    };

    // 杆与太阳方向平行，此时影长可能为 0
    check(alpha);

    // 杆与太阳方向垂直，此时影长取得极大值
    check(alpha-PI/2);
    check(alpha+PI/2);

    cout<<fixed<<setprecision(15)<<mn<<" "<<mx<<"\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin>>T;

    while(T--){
        solve();
    }

    return 0;
}