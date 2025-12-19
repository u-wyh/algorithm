#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,k;
int rounds;
int pos;

int ceil(int x,int y){
    return (x+y-1)/y;
}

int floor(int x,int y){
    return x/y;
}

void compute1(){
    rounds=0;
    for(int i=n;i>1;i-=ceil(i,k)){
        rounds++;
    }
    pos=1;
    // cout<<rounds<<endl;
    while(rounds--){
        pos=pos+ceil(pos,k-1);
    }
}

void compute2(){
    int r=n,l;
    rounds=0;
    // cout<<888<<endl;
    while(r>=k){
        int t=ceil(r,k);
        if(t==1){
            break;
        }
        l=(t-1)*k;
        int tmp=ceil(r-l,t);
        r-=tmp*t;
        rounds+=tmp;
    }
    rounds+=r-1;

    // cout<<rounds<<endl;
    // pos=k;
    // rounds-=(k-1);
    pos=1;
    // rounds=392291;
    while(rounds){
        int t=ceil(pos,k-1);
        int tmp=t*(k-1)+1;
        int round=min(ceil(tmp-pos,t),rounds);
        rounds-=round;
        pos+=round*t;
        // if(round==0){
        //     break;
        // }
    }
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n>>k;
        if(k>=n){
            cout<<n<<endl;
            continue;
        }
        if(k<=sqrt(n)){
            compute1();
        }
        else{
            compute2();
        }
        cout<<pos<<endl;
    }
    return 0;
}
/*
4
6 2
8 3
10000 2
1919810 114514

100
9829300000 1000000000
9829300000 1000000001
9829300000 1000000002
9829300000 1000000003
9829300000 1000000004
9829300000 1000000005
9829300000 1000000006
9829300000 1000000007
9829300000 1000000008
9829300000 1000000009
9829300001 1000000000
*/