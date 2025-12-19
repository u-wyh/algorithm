#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e7+5;
const int MAXM = 2e5+5;
const int MAXS = 205;

int cnt;
int prime[MAXN/2];
int num[MAXN];

int n,m;
int a[MAXM];
int b[MAXM];
int c[MAXM];
int s[MAXM];

int fa[MAXS];
int sz[MAXS];
int mx[MAXS];

int len;
int val[MAXS];

int sum[MAXS];
int times[MAXS];
int maxx[MAXS];

long long ans1[MAXS];
long long ans2[MAXS];

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

void euler(int n){
    for(int i=2;i<=n;i++){
        if(!num[i]){
            num[i]=i;
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            num[i*prime[j]]=prime[j];
            if(i%prime[j]==0){
                break;
            }
        }
    }
}

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

int computec(int val){
    int ans=0;
    while(val!=1){
        int cnt=0;
        int p=num[val];
        while(val%p==0){
            val/=p;
            cnt++;
        }
        ans=max(ans,cnt);
    }
    return ans;
}

int computes(int val){
    for(int i=(int)sqrt(val);i>=1;i--){
        if(val%(i*i)==0){
            return i;
        }
    }
    return 1;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    for(int i=1;i<=n;i++){
        b[i]=read();
    }

    euler(MAXN-1);
    
    for(int i=1;i<=n;i++){
        c[i]=computec(b[i]);
        s[i]=computes(a[i]);
    }

    // for(int i=1;i<=n;i++){
    //     cout<<c[i]<<' ';
    // }
    // cout<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<s[i]<<' ';
    // }
    // cout<<endl;


    long long all=0;
    for(int i=1;i<=n;i++){
        times[s[i]]++;
        sum[s[i]]+=c[i];
        maxx[s[i]]=max(maxx[s[i]],c[i]);
        all+=c[i];
    }

    for(int i=1;i<=200;i++){
        if(times[i]){
            val[++len]=i;
            fa[i]=i;
            sz[i]=1;
            mx[i]=maxx[i];
        }
    }

    for(int x=200;x>=2;x--){

        for(int i=1;i<=len;i++){
            for(int j=i+1;j<=len;j++){
                int fx=find(val[i]);
                int fy=find(val[j]);
                int g=gcd(val[i],val[j]);
                if(fx!=fy&&g>x){
                    fa[fx]=fy;
                    mx[fy]=max(mx[fx],mx[fy]);
                    sz[fy]+=sz[fx];
                }
            }
        }

        for(int i=1;i<=len;i++){
            if(val[i]==find(val[i])){
                if(sz[val[i]]==1){
                    if(val[i]>x){
                        ans1[x]++;
                        ans2[x]+=maxx[val[i]];
                    }
                    else{
                        ans1[x]+=times[val[i]];
                        ans2[x]+=sum[val[i]];
                    }
                }
                else{
                    ans1[x]++;
                    ans2[x]+=mx[val[i]];
                }
            }
        }
    }

    while(m--){
        int x=read();
        if(x>=200){
            cout<<n<<' '<<all<<endl;
        }
        else{
            cout<<ans1[x]<<' '<<ans2[x]<<endl;
        }
    }
    return 0;
}