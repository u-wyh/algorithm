#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
#define int long long

void solve(){
    int n; cin >> n; 
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    vector<int> fl(n + 1); 
    vector<int> b(n + 1);
    int num = 0; int mini = 0;
    for(int j = 5; j >= 0; j--){
        for(int i = 1; i <= n; i++){
            b[i] |= (a[i] & (1LL << j)); 
        }
        int cnt = 0; 
        for(int i = 1; i < n; i++){ 
            if(b[i] > b[i + 1] && (fl[i] >= mini || fl[i] == 0)){ //meidabiaoji, bushi zhiqiandengjide biaoji
                cnt++; 
            }
        }
        int sum = 1LL << (j - mini + 1 - 1);
        int suc = 0; 
        if(cnt > sum){
            //gai
            num += (1LL << j);
        }else{
            // buyihuo
            suc = 1; 
            for(int i = 1; i < n; i++){ 
                if(b[i] > b[i + 1] && (fl[i] >= mini || fl[i] == 0)){
                    fl[i] = mini; 
                    cnt++; 
                }
            }
            int nm = 0; 
            for(int i = 1; i <= n; i++){
                b[i] = nm * (1LL << j); 
                if(fl[i] > 0) nm++; 
            }
            mini = j + 1; 
        }
        cout << suc << " "; 
        for(int i = 1;  i <= n; i++){
            cout << b[i] << " "; 
        }
        cout << "\n"; 
    }
    cout << num << "\n"; 
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