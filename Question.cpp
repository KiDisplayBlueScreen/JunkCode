#include "stdafx.h"
#include <Windows.h>

int main()
{
	char *p = 0;
	int i;
	p = (char*)malloc(100);
	printf("输入字符串 \n");
	scanf_s("%s", p);
	for (int i = 0; *(p + i) != '\0'; i++)
		if (*(p + i) >= 'A'&&*(p + i) <= 'Z')
			*(p + i) = *(p + i) + ('a' - 'A');

	printf_s("%s \n", p);

	free(p);
	PAUSE;
    return 0;
}
