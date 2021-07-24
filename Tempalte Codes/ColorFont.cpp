#include<stdio.h>
#include<conio.h>
#include <windows.h>

void textcolor (int color){
    static int __BACKGROUND;

    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


    GetConsoleScreenBufferInfo(h, &csbiInfo);

    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
                             color + (__BACKGROUND << 4));
}

int main( ){
  textcolor(1);
  printf("textcolor c example with a blue blinking text");
  getch();
  return 0;
}
