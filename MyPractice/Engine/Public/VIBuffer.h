#pragma once

#include "Component.h"

BEGIN(Engine)

/* 내가 특정 모델을 위해 선언한 점들을 공간할당하여 보관한다. */
class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CVIBuffer(const CVIBuffer& Prototype);
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual HRESULT Render();

protected:
	/* 정점 버퍼를 대표하는 컴객체.*/
	LPDIRECT3DVERTEXBUFFER9				m_pVB = nullptr;
	_uint								m_iNumVertices = 0; /* 정점의 갯수 */
	_uint								m_iStride = 0; /* 정점하나의 byte크기. */
	_ulong								m_dwFVF = 0;
	D3DPRIMITIVETYPE					m_ePrimitiveType;
	_uint								m_iNumPrimitive = 0;

protected:
	HRESULT Create_VertexBuffer();

public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free();
};

END