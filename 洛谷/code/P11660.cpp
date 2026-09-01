#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 505;
const int MAXB = 155;

int n,m;
int val[MAXN];

int blen;
int bnum;
int bl[MAXB];
int br[MAXB];
int belong[MAXN];

int cnt[MAXB][MAXM][MAXM];
int diff[MAXM][MAXM];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void write(int x){
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

void addrange(int b,int l,int r){
    diff[b][l]++;
    diff[b][r+1]--;
}

void build(){
    blen=700;
    bnum=(n-1+blen)/blen;
    for(int block=1;block<=bnum;block++){
        bl[block]=(block-1)*blen+1;
        br[block]=min(n-1,block*blen);

        for(int i=0;i<MAXM;i++){
            for(int j=0;j<MAXM;j++){
                diff[i][j]=0;
            }
        }

        for(int i=bl[block];i<=br[block];i++){
            belong[i]=block;
            int x=min(val[i],val[i+1]);
            int d=max(val[i],val[i+1])-x;

            if(d>MAXM){
                continue;
            }

            for(int b=d+1;b<MAXM;b++){
                int t=x%b;
                int l=(t==0)?0:b-t;
                int r=l+b-d-1;
                if(r<b){
                    addrange(b,l,r);
                }
                else{
                    addrange(b,l,b-1);
                    addrange(b,0,r-b);
                }
            }
        }

        for(int b=1;b<MAXM;b++){
            int sum=0;
            for(int c=0;c<b;c++){
                sum+=diff[b][c];
                cnt[block][b][c]=sum;
            }
        }
    }
}

inline int check(int x,int a,int b){
    return ((val[x]+a)/b)==((val[x+1]+a)/b);
}

int query(int l,int r,int a,int b){
    int lb=belong[l];
    int rb=belong[r];
    int ans=0;
    if(lb==rb){
        for(int i=l;i<=r;i++){
            ans+=check(i,a,b);
        }
    }
    else{
        for(int i=l;i<=br[lb];i++){
            ans+=check(i,a,b);
        }
        for(int i=lb+1;i<rb;i++){
            ans+=cnt[i][b][a];
        }
        for(int i=bl[rb];i<=r;i++){
            ans+=check(i,a,b);
        }
    }
    return ans;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }

    build();

    int last=0;
    for(int i=1;i<=m;i++){
        int l,r,a,b;
        l=read()^last,r=read()^last,a=read()^last,b=read()^last;
        a%=b;
        r-=1;
        last=query(l,r,a,b);
        write(last);
        putchar('\n');
    }
    return 0;
}