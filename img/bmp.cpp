#define _WIN32_WINNT 0x0500
#include <Windows.h>
#include <stdio.h>
 
#pragma comment(lib, "kernel32")
 
int main(void)
{
    
   HWND hWnd = GetConsoleWindow();
   HDC hdc = GetDC(hWnd);
   HDC memhDc = CreateCompatibleDC(hdc);
   HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, "1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
   SelectObject(memhDc, hBitmap);
   {
      BITMAP bmp;
      int i;
      GetObject(hBitmap, sizeof(BITMAP), &bmp);
      for (i = 0; i < bmp.bmHeight / 15; ++i)
      {
         putchar('\n');
      }
      BitBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, memhDc, 0, 0, SRCCOPY);
   }
   DeleteObject(hBitmap);
   DeleteDC(memhDc);
   ReleaseDC(hWnd, hdc);
   return 0;
}