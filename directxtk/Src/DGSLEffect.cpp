//--------------------------------------------------------------------------------------
// File: DGSLEffect.cpp
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

#include "pch.h"
#include "EffectCommon.h"
#include "DemandCreate.h"

using namespace DirectXTK;

//
// Based on the Visual Studio 3D Starter Kit
//
// http://aka.ms/vs3dkit
//

#ifdef __cplusplus
EXTERN_CC_BEGIN
#endif

namespace_DirectX

namespace_EffectDirtyFlags

const int ConstantBufferMaterial = 0x10000;
const int ConstantBufferLight = 0x20000;
const int ConstantBufferObject = 0x40000;
const int ConstantBufferMisc = 0x80000;
const int ConstantBufferBones = 0x100000;

namespace_EffectDirtyFlags_end

namespace_DirectX_end

using namespace DirectX;

// Constant buffer layout. Must match the shader!
#pragma pack(push,1)

// Slot 0
struct DXTKAPI MaterialConstants
{
	XMVECTOR    Ambient;
	XMVECTOR    Diffuse;
	XMVECTOR    Specular;
	XMVECTOR    Emissive;
	float       SpecularPower;
	float       Padding0;
	float       Padding1;
	float       Padding2;
};

// Slot 1
struct DXTKAPI LightConstants
{
	XMVECTOR    Ambient;
	XMVECTOR    LightColor[DGSLEffect::MaxDirectionalLights];
	XMVECTOR    LightAttenuation[DGSLEffect::MaxDirectionalLights];
	XMVECTOR    LightDirection[DGSLEffect::MaxDirectionalLights];
	XMVECTOR    LightSpecularIntensity[DGSLEffect::MaxDirectionalLights];
	UINT        IsPointLight[DGSLEffect::MaxDirectionalLights];
	UINT        ActiveLights;
	float       Padding0;
	float       Padding1;
	float       Padding2;
};

// Note - DGSL does not appear to make use of LightAttenuation or IsPointLight. Not sure if it uses ActiveLights either.

// Slot 2
struct DXTKAPI ObjectConstants
{
	XMMATRIX    LocalToWorld4x4;
	XMMATRIX    LocalToProjected4x4;
	XMMATRIX    WorldToLocal4x4;
	XMMATRIX    WorldToView4x4;
	XMMATRIX    UvTransform4x4;
	XMVECTOR    EyePosition;
};

// Slot 3
struct DXTKAPI MiscConstants
{
	float ViewportWidth;
	float ViewportHeight;
	float Time;
	float Padding1;
};

// Slot 4
struct DXTKAPI BoneConstants
{
	XMVECTOR Bones[DGSLEffect::MaxBones][3];
};

#pragma pack(pop)

static_assert((sizeof(MaterialConstants) % 16) == 0, "CB size not padded correctly");
static_assert((sizeof(LightConstants) % 16) == 0, "CB size not padded correctly");
static_assert((sizeof(ObjectConstants) % 16) == 0, "CB size not padded correctly");
static_assert((sizeof(MiscConstants) % 16) == 0, "CB size not padded correctly");
static_assert((sizeof(BoneConstants) % 16) == 0, "CB size not padded correctly");

__declspec(align(16)) struct DXTKAPI DGSLEffectConstants
{
	MaterialConstants   material;
	LightConstants      light;
	ObjectConstants     object;
	MiscConstants       misc;
	BoneConstants       bones;
};

struct DXTKAPI DGSLEffectTraits
{
	static const int VertexShaderCount = 8;
	static const int PixelShaderCount = 12;

	static const ShaderBytecode VertexShaderBytecode[VertexShaderCount];
	static const ShaderBytecode PixelShaderBytecode[PixelShaderCount];
};

