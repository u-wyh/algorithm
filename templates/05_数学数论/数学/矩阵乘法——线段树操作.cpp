//P7435
#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
const int MAXN = 250005;

int n,a[MAXN],b[MAXN],c[MAXN],m;

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

struct mat{
    int a[4][4];
    mat(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                a[i][j]=0;
                if(i==j){
                    a[i][j]=1;
                }
            }
        }
    }
};

mat multiply(mat a,mat b){
    mat ans;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            for(int k=0;k<4;k++){
                ans.a[i][j]=a.a[i][k]*b.a[k][j];
                ans.a[i][j]%=MOD;
            }
        }
    }
    return ans;
}

struct vec{
    int v[4];
    vec(){
        v[0]=v[1]=v[2]=v[3]=0;
    }
    vec(int a,int b,int c){
        v[0]=a,v[1]=b,v[2]=c,v[3]=1;
    }
};

vec add(vec a,vec b){
    vec c;
    for(int i=0;i<4;i++){
        c.v[i]=a.v[i]+b.v[i];
        c.v[i]%=MOD;
    }
    return c;
}

vec multiply(vec a,mat b){
    vec c;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            c.v[i]+=(1ll*a.v[j]*b.a[j][i])%MOD;
        }
    }
    return c;
}

mat t1,t2,t3,t4,t5,t6;
void pre(){
    t1.a[1][0] = t2.a[2][1] = t3.a[0][2] = 1;
    t6.a[2][2] = 0;
}

vec tree[MAXN<<2];
mat tag[MAXN<<2];

void up(int i){
    tree[i]=add(tree[i<<1],tree[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=vec(a[l],b[l],c[l]);
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void lazy(int i,mat v){
    tag[i]=multiply(tag[i],v);
    tree[i]=multiply(tree[i],v);
}

void down(int i){
    lazy(i<<1,tag[i]);
    lazy(i<<1|1,tag[i]);
    tag[i]=mat();
}

void update(int jobl,int jobr,int l,int r,int i,mat jobv){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,l,mid,i<<1,jobv);
        }
        if(jobr>mid){
            update(jobl,jobr,mid+1,r,i<<1|1,jobv);
        }
        up(i);
    }
}

vec query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(l<=mid&&r>mid){
            return add(query(jobl,jobr,l,mid,i<<1),query(jobl,jobr,mid+1,r,i<<1|1));
        }
        else if(jobl<=mid){
            return query(jobl,jobr,l,mid,i<<1);
        }
        else {
            return query(jobl,jobr,mid+1,r,i<<1|1);
        }
    }
}

int main()
{
    pre();//将6个矩阵设置一下
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read(),b[i]=read(),c[i]=read();
    }
    build(1,n,1);
    m=read();
    for(int i=1;i<=m;i++){
        int l,r,v,op;
        op=read(),l=read(),r=read();
        if(op==1){
            update(l,r,1,n,1,t1);
        }
        else if(op==2){
            update(l,r,1,n,1,t2);
        }
        else if(op==3){
            update(l,r,1,n,1,t3);
        }
        else if(op==7){
            vec ans=query(l,r,1,n,1);
            printf("%d %d %d\n",ans.v[0],ans.v[1],ans.v[2]);
        }
        else{
            v=read();
            if(op==4){
                t4.a[3][0]=v;
                update(l,r,1,n,1,t4);
            }
            else if(op==5){
                t5.a[1][1]=v;
                update(l,r,1,n,1,t5);
            }
            else{
                t6.a[3][2]=v;
                update(l,r,1,n,1,t6);
            }
        }
    }
    return 0;
}