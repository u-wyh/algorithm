// https://www.luogu.com.cn/problem/P4357
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXK = 105;

int n,k;
struct Point{
    int x,y;
    int id;
};
Point nums[MAXN];
bool vis[MAXN];
int top;
Point sta[MAXN];

Point p[MAXK*2];
int cnt;

bool cmp(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

int cross(Point a,Point b,Point c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

int dis2(Point a,Point b){
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

void Andrew(){
    top=0;
    for(int i=1;i<=n;i++){
        if(vis[nums[i].id]){
            continue;
        }
        while(top>1 && cross(sta[top-1],sta[top],nums[i])<=0){
            top--;
        }
        sta[++top]=nums[i];
    }
    int t=top;
    for(int i=n-1;i>=1;i--){
        if(vis[nums[i].id]){
            continue;
        }
        while(top>t && cross(sta[top-1],sta[top],nums[i])<=0){
            top--;
        }
        sta[++top]=nums[i];
    }
    top--;
}

void rorating_calipers(){
    int res=0;
    int ans1,ans2;
    for(int i=1,j=2;i<=top;i++){
        while(cross(sta[i],sta[i+1],sta[j])<cross(sta[i],sta[i+1],sta[j+1])){
            j=(j%top)+1;
        }
        int dis0=dis2(sta[i],sta[j]);
        int dis1=dis2(sta[i+1],sta[j]);
        if(dis0>=res){
            res=dis0;
            ans1=sta[i].id;
            ans2=sta[j].id;
        }
        if(dis1>=res){
            res=dis1;
            ans1=sta[i+1].id;
            ans2=sta[j].id;
        }
    }
    vis[ans1]=true;
    vis[ans2]=true;
}

void compute(){
    priority_queue<int,vector<int>,greater<int>> heap;

    for(int i=1;i<=cnt;i++){
        for(int j=1;j<=n;j++){
            int u=p[i].id;
            int v=nums[j].id;

            if(u==v){
                continue;
            }

            // 两个端点都是关键点时只枚举一次
            if(vis[v] && u>v){
                continue;
            }

            int d=dis2(p[i],nums[j]);

            if((int)heap.size()<k){
                heap.push(d);
            }
            else if(d>heap.top()){
                heap.pop();
                heap.push(d);
            }
        }
    }

    cout<<heap.top()<<endl;
}

signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
        nums[i].id=i;
    }
    sort(nums+1,nums+n+1,cmp);

    if(2*k>n){
        for(int i=1;i<=n;i++){
            p[++cnt]=nums[i];
        }
    }
    else{
        for(int i=1;i<=k;i++){
            Andrew();
            rorating_calipers();
        }
        for(int i=1;i<=n;i++){
            if(vis[nums[i].id]){
                p[++cnt]=nums[i];
            }
        }
    }
    compute();
    return 0;
}