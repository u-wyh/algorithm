#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,k,root;
int fa[MAXN];
struct node{
    int l,r,len;
};
node nums[MAXN];

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
    int T=read();
    while(T--){
        n=read(),k=read();
        for(int i=1;i<=k;i++){
            nums[i].l=read(),nums[i].r=read();
            nums[i].len=nums[i].r-nums[i].l;
        }
        sort(nums+1,nums+k+1,cmp);
        if(k>1&&(nums[1].len==nums[2].len)&&(nums[k].len>=(nums[1].len-1))){
            cout<<"IMPOSSIBLE"<<endl;
            continue;
        }
        root=nums[1].l;
        for(int i=1;i<=k;i++){
            fa[nums[i].l]=root;
            for(int j=nums[i].l+1;j<=nums[i].r;j++){
                fa[j]=j-1;
            }
        }
        fa[root]=0;
        if(nums[1].len==nums[2].len&&k>1){
            fa[nums[k].l]=root+1;
        }
        for(int i=1;i<=n;i++){
            cout<<fa[i]<<' ';
        }
        cout<<endl;
    }
    return 0;
}
/*
2
13 3
1 5
6 10
11 13

14 3
1 5
6 10
11 14
*/