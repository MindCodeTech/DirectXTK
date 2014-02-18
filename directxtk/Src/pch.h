//--------------------------------------------------------------------------------------
// File: pch.h
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

#ifndef UNICODE
#error "DirectXTK requires a Unicode build."
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

// If app hasn't choosen, set to work with Windows 8 and beyond
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP)
#if defined(_WIN32_WINNT) && (_WIN32_WINNT < _WIN32_WINNT_WIN8)
#undef _WIN32_WINNT
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT   _WIN32_WINNT_WIN8
#endif
#ifndef WINVER
#define WINVER         _WIN32_WINNT
#endif
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS _WIN32_WINNT
#endif
#endif

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WIN8) && !defined(DXGI_1_2_FORMATS)
#define DXGI_1_2_FORMATS
#endif

#include "DirectXTKexp.h"

#if defined(_MSC_VER) && defined(DXTKLIB_EXPORTS) || defined(_LIB) || defined(DXTKLIB_IMPORTS) || defined(_DLL)
#define DXTK_AUTOLIB 0
#endif

// #define DXTK_AUTOLIB to automatically include the libs needed for DXTK
#if !defined(DXUT_AUTOLIB) && !defined(EFFECTS11_AUTOLIB)&& !defined(DXTEX_AUTOLIB)
#ifdef DXTK_AUTOLIB
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "ComCtl32.Lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "dxguid.lib" )
// #pragma comment( lib, "ole32.lib" ) // included with additional include directories 
// #pragma comment( lib, "uuid.lib" ) // included with additional include directories 
#pragma comment( lib, "USP10.Lib" )
#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WIN8) && (WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP) || defined(_WIN7_PLATFORM_UPDATE) && !defined(_XBOX_ONE)
#pragma comment( lib, "d2d1.lib" )
#endif
#pragma comment( lib, "WinMM.Lib" )
#pragma comment( lib, "Imm32.Lib" )
#pragma comment( lib, "Version.Lib" )
#endif
#endif


#ifdef DXTKLIB_IMPORTS
#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP) && (WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP)
#if defined(_WIN32) && !defined(_WIN64)
#ifdef DXTKLIB_DLL
#ifdef _DEBUG
#pragma comment( lib, "DirectXTK_d.lib" )
#else
#pragma comment( lib, "DirectXTK.lib" )
#endif
#elif DXTKLIB_STATIC
#ifdef _DEBUG
#pragma comment( lib, "DirectXTKs_d.lib" )
#else
#pragma comment( lib, "DirectXTKs.lib" )
#endif
#endif
#else
#ifdef DXTKLIB_DLL
#ifdef _DEBUG
#pragma comment( lib, "DirectXTK64_d.lib" )
#else
#pragma comment( lib, "DirectXTK64.lib" )
#endif
#elif DXTKLIB_STATIC
#ifdef _DEBUG
#pragma comment( lib, "DirectXTKs64_d.lib" )
#else
#pragma comment( lib, "DirectXTKs64.lib" )
#endif
#endif
#endif
#elif defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PC_APP) && (WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP)
#if defined(_WIN32) && !defined(_WIN64) && !defined(_ARM)
#ifdef DXTKLIB_DLL
#ifdef _DEBUG
#pragma comment( lib, "DirectXTKMetro_d.lib" )
#else
#pragma comment( lib, "DirectXTKMetro.lib" )
#endif
#elif DXTKLIB_STATIC
#ifdef _DEBUG
#pragma comment( lib, "DirectXTKsMetro_d.lib" )
#else
#pragma comment( lib, "DirectXTKsMetro.lib" )
#endif
#endif
#elif defined(_WIN64) && !defined(_ARM)
#ifdef DXTKLIB_DLL
#ifdef _DEBUG
#pragma comment( lib, "DirectXTKMetro64_d.lib" )
#else
#pragma comment( lib, "DirectXTKMetro64.lib" )
#endif
#elif DXTKLIB_STATIC
#ifdef _DEBUG
#pragma comment( lib, "DirectXTKsMetro64_d.lib" )
#else
#pragma comment( lib, "DirectXTKsMetro64.lib" )
#endif
#endif // DXTKLIB_DLL DXTKLIB_STATIC
#else
#ifdef DXTKLIB_DLL
#ifdef _DEBUG
#pragma comment( lib, "DirectXTKARM_d.lib" )
#else
#pragma comment( lib, "DirectXTKARM.lib" )
#endif
#elif DXTKLIB_STATIC
#ifdef _DEBUG
#pragma comment( lib, "DirectXTKsARM_d.lib" )
#else
#pragma comment( lib, "DirectXTKsARM.lib" )
#endif
#endif // DXTKLIB_DLL DXTKLIB_STATIC
#endif // _WIN32 _WIN64 _ARM
#elif defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
#ifdef DXTKLIB_DLL
#ifdef _DEBUG
#pragma comment( lib, "DirectXTKARM_d.lib" )
#else
#pragma comment( lib, "DirectXTKARM.lib" )
#endif
#elif DXTKLIB_STATIC
#ifdef _DEBUG
#pragma comment( lib, "DirectXTKsARM_d.lib" )
#else
#pragma comment( lib, "DirectXTKsARM.lib" )
#endif
#endif // DXTKLIB_DLL DXTKLIB_STATIC
#endif // WINAPI_FAMILY
#if !defined(DXTKLIB_DLL) ||  !defined(DXTKLIB_STATIC)
#pragma warning ("DXTKLIB_IMPORTS import librarys aren't defined")
#endif
#endif  // DXTKLIB_IMPORTS

