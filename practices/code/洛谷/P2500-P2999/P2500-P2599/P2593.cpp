// https://www.luogu.com.cn/problem/P2593
// 题意：牌面数字 1~100，N 次询问每次给出 100 种牌各自张数。
// 判断手牌能否拆分为若干句话（3 连张或 3/4 张相同）加 1
// 对相同牌（胡牌）。
// 每组输出 Yes 或 No。
// 数据范围：N <= 100，0 <= a_i <= 100。
// 难度评分：1800（洛谷分级换算）
// 算法标签：动态规划、枚举
#include <stdio.h>
#include <string.h>
bool DPC[110][3][3];
int N;
int CN[110];
bool Mod[110];
void Input()
{
    int wi;
    for(wi=1;wi<=100;++wi)
        scanf("%d",CN+wi);
    int ma,mb;
    for(ma=0;ma*3<=100;++ma)
        for(mb=0;mb*4+ma*3<=100;++mb)
            Mod[ma*3+mb*4]=1;
}
bool DPA()
{
    int win,wia,wib,wnn;
    memset(DPC,0,sizeof(DPC));
    DPC[0][0][0]=1;
    for(win=0;win<100;++win)
        for(wia=0;wia<3;++wia)
            for(wib=0;wib<3;++wib)
                if(DPC[win][wia][wib])
                    for(wnn=0;wnn<3&&wnn<=CN[win+1]-wia-wib;++wnn)
                        if(Mod[CN[win+1]-wia-wib-wnn])
                            DPC[win+1][wib][wnn]=1;
    return DPC[100][0][0];
}
void ACA()
{
    int wi;
    for(wi=1;wi<=100;++wi)
        if(CN[wi]>1)
        {
            CN[wi]-=2;
            if(DPA())
            {
                printf("Yes\n");
                return;
            }
            CN[wi]+=2;
        }
    printf("No\n");
}
int T;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        Input();
        ACA();
    }
    return 0;
}