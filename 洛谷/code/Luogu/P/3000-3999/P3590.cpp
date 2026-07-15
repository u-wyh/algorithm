#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
int a[MAXN];
int b[MAXN];
int c[MAXN];
char s[MAXN];

bool check(int l,int r){
    int u=a[r]-a[l-1];
    int v=b[r]-b[l-1];
    int w=c[r]-c[l-1];
    if((u==v&&(u!=0))||(v==w&&v)||(u==w&&w)){
        return false;
    }
    return true;
}

int main()
{
    scanf("%d",&n);
    scanf("%s",s+1);
    for(int i=1;i<=n;i++){
        a[i]=a[i-1],b[i]=b[i-1],c[i]=c[i-1];
        if(s[i]=='B'){
            a[i]++;
        }
        else if(s[i]=='C'){
            b[i]++;
        }
        else{
            c[i]++;
        }
    }
    int ans=1;
    if(n<=3){
        if(n==3){
            int k=max(a[3],max(b[3],c[3]));
            if(k>=2){
                cout<<3;
            }
            else{
                cout<<1;
            }
        }
        else if(n==2){
            int k=max(a[2],max(b[2],c[2]));
            cout<<k;
        }
        else{
            cout<<1;
        }
        return 0;
    }
    for(int i=4;i<=n;i++){
        if(check(1,i)){
            ans=max(ans,i);
        }
        if(check(2,i)){
            ans=max(ans,i-1);
        }
        if(check(3,i)){
            ans=max(ans,i-2);
        }
    }
    for(int i=1;i<=n-3;i++){
        if(check(i,n)){
            ans=max(ans,n-i+1);
        }
        if(check(i,n-1)){
            ans=max(ans,n-i);
        }
        if(check(i,n-2)){
            ans=max(ans,n-i-1);
        }
    }
    cout<<ans<<endl;
    return 0;
}