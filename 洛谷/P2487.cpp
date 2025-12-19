#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;

int n;

int h[MAXN];
int v[MAXN];

int m=1;
int arr[MAXN];

struct node{
    int h,v,id;
}nums[MAXN];

int treeval[MAXN];
double treecnt[MAXN];

int len1[MAXN];
double cnt1[MAXN];

int len2[MAXN];
double cnt2[MAXN];

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

bool cmp1(node a,node b){
    return a.h>b.h;
}

bool cmp2(node a,node b){
    return a.h<b.h;
}

int find(int val){
    int l=1,r=m,ans=1;
    while(l<=r){
        int mid=(l+r)/2;
        if(arr[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int val,double cnt){
    while(x<=m){
        if(treeval[x]<val){
            treeval[x]=val;
            treecnt[x]=cnt;
        }
        else if(treeval[x]==val){
            treecnt[x]+=cnt;
        }
        x+=lowbit(x);
    }
}

int queryval;
double querycnt;

void query(int x){
    queryval=0,querycnt=0;
    while(x){
        if(treeval[x]>queryval){
            queryval=treeval[x];
            querycnt=treecnt[x];
        }
        else if(treeval[x]==queryval){
            querycnt+=treecnt[x];
        }
        x-=lowbit(x);
    }
}

void clear(int x){
    while(x<=m){
        treeval[x]=0;
        treecnt[x]=0;
        x+=lowbit(x);
    }
}

void merge1(int l,int mid,int r){
    for(int i=l;i<=r;i++){
        nums[i]={h[i],v[i],i};
    }
    sort(nums+l,nums+mid+1,cmp1);
    sort(nums+mid+1,nums+r+1,cmp1);
    int p1=l-1,p2=mid+1;
    for(;p2<=r;p2++){
        while(p1+1<=mid&&nums[p1+1].h>=nums[p2].h){
            p1++;
            add(m-nums[p1].v+1,len1[nums[p1].id],cnt1[nums[p1].id]);
        }
        query(m-nums[p2].v+1);
        if(queryval+1>len1[nums[p2].id]){
            len1[nums[p2].id]=queryval+1;
            cnt1[nums[p2].id]=querycnt;
        }
        else if(queryval+1==len1[nums[p2].id]){
            cnt1[nums[p2].id]+=querycnt;
        }
    }
    for(int i=l;i<=p1;i++){
        clear(m-nums[i].v+1);
    }
}

void cdq1(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)/2;
    cdq1(l,mid);
    merge1(l,mid,r);
    cdq1(mid+1,r);
}

void merge2(int l,int mid,int r){
    for(int i=l;i<=r;i++){
        nums[i]={h[i],v[i],i};
    }
    sort(nums+l,nums+mid+1,cmp2);
    sort(nums+mid+1,nums+r+1,cmp2);
    int p1=l-1,p2=mid+1;
    for(;p2<=r;p2++){
        while(p1+1<=mid&&nums[p1+1].h<=nums[p2].h){
            p1++;
            add(nums[p1].v,len2[nums[p1].id],cnt2[nums[p1].id]);
        }
        query(nums[p2].v);
        if(queryval+1>len2[nums[p2].id]){
            len2[nums[p2].id]=queryval+1;
            cnt2[nums[p2].id]=querycnt;
        }
        else if(queryval+1==len2[nums[p2].id]){
            cnt2[nums[p2].id]+=querycnt;
        }
    }
    for(int i=l;i<=p1;i++){
        clear(nums[i].v);
    }
}

void cdq2(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)/2;
    cdq2(l,mid);
    merge2(l,mid,r);
    cdq2(mid+1,r);
}

void compute(){
    cdq1(1,n);

    for(int l=1,r=n;l<r;l++,r--){
        swap(h[l],h[r]);
        swap(v[l],v[r]);
    }
    cdq2(1,n);

    for(int l=1,r=n;l<r;l++,r--){
        swap(len2[l],len2[r]);
        swap(cnt2[l],cnt2[r]);
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        h[i]=read();
        v[i]=read();
        arr[i]=v[i];
    }
    sort(arr+1,arr+n+1);
    for(int i=2;i<=n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        v[i]=find(v[i]);
    }
    for(int i=1;i<=n;i++){
        len1[i]=len2[i]=1;
        cnt1[i]=cnt2[i]=1.0;
    }
    compute();
    int len = 0;
    double cnt = 0.0;
    for (int i = 1; i <= n; i++) {
        len = max(len, len1[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (len1[i] == len) {
            cnt += cnt1[i];//求出总方案数
        }
    }
    printf("%d\n", len);
    for (int i = 1; i <= n; i++) {
        if (len1[i] + len2[i] - 1 < len) {
            //无法被拦截
            printf("0 ");
        } else {
            printf("%.5f ", cnt1[i] * cnt2[i] / cnt);
        }
    }
    printf("\n");
    return 0;
}