#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;

int n,m;
char s[MAXN];

int x[MAXN];
int y[MAXN];
int c[MAXN];

int sa[MAXN];
int rk[MAXN];
int height[MAXN];

void getsa(){
    for(int i=1;i<=n;i++){
        x[i]=s[i];
        c[x[i]]++;
    }
    for(int i=1;i<=m;i++){
        c[i]+=c[i-1];
    }
    for(int i=n;i>=1;i--){
        sa[c[x[i]]--]=i;
    }

    for(int k=1;k<=n;k<<=1){
        for(int i=0;i<=m;i++){
            c[i]=0;
        }
        for(int i=1;i<=n;i++){
            y[i]=sa[i];
        }
        for(int i=1;i<=n;i++){
            c[x[y[i]+k]]++;
        }
        for(int i=1;i<=m;i++){
            c[i]+=c[i-1];
        }
        for(int i=n;i>=1;i--){
            sa[c[x[y[i]+k]]--]=y[i];
        }

        for(int i=0;i<=m;i++){
            c[i]=0;
        }
        for(int i=1;i<=n;i++){
            y[i]=sa[i];
        }
        for(int i=1;i<=n;i++){
            c[x[y[i]]]++;
        }
        for(int i=1;i<=m;i++){
            c[i]+=c[i-1];
        }
        for(int i=n;i>=1;i--){
            sa[c[x[y[i]]]--]=y[i];
        }

        for(int i=1;i<=n;i++){
            y[i]=x[i];
        }
        m=0;
        for(int i=1;i<=n;i++){
            if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]){
                x[sa[i]]=m;
            }
            else{
                x[sa[i]]=++m;
            }
        }
        if(m==n){
            break;
        }
    }
}

void getheight(){
    for(int i=1;i<=n;i++){
        rk[sa[i]]=i;
    }
    for(int i=1,k=0;i<=n;i++){
        if(rk[i]==1){
            continue;
        }
        if(k){
            k--;
        }
        int j=sa[rk[i]-1];
        while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k]){
            k++;
        }
        height[rk[i]]=k;
    }
}

int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    m=122;
    getsa();
    getheight();
    for(int i=1;i<=n;i++){
        cout<<sa[i]<<' ';
    }
    return 0;
}