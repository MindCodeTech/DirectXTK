#pragma once

using namespace std;

using namespace DirectX;


#ifdef __cplusplus
EXTERN_CC_BEGIN
#endif


//template<class Type>
//typedef class DXTEXAPI vector vector;
//typedef std std;
/*
namespace std
{
template<class _Ty>
class DXTEXAPI mallocator
: public _Allocator_base<_Ty>
{	// generic allocator for objects of class _Ty
public:
typedef allocator mallocator;
};

template<class _Ty,
class DXTEXAPI _mAlloc0>
struct _mVec_base_types
{	// types needed for a container base
typedef _mAlloc0 _mAlloc;
//typedef _Alloc _mAlloc;
typedef _mVec_base_types<_Ty, _mAlloc> _mMyt;
};

// TEMPLATE CLASS vector
template<class _Ty,
class DXTEXAPI _mAlloc = allocator<_Ty> >
class DXTEXAPI mvector
{	// varying size array of values
public:
typedef mvector<_Ty, _mAlloc> _mMyt;
typedef vector mvector;
};
}*/

namespace_DirectX

typedef struct DXTKAPI XMFLOAT2 XMFLOAT2;
typedef struct DXTKAPI XMFLOAT3 XMFLOAT3;
typedef struct DXTKAPI XMFLOAT4 XMFLOAT4;
typedef struct DXTKAPI XMFLOAT4X4 XMFLOAT4X4;
typedef struct DXTKAPI XMFLOAT4A XMFLOAT4A;
typedef DXTKAPI XMVECTOR XMVECTOR;
typedef struct DXTKAPI XMMATRIX XMMATRIX;
typedef DXTKAPI const FXMVECTOR FXMVECTOR;
typedef DXTKAPI const CXMMATRIX CXMMATRIX;

#if (DIRECTXMATH_VERSION < 305) && !defined(XM_CALLCONV)
#define XM_CALLCONV __fastcall
typedef DXTKAPI const XMVECTOR& HXMVECTOR;
typedef DXTKAPI const XMMATRIX& FXMMATRIX;
#endif

namespace_DirectX_end


#ifdef __cplusplus
EXTERN_CC_END
#endif
