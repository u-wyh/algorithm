#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;
const int MAXM = 1e5+5;

int n,m,k;
int fa[MAXN];
struct node{
    int u,v;
    int op;
};
int cnt1;
node nums1[MAXM];
int cnt2;
node nums2[MAXM];

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

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=m;i++){
        int u,v,op;
        u=read(),v=read(),op=read();
        if(op==0){
            nums2[++cnt2]={u,v,0};
        }
        else{
            nums1[++cnt1]={u,v,0};
        }
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=cnt1;i++){
        int fx=find(nums1[i].u);
        int fy=find(nums1[i].v);
        if(fx!=fy){
            fa[fx]=fy;
        }
    }
    int now=0;
    for(int i=1;i<=cnt2;i++){
        int fx=find(nums2[i].u);
        int fy=find(nums2[i].v);
        if(fx!=fy){
            fa[fx]=fy;
            nums2[i].op=1;
            now++;
        }
    }
    if(now>k){
        cout<<"no solution"<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=cnt2;i++){
        if(nums2[i].op==1){
            int fx=find(nums2[i].u);
            int fy=find(nums2[i].v);
            if(fx!=fy){
                fa[fx]=fy;
            }
        }
    }
    int i=1;
    while(now<k&&i<=cnt2){
        if(!nums2[i].op){
            int fx=find(nums2[i].u);
            int fy=find(nums2[i].v);
            if(fx!=fy){
                fa[fx]=fy;
                nums2[i].op=true;
                now++;
            }
        }
        i++;
    }
    if(now!=k){
        cout<<"no solution"<<endl;
        return 0;   
    }
    for(int i=1;i<=cnt1;i++){
        int fx=find(nums1[i].u);
        int fy=find(nums1[i].v);
        if(fx!=fy){
            fa[fx]=fy;
            nums1[i].op=true;
        }
    }
    for(int i=1;i<=cnt1;i++){
        if(nums1[i].op){
            cout<<nums1[i].u<<' '<<nums1[i].v<<' '<<1<<endl;
        }
    }
    for(int i=1;i<=cnt2;i++){
        if(nums2[i].op){
            cout<<nums2[i].u<<' '<<nums2[i].v<<' '<<0<<endl;
        }
    }
    return 0;
}