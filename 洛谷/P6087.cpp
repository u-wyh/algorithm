#include<bits/stdc++.h>
using namespace std;
const double sml = 1e-6;

int n,k,low,high;
int arr[50005];
int maxq[50005],minq[50005];

bool check(double x){
	double c[50005];
	int he=1,ta=0,q[50005];
	memset(q,0,sizeof(q));
	for(int i=1;i<=n;i++)
        c[i]=arr[i]-x*(double)i;
	for(int i=low;i<=n;i++){
		while(he<=ta&&i-q[he]>=high)
            he++;
		while(he<=ta&&c[i-low+1]<=c[q[ta]])
            ta--;
		q[++ta]=i-low+1;
		if(c[i]-c[q[he]]>=x*k)
            return 1;
	}
	he=1;
	ta=0;
	memset(q,0,sizeof(q));
	for(int i=1;i<=n;i++)
        c[i]=arr[i]+x*(double)i;
	for(int i=low;i<=n;i++){
		while(he<=ta&&i-q[he]>=high)
            he++;
		while(he<=ta&&c[i-low+1]>=c[q[ta]])
            ta--;
		q[++ta]=i-low+1;
		if(c[q[he]]-c[i]>=x*k)
            return 1;
	}
	return 0;
}

int main()
{
    int test;
    cin>>test;
    while(test--){
        double ans=0;
        cin>>n>>k>>low>>high;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
        int h1=0,t1=0,h2=0,t2=0;;
        for(int i=1;i<=n;i++){
            while(h1<t1&&maxq[h1]+low<=i){
                h1++;
            }
            while(h1<t1&&arr[maxq[t1-1]]<arr[i]){
                t1--;
            }//h<t  保证了如果队列已经是空的  那么不在t--
            maxq[t1]=i;
            t1++;
            while(h2<t2&&minq[h2]+low<=i){
                h2++;
            }
            while(h2<t2&&arr[minq[t2-1]]>arr[i]){
                t2--;
            }//h<t  保证了如果队列已经是空的  那么不在t--
            minq[t2]=i;
            t2++;
            ans=max(ans,(arr[maxq[h1]]-arr[minq[h2]])*1.0/(low-1+k));
        }
        //cout<<ans<<endl;
        double l=0,r=1e3,mid;
        while(r-l>=sml&&l<r){
            mid=(l+r)/2.0;
            if(check(mid))
                l=mid;
            else
                r=mid;
        }
        ans=max(ans,mid);
        printf("%.4lf\n",ans);
    }
    return 0;
}
