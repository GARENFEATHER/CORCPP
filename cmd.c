#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int main()
{
HANDLE consolehwnd;//�����������ϸ���֪ʶ����ٶ�һ�»��MSDN
consolehwnd=
GetStdHandle(STD_OUTPUT_HANDLE);//ʵ�������
SetConsoleTextAttribute(consolehwnd,FOREGROUND_RED);//����������ɫ
 
printf("hello");
SetConsoleTextAttribute(consolehwnd,FOREGROUND_INTENSITY|FOREGROUND_GREEN);
printf("world!\n");
getchar();
SetConsoleTextAttribute(consolehwnd,BACKGROUND_INTENSITY|BACKGROUND_BLUE);
 
printf("Itisreallybeautiful!\n");
return 0;
}