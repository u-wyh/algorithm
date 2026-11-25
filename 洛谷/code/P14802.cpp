// https://www.luogu.com.cn/problem/P14802
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int INF = 4e18;

int n;
bool vis[MAXN];

struct Point{
    int x,y,id;
};
Point p[MAXN];
Point hull1[MAXN];
int cnt1=0;
Point hull2[MAXN<<1];
int cnt2=0;

bool cmp(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

void Andrew(Point *hull,int &cnt,int all){
    if(all<=2){
        for(int i=1;i<=n;i++){
            if(!vis[p[i].id]){
                hull[++cnt]=p[i];
            }
        }
        if(cnt>0){
            hull[cnt+1]=hull[1];
        }
        return ;
    }
    for(int i=1;i<=n;i++){
        if(vis[p[i].id]){
            continue;
        }
        while(cnt>1&&cross(hull[cnt]-hull[cnt-1],p[i]-hull[cnt-1])<=0){
            cnt--;
        }
        hull[++cnt]=p[i];
    }
    int t=cnt;
    for(int i=n-1;i>=1;i--){
        if(vis[p[i].id]){
            continue;
        }
        while(cnt>t && cross(hull[cnt]-hull[cnt-1],p[i]-hull[cnt-1])<=0){
            cnt--;
        }
        hull[++cnt]=p[i];
    }
    cnt--;
    hull[cnt+1]=hull[1];
    for(int i=1;i<=cnt;i++){
        vis[hull[i].id]=true;
    }
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
        p[i].id=i;
        vis[i]=false;
    }
    sort(p+1,p+n+1,cmp);

    cnt1=cnt2=0;
    Andrew(hull1,cnt1,n);
    if(cnt1==n){
        cout<<-1<<endl;
        return ;
    }
    Andrew(hull2,cnt2,n-cnt1);
    for(int i=1;i<=cnt2;i++){
        hull2[i+cnt2]=hull2[i];
    }

    int ans=INF;
    int pos=1;
    for(int i=1;i<=cnt2;i++){
        int v=cross(hull1[2]-hull1[1],hull2[i]-hull1[1]);
        if(v<ans){
            ans=v;
            pos=i;
        }
    }

    for(int i=2;i<=cnt1;i++){
        while(pos+1<=2*cnt2&& cross(hull1[i+1]-hull1[i],hull2[pos]-hull1[i])>=cross(hull1[i+1]-hull1[i],hull2[pos+1]-hull1[i])){
            pos++;
        }
        ans=min(ans,cross(hull1[i+1]-hull1[i],hull2[pos]-hull1[i]));
    }

    ans=-ans;
    for(int i=2;i<cnt1;i++){
        ans+=cross(hull1[i]-hull1[1],hull1[i+1]-hull1[1]);
    }
    cout<<ans<<endl;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
