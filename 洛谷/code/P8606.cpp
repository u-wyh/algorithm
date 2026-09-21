// https://www.luogu.com.cn/problem/P8606
// https://www.luogu.com.cn/problem/P8606
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

int n;
int val[MAXN];
int diff[MAXN];

int main()
{
    while(cin>>val[++n]);
    n--;

    sort(val+1,val+n+1);

    for(int i=2;i<=n;i++){
        diff[i-1]=val[i]-val[i-1]-1; 
    }

    int eor=0;
    for(int i=1;i<=n-1;i+=2){
        eor^=diff[i];
    }

    if(eor==0){
        cout<<-1<<endl;
        return 0;
    }

    for(int i=1;i<n;i++){
        int old=val[i];

        for(int j=old+1;j<val[i+1];j++){
            int d=j-old;
            int neor=eor;

            if((i-1)>=1&&(i-1)%2==1){
                neor^=diff[i-1];
                neor^=(diff[i-1]+d);
            }

            if(i%2==1){
                neor^=diff[i];
                neor^=(diff[i]-d);
            }

            if(neor==0){
                cout<<old<<" "<<j<<endl;
                return 0;
            }
        }
    }

    cout<<-1<<endl;
    return 0;
}