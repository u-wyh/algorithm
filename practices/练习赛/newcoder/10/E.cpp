#include<bits/stdc++.h>
using namespace std;
#define int long long 

int val[6];
int pre[6];

bool check(int x,int sum){
    int mn=0;
    int mx=0;

    for(int i=1;i<=5;i++){
        mn+=(val[i]&1);

        int t=min(val[i],x);
        if((t&1)!=(val[i]&1)){
            t--;
        }
        if(t<0){
            return false;
        }

        mx+=t;
    }

    return mn<=3*x&&3*x<=mx;
}

void solve(){
    int sum=0;
    for(int i=1;i<=5;i++){
        cin>>val[i];
    }
    sort(val+1,val+6);
    for(int i=1;i<=5;i++){
        pre[i]=pre[i-1]+val[i];
    }
    sum=pre[5];

    int parity=sum&1;
    int best=-1;
    for(int k=0;k<=5;k++){
        int l,r;

        if(k==0){
            l=0;
        }
        else{
            l=val[k]+1;
        }

        r=sum/3;
        if(k<5){
            r=min(r,val[k+1]);
        }

        int bad=0;
        for(int i=k+1;i<=5;i++){
            if((val[i]&1)!=parity){
                bad++;
            }
        }

        if(k>=3){
            int val=pre[k]-bad;

            if(val<0){
                continue;
            }

            r=min(r,val/(k-2));
        }

        int x=r;
        if((x&1)!=parity){
            x--;
        }

        if(x<l){
            continue;
        }

        if(check(x,sum)){
            best=max(best,x);
        }
    }

    if(best==-1){
        cout<<-1<<endl;
    }
    else{
        cout<<(sum-best)/2<<endl;
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}