// 这种做法有问题  比如  5位置的可以影响到10  20位置的也可以影响到10   但是10无法影响到5 和 20
// 那么按照这种做法一个爆炸了就可以  但是实际上需要两个
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int pos[MAXN];
struct node{
    int l,r;
}nums[MAXN];

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

//找到第一个大于等于val的位置
int find1(int val){
    int l=1,r=n,ans=1;
    while(l<=r){
        int mid=(l+r)/2;
        if(pos[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

//找到第一个大于val的位置  如果没有就是n+1
int find2(int val){
    int l=1,r=n,ans=n+1;
    while(l<=r){
        int mid=(l+r)/2;
        if(pos[mid]>val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    fa[x]=y;
}

bool cmp(node a,node b){
    return a.l<b.l;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        pos[i]=read();
        int d1,d2;
        d1=read(),d2=read();
        nums[i].l=pos[i]-d1;
        nums[i].r=pos[i]+d2;
    }
    sort(pos+1,pos+n+1);
    for(int i=1;i<=n;i++){
        nums[i].l=find1(nums[i].l);
        nums[i].r=find2(nums[i].r)-1;
        // cout<<nums[i].l<<' '<<nums[i].r<<endl;
    }
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=n;i++){
        int r=nums[i].r;
        int l=find(nums[i].l);
        while(find(r)!=l){
            un(find(r),l);
            r--;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(find(i)==i){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}