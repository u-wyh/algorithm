#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,m;
int a[MAXN];
int b[MAXN];

signed main(int argc, char *argv[]) {
    int id = argc > 1 ? atoi(argv[1]) : 0;

    if(id==0){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        sort(a+1,a+n+1);

        cout<<n<<endl;
        cout.flush();
        for(int i=1;i<=n;i++){
            cout<<a[i]<<' ';
        }
        cout<<endl;
        cout.flush();

        int ans;
        cin>>ans;
        cout<<ans<<endl;
        cout.flush();
    }
    else{
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>b[i];
        }
        sort(b+1,b+n+1);
        cin>>m;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        sort(a+1,a+m+1);

        if(n!=m){
            cout<<0<<endl;
            cout.flush();
            return 0;
        }

        int ans=1;
        for(int i=1;i<=n;i++){
            if(a[i]!=b[i]){
                ans=0;
                break;
            }
        }
        cout<<ans<<endl;
        cout.flush();
    }
    return 0;
}