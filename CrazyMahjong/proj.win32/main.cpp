#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

// Handle ����ϵͳ�ں˶������ļ�������߳̾����
// HMODULE ����Ӧ�ó��������ģ�顾���Ե�ַ����
// HINSTANCE ͬ�ϣ���������win16
// LPTSTR->LongPointer _T str  ��ʾָ���ַ�/�ַ����ĳ�ָ�� 
// ������ʾchar*��MBCS����unsigned char*��UNICODE��
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
