#include<bits/stdc++.h>
using namespace std;

int n,d;
struct row{
    int x,h;
}nums[50000];
int q[50005],l[50005],r[50005],ans=0;
int head,tail;

int cmp(row a,row b){
    return a.x<b.x;
}

int main()
{
    cin>>n>>d;
    for(int i=0;i<n;i++){
        cin>>nums[i].x>>nums[i].h;
    }
    sort(nums,nums+n,cmp);
    /*
    printf("---------------------------------------\n");
    for(int i=0;i<n;i++){
        printf("%d %d\n",nums[i].x,nums[i].h);
    }
    */
    head=tail=0;
    for(int i=0;i<n;i++){
        while(head<tail&&nums[i].x-nums[q[head]].x>d){
            head++;
        }
        while(head<tail&&nums[q[tail-1]].h<nums[i].h){
            tail--;
        }
        q[tail++]=i;
        if(nums[q[head]].h/2>=nums[i].h)
            l[i]=1;
        //printf("%5d",l[i]);
    }
    //printf("\n");
    memset(q,0,sizeof(q));
    head=tail=0;
    for(int i=n-1;i>=0;i--){
        while(head<tail&&nums[q[head]].x-nums[i].x>d){
            head++;
        }
        while(head<tail&&nums[q[tail-1]].h<nums[i].h){
            tail--;
        }
        q[tail++]=i;
        if(nums[q[head]].h/2>=nums[i].h)
            r[i]=1;
        //printf("%5d",r[i]);
    }
    //printf("\n");
    for(int i=0;i<n;i++){
        if(l[i]&&r[i])
            ans++;
    }
    cout<<ans;
    return 0;
}
