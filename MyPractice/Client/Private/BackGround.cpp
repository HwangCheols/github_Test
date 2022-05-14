#include "stdafx.h"
#include "..\Public\BackGround.h"
#include "GameInstance.h"

CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CBackGround::CBackGround(const CBackGround & Prototype)
	: CGameObject(Prototype)
{
}

/* 원형객체의 초기화과정을 거친다. */
HRESULT CBackGround::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	/* 서버나 파일을 통해서 데이터 초기화를 거치낟. */

	return S_OK;
}

/* 사본객체의 추가적인 초기화과정을 거친다. */
HRESULT CBackGround::NativeConstruct(void* pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	return S_OK;
}

void CBackGround::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CBackGround::LateTick(_float fTimeDelta)
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	//m_vPosition += _float3(0.f, 0.f, 1.f) * 1.0f * fTimeDelta;


	

	__super::LateTick(fTimeDelta);

	
	pGameInstance->Add_RenderGroup(CRenderer::RENDER_PRIORITY, this);

	Safe_Release(pGameInstance);
}

HRESULT CBackGround::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	_float4x4		WorldMatrix, ViewMatrix, ProjMatrix;

	D3DXMatrixIdentity(&WorldMatrix);
	memcpy(&WorldMatrix.m[3][0], &m_vPosition, sizeof(_float3));	
	m_pGraphic_Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

	D3DXMatrixLookAtLH(&ViewMatrix, &_float3(0.f, 5.f, -4.0f), &_float3(0.f, 0.f, 0.f), &_float3(0.f, 1.f, 0.f));
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &ViewMatrix);

	D3DXMatrixPerspectiveFovLH(&ProjMatrix, D3DXToRadian(60.0f), _float(g_iWinSizeX) / g_iWinSizeY, 0.2f, 300.f);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &ProjMatrix);

	m_pTextureCom->Bind_Texture(0);

	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CBackGround::SetUp_Components()
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	m_pVIBufferCom = (CVIBuffer_Rect*)pGameInstance->Clone_Component(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"));
	if (nullptr == m_pVIBufferCom)
		return E_FAIL;

	m_pTextureCom = (CTexture*)pGameInstance->Clone_Component(LEVEL_LOGO, TEXT("Prototype_Component_Texture_Logo"));	//로더에서 로딩for 로고 함수에서 원형 생성을 로고로 해서 다른 레벨 넣으면 원형이 없으니 클론이 널 들어가는거였음
	if (nullptr == m_pTextureCom)
		return E_FAIL;
	
	Safe_Release(pGameInstance);

	return S_OK;
}

CBackGround * CBackGround::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBackGround*		pInstance = new CBackGround(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CBackGround::Clone(void* pArg)
{
	CBackGround*		pInstance = new CBackGround(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}
	return pInstance;
}


void CBackGround::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pVIBufferCom);
}
