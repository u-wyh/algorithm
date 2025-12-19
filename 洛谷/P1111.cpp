#include<bits/stdc++.h>
using namespace std;
#define Max 100005

typedef struct{
    int x,y,t;
}road;

int n,m;
road nums[100005];

int cmp(const road &a,const road &b){
    return a.t<b.t;
}

int father[Max],size[Max],stack1[Max];

void build(int n){
    for(int i=0;i<=n;i++){
        father[i]=i;
        size[i]=1;
    }
}

int find(int i){
    int size=0;
    while(i!=father[i]){
        stack1[size++]=i;
        i=father[i];
    }
    while(size>0){
        father[stack1[--size]]=i;
    }
    return i;
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        if(size[fx]>=size[fy]){
            size[fx]+=size[fy];
            father[fy]=fx;
        }else{
            size[fy]+=size[fx];
            father[fx]=fy;
        }
    }
}

bool check(int x){
    build(n);
    for(int i=1;i<=m;i++){
        if(nums[i].t>x)
            break;
        un(nums[i].x,nums[i].y);
    }
    for(int i=1;i<=n;i++){
        if(size[i]==n)
            return true;
    }
    return false;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>nums[i].x>>nums[i].y>>nums[i].t;
    }
    sort(nums+1,nums+1+m,cmp);
    int l=0,r=100005,ans=-1,mid;
    while(l<=r){
        memset(father,0,sizeof(father));
        memset(stack1,0,sizeof(stack1));
        memset(size,0,sizeof(size));
        mid=(l+r)/2;
        if(check(m)){
            ans=m;
            r=m-1;
        }else{
            l=m+1;
        }
    }
    cout<<ans;
    return 0;
}
