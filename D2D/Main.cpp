#include "DemoApp.h"

#define SCREEN_WIDTH   1024
#define SCREEN_HEIGHT  768
#define TITLE          L"D2D_Project"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    DemoApp App;

    App.Initialize(hInstance, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    App.Run();
    App.UnInitialize();

    return 0;
}