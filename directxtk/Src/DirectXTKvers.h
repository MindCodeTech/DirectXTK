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

#ifdef _MSC_VER
#pragma once
#endif

// Exclude rarely-used stuff from Windows headers
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef STRICT
#define STRICT
#endif

#include <windows.h>

#define DXTKLIB_VERSION_DATE "2013.12.24"

#define DXTKLIB_VERSION "11.0.8"
#define DXTKLIB_VERNUM 0x2B48
#define DXTKLIB_VER_MAJOR 11
#define DXTKLIB_VER_MINOR 0
#define DXTKLIB_VER_REVISION 8
#define DXTKLIB_VER_SUBREVISION 0

#define DXTKLIB_VERSION_STR DXTKLIB_VER_MAJOR, DXTKLIB_VER_MINOR, DXTKLIB_VER_REVISION, DXTKLIB_VER_SUBREVISION

#  ifdef DXTKLIB_DLL // inst need for static lib
#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
#if defined(_WIN32) && !defined(_WIN64)
#ifdef _DEBUG
#define DXTKLIB_BUILD_ "DirectXTK_d"
#else
#define DXTKLIB_BUILD_ "DirectXTK"
#endif
#elif defined(_WIN64)
#ifdef _DEBUG
#define DXTKLIB_BUILD_ "DirectXTK64_d"
#else
#define DXTKLIB_BUILD_ "DirectXTK64"
#endif
#endif
#elif defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PC_APP)
#if defined(_WIN32) && !defined(_WIN64) && !defined(_ARM)
#ifdef _DEBUG
#define DXTKLIB_BUILD_ "DirectXTKMetro_d"
#else
#define DXTKLIB_BUILD_ "DirectXTKMetro"
#endif
#elif defined(_WIN64) && !defined(_ARM)
#ifdef _DEBUG
#define DXTKLIB_BUILD_ "DirectXTKMetro64_d"
#else
#define DXTKLIB_BUILD_ "DirectXTKMetro64"
#endif
#else
#ifdef _DEBUG
#define DXTKLIB_BUILD_ "DirectXTKARM_d"
#else
#define DXTKLIB_BUILD_ "DirectXTKARM"
#endif
#endif
#elif defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
#ifdef _DEBUG
#define DXTKLIB_BUILD_ "DirectXTKPhone_d"
#else
#define DXTKLIB_BUILD_ "DirectXTKPhone"
#endif
#endif
#endif
