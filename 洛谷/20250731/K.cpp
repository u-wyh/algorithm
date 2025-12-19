#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int nums[MAXN];
int d[MAXN];
int b[MAXN];
int ans;

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

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

void check1(int x){
    if(x<ans){
        return ;
    }
    int cnt=0,all=0;
    for(int i=2;i<=n;i++){
        if(d[i]%x){
            cnt++;
            all+=d[i];
        }
        if(cnt>=3){
            return ;
        }
    }
    if(cnt<=1){
        ans=x;
    }
    else if(cnt==2){
        if(all%x==0){
            ans=x;
        }
    }
}

void check2(int x){
    if(x<ans){
        return ;
    }
    int cnt=0,all=0;
    for(int i=1;i<n;i++){
        if(b[i]%x){
            cnt++;
            all+=b[i];
        }
        if(cnt>=3){
            return ;
        }
    }
    if(cnt<=1){
        ans=x;
    }
    else if(cnt==2){
        if(all%x==0){
            ans=x;
        }
    }
}

int main()
{
    cout<<gcd(4,-4)<<endl;
    int T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            nums[i]=read();
        }
        if(n==2){
            if(nums[1]==nums[2]){
                cout<<0<<endl;
                continue;
            }
            else{
                cout<<max(nums[1],nums[2])<<endl;
                continue;
            }
        }
        bool flag=false;
        for(int i=1;i<=n;i++){
            if(nums[i]!=nums[1]){
                flag=true;
                break;
            }
        }
        if(!flag){
            cout<<0<<endl;
            continue;
        }
        for(int i=2;i<=n;i++){
            d[i]=nums[i]-nums[i-1];
        }
        for(int i=1;i<n;i++){
            b[i]=nums[i]-nums[i+1];
        }
        ans=0;
        int tmp=0;
        for(int i=2;i<=n;i++){
            tmp=gcd(tmp,abs(d[i]));
        }
        ans=max(ans,tmp);
        for(int i=1;i*i<=nums[1];i++){
            if(nums[1]%i==0){
                check1(i);
                check1(nums[1]/i);
            }
        }
        for(int i=1;i*i<=nums[n];i++){
            if(nums[n]%i==0){
                check2(i);
                check2(nums[1]/i);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}