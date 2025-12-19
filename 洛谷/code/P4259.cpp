#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e6+5;
const int MAXM = 2e3+5;

int n,m,q;

struct node{
    int val[MAXN<<2];
    int* operator[](int x){
        return val+x*m;
    }
};

node up;
node down;
node ans;
node mat;

int q1[MAXM];
int q2[MAXM];

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

void merge(int root,int ls,int rs,int lt,int rt){
    int head1=1,tail1=0,head2=1,tail2=0;
    for(int i=1,j=1;i<=m;i++){
        while(head1<=tail1&&down[ls][q1[tail1]]>down[ls][i]){
            tail1--;
        }
        q1[++tail1]=i;
        while(head2<=tail2&&up[rs][q2[tail2]]>up[rs][i]){
            tail2--;
        }
        q2[++tail2]=i;

        while(j<=i&&((i-j+1)>(up[rs][q2[head2]]+down[ls][q1[head1]]))){
            j++;
            if(q1[head1]<j){
                head1++;
            }
            if(q2[head2]<j){
                head2++;
            }
        }
        ans[root][i]=max(i-j+1,max(ans[ls][i],ans[rs][i]));
    }
    for(int i=1;i<=m;i++){
        up[root][i]=up[ls][i]+((up[ls][i]==lt)?up[rs][i]:0);
        down[root][i]=down[rs][i]+((down[rs][i]==rt)?down[ls][i]:0);
    }
}

void build(int l,int r,int i){
    if(l==r){
        for(int p=1;p<=m;p++){
            up[i][p]=down[i][p]=ans[i][p]=mat[l][p];
        }
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        merge(i,i<<1,i<<1|1,mid-l+1,r-mid);
    }
}

void update(int jobx,int joby,int l,int r,int i){
    if(l==r){
        mat[jobx][joby]^=1;
        for(int p=1;p<=m;p++){
            up[i][p]=down[i][p]=ans[i][p]=mat[l][p];
        }
    }
    else{
        int mid=(l+r)>>1;
        if(jobx<=mid){
            update(jobx,joby,l,mid,i<<1);
        }
        else{
            update(jobx,joby,mid+1,r,i<<1|1);
        }
        merge(i,i<<1,i<<1|1,mid-l+1,r-mid);
    }
}

void query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        merge(0,0,i,l-jobl,r-l+1);
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            query(jobl,jobr,mid+1,r,i<<1|1);
        }
    }
}

int main()
{
    n=read(),m=read(),q=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            mat[i][j]=read();
        }
    }
    build(1,n,1);
    for(int i=1;i<=q;i++){
        int op,x1,y1,x2,y2;
        op=read(),x1=read(),y1=read();
        if(op==0){
            update(x1,y1,1,n,1);
        }
        else{
            x2=read(),y2=read();
            for(int j=1;j<=m;j++){
                up[0][j]=0,down[0][j]=0,ans[0][j]=0;
            }
            int res=0;
            query(x1,x2,1,n,1);
            for(int j=y1;j<=y2;j++){
                res=max(res,min(j-y1+1,ans[0][j]));
            }
            printf("%d\n",res);
        }
    }
    return 0;
}