// Include the precompiled shader code.
namespace
{
#if defined(_XBOX_ONE) && defined(_TITLE)
    // VS
    #include "Shaders/Compiled/XboxOneDGSLEffect_main.inc"
    #include "Shaders/Compiled/XboxOneDGSLEffect_mainVc.inc"
    #include "Shaders/Compiled/XboxOneDGSLEffect_main1Bones.inc"
    #include "Shaders/Compiled/XboxOneDGSLEffect_main1BonesVc.inc"
    #include "Shaders/Compiled/XboxOneDGSLEffect_main2Bones.inc"
    #include "Shaders/Compiled/XboxOneDGSLEffect_main2BonesVc.inc"
    #include "Shaders/Compiled/XboxOneDGSLEffect_main4Bones.inc"
    #include "Shaders/Compiled/XboxOneDGSLEffect_main4BonesVc.inc"

    // PS
    #include "Shaders/Compiled/XboxOneDGSLUnlit_main.inc"
    #include "Shaders/Compiled/XboxOneDGSLLambert_main.inc"
    #include "Shaders/Compiled/XboxOneDGSLPhong_main.inc"

    #include "Shaders/Compiled/XboxOneDGSLUnlit_mainTk.inc"
    #include "Shaders/Compiled/XboxOneDGSLLambert_mainTk.inc"
    #include "Shaders/Compiled/XboxOneDGSLPhong_mainTk.inc"

    #include "Shaders/Compiled/XboxOneDGSLUnlit_mainTx.inc"
    #include "Shaders/Compiled/XboxOneDGSLLambert_mainTx.inc"
    #include "Shaders/Compiled/XboxOneDGSLPhong_mainTx.inc"

    #include "Shaders/Compiled/XboxOneDGSLUnlit_mainTxTk.inc"
    #include "Shaders/Compiled/XboxOneDGSLLambert_mainTxTk.inc"
    #include "Shaders/Compiled/XboxOneDGSLPhong_mainTxTk.inc"
#else
    // VS
    #include "Shaders/Compiled/DGSLEffect_main.inc"
    #include "Shaders/Compiled/DGSLEffect_mainVc.inc"
    #include "Shaders/Compiled/DGSLEffect_main1Bones.inc"
    #include "Shaders/Compiled/DGSLEffect_main1BonesVc.inc"
    #include "Shaders/Compiled/DGSLEffect_main2Bones.inc"
    #include "Shaders/Compiled/DGSLEffect_main2BonesVc.inc"
    #include "Shaders/Compiled/DGSLEffect_main4Bones.inc"
    #include "Shaders/Compiled/DGSLEffect_main4BonesVc.inc"

    // PS
    #include "Shaders/Compiled/DGSLUnlit_main.inc"
    #include "Shaders/Compiled/DGSLLambert_main.inc"
    #include "Shaders/Compiled/DGSLPhong_main.inc"

    #include "Shaders/Compiled/DGSLUnlit_mainTk.inc"
    #include "Shaders/Compiled/DGSLLambert_mainTk.inc"
    #include "Shaders/Compiled/DGSLPhong_mainTk.inc"

    #include "Shaders/Compiled/DGSLUnlit_mainTx.inc"
    #include "Shaders/Compiled/DGSLLambert_mainTx.inc"
    #include "Shaders/Compiled/DGSLPhong_mainTx.inc"

    #include "Shaders/Compiled/DGSLUnlit_mainTxTk.inc"
    #include "Shaders/Compiled/DGSLLambert_mainTxTk.inc"
    #include "Shaders/Compiled/DGSLPhong_mainTxTk.inc"
#endif
}

DXTKAPI const ShaderBytecode DGSLEffectTraits::VertexShaderBytecode[] =
{
	{ DGSLEffect_main, sizeof(DGSLEffect_main) },
	{ DGSLEffect_mainVc, sizeof(DGSLEffect_mainVc) },
	{ DGSLEffect_main1Bones, sizeof(DGSLEffect_main1Bones) },
	{ DGSLEffect_main1BonesVc, sizeof(DGSLEffect_main1BonesVc) },
	{ DGSLEffect_main2Bones, sizeof(DGSLEffect_main2Bones) },
	{ DGSLEffect_main2BonesVc, sizeof(DGSLEffect_main2BonesVc) },
	{ DGSLEffect_main4Bones, sizeof(DGSLEffect_main4Bones) },
	{ DGSLEffect_main4BonesVc, sizeof(DGSLEffect_main4BonesVc) },
};

