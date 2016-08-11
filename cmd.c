#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int main()
{
HANDLE consolehwnd;//创建句柄，详细句柄知识，请百度一下或查MSDN
consolehwnd=
GetStdHandle(STD_OUTPUT_HANDLE);//实例化句柄
SetConsoleTextAttribute(consolehwnd,FOREGROUND_RED);//设置字体颜色
 
printf("hello");
SetConsoleTextAttribute(consolehwnd,FOREGROUND_INTENSITY|FOREGROUND_GREEN);
printf("world!\n");
getchar();
SetConsoleTextAttribute(consolehwnd,BACKGROUND_INTENSITY|BACKGROUND_BLUE);
 
printf("Itisreallybeautiful!\n");
return 0;
}