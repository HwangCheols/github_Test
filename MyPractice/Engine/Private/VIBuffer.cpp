#include "..\Public\VIBuffer.h"

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{

}

CVIBuffer::CVIBuffer(const CVIBuffer & Prototype)
	: CComponent(Prototype)
	, m_pVB(Prototype.m_pVB)
	, m_iNumVertices(Prototype.m_iNumVertices)
	, m_dwFVF(Prototype.m_dwFVF)
	, m_iStride(Prototype.m_iStride)
	, m_ePrimitiveType(Prototype.m_ePrimitiveType)
	, m_iNumPrimitive(Prototype.m_iNumPrimitive)
{
	Safe_AddRef(m_pVB);
}

HRESULT CVIBuffer::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CVIBuffer::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	return S_OK;
}

HRESULT CVIBuffer::Render()
{
	if (nullptr == m_pGraphic_Device || 
		nullptr == m_pVB)
		return E_FAIL;

	m_pGraphic_Device->SetStreamSource(0, m_pVB, 0, m_iStride);

	m_pGraphic_Device->SetFVF(m_dwFVF);

	m_pGraphic_Device->DrawPrimitive(m_ePrimitiveType, 0, m_iNumPrimitive);

	return S_OK;
}

HRESULT CVIBuffer::Create_VertexBuffer()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	/* 내가 사용하고자하는 정점들을 모두 담을 수 있는 공간을 할당한다. */
	if (FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iStride * m_iNumVertices, 0, 
		m_dwFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
		return E_FAIL;

	return S_OK;
}


void CVIBuffer::Free()
{
	__super::Free();

	Safe_Release(m_pVB);
}
