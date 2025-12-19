#include<bits/stdc++.h>
using namespace std;
#define int long long

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

signed main()
{
    int T=read();
    while(T--){
        int n;
        cin>>n;
        bool flag=false;
        for(int i=2;i*i<=n;i++){
            if(n%i==0){
                flag=true;
                while(n%i==0){
                    n/=i;
                }
                if(n>1){
                    cout<<"Yes"<<endl;
                }
                else{
                    cout<<"No"<<endl;
                }
                break;
            }
        }
        if(!flag){
            cout<<"No"<<endl;
        }
    }
    return 0;
}