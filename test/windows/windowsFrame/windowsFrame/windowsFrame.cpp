// windowsFrame.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <winnls.h>


int _tmain(int argc, _TCHAR* argv[])
{
	std::string nStr="是";
	size_t nSize=nStr.length();
	wchar_t *nbuffer=new wchar_t[nSize+1];
	MultiByteToWideChar(CP_ACP,0,nStr.c_str(),nSize,nbuffer,nSize*sizeof(wchar_t));
	nbuffer[nSize]=0;

	std::string cStr = "Button";
	size_t cSize = cStr.length();
	wchar_t *cbuffer = new wchar_t[cSize + 1];
	MultiByteToWideChar(CP_ACP, 0, cStr.c_str(), cSize, cbuffer, cSize*sizeof(wchar_t));
	cbuffer[cSize] = 0;

	HWND hq=FindWindow(cbuffer,nbuffer);

	RECT rect;
	GetWindowRect(hq,&rect);

	MoveWindow(hq,100,100,100,100,false);

	if(hq){
		int i=0;
	}

	return 0;
}

