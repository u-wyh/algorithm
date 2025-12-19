#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e3+5;

int n,k;
int val[MAXN][MAXN];
int sum[MAXN][MAXN];
int up[MAXN];
int sta[MAXN];
int top;

int lt[MAXN];
int rt[MAXN];

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

int getsum(int x1,int y1,int x2,int y2){
    return sum[x2][y2]+sum[x1-1][y1-1]-sum[x2][y1-1]-sum[x1-1][y2];
}

void compute(int x1,int y1,int x2,int y2){
    int sumval=getsum(x1,y1,x2,y2);
    if(sumval>=k){
        while(sumval>=2*k){
            if(getsum(x1,y1,x1,y2)>=2*k){
                while(getsum(x1,y1,x1,y2)>=2*k){
                    y1++;
                }
                cout<<x1<<' '<<y1<<' '<<x1<<' '<<y2<<endl;
                exit(0);
            }
            x1++;
            sumval=getsum(x1,y1,x2,y2);
        }
        cout<<x1<<' '<<y1<<' '<<x2<<' '<<y2<<endl;
        exit(0);
    }
}

signed main()
{
    k=read(),n=read();
    for(int j=1;j<=n;j++){
        for(int i=1;i<=n;i++){
            val[i][j]=read();
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(val[i][j]>=k&&val[i][j]<=2*k){
                cout<<i<<' '<<j<<' '<<i<<' '<<j<<endl;
                return 0;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+val[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(val[i][j]<=2*k){
                up[j]++;
            }
            else{
                up[j]=0;
            }
            lt[j]=0,rt[j]=n+1;
        }

        top=0;
        sta[0]=0;
        for(int j=1;j<=n;j++){
            while(top&&up[sta[top]]>=up[j]){
                top--;
            }
            lt[j]=sta[top];
            sta[++top]=j;
        }

        top=0;
        sta[0]=n+1;
        for(int j=n;j>=1;j--){
            while(top&&up[sta[top]]>=up[j]){
                top--;
            }
            rt[j]=sta[top];
            sta[++top]=j;
        }

        for(int j=1;j<=n;j++){
            if(up[j])
                compute(i-up[j]+1,lt[j]+1,i,rt[j]-1);
        }
    }
    cout<<"NIE"<<endl;
    return 0;
}