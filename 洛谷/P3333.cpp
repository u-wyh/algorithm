#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e4+5;
const int BASE = 499;

char t[MAXN],a[MAXN],b[MAXN],c[MAXN];
int lt,la,lb,lc;
int ht[MAXN],ha[MAXN],hb[MAXN],hc[MAXN];

signed main()
{
    fgets(t, MAXN, stdin);
    fgets(a, MAXN, stdin);
    fgets(b, MAXN, stdin);
    fgets(c, MAXN, stdin);

    lt=1;
    int val=0;
    // t+=' ';
    for(int i=0;i<(int)strlen(t);i++){
        if(t[i]==' '||t[i]=='\n'){
            ht[lt]=val;
            val=0;
            lt++;
        }
        else{
            val=val*BASE+t[i]-'a'+1;
        }
    }
    lt--;
    
    la=1;
    // a+=' ';
    for(int i=0;i<(int)strlen(a);i++){
        if(a[i]==' '||a[i]=='\n'){
            ha[la]=val;
            val=0;
            la++;
        }
        else{
            val=val*BASE+a[i]-'a'+1;
        }
    }
    la--;
    
    lb=1;
    // b+=' ';
    for(int i=0;i<(int)strlen(b);i++){
        if(b[i]==' '||b[i]=='\n'){
            hb[lb]=val;
            val=0;
            lb++;
        }
        else{
            val=val*BASE+b[i]-'a'+1;
        }
    }
    lb--;

    lc=1;
    // c+=' ';
    for(int i=0;i<(int)strlen(c);i++){
        if(c[i]==' '||c[i]=='\n'){
            hc[lc]=val;
            val=0;
            lc++;
        }
        else{
            val=val*BASE+c[i]-'a'+1;
        }
    }
    lc--;

    int ans=0;
    int st=1,en=lt;
    for(int i=1,j=1;j<=la;i++){
        if(ht[i]==ha[j]){
            j++;
        }
        else{
            ans++;
        }
        st=i+1;
    }
    // cout<<ans<<endl;

    for(int i=lt,j=lc;j>=1;i--){
        if(ht[i]==hc[j]){
            j--;
        }
        else{
            ans++;
        }
        en=i-1;
    }
    // cout<<ans<<endl;

    int res=lt;
    for(int i=st;i<=en;i++){
        if(hb[1]==ht[i]){
            int tmp=0;
            int k=1;
            for(int j=i;j<=en&&k<=lb;j++){
                if(ht[j]==hb[k]){
                    k++;
                }
                else{
                    tmp++;
                }
            }
            if(k<=lb){
                break;
            }
            else{
                res=min(res,tmp);
            }
        }
    }
    // cout<<ans<<' '<<res<<endl;
    ans+=res;
    cout<<ans<<endl;
    return 0;
}