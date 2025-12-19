#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MAXH = 22;

int n;
char s[MAXN];
int pre[MAXN];
int suf[MAXN];

int len1[MAXN];
int len2[MAXN];

int sta[MAXN];
int top;

void prepare(){
    pre[n+1]=-2*n;
    for(int i=0;i<=n+1;i++){
        while(top&&pre[i]<pre[sta[top]]){
            int pos=sta[top];
            len1[pos]=i-pos;
            top--;
        }
        sta[++top]=i;
    }

    top=0;
    suf[0]=-2*n;
    for(int i=n+1;i>=0;i--){
        while(top&&suf[i]<suf[sta[top]]){
            int pos=sta[top];
            len2[pos]=pos-i;
            top--;
        }
        sta[++top]=i;
    }
}

bool check(int len){
    for(int i=1;i<=n-len+1;i++){
        int j=i+len-1;
        if(len1[i-1]>len&&len2[j+1]>len){
            return true;
        }
    }
    return false;
}

int main()
{
    scanf("%d %s",&n,s+1);
    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1];
        if(s[i]=='p'){
            pre[i]++;
        }
        else{
            pre[i]--;
        }
    }
    for(int i=n;i>=1;i--){
        suf[i]=suf[i+1];
        if(s[i]=='p'){
            suf[i]++;
        }
        else{
            suf[i]--;
        }
    }
    prepare();
    // for(int i=0;i<=n+1;i++){
    //     printf("%3d ",i);
    // }
    // printf("\n");
    // for(int i=0;i<=n+1;i++){
    //     printf("%3d ",pre[i]);
    // }
    // printf("\n");
    // for(int i=0;i<=n+1;i++){
    //     printf("%3d ",len1[i]);
    // }
    // printf("\n");
    // for(int i=0;i<=n+1;i++){
    //     printf("%3d ",suf[i]);
    // }
    // printf("\n");
    // for(int i=0;i<=n+1;i++){
    //     printf("%3d ",len2[i]);
    // }
    // printf("\n");
    int l=0,r=n,ans=0;
    // cout<<check(n)<<endl;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    cout<<ans<<endl;
    return 0;
}