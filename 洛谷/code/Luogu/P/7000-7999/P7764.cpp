#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,m,t=1;
struct node{
    int l,r,id;
}nums[MAXN];
int arr[MAXN];
int temp[MAXN];
int pos[MAXN];
int ans[MAXN];
int cnt[MAXN];

inline int read(){
    int x=0;int ch=getchar(),f=1;
    while (!isdigit(ch)&&(ch!='-')&&(ch!=EOF)) ch=getchar();
    if (ch=='-'){f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return x*f;
}

//奇偶性排序优化
inline bool cmp(node a,node b) {
	return (pos[a.l] ^ pos[b.l]) ? pos[a.l] < pos[b.l] : ((pos[a.l] & 1) ? a.r < b.r : a.r > b.r);
}

inline int ranking(int x){
    int l=1,r=t,ans=0;
    while(l<=r){
        int mid=l+(r-l)/2;
        if(temp[mid]>=x){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    n=read();
    m=read();
    int siz=sqrt(n);
    for(int i=1;i<=n;i++){
        arr[i]=read();
        temp[i]=arr[i];
        pos[i]=i/siz;
    }
    sort(temp+1,temp+n+1);
    for(int i=2;i<=n;i++){
        if(temp[i]!=temp[i-1]){
            temp[++t]=temp[i];
        }
    }
    for(int i=1;i<=n;i++){
        arr[i]=ranking(arr[i]);
    }
    for(int i=1;i<=m;i++){
        nums[i].l=read();
        nums[i].r=read();
        nums[i].id=i;
    }
    sort(nums+1,nums+m+1,cmp);
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        while(nums[i].l<l) cnt[arr[--l]]++;
        while(nums[i].r>r) cnt[arr[++r]]++;
        while(nums[i].l>l) cnt[arr[l++]]--;
        while(nums[i].r<r) cnt[arr[r--]]--;
        //匹配区间  得到答案
        int res=0;
        for(int i=1;i<=t;i++){
            if(cnt[i]==2){
                res++;
            }
        }
        ans[nums[i].id]=res;
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