DXTKAPI const ShaderBytecode DGSLEffectTraits::PixelShaderBytecode[] =
{
	{ DGSLUnlit_main, sizeof(DGSLUnlit_main) },             // UNLIT (no texture)
	{ DGSLLambert_main, sizeof(DGSLLambert_main) },         // LAMBERT (no texture)
	{ DGSLPhong_main, sizeof(DGSLPhong_main) },             // PHONG (no texture)

	{ DGSLUnlit_mainTx, sizeof(DGSLUnlit_mainTx) },         // UNLIT (textured)
	{ DGSLLambert_mainTx, sizeof(DGSLLambert_mainTx) },     // LAMBERT (textured)
	{ DGSLPhong_mainTx, sizeof(DGSLPhong_mainTx) },         // PHONG (textured)

	{ DGSLUnlit_mainTk, sizeof(DGSLUnlit_mainTk) },         // UNLIT (no texture, discard)
	{ DGSLLambert_mainTk, sizeof(DGSLLambert_mainTk) },     // LAMBERT (no texture, discard)
	{ DGSLPhong_mainTk, sizeof(DGSLPhong_mainTk) },         // PHONG (no texture, discard)

	{ DGSLUnlit_mainTxTk, sizeof(DGSLUnlit_mainTxTk) },     // UNLIT (textured, discard)
	{ DGSLLambert_mainTxTk, sizeof(DGSLLambert_mainTxTk) }, // LAMBERT (textured, discard)
	{ DGSLPhong_mainTxTk, sizeof(DGSLPhong_mainTxTk) },     // PHONG (textured, discard)
};

class DXTKAPI DGSLEffect::Impl : public AlignedNew<DGSLEffectConstants>
{
public:
	 Impl(_In_ ID3D11Device* device, _In_opt_ ID3D11PixelShader* pixelShader, _In_ bool enableSkinning) :
		dirtyFlags(INT_MAX),
		vertexColorEnabled(false),
		textureEnabled(false),
		specularEnabled(false),
		alphaDiscardEnabled(false),
		weightsPerVertex(enableSkinning ? 4 : 0),
		mPixelShader(pixelShader),
		mCBMaterial(device),
		mCBLight(device),
		mCBObject(device),
		mCBMisc(device),
		mDeviceResources(deviceResourcesPool.DemandCreate(device))
	{
		static_assert(_countof(DGSLEffectTraits::VertexShaderBytecode) == DGSLEffectTraits::VertexShaderCount, "array/max mismatch");
		static_assert(_countof(DGSLEffectTraits::PixelShaderBytecode) == DGSLEffectTraits::PixelShaderCount, "array/max mismatch");

		memset(&constants, 0, sizeof(constants));

		XMMATRIX id = XMMatrixIdentity();
		world = id;
		view = id;
		projection = id;
		constants.material.Specular = g_XMOne;
		constants.material.SpecularPower = 16;
		constants.object.UvTransform4x4 = id;

		static_assert(MaxDirectionalLights == 4, "Mismatch with DGSL pipline");
		for (int i = 0; i < MaxDirectionalLights; ++i)
		{
			lightEnabled[i] = (i == 0);
			lightDiffuseColor[i] = g_XMZero;
			lightSpecularColor[i] = g_XMOne;

			constants.light.LightDirection[i] = g_XMNegIdentityR1;
			constants.light.LightColor[i] = lightEnabled[i] ? lightDiffuseColor[i] : g_XMZero;
			constants.light.LightSpecularIntensity[i] = lightEnabled[i] ? lightSpecularColor[i] : g_XMZero;
		}

		if (enableSkinning)
		{
			mCBBone.Create(device);

			for (size_t j = 0; j < MaxBones; ++j)
			{
				constants.bones.Bones[j][0] = g_XMIdentityR0;
				constants.bones.Bones[j][1] = g_XMIdentityR1;
				constants.bones.Bones[j][2] = g_XMIdentityR2;
			}
		}
	}

