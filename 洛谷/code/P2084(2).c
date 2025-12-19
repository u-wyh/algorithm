#include <stdio.h>
#include <string.h>

int m;
char c[1001];

int main()
{
    scanf("%d ", &m); // 注意：这里有一个空格在%d后面，它会导致scanf读取整数后跳过随后的空白字符
    // 使用fgets代替gets，注意fgets会读取换行符，并且我们需要确保不要覆盖数组边界
    fgets(c, sizeof(c), stdin);
    // 去除fgets读取的换行符（如果存在）
    c[strcspn(c, "\n")] = 0;

    int len = strlen(c);
    for (int i = 0; i < len; i++)
    {
        if (i != 0 && c[i] != '0')
            printf("+");
        if (c[i] == '0')
            continue;
        printf("%c*%d^%d", c[i], m, len - i - 1);
    }
    printf("\n"); // 在最后添加一个换行符以保持输出格式的一致性（可选）
    return 0;
}
