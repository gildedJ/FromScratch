#pragma once

#include <Windows.h>
#include <gl\GL.h>
#include "wglext.h"

bool WGLExtensionSupported(const char *extension_name)
{
  PFNWGLGETEXTENSIONSSTRINGEXTPROC _wglGetExtensionStringEXT = NULL;
  _wglGetExtensionStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)wglGetProcAddress("wglGetExtensionsStringEXT");

  if (strstr(_wglGetExtensionStringEXT(), extension_name) == NULL)
  {
    return false;
  }
  return true;
}

void *LoadGLFunction(const char *name)
{
  void *p = (void *)wglGetProcAddress(name);
  if (p == 0 ||
    (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
    (p == (void*)-1))
  {
    HMODULE module = LoadLibraryA("opengl32.dll");
    p = (void *)GetProcAddress(module, name);
  }

  return p;
}

PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
//PFNGLUSEPROGRAMPROC glUseProgram = NULL;
//PFNGLCREATESHADERPROC glCreateShader = NULL;
//PFNGLSHADERSOURCEPROC glShaderSource = NULL;
//PFNGLCOMPILESHADERPROC glCompileShader = NULL;
//PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
//PFNGLATTACHSHADERPROC glAttachShader = NULL;
//PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
//PFNGLDELETESHADERPROC glDeleteShader = NULL;
//PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
//PFNGLUNIFORM1FPROC glUniform1f = NULL;
//PFNGLUNIFORM2FPROC glUniform2f = NULL;
//PFNGLUNIFORM3FPROC glUniform3f = NULL;
//PFNGLUNIFORM4FPROC glUniform4f = NULL;
//PFNGLUNIFORM1IPROC glUniform1i = NULL;
//PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL;
//PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
//PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
//PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
//PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;

void InitializeGLExtFunctions()
{
  if (WGLExtensionSupported("WGL_EXT_swap_control"))
  {
    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)LoadGLFunction("wglSwapIntervalEXT");
  }
 /* glUseProgram = (PFNGLUSEPROGRAMPROC)LoadGLFunction("glUseProgram");
  glCreateShader = (PFNGLCREATESHADERPROC)LoadGLFunction("glCreateShader");
  glShaderSource = (PFNGLSHADERSOURCEPROC)LoadGLFunction("glShaderSource");
  glCompileShader = (PFNGLCOMPILESHADERPROC)LoadGLFunction("glCompileShader");
  glCreateProgram = (PFNGLCREATEPROGRAMPROC)LoadGLFunction("glCreateProgram");
  glAttachShader = (PFNGLATTACHSHADERPROC)LoadGLFunction("glAttachShader");
  glLinkProgram = (PFNGLLINKPROGRAMPROC)LoadGLFunction("glLinkProgram");
  glDeleteShader = (PFNGLDELETESHADERPROC)LoadGLFunction("glDeleteShader");
  glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)LoadGLFunction("glGetUniformLocation");
  glUniform1f = (PFNGLUNIFORM1FPROC)LoadGLFunction("glUniform1f");
  glUniform2f = (PFNGLUNIFORM2FPROC)LoadGLFunction("glUniform2f");
  glUniform3f = (PFNGLUNIFORM3FPROC)LoadGLFunction("glUniform3f");
  glUniform4f = (PFNGLUNIFORM4FPROC)LoadGLFunction("glUniform4f");
  glUniform1i = (PFNGLUNIFORM1IPROC)LoadGLFunction("glUniform1i");
  glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)LoadGLFunction("glUniformMatrix4fv");
  glGetShaderiv = (PFNGLGETSHADERIVPROC)LoadGLFunction("glGetShaderiv");
  glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)LoadGLFunction("glGetShaderInfoLog");
  glGetProgramiv = (PFNGLGETPROGRAMIVPROC)LoadGLFunction("glGetProgramiv");
  glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)LoadGLFunction("glGetProgramInfoLog");*/
}