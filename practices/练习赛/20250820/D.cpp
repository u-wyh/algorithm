#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
struct node{
    int l,r,len;
};
node nums[MAXN];
int tree[MAXN<<1];

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
    return a.len>b.len;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i].l=read(),nums[i].r=read();
        if(nums[i].l>nums[i].r){
            swap(nums[i].l,nums[i].r);
        }
        nums[i].len=nums[i].r-nums[i].l;
    }
    sort(nums+1,nums+n+1,cmp);
    bool flag=false;
    for(int i=1;i<=n;i++){
        if(query(nums[i].r)-query(nums[i].l-1)!=0){
            flag=true;
            break;
        }
        add(nums[i].r,1);
        add(nums[i].l,1);
    }
    if(flag){
        cout<<"Yes"<<endl;
    }
    else{
        cout<<"No"<<endl;
    }
    return 0;
}