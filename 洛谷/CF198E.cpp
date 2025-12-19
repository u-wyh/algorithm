#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 250005;
const int MAXM = 1e3+5;

int n;

struct node{
    int x,y,m,p,range,dist;
};
node nums[MAXN];

int blen,bnum;
int bl[MAXM];
int br[MAXM];
int bi[MAXN];
int maxm[MAXN];

int que[MAXN];
bool vis[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

bool cmpm(node a,node b){
    return a.m<b.m;
}

bool cmpd(node a,node b){
    return a.dist<b.dist;
}

int bfs(){
    int ans=0;
    vis[0]=true;
    int l=1,r=0;
    que[++r]=0;
    while(l<=r){
        int cur=que[l++];
        for(int b=1;b<=bnum;b++){
            if(maxm[b]<=nums[cur].p){
                while(bl[b]<=br[b]&&nums[bl[b]].dist<=nums[cur].range){
                    int i=bl[b];
                    if(!vis[i]){
                        vis[i]=true;
                        que[++r]=i;
                        ans++;
                    }
                    bl[b]++;
                }
            }
            else{
                for(int i=bl[b];i<=br[b];i++){
                    if(nums[i].dist<=nums[cur].range&&nums[i].m<=nums[cur].p&&!vis[i]){
                        vis[i]=true;
                        que[++r]=i;
                        ans++;
                    }
                }
                break;
            }
        }
    }
    return ans;
}

void prepare(){
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }
    sort(nums+1,nums+n+1,cmpm);
    for(int i=1;i<=bnum;i++){
        maxm[i]=nums[br[i]].m;
        sort(nums+bl[i],nums+br[i]+1,cmpd);
    }
}

signed main()
{
    int x,y,m,p,range;
    x=read(),y=read(),p=read(),range=read();
    n=read();
    nums[0]={x,y,0,p,range,0};
    for(int i=1;i<=n;i++){
        x=read(),y=read(),m=read(),p=read(),range=read();
        nums[i]={x,y,m,p,range,0};
    }
    int xd,yd;
    for(int i=0;i<=n;i++){
        nums[i].range=(nums[i].range*nums[i].range);
        xd=nums[i].x-nums[0].x;
        yd=nums[i].y-nums[0].y;
        nums[i].dist=(xd*xd+yd*yd);
    }
    prepare();
    cout<<bfs()<<endl;
    return 0;
}