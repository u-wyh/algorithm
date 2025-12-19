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