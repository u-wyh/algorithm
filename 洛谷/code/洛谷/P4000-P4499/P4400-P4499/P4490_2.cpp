// https://www.luogu.com.cn/problem/P4490
// 题意：三维空间中高度 h 处有 n 个水平喷头从 (x_i, y_i, h)
// 平抛喷水，落到地面 (x'_i, y'_i, 0)（重力加速度 g
// 空中任意点至多被三个喷头喷到），
// 求在某个水平高度放置能拦截全部水流的凸多边形滤水层的最小面积。
// 数据范围：1 <= n <= 100，0 < h <= 10000.0，
// 0 < g <= 100.0
// 0 <= x_i, y_i, x'_i, y'_i <= 1000。
// 算法标签：计算几何、动态凸包、扫描线
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=105;
const int MAXT=400005;
const long double EPS=1e-14L;

int n,top,cntt;

struct Vec{
    long long x,y;
};
struct Point{
    long double x,y;
    int id;
};
struct Event{
    long double t;
    int a,b,c;
};
struct Poly{
    long long A,B,C;
};

Vec a[MAXN],v[MAXN];
Point nums[MAXN],sta[MAXN<<1];
Event ev[MAXT];

int pre[MAXN],nxt[MAXN];
bool on[MAXN];
Poly poly;

Vec operator-(Vec a,Vec b){
    return {a.x-b.x,a.y-b.y};
}

long long cross(Vec a,Vec b){
    return a.x*b.y-a.y*b.x;
}

long double cross(Point a,Point b,Point c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

// 三点共线对应的二次函数
Poly orient(int i,int j,int k){
    Vec d=a[j]-a[i],e=a[k]-a[i];
    Vec u=v[j]-v[i],z=v[k]-v[i];
    return {cross(u,z),cross(d,z)+cross(u,e),cross(d,e)};
}

// 一条有向边对两倍面积的贡献
Poly edge(int i,int j){
    return {
        cross(v[i],v[j]),
        cross(a[i],v[j])+cross(v[i],a[j]),
        cross(a[i],a[j])
    };
}

void change(int i,int j,int s){
    Poly p=edge(i,j);
    poly.A+=s*p.A;
    poly.B+=s*p.B;
    poly.C+=s*p.C;
}

long double area(long double t){
    return (((long double)poly.A*t+poly.B)*t+poly.C)/2;
}

// 求当前面积二次函数在区间内的最小值
long double calc(long double l,long double r){
    long double res=min(area(l),area(r));
    if(poly.A>0){
        long double t=-(long double)poly.B/(2*poly.A);
        if(t>=l&&t<=r){
            res=min(res,area(t));
        }
    }
    return max(res,0.0L);
}

void addtime(long double t,int i,int j,int k){
    if(t>0&&t<1){
        ev[++cntt]={t,i,j,k};
    }
}

// 解三点共线的时间
void roots(Poly p,int i,int j,int k){
    long long A=p.A,B=p.B,C=p.C;

    if(A==0){
        if(B){
            addtime(-(long double)C/B,i,j,k);
        }
        return;
    }

    long long delta=B*B-4*A*C;
    if(delta<=0){
        return;
    }

    long double sq=sqrtl((long double)delta);
    long double q=-0.5L*(B+copysignl(sq,(long double)B));

    if(q){
        addtime(q/A,i,j,k);
        addtime((long double)C/q,i,j,k);
    }
    else{
        addtime(-((long double)B+sq)/(2*A),i,j,k);
        addtime(-((long double)B-sq)/(2*A),i,j,k);
    }
}

// 预处理所有关键事件
void prepare(){
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            Vec d=a[j]-a[i],u=v[j]-v[i];

            // 两点重合事件
            if(u.x&&cross(d,u)==0){
                addtime(-(long double)d.x/u.x,i,j,0);
            }
            else if(!u.x&&u.y&&!d.x){
                addtime(-(long double)d.y/u.y,i,j,0);
            }

            for(int k=j+1;k<=n;k++){
                roots(orient(i,j,k),i,j,k);
            }
        }
    }

    sort(ev+1,ev+cntt+1,[](Event x,Event y){
        return x.t<y.t;
    });
}

bool cmp(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    if(a.y!=b.y){
        return a.y<b.y;
    }
    return a.id<b.id;
}

// Andrew严格凸包
void Andrew(){
    top=0;
    sort(nums+1,nums+n+1,cmp);

    int cnt=0;
    for(int i=1;i<=n;i++){
        if(!cnt||nums[i].x!=nums[cnt].x||nums[i].y!=nums[cnt].y){
            nums[++cnt]=nums[i];
        }
    }

    if(cnt<=2){
        for(int i=1;i<=cnt;i++){
            sta[++top]=nums[i];
        }
        if(top){
            sta[top+1]=sta[1];
        }
        return;
    }

    for(int i=1;i<=cnt;i++){
        while(top>1&&cross(sta[top-1],sta[top],nums[i])<=0){
            top--;
        }
        sta[++top]=nums[i];
    }

    int t=top;
    for(int i=cnt-1;i>=1;i--){
        while(top>t&&cross(sta[top-1],sta[top],nums[i])<=0){
            top--;
        }
        sta[++top]=nums[i];
    }

    top--;
    sta[top+1]=sta[1];
}

