#include<stdio.h>

int main()
{
    int k,a,b,c;
    scanf("%d %d %d %d",&k,&a,&b,&c);
    int nums[k];
    for(int i=0;i<k;i++)
    {
        scanf("%d",&nums[i]);
    }
    int sum=0;
    for(int i=0;i<k;i++)
    {
        if(nums[i]<=10)
            sum+=nums[i]*a;
        else if(nums[i]<=100)
            sum+=((nums[i]-10)*b+10*a);
        else
            sum+=((nums[i]-100)*c+90*b+10*a);
    }
    printf("%d\n",sum);
    return 0;
}