	// Methods
	 void Apply(_In_ ID3D11DeviceContext* deviceContext);
	 void GetVertexShaderBytecode(_Out_ void const** pShaderByteCode, _Out_ size_t* pByteCodeLength);

	// Fields
	DGSLEffectConstants constants;

	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;

	bool lightEnabled[MaxDirectionalLights];
	XMVECTOR lightDiffuseColor[MaxDirectionalLights];
	XMVECTOR lightSpecularColor[MaxDirectionalLights];

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textures[MaxTextures];

	int dirtyFlags;

	bool vertexColorEnabled;
	bool textureEnabled;
	bool specularEnabled;
	bool alphaDiscardEnabled;
	int weightsPerVertex;

private:
	ConstantBuffer<MaterialConstants>           mCBMaterial;
	ConstantBuffer<LightConstants>              mCBLight;
	ConstantBuffer<ObjectConstants>             mCBObject;
	ConstantBuffer<MiscConstants>               mCBMisc;
	ConstantBuffer<BoneConstants>               mCBBone;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>   mPixelShader;

	 int GetCurrentVSPermutation() const;
	 int GetCurrentPSPermutation() const;

	// Only one of these helpers is allocated per D3D device, even if there are multiple effect instances.
	 class DXTKAPI DeviceResources : protected EffectDeviceResources
	{
	public:
		 DeviceResources(_In_ ID3D11Device* device) : EffectDeviceResources(device) {}

		// Gets or lazily creates the vertex shader.
		 ID3D11VertexShader* GetVertexShader(int permutation)
		{
			assert(permutation < DGSLEffectTraits::VertexShaderCount);

			return DemandCreateVertexShader(mVertexShaders[permutation], DGSLEffectTraits::VertexShaderBytecode[permutation]);
		}

		// Gets or lazily creates the specified pixel shader permutation.
		 ID3D11PixelShader* GetPixelShader(int permutation)
		{
			assert(permutation < DGSLEffectTraits::PixelShaderCount);

			return DemandCreatePixelShader(mPixelShaders[permutation], DGSLEffectTraits::PixelShaderBytecode[permutation]);
		}

		// Gets or lazily creates the default texture
		 ID3D11ShaderResourceView* GetDefaultTexture() { return EffectDeviceResources::GetDefaultTexture(); }

	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShaders[DGSLEffectTraits::VertexShaderCount];
		Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShaders[DGSLEffectTraits::PixelShaderCount];
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mDefaultTexture;
	};

	// Per-device resources.
	std::shared_ptr<DeviceResources> mDeviceResources;

	static SharedResourcePool<ID3D11Device*, DeviceResources> deviceResourcesPool;
};

DXTKAPI SharedResourcePool<ID3D11Device*, DGSLEffect::Impl::DeviceResources> DGSLEffect::Impl::deviceResourcesPool;

