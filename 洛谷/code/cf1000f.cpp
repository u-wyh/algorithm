#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

struct node{
    int l,r,id;
}nums[MAXN];
int n,m;
int arr[MAXN];
int pos[MAXN];
int sum[5005];
int ed[5005];
int ans[MAXN];
int cnt[MAXN];

//∆Ê≈º–‘≈≈–Ú”≈ªØ
bool cmp(node a,node b) {
	return (pos[a.l] ^ pos[b.l]) ? pos[a.l] < pos[b.l] : ((pos[a.l] & 1) ? a.r < b.r : a.r > b.r);
}

void Add(int n){
    cnt[arr[n]]++;
    if(cnt[arr[n]]==1){
        sum[pos[n]]++;
    }
    if(cnt[arr[n]]==2){
        sum[pos[n]]--;
    }
}

void Sub(int n){
    cnt[arr[n]]--;
    if(cnt[arr[n]]==1){
        sum[pos[n]]++;
    }
    if(cnt[arr[n]]==0){
        sum[pos[n]]--;
    }
}

int fun(){
    for(int i=0;i<=pos[n];i++){
        if(sum[i]==0){
            continue;
        }
        for(int j=ed[i];pos[j]==i&&j>0;j--){
            if(cnt[arr[j]]==1){
                return arr[j];
            }
        }
    }
    return 0;
}

int main()
{
    scanf("%d",&n);
    int siz=1000;
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
        pos[i]=i/siz;
        ed[pos[i]]=i;
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%d %d",&nums[i].l,&nums[i].r);
        nums[i].id=i;
    }
    sort(nums+1,nums+m+1,cmp);
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        while(nums[i].l<l) Add(--l);
        while(nums[i].l>l) Sub(l++);
        while(nums[i].r<r) Sub(r--);
        while(nums[i].r>r) Add(++r);
        ans[nums[i].id]=fun();
    }
    for(int i=1;i<=m;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}
