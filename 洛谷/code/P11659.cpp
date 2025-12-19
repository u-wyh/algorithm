#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m,sz;
long long res;
int arr[MAXN];
int pos[MAXN];

struct node{
    int l,r,sub;
}nums[MAXN];
long long ans[MAXN];

int cnt[MAXN];
int cnt1[MAXN];
int cnt2[MAXN];

bool cmp(node a,node b){
    return (pos[a.l]==pos[b.l])?((pos[a.l]&1)?a.r<b.r:a.r>b.r):(pos[a.l]<pos[b.l]);
}

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

inline void addhead(int i){
    cnt[arr[i]]++;
    if(arr[i]%2){
        return ;
    }
    res+=cnt1[arr[i]/2];
    cnt1[arr[i]]+=cnt[3*arr[i]/2];
    cnt2[arr[i]/2]+=cnt[arr[i]/2];
}

inline void delhead(int i){
    cnt[arr[i]]--;
    if(arr[i]%2){
        return ;
    }
    res-=cnt1[arr[i]/2];
    cnt1[arr[i]]-=cnt[3*arr[i]/2];
    cnt2[arr[i]/2]-=cnt[arr[i]/2];
}

inline void addtail(int i){
    cnt[arr[i]]++;
    cnt2[arr[i]]+=cnt[2*arr[i]];
    if(arr[i]%3){
        return ;
    }
    res+=cnt2[2*arr[i]/3];
    cnt1[2*arr[i]/3]+=cnt[2*arr[i]/3];
}

inline void deltail(int i){
    cnt[arr[i]]--;
    cnt2[arr[i]]-=cnt[2*arr[i]];
    if(arr[i]%3){
        return ;
    }
    res-=cnt2[2*arr[i]/3];
    cnt1[2*arr[i]/3]-=cnt[2*arr[i]/3];
}

int main()
{
    n=read(),m=read();
    sz=sqrt(n);
    for(int i=1;i<=n;i++){
        arr[i]=read();
        pos[i]=i/sz;
    }
    for(int i=1;i<=m;i++){
        nums[i].l=read(),nums[i].r=read();
        nums[i].sub=i;
    }
    sort(nums+1,nums+m+1,cmp);
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        while(l<nums[i].l) delhead(l++);
        while(l>nums[i].l) addhead(--l);
        while(r>nums[i].r) deltail(r--);
        while(r<nums[i].r) addtail(++r);
        ans[nums[i].sub]=res;
    }
    for(int i=1;i<=m;i++){
        printf("%lld\n",ans[i]);
    }
    return 0;
}