DXTKAPI void DGSLEffect::Impl::Apply(_In_ ID3D11DeviceContext* deviceContext)
{
	auto vertexShader = mDeviceResources->GetVertexShader(GetCurrentVSPermutation());
	auto pixelShader = mPixelShader.Get();
	if (!pixelShader)
	{
		pixelShader = mDeviceResources->GetPixelShader(GetCurrentPSPermutation());
	}

	deviceContext->VSSetShader(vertexShader, nullptr, 0);
	deviceContext->PSSetShader(pixelShader, nullptr, 0);

	// Check for any required matrices updates
	if (dirtyFlags & EffectDirtyFlags::WorldViewProj)
	{
		constants.object.LocalToWorld4x4 = XMMatrixTranspose(world);
		constants.object.WorldToView4x4 = XMMatrixTranspose(view);

		XMMATRIX worldView = XMMatrixMultiply(world, view);

		constants.object.LocalToProjected4x4 = XMMatrixTranspose(XMMatrixMultiply(worldView, projection));

		dirtyFlags &= ~EffectDirtyFlags::WorldViewProj;
		dirtyFlags |= EffectDirtyFlags::ConstantBufferObject;
	}

	if (dirtyFlags & EffectDirtyFlags::WorldInverseTranspose)
	{
		XMMATRIX worldInverse = XMMatrixInverse(nullptr, world);

		constants.object.WorldToLocal4x4 = XMMatrixTranspose(worldInverse);

		dirtyFlags &= ~EffectDirtyFlags::WorldInverseTranspose;
		dirtyFlags |= EffectDirtyFlags::ConstantBufferObject;
	}

	if (dirtyFlags & EffectDirtyFlags::EyePosition)
	{
		XMMATRIX viewInverse = XMMatrixInverse(nullptr, view);

		constants.object.EyePosition = viewInverse.r[3];

		dirtyFlags &= ~EffectDirtyFlags::EyePosition;
		dirtyFlags |= EffectDirtyFlags::ConstantBufferObject;
	}

	// Make sure the constant buffers are up to date.
	if (dirtyFlags & EffectDirtyFlags::ConstantBufferMaterial)
	{
		mCBMaterial.SetData(deviceContext, constants.material);

		dirtyFlags &= ~EffectDirtyFlags::ConstantBufferMaterial;
	}

	if (dirtyFlags & EffectDirtyFlags::ConstantBufferLight)
	{
		mCBLight.SetData(deviceContext, constants.light);

		dirtyFlags &= ~EffectDirtyFlags::ConstantBufferLight;
	}

	if (dirtyFlags & EffectDirtyFlags::ConstantBufferObject)
	{
		mCBObject.SetData(deviceContext, constants.object);

		dirtyFlags &= ~EffectDirtyFlags::ConstantBufferObject;
	}

	if (dirtyFlags & EffectDirtyFlags::ConstantBufferMisc)
	{
		mCBMisc.SetData(deviceContext, constants.misc);

		dirtyFlags &= ~EffectDirtyFlags::ConstantBufferMisc;
	}

	if (weightsPerVertex > 0)
	{
		if (dirtyFlags & EffectDirtyFlags::ConstantBufferBones)
		{
			mCBBone.SetData(deviceContext, constants.bones);

			dirtyFlags &= ~EffectDirtyFlags::ConstantBufferBones;
		}

		ID3D11Buffer* buffers[5] = { mCBMaterial.GetBuffer(), mCBLight.GetBuffer(), mCBObject.GetBuffer(),
			mCBMisc.GetBuffer(), mCBBone.GetBuffer() };

		deviceContext->VSSetConstantBuffers(0, 5, buffers);
		deviceContext->PSSetConstantBuffers(0, 4, buffers);
	}
	else
	{
		ID3D11Buffer* buffers[4] = { mCBMaterial.GetBuffer(), mCBLight.GetBuffer(), mCBObject.GetBuffer(), mCBMisc.GetBuffer() };

		deviceContext->VSSetConstantBuffers(0, 4, buffers);
		deviceContext->PSSetConstantBuffers(0, 4, buffers);
	}

	// Set the textures
	if (textureEnabled)
	{
		ID3D11ShaderResourceView* txt[MaxTextures] = { textures[0].Get(), textures[1].Get(), textures[2].Get(), textures[3].Get(),
			textures[4].Get(), textures[5].Get(), textures[6].Get(), textures[7].Get() };
		deviceContext->PSSetShaderResources(0, MaxTextures, txt);
	}
	else
	{
		ID3D11ShaderResourceView* txt[MaxTextures] = { mDeviceResources->GetDefaultTexture(), 0 };
		deviceContext->PSSetShaderResources(0, MaxTextures, txt);
	}
}

