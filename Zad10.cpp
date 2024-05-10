#include <windows.h>
#include <tchar.h>
#include <iostream>
#include "Target.h"
#include "float4.h"
#include "vector3.h"
#include "VertexProcessor.h"
#include "Cone.h"
#include "Sphere.h"
#include "Torus.h"
#include <chrono>
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "NoLight.h"
#include "Texture.h"

// Global variables
float t = 0;
// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("App");

// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;

unsigned int width = 800, height = 600;
Sphere sphere(4, 8, 0.1, 1);
Cone cone(0.1, 0.2, 8);
Torus torus(8, 12, 0.2, 0.1);
VertexProcessor vp;
Light* dlight;
Light* dlight2;
Light* nlight;
Texture texture1;
Texture texture2;

TGABuffer* target;
BITMAPINFO m_bi;
char* buffer = 0;

void updateBuffer();
void setbuffer()
{
    m_bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    m_bi.bmiHeader.biWidth = width;
    m_bi.bmiHeader.biHeight = height;
    m_bi.bmiHeader.biPlanes = 1;
    m_bi.bmiHeader.biBitCount = 24;
    m_bi.bmiHeader.biCompression = BI_RGB;
    m_bi.bmiHeader.biSizeImage = 0;
    m_bi.bmiHeader.biXPelsPerMeter = 100;
    m_bi.bmiHeader.biYPelsPerMeter = 100;
    m_bi.bmiHeader.biClrUsed = 0;
    m_bi.bmiHeader.biClrImportant = 0;

    size_t paddedWidth = (width * 3 + 3) & ~3;
    buffer = new char[paddedWidth * height * 3];

    //updateBuffer();
}

void updateBuffer() {
    size_t paddedWidth = (width * 3 + 3) & ~3;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {

            unsigned int hexValue = target->getColorBuffer()[y * width + x];
            buffer[y * paddedWidth + x * 3 + 2] = ((hexValue >> 16) & 0xFF);
            buffer[y * paddedWidth + x * 3 + 1] = ((hexValue >> 8) & 0xFF);
            buffer[y * paddedWidth + x * 3 + 0] = ((hexValue) & 0xFF);

        }
    }
}

void render() {
    vp.setLookAt({ 0, 0,  2}, {0, 0, 0}, {0, 1, 0});
    //vp.setLookAt({ cos(t * 0.002f) * 2, 0, sin(t * 0.002f) * 2 }, { 0, 0, 0 }, { 0, 1, 0 });

    float4x4 model;

    model = model.rotate(-90, { 1, 0, 0 });
    model = model.scale({ 0.5, 0.5, 0.5 });

    model = model.rotate(t, { 0, 1, 0 });
    model = model.translate({ 0.5, -0.0, 0 });
    vp.setModel(model);

    target->ClearColor(90, 90, 102);
    target->ClearDepth();


    cone.Draw(*target, vp, *dlight2, true);
   
    model = model.indentity();
    model = model.rotate(t, { 0, 1, 0 });
    model = model.translate({ 0.5, -0.3, 0 });

    vp.setModel(model);

    sphere.Draw(*target, vp, *dlight2, true);


    model = model.indentity();
    model = model.rotate(t, { 0, 1, 0 });
    model = model.translate({ -0.0 , 0, -0.25 });

    vp.setModel(model);

    sphere.Draw(*target, vp, *dlight, true);

    model = model.indentity();
    model = model.rotate(t, { 0, 1, 0 });
    //model = model.rotate(-90, { 1, 0, 0 });
    model = model.scale({ 0.5, 0.5, 0.5 });

    model = model.translate({ -0.5, -0.0, 0 });

    vp.setModel(model);

    torus.Draw(*target, vp, *nlight, true);
}

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    texture1 = Texture("texture1.jpg");
    texture2 = Texture("texture2.jpg");
    target = new TGABuffer(width, height);
    dlight = new DirectionalLight({ 0, 0, 0 }, { 0, 1, 0 }, { 150, 145, 138 }, { 154, 200, 116 }, { 255, 223, 211 }, 128, &texture1);
    dlight2 = new DirectionalLight({ 0, 0, 0 }, { 0, 1, 0 }, { 150, 145, 138 }, { 154, 200, 116 }, { 255, 223, 211 }, 128, &texture2);
    //dlight = new PointLight({ 0, 0, 0 }, { 100, 45, 88 }, { 154, 100, 116 }, { 255, 223, 211 }, 2);
    //dlight = new SpotLight({ 0, 0, -1 }, { -0.2, -1, 0 }, { 100, 45, 88 }, { 154, 100, 116 }, { 255, 223, 211 }, 128, 0.1f, 1.2f);
    nlight = new NoLight(&texture1);
    vp.setPerspective(30, static_cast<float>(width) / height, 0.1, 100);

    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain

    render();

    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);
    target->Save("out");

    // Main message loop:
    MSG msg;

    while (TRUE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) //<=== **** EDITED **** 
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            typedef std::chrono::high_resolution_clock hiresclock;
            static auto timer = hiresclock::now();
            auto milisec = (hiresclock::now() - timer).count() / 1000000;
            if (milisec > 16)
            {
                timer = hiresclock::now();
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
    }


    target->ClearBuffer();

    delete target;
    delete dlight;
    delete nlight;
    texture1.cleanUp();

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Hello, Windows desktop!");
    DWORD result;

    switch (message)
    {
    case WM_CREATE:
        setbuffer();
        break;
    case WM_PAINT:

        t += 2;
        render();
        updateBuffer();

        hdc = BeginPaint(hWnd, &ps);

        // Here your application is laid out.
        // For this introduction, we just print out "Hello, Windows desktop!"
        // in the top left corner.
        //TextOut(hdc,
        //    5, 5,
        //    greeting, _tcslen(greeting));
        // End application-specific layout section.

        result = StretchDIBits(hdc,
            0, 0,
            width, height,
            0, 0,
            width, height,
            buffer, &m_bi, DIB_RGB_COLORS, SRCCOPY);
        if (result != height)
        {
            //Drawing failed
            DebugBreak();
        }

        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}