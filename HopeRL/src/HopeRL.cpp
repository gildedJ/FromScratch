#include <Windows.h>
#include <GL/glew.h>

#include "opengl\glFuncs.h"

#include <cassert>
#include <iostream>

#include "Game.h"

#include "utility\timer.h"

inline HINSTANCE GetHInstance()
{
  return static_cast<HINSTANCE>(GetModuleHandle(nullptr));
}

inline HINSTANCE GetHPrevInstance()
{
  return static_cast<HINSTANCE>(nullptr);
}

inline LPWSTR GetLPCmdLine()
{
  // The first argument is the program name. To allow it to have spaces, it can be surrounded by 
  // quotes. We must track if the first argument is quoted since a space is also used to separate 
  // each parameter. 
  bool isQuoted = false;
  const wchar_t space = L' ';
  const wchar_t quote = L'\"';
  const wchar_t nullTerminator = L'\0';

  LPWSTR lpCmdLine = GetCommandLineW();
  assert(lpCmdLine != nullptr);

  // The lpCmdLine in a WinMain is the command line as a string excluding the program name. 
  // Program names can be quoted to allow for space characters so we need to deal with that. 
  while (*lpCmdLine <= space || isQuoted) {
    if (*lpCmdLine == quote) {
      isQuoted = !isQuoted;
    }
    lpCmdLine++;
  }

  // Get past any additional whitespace between the end of the program name and the beginning 
  // of the first parameter (if any). If we reach a null terminator we are done (i.e. there are 
  // no arguments and the pointer itself is still properly valid). 
  while (*lpCmdLine <= space && *lpCmdLine != nullTerminator) {
    lpCmdLine++;
  }

  // This will now be a valid pointer to either a null terminator or to the first character of 
  // the first command line parameter after the program name. 
  return lpCmdLine;
}

inline int GetNCmdShow()
{
  STARTUPINFOW startupInfo;
  GetStartupInfoW(&startupInfo);
  if ((startupInfo.dwFlags & STARTF_USESHOWWINDOW) != 0)
  {
    return startupInfo.wShowWindow;
  }
  return SW_SHOWDEFAULT;
}

LRESULT CALLBACK WndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
    case WM_CLOSE:
      DestroyWindow(window);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    default: 
      return DefWindowProc(window, message, wParam, lParam);
  }
  return 0;
}

void InitOpenGL(HWND window, HDC windowDC)
{
  PIXELFORMATDESCRIPTOR desiredPixelFormat = {};
  desiredPixelFormat.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  desiredPixelFormat.nVersion = 1;
  desiredPixelFormat.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
  desiredPixelFormat.cColorBits = 24;
  desiredPixelFormat.cAlphaBits = 8;
  desiredPixelFormat.iLayerType = PFD_MAIN_PLANE;

  int suggestedPixelFormatIndex = ChoosePixelFormat(windowDC, &desiredPixelFormat);
  PIXELFORMATDESCRIPTOR suggestedPixelFormat;
  DescribePixelFormat(windowDC, suggestedPixelFormatIndex, sizeof(suggestedPixelFormat), &suggestedPixelFormat);
  SetPixelFormat(windowDC, suggestedPixelFormatIndex, &suggestedPixelFormat);
  HGLRC openGLRC = wglCreateContext(windowDC);
  if (wglMakeCurrent(windowDC, openGLRC))
  {
    glewExperimental = GL_TRUE;
    glewInit();
    InitializeGLExtFunctions();
    // This turns off vsync
    wglSwapIntervalEXT(0);
  }
  else
  {
    /// ERROR!
    MessageBoxA(NULL, "Failed to create OpenGL RC!", "Error!", MB_ICONEXCLAMATION | MB_OK);
  }
}

void Run(MSG &msg, HWND window, HDC windowDC)
{
  Game thisGame;
  thisGame.Init();

  bool done = false;

  const int DESIRED_FRAMES_PER_SECOND = 70;
  const int MS_PER_FRAME = 1000 / DESIRED_FRAMES_PER_SECOND;
  const int MAX_FRAMESKIP = 10;
  Timer frameTimer("Frame");
  Timer updateTimer("Update");
  Timer renderTimer("Render");
  int loops = 0;
  while (!done)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT || msg.message == WM_DESTROY || msg.message == WM_CLOSE)
      {
        break;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    loops = 0;
    frameTimer.Start();
    GLfloat dt = 0.0;
    while (frameTimer.CurrentElapsedMS() < MS_PER_FRAME && loops < MAX_FRAMESKIP)
    {
      updateTimer.Start();
      thisGame.Update(dt);
      updateTimer.Stop();
      updateTimer.ReportElapsedTime();

      loops++;
    }
    renderTimer.Start();
    thisGame.Render(windowDC);
    renderTimer.Stop();
    renderTimer.ReportElapsedTime();

    dt = (GLfloat)frameTimer.Stop();
    frameTimer.ReportElapsedTime();
  }
}

HWND InitializeWindow(HINSTANCE hInstance, int nCmdShow, const char *title)
{
  const char className[] = "Hope Window Class";

  WNDCLASSEXA wc = {};
  HWND window;

  wc.cbSize = sizeof(WNDCLASSEX);
  wc.lpfnWndProc = WndProc;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wc.lpszClassName = className;
  wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  if (!RegisterClassExA(&wc))
  {
    MessageBoxA(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    return 0;
  }

  window = CreateWindowExA(0, className, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
  if (window == NULL)
  {
    MessageBoxA(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    return 0;
  }

  ShowWindow(window, nCmdShow);
  UpdateWindow(window);

  return window;
}

int main(int argc, char *argv[])
{
  HINSTANCE hInstance = GetHInstance();
  HINSTANCE hPrevInstance = GetHPrevInstance();
  LPWSTR lpCmdLine = GetLPCmdLine();
  int nCmdShow = GetNCmdShow();

  assert(hInstance != nullptr);
  assert(hPrevInstance == nullptr);
  assert(lpCmdLine != nullptr);

  HWND window = InitializeWindow(hInstance, nCmdShow, "Pandoran Remains");
  HDC deviceContext = GetDC(window);
  MSG msg = {};

  InitOpenGL(window, deviceContext);

  Run(msg, window, deviceContext);

  ReleaseDC(window, deviceContext);
  return msg.wParam;
}