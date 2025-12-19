#include<bits/stdc++.h>
using namespace std;
const int OFFSET = (1<<30)-1;
const int MAXN = 1e5+5;

int n;
int nums[MAXN];
int nodecnt;

int query(int x){
    cout<<"? "<<x<<endl;
    int ans;
    cin>>ans;
    return ans^x;
}

void compute(int l,int r){
    if(nodecnt==n){
        return ;
    }
    if(r==l+1){
        return ;
    }
    int base=0;
    int pos=0;
    for(int i=29;i>=0;i--){
        if((l&(1<<i))==(r&(1<<i))){
            base+=(1<<i)-(l&(1<<i));
        }
        else{
            pos=i;
            break;
        }
    }
    int lt=query(base+(1<<pos));
    int rt=query(base+(1<<pos)-1);
    if(lt!=l&&rt!=r){
        nums[++nodecnt]=lt;
        nums[++nodecnt]=rt;
        compute(l,lt);
        compute(rt,r);
    }
    else if(lt!=l){
        nums[++nodecnt]=lt;
        compute(l,lt);
    }
    else if(rt!=r){
        nums[++nodecnt]=rt;
        compute(rt,r);
    }
}

int main()
{
    // cout<<OFFSET<<endl;
    // int ans=0;
    // for(int i=0;i<=29;i++){
    //     ans+=(1<<i);
    // }
    // cout<<ans<<endl;
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        int l=query(OFFSET);
        int r=query(0);
        nodecnt=0;
        nums[++nodecnt]=l;
        nums[++nodecnt]=r;
        compute(l,r);
        cout<<"!";
        for(int i=1;i<=n;i++){
            cout<<' '<<nums[i];
        }
        cout<<endl;
        cout.flush();
    }
    return 0;
}