DXTKAPI void DGSLEffect::Impl::GetVertexShaderBytecode(_Out_ void const** pShaderByteCode, _Out_ size_t* pByteCodeLength)
{
	int permutation = GetCurrentVSPermutation();

	assert(permutation < DGSLEffectTraits::VertexShaderCount);

	auto shader = DGSLEffectTraits::VertexShaderBytecode[permutation];
	*pShaderByteCode = shader.code;
	*pByteCodeLength = shader.length;
}

DXTKAPI int DGSLEffect::Impl::GetCurrentVSPermutation() const
{
	int permutation = (vertexColorEnabled) ? 1 : 0;

	if (weightsPerVertex > 0)
	{
		// Evaluate 1, 2, or 4 weights per vertex?
		permutation += 2;

		if (weightsPerVertex == 2)
		{
			permutation += 2;
		}
		else if (weightsPerVertex == 4)
		{
			permutation += 4;
		}
	}

	return permutation;
}

DXTKAPI int DGSLEffect::Impl::GetCurrentPSPermutation() const
{
	int permutation = 0;

	if (constants.light.ActiveLights > 0)
	{
		permutation = (specularEnabled) ? 2 : 1;
	}

	if (textureEnabled)
		permutation += 3;

	if (alphaDiscardEnabled)
		permutation += 6;

	return permutation;
}

//--------------------------------------------------------------------------------------
// DGSLEffect
//--------------------------------------------------------------------------------------

DXTKAPI DGSLEffect::DGSLEffect(_In_ ID3D11Device* device, _In_opt_ ID3D11PixelShader* pixelShader, _In_ bool enableSkinning)
: pImpl(new Impl(device, pixelShader, enableSkinning))
{
}

DXTKAPI DGSLEffect::DGSLEffect(DGSLEffect&& moveFrom)
: pImpl(std::move(moveFrom.pImpl))
{
}

DXTKAPI DGSLEffect& DGSLEffect::operator= (DGSLEffect&& moveFrom)
{
	pImpl = std::move(moveFrom.pImpl);
	return *this;
}

DXTKAPI DGSLEffect::~DGSLEffect()
{
}

// IEffect methods
DXTKAPI void DGSLEffect::Apply(_In_ ID3D11DeviceContext* deviceContext)
{
	pImpl->Apply(deviceContext);
}

DXTKAPI void DGSLEffect::GetVertexShaderBytecode(_Out_ void const** pShaderByteCode, _Out_ size_t* pByteCodeLength)
{
	pImpl->GetVertexShaderBytecode(pShaderByteCode, pByteCodeLength);
}

// Camera settings
DXTKAPI void XM_CALLCONV DGSLEffect::SetWorld(FXMMATRIX value)
{
	pImpl->world = value;

	pImpl->dirtyFlags |= EffectDirtyFlags::WorldViewProj | EffectDirtyFlags::WorldInverseTranspose;
}

DXTKAPI void XM_CALLCONV DGSLEffect::SetView(FXMMATRIX value)
{
	pImpl->view = value;

	pImpl->dirtyFlags |= EffectDirtyFlags::WorldViewProj | EffectDirtyFlags::EyePosition;
}

DXTKAPI void XM_CALLCONV DGSLEffect::SetProjection(FXMMATRIX value)
{
	pImpl->projection = value;

	pImpl->dirtyFlags |= EffectDirtyFlags::WorldViewProj;
}

// Material settings
DXTKAPI void XM_CALLCONV DGSLEffect::SetAmbientColor(FXMVECTOR value)
{
	pImpl->constants.material.Ambient = value;

	pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferMaterial;
}

DXTKAPI void XM_CALLCONV DGSLEffect::SetDiffuseColor(FXMVECTOR value)
{
	pImpl->constants.material.Diffuse = value;

	pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferMaterial;
}

