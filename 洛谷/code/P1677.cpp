#include<bits/stdc++.h>
using namespace std;
#define MAX 105

int n;
int nums[MAX];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    sort(nums+1,nums+n+1);

    return 0;
}
