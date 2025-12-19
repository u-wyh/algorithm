#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MOD = 20091119;

string s;
int arr[MAXN];
int cnt[MAXN];
int n,ans=0;
int p[MAXN];

void check(){
    for(int i=n/2;i>=1;i--){
        int j=n+1-i;
        if(arr[i-1]<arr[j-1]){
            ans=(ans+1)%MOD;
            return ;
        }
        else if(arr[i-1]==arr[j-1]){
            continue;
        }
        else{
            return ;
        }
    }
    ans=(ans+1)%MOD;
}

void dfs(int pos){
    if(pos>(n+1)/2){
        //cout<<ans<<endl;
        check();
        return ;
    }
    if(pos!=1){
        ans=((ans+arr[pos-1]*p[(n+1)/2-pos])%MOD+MOD)%MOD;
        //这一位置上选较小的
        dfs(pos+1);
    }
    else if(pos==1&&arr[0]==1){
        dfs(pos+1);
    }
    else{
        ans=((ans+(arr[pos-1]-1)*p[(n+1)/2-pos])%MOD+MOD)%MOD;
        //这一位置上选较小的
        dfs(pos+1);
    }
}

int main()
{
    cin>>s;
    n=s.length();
    if(n==1){
        cout<<s<<endl;
        return 0;
    }
    cnt[1]=9,cnt[2]=9;
    for(int i=3;i<n;i++){
        cnt[i]=(cnt[i-2]*10)%MOD;
    }
    for(int i=1;i<n;i++){
        ans=(ans+cnt[i])%MOD;
        //计算出所有位数不足的可能性
    }
    p[0]=1;
    for(int i=1;i<n;i++){
        p[i]=(p[i-1]*10)%MOD;
    }
    for(int i=0;i<n;i++){
        arr[i]=s[i]-'0';
    }
    //cout<<' '<<ans<<endl;
    dfs(1);
    cout<<ans<<endl;
    return 0;
}
