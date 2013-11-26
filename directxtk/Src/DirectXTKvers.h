//--------------------------------------------------------------------------------------
// File: DirectXTexvers.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
//--------------------------------------------------------------------------------------

#define DXTKLIB_VERSION_DATE "2013.11.19"

// I have defined to version 8 in reference to windows 8 but we can change-it !!(I cant find info about DXTK version)
#define DXTKLIB_VERSION "11.0.8"
#define DXTKLIB_VERNUM 0x11080
#define DXTKLIB_VER_MAJOR 11
#define DXTKLIB_VER_MINOR 0
#define DXTKLIB_VER_REVISION 8
#define DXTKLIB_VER_SUBREVISION 0

#define DXTKLIB_VERSION_STR DXTKLIB_VER_MAJOR, DXTKLIB_VER_MINOR, DXTKLIB_VER_REVISION, DXTKLIB_VER_SUBREVISION

#ifdef _DEBUG
#define DXTKLIB_BUILD_ "_d"
#else
#define DXTKLIB_BUILD_ ""
#endif
