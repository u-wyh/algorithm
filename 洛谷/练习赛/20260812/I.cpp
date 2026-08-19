
#include<bits/stdc++.h>
using namespace std;
#define int long long 
void solve(){
    int n, m; cin >> n >> m;
    vector<int> a(2 * n + 1); 
    for(int i = 1; i <= 2 * n; i++){
        cin >> a[i]; 
    }
    auto b = a;
    b[1] += m; 
    int pt = b[1] ; 
    int mini = 0, maxi = 0; 
    if(b[2] > pt){
        mini++; 
    }
    for(int i = 2; i <= n; i++){
        int num1 = b[2 * i - 1];
        int num2 = b[2 * i];
        if(num1 > pt){
            mini++;
            if(num2 > pt){
                mini++; 
            }
        }else{
            int fen1 = pt - num1;
            num2 += max(0, m - fen1);  
            if(num2 > pt){
                mini++; 
            }
        }
    }
    b = a; 
    pt = b[1];
    if(b[2] + m > pt){
        maxi++; 
    } 
    for(int i = 2; i <= n; i++){
        int num1 = b[2 * i - 1];
        int num2 = b[2 * i];
        int ad = num1 + num2; 
        num1 = max(num1, num2); 
        num2 = ad - num1; 
        if(num1 > pt){
            maxi++; 
            num2 += m;
            if(num2 > pt){
                maxi++; 
            }
        }else{
            int ad1 = pt - num1;
            if(ad1 + 1 <= m){
                maxi++; 
            }
            int ad2 = pt - num2 ; 
            if(ad1 + ad2 + 1 <= m){
                maxi++; 
            }
             
        }
    }
    
    cout << mini <<  " " <<  maxi << "\n";
}


signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t; 
    while(t--) solve(); 
    return 0;
}