//--------------------------------------------------------------------------------------
// File: VertexTypes.h
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

#ifdef extern_cplus
extern "C" {
#endif

#ifdef extern_cplusplus
	extern "C++" {
#endif

namespace DirectX
{
    // Vertex struct holding position and color information.
    struct DXTKAPI VertexPositionColor
    {
        VertexPositionColor()
        { }

        VertexPositionColor(XMFLOAT3 const& position, XMFLOAT4 const& color)
          : position(position),
            color(color)
        { }

        VertexPositionColor(FXMVECTOR position, FXMVECTOR color)
        {
            XMStoreFloat3(&this->position, position);
            XMStoreFloat4(&this->color, color);
        }

        XMFLOAT3 position;
        XMFLOAT4 color;

        static const int InputElementCount = 2;
        static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };


    // Vertex struct holding position and texture mapping information.
    struct DXTKAPI VertexPositionTexture
    {
        VertexPositionTexture()
        { }

        VertexPositionTexture(XMFLOAT3 const& position, XMFLOAT2 const& textureCoordinate)
          : position(position),
            textureCoordinate(textureCoordinate)
        { }

        VertexPositionTexture(FXMVECTOR position, FXMVECTOR textureCoordinate)
        {
            XMStoreFloat3(&this->position, position);
            XMStoreFloat2(&this->textureCoordinate, textureCoordinate);
        }

        XMFLOAT3 position;
        XMFLOAT2 textureCoordinate;

        static const int InputElementCount = 2;
        static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };


    // Vertex struct holding position and normal vector.
    struct DXTKAPI VertexPositionNormal
    {
        VertexPositionNormal()
        { }

        VertexPositionNormal(XMFLOAT3 const& position, XMFLOAT3 const& normal)
          : position(position),
            normal(normal)
        { }

        VertexPositionNormal(FXMVECTOR position, FXMVECTOR normal)
        {
            XMStoreFloat3(&this->position, position);
            XMStoreFloat3(&this->normal, normal);
        }

        XMFLOAT3 position;
        XMFLOAT3 normal;

        static const int InputElementCount = 2;
        static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };


    // Vertex struct holding position, color, and texture mapping information.
    struct DXTKAPI VertexPositionColorTexture
    {
        VertexPositionColorTexture()
        { }

        VertexPositionColorTexture(XMFLOAT3 const& position, XMFLOAT4 const& color, XMFLOAT2 const& textureCoordinate)
          : position(position),
            color(color),
            textureCoordinate(textureCoordinate)
        { }

        VertexPositionColorTexture(FXMVECTOR position, FXMVECTOR color, FXMVECTOR textureCoordinate)
        {
            XMStoreFloat3(&this->position, position);
            XMStoreFloat4(&this->color, color);
            XMStoreFloat2(&this->textureCoordinate, textureCoordinate);
        }

        XMFLOAT3 position;
        XMFLOAT4 color;
        XMFLOAT2 textureCoordinate;

        static const int InputElementCount = 3;
        static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };


    // Vertex struct holding position, normal vector, and color information.
    struct DXTKAPI VertexPositionNormalColor
    {
        VertexPositionNormalColor()
        { }

        VertexPositionNormalColor(XMFLOAT3 const& position, XMFLOAT3 const& normal, XMFLOAT4 const& color)
          : position(position),
            normal(normal),
            color(color)
        { }

        VertexPositionNormalColor(FXMVECTOR position, FXMVECTOR normal, FXMVECTOR color)
        {
            XMStoreFloat3(&this->position, position);
            XMStoreFloat3(&this->normal, normal);
            XMStoreFloat4(&this->color, color);
        }

        XMFLOAT3 position;
        XMFLOAT3 normal;
        XMFLOAT4 color;

        static const int InputElementCount = 3;
        static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };


    // Vertex struct holding position, normal vector, and texture mapping information.
    struct DXTKAPI VertexPositionNormalTexture
    {
        VertexPositionNormalTexture()
        { }

        VertexPositionNormalTexture(XMFLOAT3 const& position, XMFLOAT3 const& normal, XMFLOAT2 const& textureCoordinate)
          : position(position),
            normal(normal),
            textureCoordinate(textureCoordinate)
        { }

        VertexPositionNormalTexture(FXMVECTOR position, FXMVECTOR normal, FXMVECTOR textureCoordinate)
        {
            XMStoreFloat3(&this->position, position);
            XMStoreFloat3(&this->normal, normal);
            XMStoreFloat2(&this->textureCoordinate, textureCoordinate);
        }

        XMFLOAT3 position;
        XMFLOAT3 normal;
        XMFLOAT2 textureCoordinate;

        static const int InputElementCount = 3;
        static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };


    // Vertex struct holding position, normal vector, color, and texture mapping information.
    struct DXTKAPI VertexPositionNormalColorTexture
    {
        VertexPositionNormalColorTexture()
        { }

        VertexPositionNormalColorTexture(XMFLOAT3 const& position, XMFLOAT3 const& normal, XMFLOAT4 const& color, XMFLOAT2 const& textureCoordinate)
          : position(position),
            normal(normal),
            color(color),
            textureCoordinate(textureCoordinate)
        { }

        VertexPositionNormalColorTexture(FXMVECTOR position, FXMVECTOR normal, FXMVECTOR color, CXMVECTOR textureCoordinate)
        {
            XMStoreFloat3(&this->position, position);
            XMStoreFloat3(&this->normal, normal);
            XMStoreFloat4(&this->color, color);
            XMStoreFloat2(&this->textureCoordinate, textureCoordinate);
        }

        XMFLOAT3 position;
        XMFLOAT3 normal;
        XMFLOAT4 color;
        XMFLOAT2 textureCoordinate;

        static const int InputElementCount = 4;
        static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };


    // Vertex struct for Visual Studio Shader Designer (DGSL) holding position, normal,
    // tangent, color (RGBA), and texture mapping information
    struct DXTKAPI VertexPositionNormalTangentColorTexture
    {
        VertexPositionNormalTangentColorTexture()
        { }

        XMFLOAT3 position;
        XMFLOAT3 normal;
        XMFLOAT4 tangent;
        uint32_t color;
        XMFLOAT2 textureCoordinate;

        VertexPositionNormalTangentColorTexture(XMFLOAT3 const& position, XMFLOAT3 const& normal, XMFLOAT4 const& tangent, uint32_t rgba, XMFLOAT2 const& textureCoordinate)
          : position(position),
            normal(normal),
            tangent(tangent),
            color(rgba),
            textureCoordinate(textureCoordinate)
        {
        }

        VertexPositionNormalTangentColorTexture(FXMVECTOR position, FXMVECTOR normal, FXMVECTOR tangent, uint32_t rgba, CXMVECTOR textureCoordinate)
          : color(rgba)
        {
            XMStoreFloat3(&this->position, position);
            XMStoreFloat3(&this->normal, normal);
            XMStoreFloat4(&this->tangent, tangent);
            XMStoreFloat2(&this->textureCoordinate, textureCoordinate);
        }

        VertexPositionNormalTangentColorTexture(XMFLOAT3 const& position, XMFLOAT3 const& normal, XMFLOAT4 const& tangent, XMFLOAT4 const& color, XMFLOAT2 const& textureCoordinate)
          : position(position),
            normal(normal),
            tangent(tangent),
            textureCoordinate(textureCoordinate)
        {
            SetColor( color );
        }

        VertexPositionNormalTangentColorTexture(FXMVECTOR position, FXMVECTOR normal, FXMVECTOR tangent, CXMVECTOR color, CXMVECTOR textureCoordinate)
        {
            XMStoreFloat3(&this->position, position);
            XMStoreFloat3(&this->normal, normal);
            XMStoreFloat4(&this->tangent, tangent);
            XMStoreFloat2(&this->textureCoordinate, textureCoordinate);

            SetColor( color );
        }

        void SetColor( XMFLOAT4 const& color ) { SetColor( XMLoadFloat4( &color ) ); }
        void XM_CALLCONV SetColor( FXMVECTOR color );

        static const int InputElementCount = 5;
        static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };


    // Vertex struct for Visual Studio Shader Designer (DGSL) holding position, normal,
    // tangent, color (RGBA), texture mapping information, and skinning weights
    struct DXTKAPI VertexPositionNormalTangentColorTextureSkinning : public VertexPositionNormalTangentColorTexture
    {
        VertexPositionNormalTangentColorTextureSkinning()
        { }

        uint32_t indices;
        uint32_t weights;

        VertexPositionNormalTangentColorTextureSkinning(XMFLOAT3 const& position, XMFLOAT3 const& normal, XMFLOAT4 const& tangent, uint32_t rgba,
                                                        XMFLOAT2 const& textureCoordinate, XMUINT4 const& indices, XMFLOAT4 const& weights)
          : VertexPositionNormalTangentColorTexture(position,normal,tangent,rgba,textureCoordinate)
        {
            SetBlendIndices( indices );
            SetBlendWeights( weights );
        }

        VertexPositionNormalTangentColorTextureSkinning(FXMVECTOR position, FXMVECTOR normal, FXMVECTOR tangent, uint32_t rgba, CXMVECTOR textureCoordinate,
                                                        XMUINT4 const& indices, CXMVECTOR weights)
          : VertexPositionNormalTangentColorTexture(position,normal,tangent,rgba,textureCoordinate)
        {
            SetBlendIndices( indices );
            SetBlendWeights( weights );
        }

        VertexPositionNormalTangentColorTextureSkinning(XMFLOAT3 const& position, XMFLOAT3 const& normal, XMFLOAT4 const& tangent, XMFLOAT4 const& color,
                                                        XMFLOAT2 const& textureCoordinate, XMUINT4 const& indices, XMFLOAT4 const& weights)
          : VertexPositionNormalTangentColorTexture(position,normal,tangent,color,textureCoordinate)
        {
            SetBlendIndices( indices );
            SetBlendWeights( weights );
        }

        VertexPositionNormalTangentColorTextureSkinning(FXMVECTOR position, FXMVECTOR normal, FXMVECTOR tangent, CXMVECTOR color, CXMVECTOR textureCoordinate,
                                                        XMUINT4 const& indices, CXMVECTOR weights)
          : VertexPositionNormalTangentColorTexture(position,normal,tangent,color,textureCoordinate)
        {
            SetBlendIndices( indices );
            SetBlendWeights( weights );
        }

        void SetBlendIndices( XMUINT4 const& indices );

        void SetBlendWeights( XMFLOAT4 const& weights ) { SetBlendWeights( XMLoadFloat4( &weights ) ); }
        void XM_CALLCONV SetBlendWeights( FXMVECTOR weights );

        static const int InputElementCount = 7;
        static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };
}

#if defined(extern_cplus) && defined(extern_cplusplus)
	}
	}
#elif defined(extern_cplus) && !defined(extern_cplusplus)
}
#elif defined(extern_cplusplus) && !defined(extern_cplus)
}
#endif
