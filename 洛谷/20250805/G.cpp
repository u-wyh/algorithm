#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
int prime[MAXN];
int num[MAXN];
int cnt=0;
int all[MAXN];
int sum[MAXN];

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

int euler(int n){
    for(int i=2;i<=n;i++){
        if(num[i]==0){
            prime[++cnt]=i;
            all[i]=1;
        }

        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            num[i*prime[j]]=prime[j];
            all[i*prime[j]]=1+all[i];
            if(i%prime[j]==0){
                break; // 每个合数只被其最小的质因数筛去一次
            }
        }
    }
    return cnt;
}

int main()
{
    euler(MAXN-1);
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1];
        if(all[i]%2){
            sum[i]++;
        }
    }
    int T=read();
    while(T--){
        int n=read();
        int need=n/2;
        for(int i=1;i<=n&&need;i++){
            if(all[i]%2){
                cout<<i<<' ';
                need--;
            }
        }
        cout<<endl;
    }
    return 0;
}