#include<bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int p = 3;
    for(int q = 1; q <= 100; q++){
        for (int x1 = 1; x1 < q; x1++){
            for(int x2 = 1; x2 < p; x2++){
                if((x1 * x1) % q  == (p)% q  && (x2 * x2) % p  == (q)% p){
                    cout << x1 <<  " " << x2 <<  " " << q << "\n"; 
                }
            }
        }
    }
    return 0;
}