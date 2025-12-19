#include <bits/stdc++.h>
#define int long long
using namespace std;
int dx[]={1,0,-1,0};
int dy[]={0,-1,0,1};
int n,m;
const int inf=1e9;

vector<vector<int>> g;
vector<vector<int>> dis;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}
void write(int x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

bool check(int x,int y){
    if(x<1||x>n||y<1||y>m||dis[x][y]!=inf||g[x][y]) return 1;
    return 0;
}

bool check(int mid){
    bool flag=false;
    int maxx=INT_MIN,minx=INT_MAX,maxy=INT_MIN,miny=INT_MAX;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(dis[i][j]>mid){
                flag=true;
                maxx=max(maxx,i+j);
                minx=min(minx,i+j);
                maxy=max(maxy,j-i);
                miny=min(miny,j-i);
            }
        }
    }
    // if(!flag){
    //     return true;
    // }
    return max(maxx-minx,maxy-miny)<=2*mid;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++){
    //         int x=i+j;
    //         int y=j-i;
    //         if((x-mid<=minx)&&(x+mid>=maxx)&&(y-mid<=miny)&&(y+mid>=maxy)){
    //             return true;
    //         }
    //     }
    // }
    // return false;
}

signed main(){
    n=read(),m=read();
    g.resize(n+10),dis.resize(n+10);
    for(int i=0;i<=n;i++){
        g[i].resize(m+10);
        dis[i].resize(m+10);
        for(int j=1;j<=m;j++) 
            dis[i][j]=inf;
    }
    queue<pair<int,int>> q;
    int all=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            g[i][j]=read();
            all+=g[i][j];
        }
    }
    if(all==0){
        // cout<<((n+1)/2+(m+1)/2)<<endl;
        int maxx=n+m;
        int minx=2;
        int maxy=m-1;
        int miny=1-n;
        int ans=inf;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                int x=i+j,y=j-i;
                ans=min(ans,max(max(x-minx,maxx-x),max(y-miny,maxy-y)));
            }
        }
        cout<<ans<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(g[i][j]){
                q.push({i,j});
                dis[i][j]=0;
            }
        }
    }
    while(q.size()){
        int x=q.front().first,y=q.front().second;
        q.pop();
        for(int i=0;i<4;i++){
            int tx=x+dx[i];
            int ty=y+dy[i];
            if(check(tx,ty)) continue;
            q.push({tx,ty});
            dis[tx][ty]=min(dis[tx][ty],dis[x][y]+1);
        }
    }
    int l=0,r=max(n,m),ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}