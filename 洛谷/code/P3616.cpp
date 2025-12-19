#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,q,m;
int nums[MAXN];
int arr[MAXN<<1];
int tree[MAXN<<1];
int op[MAXN];
int a[MAXN],b[MAXN];

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
    // cout<<x<<' '<<v<<endl;
    while(x<=m){
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
    int l=1,r=m,ans=m;
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

int main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
        arr[i]=nums[i];
    }
    for(int i=1;i<=q;i++){
        op[i]=read(),a[i]=read();
        if(op[i]==1){
            arr[n+i]=a[i];
        }
        else{
            b[i]=read();
            arr[n+i]=b[i];
        }
    }
    arr[n+1+q]=0;
    sort(arr+1,arr+n+2+q);
    m=1;
    for(int i=2;i<=n+q+1;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i]=find(nums[i]);
    }
    // for(int i=1;i<=n;i++){
    //     cout<<nums[i]<<' ';
    // }
    // cout<<endl;
    for(int i=1;i<=q;i++){
        if(op[i]==1){
            a[i]=find(a[i]);
        }
        else{
            b[i]=find(b[i]);
        }
    }

    // cout<<' '<<m<<endl;
    // cout<<endl;

    add(1,1);
    add(2,-1);
    nums[0]=1;
    nums[n+1]=1;
    for(int i=1;i<=n;i++){
        int hl=nums[i-1];
        int hr=1;
        int hm=1,mh=nums[i];
        if(mh>max(max(hl,hr),hm)){
            add(max(max(hl,hr),hm)+1,1);
            add(mh+1,-1);
        }
        if(hm<min(min(hl,hr),mh)){
            add(hm+1,-1);
            add(min(min(hl,hr),mh)+1,1);
        }
    }
    // cout<<endl;

    for(int i=1;i<=q;i++){
        if(op[i]==1){
            cout<<query(a[i])<<endl;
        }
        else{
            int hl=nums[a[i]-1];
            int hr=nums[a[i]+1];
            int hm=nums[a[i]];
            int mh=b[i];
            if(mh>hm){
                if(mh>max(max(hl,hr),hm)){
                    add(max(max(hl,hr),hm)+1,1);
                    add(mh+1,-1);
                }
                if(hm<min(min(hl,hr),mh)){
                    add(hm+1,-1);
                    add(min(min(hl,hr),mh)+1,1);
                }
            }
            else if(hm>mh){
                if(hm>max(max(hl,hr),mh)){
                    add(max(max(hl,hr),mh)+1,-1);
                    add(hm+1,1);
                }
                if(mh<min(min(hl,hr),hm)){
                    add(mh+1,1);
                    add(min(min(hl,hr),hm)+1,-1);
                }
            }
            nums[a[i]]=b[i];
        }
    }
    return 0;
}