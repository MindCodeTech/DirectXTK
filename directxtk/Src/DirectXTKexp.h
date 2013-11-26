/* DXTKLibExports.c -- DXTK library export types definitions  Entry point
 : Public domain */
#pragma once

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

#ifndef _WINDOWS_
#include <windows.h>
#endif

#if defined(_WINDOWS) || defined(_WIN32)
/* If building or using DirectXTK lib as a DLL, define DXTKLIB_DLL.
* This is not mandatory, but it offers a little performance increase.
*/

#if defined(LIB_EXPORT) || defined(DXTKLIB_EXPORT)
#ifndef DXTKLIB_IMPORT
#ifndef DXTKLIB_EXPORT
#define DXTKLIB_EXPORT 0
#endif
#endif
#endif

#if defined(LIB_IMPORT) || defined(DXTKLIB_IMPORT)
#if defined(DXTKLIB_EXPORT)
#error ("!!!You are bulding DirectXTK export and import simultaniously")
#else
#ifndef DXTKLIB_IMPORT
#define DXTKLIB_IMPORT 0
#endif
#endif
#endif

#if defined(LIB_STATIC) || defined(DXTKLIB_STATIC)
#ifndef DXTKLIB_DLL
#ifndef DXTKLIB_STATIC 
#define DXTKLIB_STATIC 0
#endif
#endif
#endif

#if (defined(_DLL) || defined(_USRDLL) || defined(_WINDLL) || defined(LIB_DYNAMIC) || defined(DXTKLIB_DLL)) && !defined(_LIB) && !defined(DXTKLIB_STATIC)
#ifndef DXTKLIB_STATIC
#ifndef DXTKLIB_DLL
#define DXTKLIB_DLL 0
#endif
#endif
#endif

#if !defined(DXTKLIB_DLL) && !defined(DXTKLIB_STATIC)
#error ("!!!Your DirectXTK lib type static or dll aren't defined")
#endif

//#define extern_cplus

// Defined for Templates functions export
#define extern_cplusplus

#ifdef extern_cplus
#define _EXTERN_C_START extern "C" {
#define _EXTERN_C_END  }
#endif

#ifdef extern_cplusplus
#define _EXTERN_CPP_START extern "C++" {
#define _EXTERN_CPP_END  }
#endif

#define _EXTERN extern

#  ifdef DXTKLIB_DLL
#    if defined(WIN32) && (!defined(__BORLANDC__) || (__BORLANDC__ >= 0x500))
#      if defined(DXTKLIB_EXPORT) && !defined(DXTKLIB_STATIC)
#        define DXTKAPI __declspec(dllexport)
#      elif defined (DXTKLIB_IMPORT) && (defined(_DLL) || defined(_WINDLL) || defined(_USRDLL)) && !defined(DXTKLIB_STATIC)
#        define DXTKAPI __declspec(dllimport)
#      else // DXTKLIB_STATIC  _LIB
#        define DXTKAPI
#      endif
#    endif
#  else  // DXTKLIB_LIB
#      define DXTKAPI
#  endif  /* ! DXTKLIB_DLL */

#else
#	define DXTKAPI
#endif // _WINDOWS



//#define DXSTDAPI                  EXTERN_C DXTKAPI HRESULT STDAPICALLTYPE
//#define DXSTDAPI_(type)           EXTERN_C DXTKAPI type STDAPICALLTYPE


