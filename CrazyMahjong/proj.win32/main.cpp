#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

// Handle 代表系统内核对象，如文件句柄，线程句柄，
// HMODULE 代表应用程序载入的模块【线性地址】，
// HINSTANCE 同上，但可用于win16
// LPTSTR->LongPointer _T str  表示指向字符/字符串的长指针 
// 这个宏表示char*【MBCS】或unsigned char*【UNICODE】
//int APIENTRY _tWinMain(HINSTANCE hInstance,
//						HINSTANCE		hPrevInstance,
//						LPTSTR	lpCmdLine,
//						int	nCmdShow)

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
	
    return Application::getInstance()->run();
}
