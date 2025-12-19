#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

int cmp(const void *a,const void *b){
    return (*(int *)a-*(int *)b);
}

int min(int a,int b){
    return a<b?a:b;
}

bool check(int limit,int *a,int n,int *b,int m){
    int i=1,j=1,cnt=0;
    while(i<=n&&j<=m){
        if(abs(a[i]-b[j])<=limit){
            i++;
            j++;
            cnt++;
        }else{
            if(n>=m){
                i++;
            }else{
                j++;
            }
        }
    }
    return cnt>=min(n,m);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[m+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%d",&b[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    qsort(b+1,m,sizeof(int),cmp);
    int l=0,r=1e9,mid,ans;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid,a,n,b,m)){
            ans=mid;
            r=mid-1;
            //l=mid+1;
        }else{
            //r=mid-1;
            l=mid+1;
        }
    }
    printf("%d\n",ans);
    return 0;
}

