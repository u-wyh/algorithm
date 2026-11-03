
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+5;

int n;

struct Point{
    long long x,y;
    int id;
};

Point nums[MAXN];
Point sta[MAXN];
int top;

bool cmp(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

long long cross(Point a,Point b,Point c){
    return (b.x-a.x)*(c.y-a.y)
          -(b.y-a.y)*(c.x-a.x);
}

long long dis(Point a,Point b){
    long long dx=a.x-b.x;
    long long dy=a.y-b.y;
    return dx*dx+dy*dy;
}

void Andrew(){
    top=0;
    sort(nums+1,nums+n+1,cmp);

    // 去除坐标重复的点
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(cnt==0 || nums[i].x!=nums[cnt].x
                  || nums[i].y!=nums[cnt].y){
            nums[++cnt]=nums[i];
        }
    }
    n=cnt;

    // 下凸包
    for(int i=1;i<=n;i++){
        while(top>1 && cross(sta[top-1],sta[top],nums[i])<=0){
            top--;
        }
        sta[++top]=nums[i];
    }

    int t=top;

    // 上凸包
    for(int i=n-1;i>=1;i--){
        while(top>t && cross(sta[top-1],sta[top],nums[i])<=0){
            top--;
        }
        sta[++top]=nums[i];
    }

    top--;
    sta[top+1]=sta[1];
}

void rotating_calipers(){
    // 所有点坐标相同
    if(top==1){
        cout<<0<<' '<<1<<endl;
        return;
    }

    long long res=-1;
    int ans1=0,ans2=1;

    for(int i=1,j=2;i<=top;i++){
        while(cross(sta[i],sta[i+1],sta[j])
              <cross(sta[i],sta[i+1],sta[j%top+1])){
            j=(j%top)+1;
        }

        long long dis1=dis(sta[i],sta[j]);
        long long dis2=dis(sta[i+1],sta[j]);

        if(dis1>res){
            res=dis1;
            ans1=sta[i].id;
            ans2=sta[j].id;
        }

        if(dis2>res){
            res=dis2;
            ans1=sta[i+1].id;
            ans2=sta[j].id;
        }
    }

    cout<<ans1<<' '<<ans2<<endl;
}

void solve(){
    cin>>n;

    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
        nums[i].id=i-1;
    }

    Andrew();
    rotating_calipers();
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
