// https://www.luogu.com.cn/problem/P1247
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n;
int val[MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    int eor=0;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        eor^=val[i];
    }
    if(eor){
        for(int i=1;i<=n;i++){
            if((eor^val[i])<=val[i]){
                cout<<(val[i]-(eor^val[i]))<<' '<<i<<endl;
                for(int j=1;j<=n;j++){
                    int v=val[j];
                    if(i==j){
                        v=eor^val[i];
                    }
                    cout<<v<<' ';
                }
                cout<<endl;
                return 0;
            }
        }
    }
    else{
        cout<<"lose"<<endl;
    }
    return 0;
}