#include<bits/stdc++.h>
using namespace std;
#define int long long
const int BASE = 499;
const int MOD = 1e9+7;
const int BASE2 = 131;
const int MOD2 = 998244353;
const int MAXN = 2e5+5;

int n,m;
char s[MAXN];
int h[26][MAXN];
int h2[26][MAXN];
int p[MAXN];
int p2[MAXN];

int val[26];
int val2[26];
int val3[26];
int val4[26];

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

int gethash(int l,int r,int op){
    return (h[op][r]-h[op][l-1]*p[r-l+1]%MOD+MOD)%MOD;
}

int gethash2(int l,int r,int op){
    return (h2[op][r]-h2[op][l-1]*p2[r-l+1]%MOD2+MOD2)%MOD2;
}

void prepare(){
    p[0]=1;
    p2[0]=1;
    for(int i=1;i<=n;i++){
        p[i]=(p[i-1]*BASE)%MOD;
        p2[i]=(p2[i-1]*BASE2)%MOD2;
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<26;j++){
            h[j][i]=(h[j][i-1]*BASE)%MOD;
            h2[j][i]=(h2[j][i-1]*BASE2)%MOD2;
        }
        int op=s[i]-'a';
        h[op][i]=(h[op][i]+1)%MOD;
        h2[op][i]=(h2[op][i]+1)%MOD2;
    }
}

signed main()
{
    n=read(),m=read();
    scanf("%s",s+1);
    prepare();
    for(int i=1;i<=m;i++){
        int l,r,len;
        l=read(),r=read(),len=read();
        for(int j=0;j<26;j++){
            val[j]=gethash(l,l+len-1,j);
            val2[j]=gethash(r,r+len-1,j);
        }
        for(int j=0;j<26;j++){
            val3[j]=gethash2(l,l+len-1,j);
            val4[j]=gethash2(r,r+len-1,j);
        }
        sort(val,val+26);
        sort(val2,val2+26);
        sort(val3,val3+26);
        sort(val4,val4+26);
        bool flag=false;
        for(int j=0;j<26;j++){
            if((val[j]!=val2[j])||(val3[j]!=val4[j])){
                flag=true;
                break;
            }
        }
        if(flag){
            printf("NO\n");
        }
        else{
            printf("YES\n");
        }
    }
    return 0;
}