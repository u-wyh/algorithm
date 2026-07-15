#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20005;

int n;
int x[MAXN];
int y[MAXN];
bool flag[MAXN];

bool vis[MAXN];

int minx,maxx,miny,maxy;
int xmin,xmax,ymin,ymax;

bool compute(int xl,int xr,int yl,int yr,int lx,int rx,int ly,int ry){
    for(int i=1;i<=n;i++){
        if((x[i]>=xl&&x[i]<=xr&&y[i]>=yl&&y[i]<=yr)||(x[i]>=lx&&x[i]<=rx&&y[i]>=ly&&y[i]<=ry)){
            vis[i]=true;
        }
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            return false;
        }
    }
    return true;
}

bool check(int len){
    int xl,xr,yl,yr;

    for(int i=1;i<=n;i++){
        flag[i]=false;
    }
    xl=minx,xr=minx+len,yl=miny,yr=miny+len;
    for(int i=1;i<=n;i++){
        if(x[i]>=xl&&x[i]<=xr&&y[i]>=yl&&y[i]<=yr){
            flag[i]=true;
        }
    }
    xmin=INT_MAX,ymin=INT_MAX,xmax=INT_MIN,ymax=INT_MIN;
    for(int i=1;i<=n;i++){
        vis[i]=flag[i];
        if(!flag[i]){
            xmin=min(xmin,x[i]);
            xmax=max(xmax,x[i]);
            ymin=min(ymin,y[i]);
            ymax=max(ymax,y[i]);
        }
    }
    if(compute(xmin,xmin+len,ymin,ymin+len,xmax-len,xmax,ymax-len,ymax)){
        return true;
    }
    for(int i=1;i<=n;i++){
        vis[i]=flag[i];
    }
    if(compute(xmin,xmin+len,ymax-len,ymax,xmax-len,xmax,ymin,ymin+len)){
        return true;
    }


    for(int i=1;i<=n;i++){
        flag[i]=false;
    }
    xl=minx,xr=minx+len,yl=maxy-len,yr=maxy;
    for(int i=1;i<=n;i++){
        if(x[i]>=xl&&x[i]<=xr&&y[i]>=yl&&y[i]<=yr){
            flag[i]=true;
        }
    }
    xmin=INT_MAX,ymin=INT_MAX,xmax=INT_MIN,ymax=INT_MIN;
    for(int i=1;i<=n;i++){
        vis[i]=flag[i];
        if(!flag[i]){
            xmin=min(xmin,x[i]);
            xmax=max(xmax,x[i]);
            ymin=min(ymin,y[i]);
            ymax=max(ymax,y[i]);
        }
    }
    if(compute(xmin,xmin+len,ymin,ymin+len,xmax-len,xmax,ymax-len,ymax)){
        return true;
    }
    for(int i=1;i<=n;i++){
        vis[i]=flag[i];
    }
    if(compute(xmin,xmin+len,ymax-len,ymax,xmax-len,xmax,ymin,ymin+len)){
        return true;
    }


    for(int i=1;i<=n;i++){
        flag[i]=false;
    }
    xl=maxx-len,xr=maxx,yl=maxy-len,yr=maxy;
    for(int i=1;i<=n;i++){
        if(x[i]>=xl&&x[i]<=xr&&y[i]>=yl&&y[i]<=yr){
            flag[i]=true;
        }
    }
    xmin=INT_MAX,ymin=INT_MAX,xmax=INT_MIN,ymax=INT_MIN;
    for(int i=1;i<=n;i++){
        vis[i]=flag[i];
        if(!flag[i]){
            xmin=min(xmin,x[i]);
            xmax=max(xmax,x[i]);
            ymin=min(ymin,y[i]);
            ymax=max(ymax,y[i]);
        }
    }
    if(compute(xmin,xmin+len,ymin,ymin+len,xmax-len,xmax,ymax-len,ymax)){
        return true;
    }
    for(int i=1;i<=n;i++){
        vis[i]=flag[i];
    }
    if(compute(xmin,xmin+len,ymax-len,ymax,xmax-len,xmax,ymin,ymin+len)){
        return true;
    }


    for(int i=1;i<=n;i++){
        flag[i]=false;
    }
    xl=maxx-len,xr=maxx,yl=miny,yr=miny+len;
    for(int i=1;i<=n;i++){
        if(x[i]>=xl&&x[i]<=xr&&y[i]>=yl&&y[i]<=yr){
            flag[i]=true;
        }
    }
    xmin=INT_MAX,ymin=INT_MAX,xmax=INT_MIN,ymax=INT_MIN;
    for(int i=1;i<=n;i++){
        vis[i]=flag[i];
        if(!flag[i]){
            xmin=min(xmin,x[i]);
            xmax=max(xmax,x[i]);
            ymin=min(ymin,y[i]);
            ymax=max(ymax,y[i]);
        }
    }
    if(compute(xmin,xmin+len,ymin,ymin+len,xmax-len,xmax,ymax-len,ymax)){
        return true;
    }
    for(int i=1;i<=n;i++){
        vis[i]=flag[i];
    }
    if(compute(xmin,xmin+len,ymax-len,ymax,xmax-len,xmax,ymin,ymin+len)){
        return true;
    }
    return false;
}

int main()
{
    cin>>n;
    minx=INT_MAX,miny=INT_MAX,maxx=INT_MIN,maxy=INT_MIN;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
        minx=min(minx,x[i]);
        maxx=max(maxx,x[i]);
        miny=min(miny,y[i]);
        maxy=max(maxy,y[i]);
    }
    int l=0,r=2000000000,ans=0;
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