#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 19940417;
const int MAXN = 5e4+5;
const int MAXC = 21;

int n,q;
int val[MAXN];
int res[MAXC];

int f[MAXN<<2][MAXC];
int addtag[MAXN<<2];
bool rev[MAXN<<2];
int len[MAXN<<2];

int comb[MAXN][MAXC];

void merge(int *f,int *a,int *b){
    for(int i=0;i<MAXC;i++){
        f[i]=0;
    }
    for(int i=0;i<MAXC;i++){
        for(int j=0;j+i<MAXC;j++){
            f[i+j]=(f[i+j]+a[i]*b[j])%MOD;
        }
    }
}

void build(int l,int r,int i){
    len[i]=r-l+1;
    if(l==r){
        f[i][0]=1;
        f[i][1]=val[l]%MOD;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        merge(f[i],f[i<<1],f[i<<1|1]);
    }
}

void reverselazy(int i){
    for(int p=1;p<MAXC;p+=2){
        f[i][p]=(MOD-f[i][p])%MOD;
    }
    addtag[i]=(MOD-addtag[i])%MOD;
    rev[i]^=1;
}

void addlazy(int i,int v){
    int temp[MAXC];
    for(int p=0;p<MAXC;p++){
        temp[p]=0;
    }
    int length=len[i];
    int p[MAXC];
    p[0]=1;
    for(int id=1;id<MAXC;id++){
        p[id]=(p[id-1]*v)%MOD;
    }

    for(int k=0;k<min(length+1,MAXC);k++){
        for(int j=0;j<=k;j++){
            temp[k]=(temp[k]+f[i][j]*comb[length-j][k-j]%MOD*p[k-j])%MOD;
        }
    }
    for(int p=0;p<MAXC;p++){
        f[i][p]=temp[p];
    }
    addtag[i]=(addtag[i]+v)%MOD;
}

// void addlazy(int i,int v){
//     int temp[MAXC] = {0};  // 修复：初始化为0
//     int length=len[i];
//     int p[MAXC];
//     p[0]=1;
    
//     // 修复：避免变量名冲突
//     for(int idx=1;idx<MAXC;idx++){
//         p[idx]=(p[idx-1]*v)%MOD;
//     }

//     // 修复：循环到MAXC而不是min(length,MAXC)
//     for(int k=0;k<MAXC;k++){
//         for(int j=0;j<=k;j++){
//             // 添加边界检查
//             if(length - j >= k - j && k - j >= 0){
//                 temp[k]=(temp[k]+f[i][j]*comb[length-j][k-j]%MOD*p[k-j])%MOD;
//             }
//         }
//     }
    
//     for(int idx=0;idx<MAXC;idx++){
//         f[i][idx]=temp[idx];
//     }
//     addtag[i]=(addtag[i]+v)%MOD;
// }

void down(int i){
    if(rev[i]){
        reverselazy(i<<1);
        reverselazy(i<<1|1);
        rev[i]=0;
    }
    if(addtag[i]){
        addlazy(i<<1,addtag[i]);
        addlazy(i<<1|1,addtag[i]);
        addtag[i]=0;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addlazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        merge(f[i],f[i<<1],f[i<<1|1]);
    }
}

void reverse(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        reverselazy(i);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            reverse(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            reverse(jobl,jobr,mid+1,r,i<<1|1);
        }
        merge(f[i],f[i<<1],f[i<<1|1]);
    }
}

void query(int jobl,int jobr,int l,int r,int i,int *res){
    if(jobl<=l&&r<=jobr){
        for(int p=0;p<MAXC;p++){
            res[p]=f[i][p];
        }
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid&&jobr>mid){
            int lt[MAXC]={0};
            int rt[MAXC]={0};
            query(jobl,jobr,l,mid,i<<1,lt);
            query(jobl,jobr,mid+1,r,i<<1|1,rt);
            merge(res,lt,rt);
        }
        else if(jobl<=mid){
            query(jobl,jobr,l,mid,i<<1,res);
        }
        else{
            query(jobl,jobr,mid+1,r,i<<1|1,res);
        }
    }
}

signed main()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }

    comb[0][0]=1;
    for(int i=1;i<=n;i++){
        comb[i][0]=1;
        for(int j=1;j<=min(i,20ll);j++){
            comb[i][j]=(comb[i-1][j]+comb[i-1][j-1])%MOD;
        }
    }
    build(1,n,1);
    while(q--){
        char op;
        int a,b,c;
        cin>>op>>a>>b;
        if(op=='I'){
            cin>>c;
            c=(c%MOD+MOD)%MOD;
            add(a,b,c,1,n,1);
        }
        else if(op=='R'){
            reverse(a,b,1,n,1);
        }
        else{
            cin>>c;
            for(int i=0;i<=20;i++){
                res[i]=0;
            }
            query(a,b,1,n,1,res);
            cout<<((res[c]%MOD+MOD)%MOD)<<endl;
        }
    }
    return 0;
}