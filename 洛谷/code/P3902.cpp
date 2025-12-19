#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,ans=1;
    scanf("%d",&n);
    int a[n],sa[n];
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    sa[ans]=a[0];
    for(int tz,i=1;i<n;i++){
        if(sa[ans]<a[i]){
            ans++;
            sa[ans]=a[i];
        }else{
            tz=lower_bound(sa,sa+ans,a[i])-sa;
            //这里用tz临时存储找到的下标
            sa[tz]=a[i];
        }
    }
    printf("%d",n-ans);
    return 0;
}
