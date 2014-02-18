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


#define namespace_DirectX namespace DirectX {
#define namespace_DirectX_end }

#define namespace_DirectXTK namespace DirectXTK {
#define namespace_DirectXTK_end }

#define namespace_Internal namespace Internal {
#define namespace_Internal_end }

#define namespace_SimpleMath namespace SimpleMath {
#define namespace_SimpleMath_end }

#define namespace_std namespace std {
#define namespace_std_end }

#define namespace_EffectDirtyFlags namespace EffectDirtyFlags {
#define namespace_EffectDirtyFlags_end }

#define namespace_Bezier namespace Bezier {
#define namespace_Bezier_end }

#define namespace_DXUT namespace DXUT {
#define namespace_DXUT_end }

#define namespace_VSD3DStarter namespace VSD3DStarter {
#define namespace_VSD3DStarter_end }

#define namespace_DDSTextureLoader namespace DDSTextureLoader {
#define namespace_DDSTextureLoader_end }

#define namespace_WICTextureLoader namespace WICTextureLoader {
#define namespace_WICTextureLoader_end }

#define namespace_ScreenGrab namespace ScreenGrab {
#define namespace_ScreenGrab_end }


#ifdef __cplusplus
#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END }
#define EXTERN_CC_BEGIN extern "C++" {
#define EXTERN_CC_END }
#else
#define EXTERN_C_BEGIN
#define EXTERN_C_END
#define EXTERN_CC_BEGIN
#define EXTERN_CC_END
#endif

#ifdef __cplusplus
EXTERN_CC_BEGIN
#endif

#ifdef __cplusplus
EXTERN_CC_END
#endif

#ifdef __cplusplus
#ifndef _EXTERNC
#define _EXTERNC extern "C"
#endif
#ifndef _EXTERNCC
#define _EXTERNCC extern "C++"
#endif
#ifndef _EXTERN
#define _EXTERN extern
#endif
#else
#ifndef _EXTERN
#define _EXTERN extern
#endif
#endif


#ifdef __cplusplus
#define DXTKEXTERNC extern "C"
#define DXTKEXTERNCC extern "C++"
#define DXTKEXTERN extern
#else
#define DXTKEXTERNC
#define DXTKEXTERNCC
#define DXTKEXTERN extern
#endif


#if defined(_WINDOWS) || defined(_WIN32)
/* If building or using DirectXTK lib as a DLL, define DXTKLIB_DLL.
* This is not mandatory, but it offers a little performance increase.
*/

#if defined(LIB_EXPORTS) || defined(DXTKLIB_EXPORTS)
#ifndef DXTKLIB_IMPORTS
#ifndef DXTKLIB_EXPORTS
#define DXTKLIB_EXPORTS 1
#endif
#endif
#endif

#if defined(LIB_IMPORTS) || defined(DXTKLIB_IMPORTS)
#if defined(DXTKLIB_EXPORTS)
#error ("!!!You are bulding DirectXTK export and import simultaniously")
#else
#ifndef DXTKLIB_IMPORTS
#define DXTKLIB_IMPORTS 1
#endif
#endif
#endif

#if defined(LIB_STATIC) || defined(DXTKLIB_STATIC)
#ifndef DXTKLIB_DLL
#ifndef DXTKLIB_STATIC 
#define DXTKLIB_STATIC 1
#endif
#endif
#endif

#if (defined(_DLL) || defined(_USRDLL) || defined(_WINDLL) || defined(LIB_DYNAMIC) || defined(DXTKLIB_DLL)) && !defined(_LIB) && !defined(DXTKLIB_STATIC)
#ifndef DXTKLIB_STATIC
#ifndef DXTKLIB_DLL
#define DXTKLIB_DLL 1
#endif
#endif
#endif

#if !defined(DXTKLIB_DLL) && !defined(DXTKLIB_STATIC)
#error ("!!!Your DirectXTK lib type static or dll aren't defined")
#endif


#  ifdef DXTKLIB_DLL
#    if defined(WIN32) && (!defined(__BORLANDC__) || (__BORLANDC__ >= 0x500))
#      if defined(DXTKLIB_EXPORTS) && !defined(DXTKLIB_STATIC)
#        define DXTKAPI __declspec(dllexport)
#      elif defined (DXTKLIB_IMPORTS) && (defined(_DLL) || defined(_WINDLL) || defined(_USRDLL)) && !defined(DXTKLIB_STATIC)
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



//#define DXSTDAPI                  EXTERN_C HRESULT STDAPICALLTYPE
//#define DXSTDAPI_(type)           EXTERN_C type STDAPICALLTYPE


