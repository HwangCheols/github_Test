#pragma once

/* 네모를 구성한다. */

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Rect final : public CVIBuffer
{
private:
	explicit CVIBuffer_Rect(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CVIBuffer_Rect(const CVIBuffer_Rect& Prototype);
	virtual ~CVIBuffer_Rect() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);

public:
	static CVIBuffer_Rect* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg);
	virtual void Free();
};

END