DXTKAPI void XM_CALLCONV DGSLEffect::SetEmissiveColor(FXMVECTOR value)
{
	pImpl->constants.material.Emissive = value;

	pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferMaterial;
}

DXTKAPI void XM_CALLCONV DGSLEffect::SetSpecularColor(FXMVECTOR value)
{
	pImpl->specularEnabled = true;
	pImpl->constants.material.Specular = value;

	pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferMaterial;
}

DXTKAPI void DGSLEffect::SetSpecularPower(float value)
{
	pImpl->specularEnabled = true;
	pImpl->constants.material.SpecularPower = value;

	pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferMaterial;
}

DXTKAPI void DGSLEffect::DisableSpecular()
{
	pImpl->specularEnabled = false;
	pImpl->constants.material.Specular = g_XMZero;
	pImpl->constants.material.SpecularPower = 1.f;

	pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferMaterial;
}

DXTKAPI void DGSLEffect::SetAlpha(float value)
{
	// Set w to new value, but preserve existing xyz (diffuse color).
	pImpl->constants.material.Diffuse = XMVectorSetW(pImpl->constants.material.Diffuse, value);

	pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferMaterial;
}

// Additional settings.
DXTKAPI void XM_CALLCONV DGSLEffect::SetUVTransform(FXMMATRIX value)
{
	pImpl->constants.object.UvTransform4x4 = XMMatrixTranspose(value);

	pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferObject;
}

DXTKAPI void DGSLEffect::SetViewport(float width, float height)
{
	pImpl->constants.misc.ViewportWidth = width;
	pImpl->constants.misc.ViewportHeight = height;

	pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferMisc;
}

DXTKAPI void DGSLEffect::SetTime(float time)
{
	pImpl->constants.misc.Time = time;

	pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferMisc;
}

DXTKAPI void DGSLEffect::SetAlphaDiscardEnable(bool value)
{
	pImpl->alphaDiscardEnabled = value;
}

// Light settings
DXTKAPI void DGSLEffect::SetLightingEnabled(bool value)
{
	if (value)
	{
		if (!pImpl->constants.light.ActiveLights)
			pImpl->constants.light.ActiveLights = 1;
	}
	else
	{
		pImpl->constants.light.ActiveLights = 0;
	}

	pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferLight;
}

DXTKAPI void DGSLEffect::SetPerPixelLighting(bool)
{
	// Unsupported interface method.
}

DXTKAPI void XM_CALLCONV DGSLEffect::SetAmbientLightColor(FXMVECTOR value)
{
	pImpl->constants.light.Ambient = value;

	pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferLight;
}

DXTKAPI void DGSLEffect::SetLightEnabled(int whichLight, bool value)
{
	if (whichLight < 0 || whichLight >= MaxDirectionalLights)
		throw std::out_of_range("whichLight parameter out of range");

	if (pImpl->lightEnabled[whichLight] == value)
		return;

	pImpl->lightEnabled[whichLight] = value;

	if (value)
	{
		if (whichLight >= (int)pImpl->constants.light.ActiveLights)
			pImpl->constants.light.ActiveLights = static_cast<UINT>(whichLight + 1);

		pImpl->constants.light.LightColor[whichLight] = pImpl->lightDiffuseColor[whichLight];
		pImpl->constants.light.LightSpecularIntensity[whichLight] = pImpl->lightSpecularColor[whichLight];
	}
	else
	{
		pImpl->constants.light.LightColor[whichLight] =
			pImpl->constants.light.LightSpecularIntensity[whichLight] = g_XMZero;
	}

	pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferLight;
}

DXTKAPI void XM_CALLCONV DGSLEffect::SetLightDirection(int whichLight, FXMVECTOR value)
{
	if (whichLight < 0 || whichLight >= MaxDirectionalLights)
		throw std::out_of_range("whichLight parameter out of range");

	// DGSL effects lights do not negate the direction like BasicEffect
	pImpl->constants.light.LightDirection[whichLight] = XMVectorNegate(value);

	pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferLight;
}

