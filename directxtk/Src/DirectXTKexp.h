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


#define NAMESPACE_DirectX namespace DirectX {
#define NAMESPACE_DirectX_END }

#define NAMESPACE_DirectXTK namespace DirectXTK {
#define NAMESPACE_DirectXTK_END }

#define NAMESPACE_Internal namespace Internal {
#define NAMESPACE_Internal_END }

#define NAMESPACE_SimpleMath namespace SimpleMath {
#define NAMESPACE_SimpleMath_END }

#define NAMESPACE_std namespace std {
#define NAMESPACE_std_END }

#define NAMESPACE_EffectDirtyFlags namespace EffectDirtyFlags {
#define NAMESPACE_EffectDirtyFlags_END }

#define NAMESPACE_Bezier namespace Bezier {
#define NAMESPACE_Bezier_END }

#define NAMESPACE_DXUT namespace DXUT {
#define NAMESPACE_DXUT_END }

#define NAMESPACE_VSD3DStarter namespace VSD3DStarter {
#define NAMESPACE_VSD3DStarter_END }

#define NAMESPACE_DDSTextureLoader namespace DDSTextureLoader {
#define NAMESPACE_DDSTextureLoader_END }

#define NAMESPACE_WICTextureLoader namespace WICTextureLoader {
#define NAMESPACE_WICTextureLoader_END }

#define NAMESPACE_ScreenGrab namespace ScreenGrab {
#define NAMESPACE_ScreenGrab_END }


//#define extern_cplus

// Defined for Templates functions export
#define extern_cplusplus

#ifndef EXTERN_C_BEGIN
#ifdef __cplusplus
#ifdef extern_cplus
#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END }
#endif
#ifdef extern_cplusplus
#define EXTERN_C_BEGIN extern "C++" {
#define EXTERN_C_END }
#endif
#else
#define EXTERN_C_BEGIN
#define EXTERN_C_END
#endif
#endif

#ifdef __cplusplus
EXTERN_C_BEGIN
#endif

#ifdef __cplusplus
EXTERN_C_END
#endif

#ifdef __cplusplus
#if defined(extern_cplus)
#define _EXTERN extern "C"
#elif defined(extern_cplusplus)
#define _EXTERN extern "C++"
#endif
#else
#define _EXTERN extern
#endif

#ifdef __cplusplus
#if defined(extern_cplus)
#define DXTKEXTERN extern "C"
#elif defined(extern_cplusplus)
#define DXTKEXTERN extern "C++"
#endif
#else
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


