#include<bits/stdc++.h>
using namespace std;
const int BIT = 40;

int n;
long arr[105];
long basis[BIT];

bool insert(long num) {
	for (int i = BIT; i >= 0; i--) {
		if (num >> i == 1) {
			if (basis[i] == 0) {
				basis[i] = num;
				return true;
			}
			num ^= basis[i];
		}
	}
	return false;
}

bool cmp(long a,long b){
    return a>b;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    sort(arr+1,arr+n+1,cmp);
    long ans=0;
    for(int i=1;i<=n;i++){
        if(!insert(arr[i])){
            ans+=arr[i];
        }
    }
    if(ans==0){
        ans=-1;
    }
    cout<<ans;
    return 0;
}
