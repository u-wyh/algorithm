#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m;
char s[MAXN];
char t[MAXN];

int nxt[MAXN];

void calcnxt(){
    nxt[1]=0;
    for(int i=2,j=0;i<=m;i++){
        while(j>0&&t[i]!=t[j+1]){
            j=nxt[j];
        }
        if(t[i]==t[j+1]){
            j++;
        }
        nxt[i]=j;
    }
}

void kmp(){
    calcnxt();
    for(int i=1,j=0;i<=n;i++){
        while(j>0&&s[i]!=t[j+1]){
            j=nxt[j];
        }
        if(s[i]==t[j+1]){
            j++;
        }
        if(j==m){
            cout<<(i-m+1)<<endl;
            j=nxt[j];
        }
    }
}

int main()
{
    scanf("%s %s",s+1,t+1);
    n=strlen(s+1);
    m=strlen(t+1);

    kmp();
    for(int i=1;i<=m;i++){
        cout<<nxt[i]<<' ';
    }
    return 0;
}