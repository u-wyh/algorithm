#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MAXM = 3e4+5;

int n,m;
struct node{
    int l,r,w;
}nums[MAXN],tmp[MAXN];

int fa[MAXN];

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

bool cmp(node a,node b){
    return a.w>b.w;
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

bool check(int t){
    for(int i=1;i<=n+1;i++){
        fa[i]=i;
    }
    for(int i=1;i<=t;i++){
        tmp[i]=nums[i];
    }
    sort(tmp+1,tmp+t+1,cmp);
    int l=1,r=2;
    int lt,tl,rt,tr;
    while(l<=t){
        tl=lt=tmp[l].l,tr=rt=tmp[l].r;
        while(tmp[r].w==tmp[l].w&&r<=t){
            r++;
        }
        for(int i=l+1;i<r;i++){
            if(tmp[i].r<lt||tmp[i].l>rt){
                return false;
            }
            tl=min(tl,tmp[i].l);
            tr=max(tr,tmp[i].r);
            rt=min(rt,tmp[i].r);
            lt=max(lt,tmp[i].l);
        }
        if(find(lt)>rt){
            return false;
        }
        for(int i=find(tl);i<=tr;i=find(i+1)){
            un(i,i+1);
        }
        l=r;
    }
    return 1;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        nums[i].l=read(),nums[i].r=read(),nums[i].w=read();
    }
    int l=1,r=m,ans=0;//这里二分答案求的是最大可以符合条件的
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    if(ans==m){
        ans=-1;
    }
    cout<<(ans+1)<<endl;
    return 0;
}