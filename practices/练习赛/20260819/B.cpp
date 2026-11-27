#include<bits/stdc++.h>
using namespace std;

int n,k,m;

inline double compute(){
    multiset<double>s;
    for(int i=1;i<=n;i++){
        s.insert(1.0*rand()/RAND_MAX);
    }

    double ans=0;
    for(int i=1;i<=k;i++){
        auto it = prev(s.end());
        double maxn = (*it);
        s.erase(it);
        ans+=maxn;

        s.insert(1.0*rand()/RAND_MAX);
    }
    return ans;
}

signed main()
{
    // cin>>n>>m>>k;
    n=2,m=10,k=6;
    for(n=1;n<=10;n++){
        double ans=0;
        for(int i=1;i<=1e6;i++){
            ans+=compute();
        }
        cout<<setprecision(9)<<(ans*m/1e5)<<endl;
    }
    return 0;
}