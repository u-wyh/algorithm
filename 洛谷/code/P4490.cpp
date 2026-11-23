// https://www.luogu.com.cn/problem/P4490
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXT = 4e5+5;
const double eps = 1e-9;

int n;
double h,g;

struct Point{
    double x,y;
    int id;
};
Point a[MAXN],v[MAXN];
Point nums[MAXN];
int top;
Point sta[MAXN<<1];
double tim[MAXT];
int cntt;

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

Point operator+(Point a,Point b){
    return {a.x+b.x,a.y+b.y};
}

Point operator*(Point a,double k){
    return {a.x*k,a.y*k};
}

double cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

double cross(Point a,Point b,Point c){
    return cross(b-a,c-a);
}

bool cmp(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

void Andrew(){
    top=0;
    sort(nums+1,nums+n+1,cmp);
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(cnt==0 || nums[i].x!=nums[cnt].x || nums[i].y!=nums[cnt].y){
            nums[++cnt]=nums[i];
        }
    }
    if(cnt<=2){
        for(int i=1;i<=cnt;i++){
            sta[++top]=nums[i];
        }
        if(top>0){
            sta[top+1]=sta[1];
        }
        return;
    }

    // 下凸链
    for(int i=1;i<=cnt;i++){
        while(top>1 && cross(sta[top-1],sta[top],nums[i])<=0){
            top--;
        }
        sta[++top]=nums[i];
    }
    int t=top;

    // 上凸链
    for(int i=cnt-1;i>=1;i--){
        while(top>t && cross(sta[top-1],sta[top],nums[i])<=0){
            top--;
        }
        sta[++top]=nums[i];
    }
    top--;
    sta[top+1]=sta[1];
}

void addtime(double t){
    if(t>=-eps && t<=1+eps){
        tim[++cntt]=min(1.0,max(0.0,t));
    }
}

void prepare(){
    addtime(0);
    addtime(1);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            Point d=a[j]-a[i];
            Point u=v[j]-v[i];
            if(u.x!=0){
                double t=-d.x/u.x;
                if(fabs(d.y+u.y*t)<eps){
                    addtime(t);
                }
            }
            else if(u.y!=0){
                double t=-d.y/u.y;
                if(fabs(d.x+u.x*t)<eps){
                    addtime(t);
                }
            }
            for(int k=j+1;k<=n;k++){
                Point e=a[k]-a[i];
                Point z=v[k]-v[i];

                // 三点共线：At^2+Bt+C=0
                double A=cross(u,z);
                double B=cross(d,z)+cross(u,e);
                double C=cross(d,e);

                if(A==0){
                    if(B!=0){
                        addtime(-C/B);
                    }
                    continue;
                }

                double delta=B*B-4*A*C;
                if(delta<0){
                    continue;
                }

                double sq=sqrt(delta);
                addtime((-B-sq)/(2*A));
                addtime((-B+sq)/(2*A));
            }
        }
    }
    sort(tim+1,tim+cntt+1);

    // 关键时刻去重
    int sz=0;
    for(int i=1;i<=cntt;i++){
        if(sz==0 || tim[i]-tim[sz]>eps){
            tim[++sz]=tim[i];
        }
    }
    cntt=sz;

}

// 求区间[l,r]内的最小凸包面积
double calc(double l,double r){
    double mid=(l+r)/2;

    // 在区间中点求出凸包结构
    for(int i=1;i<=n;i++){
        nums[i]={
            a[i].x+v[i].x*mid,
            a[i].y+v[i].y*mid,
            i
        };
    }

    Andrew();

    if(top<=2){
        return 0;
    }

    // 两倍面积为At^2+Bt+C
    double A=0,B=0,C=0;

    for(int i=1;i<=top;i++){
        int x=sta[i].id;
        int y=sta[i+1].id;

        A+=cross(v[x],v[y]);
        B+=cross(a[x],v[y])+cross(v[x],a[y]);
        C+=cross(a[x],a[y]);
    }

    auto area=[&](double t){
        return (A*t*t+B*t+C)/2;
    };

    // 先检查区间端点
    double ans=min(area(l),area(r));

    // 二次函数开口向上时检查顶点
    if(A>0){
        double t=-B/(2*A);
        if(t>=l && t<=r){
            ans=min(ans,area(t));
        }
    }

    return max(ans,0.0);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>h>>g>>n;
    for(int i=1;i<=n;i++){
        int x,y,xx,yy;
        cin>>x>>y>>xx>>yy;
        a[i]={x,y,i};
        v[i]={xx-x,yy-y,0};
    }

    if(n<=2){
        cout<<"0.000000"<<endl;
        return 0;
    }

    prepare();

    double ans=1e100;
    for(int i=1;i<cntt;i++){
        ans=min(ans,calc(tim[i],tim[i+1]));
    }
    cout<<fixed<<setprecision(6)<<ans<<endl;
    return 0;
}