DXTKAPI void XM_CALLCONV DGSLEffect::SetLightDiffuseColor(int whichLight, FXMVECTOR value)
{
	if (whichLight < 0 || whichLight >= MaxDirectionalLights)
		throw std::out_of_range("whichLight parameter out of range");

	pImpl->lightDiffuseColor[whichLight] = value;

	if (pImpl->lightEnabled[whichLight])
	{
		pImpl->constants.light.LightColor[whichLight] = value;

		pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferLight;
	}
}

DXTKAPI void XM_CALLCONV DGSLEffect::SetLightSpecularColor(int whichLight, FXMVECTOR value)
{
	if (whichLight < 0 || whichLight >= MaxDirectionalLights)
		throw std::out_of_range("whichLight parameter out of range");

	pImpl->lightSpecularColor[whichLight] = value;

	if (pImpl->lightEnabled[whichLight])
	{
		pImpl->constants.light.LightSpecularIntensity[whichLight] = value;

		pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferLight;
	}
}

DXTKAPI void DGSLEffect::EnableDefaultLighting()
{
	EffectLights::EnableDefaultLighting(this);
}

// Vertex color setting.
DXTKAPI void DGSLEffect::SetVertexColorEnabled(bool value)
{
	pImpl->vertexColorEnabled = value;
}

// Texture settings
DXTKAPI void DGSLEffect::SetTextureEnabled(bool value)
{
	pImpl->textureEnabled = value;
}

DXTKAPI void DGSLEffect::SetTexture(_In_opt_ ID3D11ShaderResourceView* value)
{
	pImpl->textures[0] = value;
}

DXTKAPI void DGSLEffect::SetTexture(int whichTexture, _In_opt_ ID3D11ShaderResourceView* value)
{
	if (whichTexture < 0 || whichTexture >= MaxTextures)
		throw std::out_of_range("whichTexture parameter out of range");

	pImpl->textures[whichTexture] = value;
}

// Animation setting
DXTKAPI void DGSLEffect::SetWeightsPerVertex(int value)
{
	if (!pImpl->weightsPerVertex)
	{
		// Safe to ignore since it's only an optimization hint
		return;
	}

	if ((value != 1) &&
		(value != 2) &&
		(value != 4))
	{
		throw std::out_of_range("WeightsPerVertex must be 1, 2, or 4");
	}

	pImpl->weightsPerVertex = value;
}

DXTKAPI void DGSLEffect::SetBoneTransforms(_In_reads_(count) XMMATRIX const* value, size_t count)
{
	if (!pImpl->weightsPerVertex)
		throw std::exception("Skinning not enabled for this effect");

	if (count > MaxBones)
		throw std::out_of_range("count parameter out of range");

	auto boneConstant = pImpl->constants.bones.Bones;

	for (size_t i = 0; i < count; i++)
	{
		XMMATRIX boneMatrix = XMMatrixTranspose(value[i]);

		boneConstant[i][0] = boneMatrix.r[0];
		boneConstant[i][1] = boneMatrix.r[1];
		boneConstant[i][2] = boneMatrix.r[2];
	}

	pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferBones;
}

DXTKAPI void DGSLEffect::ResetBoneTransforms()
{
	if (!pImpl->weightsPerVertex)
	{
		// Safe to ignore since it just returns things back to default settings
		return;
	}

	auto boneConstant = pImpl->constants.bones.Bones;

	XMMATRIX id = XMMatrixIdentity();

	for (size_t i = 0; i < MaxBones; ++i)
	{
		boneConstant[i][0] = g_XMIdentityR0;
		boneConstant[i][1] = g_XMIdentityR1;
		boneConstant[i][2] = g_XMIdentityR2;
	}

	pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBufferBones;
}

#ifdef __cplusplus
EXTERN_CC_END
#endif