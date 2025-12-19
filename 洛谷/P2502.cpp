#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;

int n,m,st,en;
struct node{
    int u,v,w;
}nums[5005];
int fa[MAXN];

int gcd(int a,int b){
    return a%b==0?b:gcd(b,a%b);
}

bool cmp(node a,node b){
    return a.w<b.w;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        cin>>nums[i].u>>nums[i].v>>nums[i].w;
        un(nums[i].u,nums[i].v);
    }
    sort(nums+1,nums+m+1,cmp);
    cin>>st>>en;
    if(find(st)!=find(en)){
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }
    double ans=INT_MAX;
    int x=1,y=1;
    for(int i=m;i>=1;i--){
        for(int j=1;j<=n;j++){
            fa[j]=j;
        }
        un(nums[i].u,nums[i].v);
        if(find(st)==find(en)){
            cout<<1<<endl;
            return 0;
        }
        for(int j=i-1;j>=1;j--){
            un(nums[j].u,nums[j].v);
            if(find(st)==find(en)){
                if(ans>(1.0*nums[i].w/nums[j].w)){
                    ans=(1.0*nums[i].w/nums[j].w);
                    int t=gcd(nums[i].w,nums[j].w);
                    x=nums[i].w/t,y=nums[j].w/t;
                }
                break;
            }
        }
        if(find(st)!=find(en)){
            break;
        }
    }
    if(y!=1)
        cout<<x<<'/'<<y<<endl;
    else
        cout<<x<<endl;
    return 0;
}
