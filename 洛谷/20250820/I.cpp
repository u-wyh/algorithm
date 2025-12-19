#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,k;
int nums[MAXN];
int val[MAXN];

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

int main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    if(k==n){
        sort(nums+1,nums+n+1);
        for(int i=1;i<=n;i++){
            cout<<nums[i]<<' ';
        }
        cout<<endl;
        return 0;
    }

    bool flag=false;
    val[n]=1;
    for(int i=n-1;i>=1;i--){
        if(nums[i]<nums[i+1]){
            val[i]=val[i+1]+1;
        }
        else{
            val[i]=1;
        }
        if(val[i]>=k){
            flag=true;
            break;
        }
    }
    if(flag){
        for(int i=1;i<=n;i++){
            cout<<nums[i]<<' ';
        }
        cout<<endl;
        return 0;
    }

    int maxpos=0,pos=1;
    for(int i=1;i<=n-k+1;i++){
        if(i+val[i]>maxpos){
            maxpos=i+val[i];
            pos=i;
        }
        else if((i+val[i]==maxpos)&&(nums[pos]>nums[maxpos])){
            pos=i;
        }
    }
    sort(nums+pos,nums+pos+k);
    for(int i=1;i<=n;i++){
        cout<<nums[i]<<' ';
    }
    cout<<endl;
    return 0;
}