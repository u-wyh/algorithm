#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int ans[MAXN];
struct node{
    int x1,y1,x2,y2;
};
node nums[MAXN];
node tmp[MAXN];

struct QUERY{
    int op,x,y,id;
};
QUERY q[MAXN<<1];
int cnte;

int tree[MAXN<<1];

int arr[MAXN<<1];
int m;

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

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=2*n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

int find(int val){
    int l=1,r=m,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
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

void prepare(){
    for(int i=1;i<=n;i++){
        arr[2*i-1]=nums[i].x1;
        arr[2*i]=nums[i].x2;
    }
    sort(arr+1,arr+2*n+1);
    m=1;
    for(int i=2;i<=2*n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i].x1=find(nums[i].x1);
        nums[i].x2=find(nums[i].x2);
    }

    for(int i=1;i<=n;i++){
        arr[2*i-1]=nums[i].y1;
        arr[2*i]=nums[i].y2;
    }
    sort(arr+1,arr+2*n+1);
    m=1;
    for(int i=2;i<=2*n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i].y1=find(nums[i].y1);
        nums[i].y2=find(nums[i].y2);
    }

    for(int k=1;k<=4;k++){
        for(int i=n;i>=1;i--){
            if(k==1){
                ans[i]+=(n-i)-query(nums[i].x2);
                add(nums[i].x1,1);
            }
            else if(k==2){
                ans[i]+=query(nums[i].x1-1);
                add(nums[i].x2,1);
            }
            else if(k==3){
                ans[i]+=query(nums[i].y1-1);
                add(nums[i].y2,1);
            }
            else{
                ans[i]+=(n-i)-query(nums[i].y2);
                add(nums[i].y1,1);
            }
        }

        // cout<<k<<":  "<<endl;
        // for(int i=1;i<=n;i++){
        //     cout<<i<<":   "<<ans[i]<<endl;
        // }

        for(int i=1;i<=2*n;i++){
            tree[i]=0;
        }
    }
}

bool cmp(QUERY a,QUERY b){
    return a.x<b.x;
}

void merge(int l,int m,int r){
    int p1,p2;
    for(p1=l-1,p2=m+1;p2<=r;p2++){
        while(p1+1<=m&&q[p1+1].x<=q[p2].x){
            p1++;
            if(q[p1].op==1){
                add(q[p1].y,1);
            }
        }
        if(q[p2].op==2){
            ans[q[p2].id]-=query(q[p2].y);
        }
    }
    for(int i=l;i<=p1;i++){
        if(q[i].op==1){
            add(q[i].y,-1);
        }
    }
    sort(q+l,q+r+1,cmp);
}

void cdq(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    merge(l,mid,r);
}

void pre(){
    for(int i=1;i<=2*n;i++){
        tree[i]=0;
    }
    cnte=0;
    for(int i=n;i>=1;i--){
        q[++cnte]={2,tmp[i].x1-1,tmp[i].y1-1,i};
        q[++cnte]={1,tmp[i].x2,tmp[i].y2,0};
    }
}

void to1(){
    for(int i=1;i<=n;i++){
        tmp[i]=nums[i];
    }
    pre();
    // cout<<1<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<i<<":  "<<tmp[i].x1<<' '<<tmp[i].y1<<' '<<tmp[i].x2<<' '<<tmp[i].y2<<endl;
    // }
    cdq(1,cnte);
}

void to2(){
    for(int i=1;i<=n;i++){
        tmp[i].x1=nums[i].y1;
        tmp[i].y1=2*n+1-nums[i].x2;
        tmp[i].x2=nums[i].y2;
        tmp[i].y2=2*n+1-nums[i].x1;
    }
    pre();
    // cout<<2<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<i<<":  "<<tmp[i].x1<<' '<<tmp[i].y1<<' '<<tmp[i].x2<<' '<<tmp[i].y2<<endl;
    // }
    cdq(1,cnte);
}

void to3(){
    for(int i=1;i<=n;i++){
        tmp[i].x1=2*n+1-nums[i].x2;
        tmp[i].y1=2*n+1-nums[i].y2;
        tmp[i].x2=2*n+1-nums[i].x1;
        tmp[i].y2=2*n+1-nums[i].y1;
    }
    pre();
    // cout<<3<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<i<<":  "<<tmp[i].x1<<' '<<tmp[i].y1<<' '<<tmp[i].x2<<' '<<tmp[i].y2<<endl;
    // }
    cdq(1,cnte);
}

void to4(){
    for(int i=1;i<=n;i++){
        tmp[i].x1=2*n+1-nums[i].y2;
        tmp[i].y1=nums[i].x1;
        tmp[i].x2=2*n+1-nums[i].y1;
        tmp[i].y2=nums[i].x2;
    }
    pre();
    // cout<<4<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<i<<":  "<<tmp[i].x1<<' '<<tmp[i].y1<<' '<<tmp[i].x2<<' '<<tmp[i].y2<<endl;
    // }
    cdq(1,cnte);
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        int x,y,a,b;
        cin>>x>>y>>a>>b;
        // cout<<i<<":  "<<(x+1)<<' '<<(y+1)<<' '<<(x+a)<<' '<<(y+b)<<endl;
        nums[i]={x+1,y+1,x+a,y+b};
    }
    prepare();

    // for(int i=1;i<=n;i++){
    //     cout<<i<<":   "<<ans[i]<<endl;
    // }

    to1();
    to2();
    to3();
    to4();

    // for(int i=1;i<=n;i++){
    //     cout<<i<<":   "<<ans[i]<<endl;
    // }

    for(int i=1;i<=n;i++){
        if(ans[i]==n-i){
            printf("DA\n");
        }
        else{
            printf("NE\n");
        }
    }
    return 0;
}
/*
5
1 1 4 2
6 1 1 1
2 2 2 3
3 4 3 2
4 0 1 2
*/