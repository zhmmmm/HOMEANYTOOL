#pragma once
#include "ATENGINE/MAIN/OpenGL_AY_Engine.h"


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#define IOGL                                         ImplantOpenGL
class ImplantOpenGL
{
	int m_nGLPixelIndex;
	HGLRC m_hGLContext;
public:
	BOOL InitHDCTOMFC(HDC Hdc);
	BOOL InitHDCTOMFC(HWND HWnd);

	BOOL InitHDCTOMFC(CDialogEx *This);

	HGLRC GetGLContext() { return m_hGLContext; }
	void SetGLContext(HGLRC GLContext) {  m_hGLContext = GLContext; }
private:
	BOOL SetWindowPixelFormat(HDC Hdc);
	BOOL CreateGLContext(HDC Hdc);
public:

	void OpenGL_TO_MFC__Init_ATENGINE(Object *object,int Width,int Height);
	void OpenGL_TO_MFC__Update_ATENGINE(Object *object);
	void OpenGL_TO_MFC__End_ATENGINE(Object *object);

};