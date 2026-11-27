#include<bits/stdc++.h>
using namespace std;

int n;
int diff[86405]; 

struct node{
    int l,r;
}nums[86405];

bool cmp(node a,node b){
    return a.l<b.l;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int h1,m1,s1,h2,m2,s2;
        scanf("%d:%d:%d - %d:%d:%d",&h1,&m1,&s1,&h2,&m2,&s2);
        nums[i].l=h1*3600+m1*60+s1;
        nums[i].r=h2*3600+m2*60+s2;
    }
    sort(nums+1,nums+n+1,cmp);
    if(nums[1].l!=0){
        int st=0;
        int en=nums[1].l;
        
        int h1=st/3600;
        st%=3600;
        int m1=st/60;
        int s1=st%60;
        
        int h2=en/3600;
        en%=3600;
        int m2=en/60;
        int s2=en%60;
        
        printf("%02d:%02d:%02d - %02d:%02d:%02d\n",h1,m1,s1,h2,m2,s2);
    }
    for(int i=1;i<n;i++){
        if(nums[i].r!=nums[i+1].l){
            int st=nums[i].r;
            int en=nums[i+1].l;
            
            int h1=st/3600;
            st%=3600;
            int m1=st/60;
            int s1=st%60;
            
            int h2=en/3600;
            en%=3600;
            int m2=en/60;
            int s2=en%60;
            
            printf("%02d:%02d:%02d - %02d:%02d:%02d\n",h1,m1,s1,h2,m2,s2);
        }
    }
    if(nums[n].r!=86399){
        int st=nums[n].r;
        int en=86399;
        
        int h1=st/3600;
        st%=3600;
        int m1=st/60;
        int s1=st%60;
        
        int h2=en/3600;
        en%=3600;
        int m2=en/60;
        int s2=en%60;
        
        printf("%02d:%02d:%02d - %02d:%02d:%02d\n",h1,m1,s1,h2,m2,s2);
    }
    // for(int i=0;i<=86400;i++){
    //     diff[i]+=diff[i-1];
	// 	if(diff[i]>=2){
	// 		diff[i]=1;
	// 	}
    // }
    
    // vector<pair<int, int>>time;
    // int u=0;

    // for(int i=0;i<=86399;i++){
    //     if(diff[i]==0)
    // }

    // for(int i=0;i<=86399;i++){
    //     if(diff[i]==0&&u==-1){
    //         u=i;
    //     } 
	// 	else if(diff[i]>0&&u!=-1){
    //         time.push_back({u, i});
    //         u=-1;
    //     }
    // }
    
    // if(u!=-1){
    //     time.push_back({u, 86399});
    // }
    
    // for(int i=0;i<(int)time.size();i++){
    //     int st=time[i].first;
    //     int en=time[i].second;
        
    //     int h1=st/3600;
    //     st%=3600;
    //     int m1=st/60;
    //     int s1=st%60;
        
    //     int h2=en/3600;
    //     en%=3600;
    //     int m2=en/60;
    //     int s2=en%60;
        
    //     printf("%02d:%02d:%02d - %02d:%02d:%02d\n",h1,m1,s1,h2,m2,s2);
    // }
    
    return 0;
}