// 在指定时刻重新建立凸包
void rebuild(long double t){
    memset(on,0,sizeof on);
    memset(pre,0,sizeof pre);
    memset(nxt,0,sizeof nxt);

    for(int i=1;i<=n;i++){
        nums[i]={
            a[i].x+v[i].x*t,
            a[i].y+v[i].y*t,
            i
        };
    }

    Andrew();
    poly={0,0,0};

    if(top<=2){
        return;
    }

    for(int i=1;i<=top;i++){
        int x=sta[i].id;
        int y=sta[i%top+1].id;
        int z=sta[(i+top-2)%top+1].id;

        on[x]=true;
        pre[x]=z;
        nxt[x]=y;
        change(x,y,1);
    }
}

// 在凸包边x->y之间插入z
void insert(int x,int y,int z){
    change(x,y,-1);
    change(x,z,1);
    change(z,y,1);

    nxt[x]=z;
    pre[z]=x;
    nxt[z]=y;
    pre[y]=z;
    on[z]=true;
    top++;
}

// 删除凸包顶点z
void erase(int z){
    int x=pre[z],y=nxt[z];

    change(x,z,-1);
    change(z,y,-1);
    change(x,y,1);

    nxt[x]=y;
    pre[y]=x;
    on[z]=false;
    pre[z]=nxt[z]=0;
    top--;
}

// 判断点z是否在线段xy内部
bool between(int x,int y,int z,long double t){
    long double dx=a[y].x-a[x].x+(v[y].x-v[x].x)*t;
    long double dy=a[y].y-a[x].y+(v[y].y-v[x].y)*t;
    long double ex=a[z].x-a[x].x+(v[z].x-v[x].x)*t;
    long double ey=a[z].y-a[x].y+(v[z].y-v[x].y)*t;

    long double d=dx*ex+dy*ey;
    return d>0&&d<dx*dx+dy*dy;
}

long double deriv(Poly p,long double t){
    return 2*(long double)p.A*t+p.B;
}

// 处理一次三点共线事件
void process(Event e){
    if(top<=2){
        return;
    }

    int p[3]={e.a,e.b,e.c};

    // 判断凸包顶点是否退出
    for(int z=0;z<3;z++){
        int c=p[z];
        if(!on[c]){
            continue;
        }

        int x=pre[c],y=nxt[c];
        if(!x||!y){
            continue;
        }

        bool f1=(x==p[0]||x==p[1]||x==p[2]);
        bool f2=(y==p[0]||y==p[1]||y==p[2]);

        if(f1&&f2&&deriv(orient(x,c,y),e.t)<0){
            erase(c);
            return;
        }
    }

    // 判断新顶点是否加入凸包
    for(int z=0;z<3;z++){
        int c=p[z];
        if(on[c]){
            continue;
        }

        int x=p[(z+1)%3],y=p[(z+2)%3];
        if(!on[x]||!on[y]){
            continue;
        }

        if(nxt[x]==y&&deriv(orient(x,y,c),e.t)<0&&between(x,y,c,e.t)){
            insert(x,y,c);
            return;
        }

        if(nxt[y]==x&&deriv(orient(y,x,c),e.t)<0&&between(y,x,c,e.t)){
            insert(y,x,c);
            return;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double h,g;
    cin>>h>>g>>n;

    for(int i=1;i<=n;i++){
        long long x,y,xx,yy;
        cin>>x>>y>>xx>>yy;
        a[i]={x,y};
        v[i]={xx-x,yy-y};
    }

    if(n<=2){
        cout<<"0.000000"<<endl;
        return 0;
    }

    prepare();
    rebuild((cntt?ev[1].t:1)/2);

    long double last=0,ans=1e100L;

    for(int i=1;i<=cntt;){
        int j=i+1;
        while(j<=cntt&&fabsl(ev[j].t-ev[i].t)<=EPS){
            j++;
        }

        long double t=ev[i].t;
        ans=min(ans,calc(last,t));

        if(ans<1e-9L){
            cout<<"0.000000"<<endl;
            return 0;
        }

        // 同时事件或两点重合，重新建立凸包
        if(j-i>1||ev[i].c==0){
            long double next=j<=cntt?ev[j].t:1;
            rebuild((t+next)/2);
        }
        else{
            process(ev[i]);
        }

        last=t;
        i=j;
    }

    ans=min(ans,calc(last,1));

    cout<<fixed<<setprecision(7)<<(double)ans<<endl;
    return 0;
}
