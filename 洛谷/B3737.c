#include<stdio.h>

int main()
{
    int x,y;
    scanf("%d %d",&x,&y);
    int count1=0;
    for(int i=1900;i<x;i++)
    {
        if(i%400==0||(i%100!=0&&i%4==0))
            count1++;
    }
    int days=(x-1900-count1)*365+count1*366;
    int days2;
    int count=0;
    for(int i=x;i<=y;i++)
    {
        if(i%400==0||(i%100!=0&&i%4==0))
            days2=days+316;
        else
            days2=days+315;
        if(i%400==0||(i%100!=0&&i%4==0))
            days+=366;
        else
            days+=365;
        if(days2%7==0||days2%7==6)
            count++;
    }
    printf("%d\n",count);
    return 0;
}