// warning 4447 disabled wasking for threading model Platform::Array<Platform::String^>^ args
#pragma warning(disable : 4067 4102 4127 4201 4251 4324 4447 4481 4505 4616 4706 6326 6993 )

#pragma warning(push)
#pragma warning(disable : 4005)

// STL includes
#include <assert.h>
#include <tchar.h>
#include <wchar.h>
#include <new.h>      // for placement new
#include <math.h>
#include <malloc.h>
#include <limits.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <intsafe.h>
#include <string>
#include <algorithm>
#include <array>
#include <memory.h>
#include <memory>
#include <map>
#include <float.h>
#include <cmath>
#include <vector>
#include <functional>
#include <set>
#include <search.h>
#include <exception>
#include <type_traits>
#include <list>
#include <unordered_map>
#ifdef _OPENMP
#include <omp.h>
#endif

#pragma pack(push)
#pragma pack(8)

// Standard Windows includes
#include <ocidl.h>
#include <initguid.h>
#include <commctrl.h> // for InitCommonControls()
#include <shellapi.h> // for ExtractIcon()
#include <shlobj.h>
#include <usp10.h>
#include <dimm.h>
#include <sal.h>
#include <strsafe.h>
#include <msctf.h>
#include <mmsystem.h>
#include <ks.h>
#include <ole2.h>
#include <wrl.h>
#include <objbase.h>
#include <mmreg.h>


// Direct3D11 includes
#if defined(_XBOX_ONE) && defined(_TITLE) && MONOLITHIC
#include <d3d11_x.h>
#define DCOMMON_H_INCLUDED
#define NO_D3D11_DEBUG_NAME
#endif

//#include <d3dcommon.h>
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP)
#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE) && !defined(_XBOX_ONE)
#include <dxgi1_3.h>
#include <d3d11_2.h>
#include <d2d1_2.h>
#elif defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WIN8) || defined(_WIN7_PLATFORM_UPDATE) && !defined(_XBOX_ONE)
#include <dxgi1_2.h>
#include <d3d11_1.h>
#include <d2d1_1.h>
#endif
#else  // check winphone includes
#include <dxgi1_2.h>
#include <d3d11_1.h>

#endif

#if defined(DEBUG) || defined(_DEBUG)
#include <dxgidebug.h>
#endif

// DirectXMath includes
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <directxpackedvector.h>
#include <DirectXCollision.h>

// WIC includes
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP)
#include <wincodec.h>
#endif

#if defined(_XBOX_ONE) && defined(_TITLE)
#include <xma2defs.h>
#pragma comment(lib,"acphal.lib")
#endif

#if defined(WINAPI_FAMILY) && WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
#pragma comment(lib,"PhoneAudioSes.lib")
#endif

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WIN8 /*_WIN32_WINNT_WIN8*/)
#if defined(_MSC_VER) && (_MSC_VER < 1700)
#error DirectX Tool Kit for Audio does not support VS 2010 without the DirectX SDK 
#endif
#include <xaudio2.h>
#include <xaudio2fx.h>
#include <x3daudio.h>
#include <xapofx.h>
#pragma comment(lib,"xaudio2.lib")
#else
// Using XAudio 2.7 requires the DirectX SDK
#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\comdecl.h>
#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xaudio2.h>
#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xaudio2fx.h>
#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xapofx.h>
#pragma warning(push)
#pragma warning( disable : 4005 )
#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\x3daudio.h>
#pragma warning(pop)
#pragma comment(lib,"x3daudio.lib")
#pragma comment(lib,"xapofx.lib")
#endif

// XInput includes
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP)
#include <xinput.h>
#endif

#pragma pack (pop)


