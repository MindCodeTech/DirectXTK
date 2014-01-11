//--------------------------------------------------------------------------------------
// File: Model.h
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

#pragma once

#ifdef __cplusplus
EXTERN_C_BEGIN
#endif

NAMESPACE_DirectX

class IEffect;
class IEffectFactory;
class CommonStates;
class ModelMesh;
class ModelMeshPart;
class Model;

// inserted
//typedef std::vector<std::unique_ptr<ModelMeshPart>> Collection;

// Each mesh part is a submesh with a single effect
class ModelMeshPart
{
public:
	DXTKAPI ModelMeshPart();

	uint32_t                                                indexCount;
	uint32_t                                                startIndex;
	uint32_t                                                vertexOffset;
	uint32_t                                                vertexStride;
	D3D_PRIMITIVE_TOPOLOGY                                  primitiveType;
	DXGI_FORMAT                                             indexFormat;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>               inputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer>                    indexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>                    vertexBuffer;
	std::shared_ptr<IEffect>                                effect;
	std::shared_ptr<std::vector<D3D11_INPUT_ELEMENT_DESC>>  vbDecl;
	bool                                                    isAlpha;

	typedef std::vector<std::unique_ptr<ModelMeshPart>> Collection;

	// Draw mesh part with custom effect
	DXTKAPI void Draw(_In_ ID3D11DeviceContext* deviceContext, _In_ IEffect* effect, _In_ ID3D11InputLayout* inputLayout,
		_In_opt_ std::function<void()> setCustomState = nullptr) const;

	// Create input layout for drawing with a custom effect.
	DXTKAPI void CreateInputLayout(_In_ ID3D11Device* d3dDevice, _In_ IEffect* effect, _Outptr_ ID3D11InputLayout** inputLayout);

	// Change effect used by part and regenerate input layout (be sure to call Model::Modified as well)
	DXTKAPI void ModifyEffect(_In_ ID3D11Device* d3dDevice, _In_ std::shared_ptr<IEffect>& effect, bool isalpha = false);
};

// A mesh consists of one or more model parts
class ModelMesh
{
public:
	DXTKAPI ModelMesh();

	BoundingSphere              boundingSphere;
	BoundingBox                 boundingBox;
	ModelMeshPart::Collection   meshParts;
	std::wstring                name;
	bool                        ccw;
	bool                        pmalpha;

	typedef std::vector<std::shared_ptr<ModelMesh>> Collection;

	// Setup states for drawing mesh
	DXTKAPI void PrepareForRendering(_In_ ID3D11DeviceContext* deviceContext, CommonStates& states, bool alpha = false, bool wireframe = false) const;

	// Draw the mesh
	DXTKAPI void XM_CALLCONV Draw(_In_ ID3D11DeviceContext* deviceContext, FXMMATRIX world, CXMMATRIX view, CXMMATRIX projection,
		bool alpha = false, _In_opt_ std::function<void()> setCustomState = nullptr) const;
};

// A model consists of one or more meshes
class DXTKAPI Model
{
public:
	ModelMesh::Collection   meshes;
	std::wstring            name;

	// Draw all the meshes in the model
	void XM_CALLCONV Draw(_In_ ID3D11DeviceContext* deviceContext, CommonStates& states, FXMMATRIX world, CXMMATRIX view, CXMMATRIX projection,
		bool wireframe = false, _In_opt_ std::function<void()> setCustomState = nullptr) const;

	// Notify model that effects, parts list, or mesh list has changed
	void Modified() { mEffectCache.clear(); }

	// Update all effects used by the model
	void UpdateEffects(_In_ std::function<void(IEffect*)> setEffect);

	// Loads a model from a Visual Studio Starter Kit .CMO file
	static std::unique_ptr<Model> CreateFromCMO(_In_ ID3D11Device* d3dDevice, _In_reads_bytes_(dataSize) const uint8_t* meshData, size_t dataSize,
		_In_ IEffectFactory& fxFactory, bool ccw = true, bool pmalpha = false);
	static std::unique_ptr<Model> CreateFromCMO(_In_ ID3D11Device* d3dDevice, _In_z_ const wchar_t* szFileName,
		_In_ IEffectFactory& fxFactory, bool ccw = true, bool pmalpha = false);

	// Loads a model from a DirectX SDK .SDKMESH file
	static std::unique_ptr<Model> CreateFromSDKMESH(_In_ ID3D11Device* d3dDevice, _In_reads_bytes_(dataSize) const uint8_t* meshData, _In_ size_t dataSize,
		_In_ IEffectFactory& fxFactory, bool ccw = false, bool pmalpha = false);
	static std::unique_ptr<Model> CreateFromSDKMESH(_In_ ID3D11Device* d3dDevice, _In_z_ const wchar_t* szFileName,
		_In_ IEffectFactory& fxFactory, bool ccw = false, bool pmalpha = false);

private:
	std::set<IEffect*>  mEffectCache;
};

NAMESPACE_DirectX_END

#ifdef __cplusplus
EXTERN_C_END
#endif
