#include<bits/stdc++.h>
using namespace std;

int maxval;
int ans[1005];
int top;

int compute(int val){
    if(val<10){
        return 0;
    }
    int ans=1;
    while(val){
        ans*=(val%10);
        val/=10;
    }
    return 1+compute(ans);
}

int main()
{
    int a,b;
    cin>>a>>b;
    for(int i=a;i<=b;i++){
        int val=1;
        // if(i<10){
        //     val=1;
        // }
        // else{
            val=compute(i);
        // }
        if(val>maxval){
            maxval=val;
            top=0;
            ans[++top]=i;
        }
        else if(val==maxval){
            ans[++top]=i;
        }
    }
    cout<<maxval<<endl;
    cout<<ans[1];
    for(int i=2;i<=top;i++){
        cout<<' '<<ans[i];
    }
    return 0;
}