#if defined(_XBOX_ONE) && defined(_TITLE)
#include <apu.h>
#endif

// CRT's memory leak detection
#if defined(DEBUG) || defined(_DEBUG)
#include <crtdbg.h>
#endif

#pragma warning(pop)


/*
namespace_DirectX
#if (DIRECTXMATH_VERSION < 305) && !defined(XM_CALLCONV)
#define XM_CALLCONV __fastcall
typedef const XMVECTOR& HXMVECTOR;
typedef const XMMATRIX& FXMMATRIX;
#endif
namespace_DirectX_end*/


		//--------------------------------------------------------------------------------------
		// SAL2 fixups for VS 2010
		//--------------------------------------------------------------------------------------

		/*
		#if defined(_MSC_VER) && (_MSC_VER<1610) && !defined(_In_reads_)
		#define _Analysis_assume_(exp)
		#define _In_reads_(exp)
		#define _In_reads_opt_(exp)
		#define _Out_writes_(exp)
		#define _Out_writes_opt_(exp)
		#define _In_reads_bytes_(exp)
		#define _Out_writes_bytes_(exp)
		#define _Out_writes_bytes_to_opt_(a,b)
		#define _Inout_updates_bytes_(exp)
		#define _Inout_updates_all_(exp)
		#define _Inout_updates_all_opt_(exp)
		#define _COM_Outptr_
		#define _Outptr_
		#define _Outptr_opt_
		#define _Outptr_result_z_
		#define _Outptr_opt_result_maybenull_
		#define _When_(a,b)
		#define _Acquires_lock_(exp)
		#define _Releases_lock_(exp)
		#define _Inexpressible_(exp)
		#endif*/

#if defined(_MSC_VER) && (_MSC_VER<1610) && !defined(_In_reads_)
#define _Analysis_assume_(exp) __analysis_assume(exp)
#define _In_reads_(exp) _In_count_x_(exp)
#define _In_reads_opt_(exp) _In_opt_count_x_(exp)
#define _In_reads_bytes_(exp) _In_bytecount_x_(exp)
#define _Inout_updates_(exp) _Inout_cap_x_(exp)
#define _Inout_updates_z_(exp) _Inout_z_cap_x_(exp)
#define _Inout_updates_bytes_(exp) _Inout_bytecap_x_(exp)
#define _Inout_updates_all_(exp) _Inout_z_cap_x_(exp)
#define _Inout_updates_all_opt_(exp) _Inout_opt_z_cap_x_(exp)
#define _Out_writes_(exp) _Out_cap_x_(exp)
#define _Out_writes_opt_(exp) _Out_opt_cap_x_(exp)
#define _Out_writes_bytes_(exp) _Out_bytecap_x_(exp)
#define _Out_writes_bytes_to_opt_(a,b) _Out_opt_bytecap_x_(a,b)
#define _Outptr_ _Deref_out_
#define _Outptr_opt_ _Deref_out_opt_
#define _Outptr_result_z_ _Deref_out_z_
#define _Outptr_opt_result_maybenull_ _Deref_opt_out_opt_
#define _Outptr_result_maybenull_z_ _Deref_opt_out_opt_z_
#define _Outptr_result_buffer_(exp) _Deref_post_cap_x_(exp)
#define _Outptr_result_buffer_all_maybenull_(exp) _Deref_post_opt_cap_x_(exp)
#define _COM_Outptr_ _Deref_out_
#define _When_(test,exp)
#define _Acquires_lock_(exp)
#define _Releases_lock_(exp)
#define _Inexpressible_(exp)
#endif

#ifndef _Use_decl_annotations_
#define _Use_decl_annotations_
#endif


///////////////////////////////////////////////////////////////////////////////
// DirectXTK
#include "DirectXTKvers.h"

#include "typesexport.h"
#include "PlatformHelpers.h"
#include "DDS.h"
#include "DDSTextureLoader.h"
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP)
#include "WICTextureLoader.h"
#endif
#include "ScreenGrab.h"

#ifdef _PCH_BUILD
#include "GeometricPrimitive.h"
#include "PrimitiveBatch.h"
#include "Effects.h"
#include "SpriteFont.h"
#include "SpriteBatch.h"
#include "ConstantBuffer.h"
#include "Model.h"
#include "CommonStates.h"
#include "VertexTypes.h"
#include "SharedResourcePool.h"
#include "Bezier.h"
#include "AlignedNew.h"
#include "EffectCommon.h"
#include "DemandCreate.h"
#include "BinaryReader.h"
#include "SimpleMath.h"
#include "Audio.h"
#include "WAVFileReader.h"
#include "WaveBankReader.h"
#include "SoundCommon.h"
#endif



