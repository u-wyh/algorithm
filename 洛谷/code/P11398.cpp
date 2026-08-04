#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int MAXB = 25;

int T,n,m,maxv;
int a[MAXN];
int b[MAXN];

int bcnt;
int belong[MAXN];
int bl[MAXB];
int br[MAXB];
int mode[MAXB];

long long cnt[MAXB][MAXN];
long long tmp[MAXN];

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

void build(){
    int r=n;
    int len=1;

    while(r>=1){
        ++bcnt;
        bl[bcnt]=max(1,r-len+1);
        br[bcnt]=r;
        for(int i=bl[bcnt];i<=br[bcnt];i++){
            belong[i]=bcnt;
        }
        r-=len;
        len<<=1;
    }

    for(int block=bcnt;block>=1;block--){
        for(int i=0;i<=maxv;i++){
            cnt[block][i]=cnt[block+1][i];
        }
        mode[block]=mode[block+1];

        for(int i=bl[block];i<=br[block];i++){
            int val=b[i];
            cnt[block][val]+=a[i];

            int pre=mode[block];
            if((cnt[block][val]>cnt[block][pre])||((cnt[block][val]==cnt[block][pre])&&val>pre)){
                mode[block]=val;
            }
        }
    }
}

void update(int x,int y){
    a[x]+=y;
    int val=b[x];
    for(int i=belong[x];i>=1;i--){
        cnt[i][val]+=y;
        int pre=mode[i];
        if((cnt[i][val]>cnt[i][pre])||((cnt[i][val]==cnt[i][pre])&&val>pre)){
            mode[i]=val;
        }
    }
}

int query(int q){
    long long sum=0;
    for(int i=1;i<=bcnt;i++){
        int pre=mode[i+1];

        long long *now=cnt[i+1];
        for(int j=bl[i];j<=br[i];j++){
            int val=b[j];
            now[val]+=a[j];
            if((now[val]>now[pre])||((now[val]==now[pre])&&val>pre)){
                pre=val;
            }
            tmp[j]=pre*a[j];
        }
        for(int j=bl[i];j<=br[i];j++){
            int val=b[j];
            now[val]-=a[j];
        }

        for(int j=br[i];j>=bl[i];j--){
            sum^=tmp[j];
            if(sum==q){
                return n-j+1;
            }
        }
    }
    return n;
}

int main()
{
    T=read();
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        b[i]=read();
        maxv=max(maxv,b[i]);
    }

    build();

    while(m--){
        int op=read();
        if(op==1){
            int x,y;
            x=read(),y=read();
            update(x,y);
        }
        else{
            int p=read();
            int ans=query(p);
            write(ans);
            putchar('\n');
        }
    }
    return 0;
}