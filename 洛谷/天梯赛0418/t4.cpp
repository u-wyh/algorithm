#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        double val;
        cin>>val;
        if(val<(1.0*m)){
            printf("On Sale! %.1lf\n",val);
        }
    }
    return 0;
}