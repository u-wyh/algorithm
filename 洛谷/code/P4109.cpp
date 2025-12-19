#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int ans[MAXN];
int res[MAXN];

int compute(int val){
    int t=0;
    while(val%10==0){
        val/=10;
    }
    int rest=((val%10)==5)?1:2;
    val/=10;
    while(val){
        val/=10;
        t++;
    }
    return t*2+rest;
}

signed main()
{
    int block = 10000;
    ans[1]=5;
    res[1]=1;
    for(int i=2;i<=100000;i++){
        ans[i]=i*block;
        res[i]=compute(ans[i]);
    }
    int T;
    cin>>T;
    while(T--){
        int l,r;
        cin>>l>>r;
        int resu=INT_MAX;
        int num=r;

        if(r-l+1<=20000){
            for(int i=l;i<=r;i++){
                int k=compute(i);
                if(k<resu){
                    num=i;
                    resu=k;
                }
            }
        }
        else{
            int bl=(l-1)/block+1;
            int br=(r-1)/block+1;
            for(int i=l;i<=bl*block;i++){
                int k=compute(i);
                if(k<resu){
                    num=i;
                    resu=k;
                }
            }
            for(int i=bl+1;i<=br-1;i++){
                if(res[i]<resu){
                    resu=res[i];
                    num=ans[i];
                }
            }
            for(int i=(br-1)*block+1;i<=r;i++){
                int k=compute(i);
                if(k<resu){
                    num=i;
                    resu=k;
                }
            }
        }
        cout<<num<<endl;
    }
    return 0;
}