// https://www.luogu.com.cn/problem/P6504
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int INF = 505;

int r,c;
int val[MAXN][MAXN];
int sum[26][MAXN][MAXN];

int n;
struct Point{
    int x,y;
};
Point p[MAXN];

void prepare(){
    for(int v=0;v<=25;v++){
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                if(val[i][j]==v){
                    sum[v][i][j]=1;
                }
            }
        }
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                sum[v][i][j]+=sum[v][i][j-1]+sum[v][i-1][j]-sum[v][i-1][j-1];
            }
        }
    }
}

int main()
{
    cin>>r>>c;
    for(int i=1;i<=r;i++){
        string s;
        cin>>s;
        for(int j=1;j<=c;j++){
            val[i][j]=s[j-1]-'a';
        }
    }

    prepare();

    cin>>n;
    int minx=INF,miny=INF;
    int maxx=0,maxy=0;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
        minx=min(minx,p[i].x);
        miny=min(miny,p[i].y);
        maxx=max(maxx,p[i].x);
        maxy=max(maxy,p[i].y);
    }
    int w=maxx-minx;
    int h=maxy-miny;
    int area=0;
    for(int i=1;i<=n;i++){
        p[i].x-=minx;
        p[i].y-=miny;
    }
    p[n+1]=p[1];

    int sx=-1,sy=-1;
    for(int i=1;i<=n;i++){
        area+=p[i].x*p[i+1].y-p[i+1].x*p[i].y;
        if(p[i].y==p[i+1].y&&p[i].x<p[i+1].x){
            sx=p[i].x;
            sy=p[i].y;
        }
    }
    area/=2;

    int ans=0;
    for(int dy=0;dy+h<=r;dy++){
        for(int dx=0;dx+w<=c;dx++){
            int v=val[dy+sy+1][dx+sx+1];
            int cnt=0;
            for(int i=1;i<=n;i++){
                if(p[i].y!=p[i+1].y){
                    continue;
                }
                int y=dy+p[i].y;
                int x1=dx+p[i].x;
                int x2=dx+p[i+1].x;
                cnt+=sum[v][y][x1]-sum[v][y][x2];
            }
            if(cnt==area){
                ans++;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}