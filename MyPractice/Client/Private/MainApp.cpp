#include "stdafx.h"
#include "..\Public\MainApp.h"
#include "GameInstance.h"
#include "Level_Loading.h"

CMainApp::CMainApp()
	: m_pGameInstance(CGameInstance::Get_Instance())
{
	Safe_AddRef(m_pGameInstance);


//	D3DXCOLOR			vSourColor, vDestColor;
//
////vSourColor : 내가 그릴려고했던 픽셀의 색. 
////vDestColor : 내가 픽셀을 그릴려고했던 위치에 이미 그려져있던 색. 
//
//	vSourColor.rgb * vSourColor.a  + 
//		vDestColor.rgb * (1.f - vSourColor.a) = 

	
	
}

HRESULT CMainApp::NativeConstruct()
{
	GRAPHICDESC		GraphicDesc;
	ZeroMemory(&GraphicDesc, sizeof(GRAPHICDESC));

	GraphicDesc.hWnd = g_hWnd;
	GraphicDesc.iWinCX = g_iWinSizeX;
	GraphicDesc.iWinCY = g_iWinSizeY;
	GraphicDesc.isWindowed = true;	

	if (FAILED(m_pGameInstance->Initialize_Engine(LEVEL_END, GraphicDesc, &m_pGraphic_Device)))
		return E_FAIL;

	if (FAILED(Ready_RenderState()))
		return E_FAIL;

	if (FAILED(Ready_Prototype_Component_Static()))
		return E_FAIL;

	if (FAILED(Open_Level(LEVEL_LOGO)))
		return E_FAIL;

	return S_OK;
}

void CMainApp::Tick(float fTimeDelta)
{
	if (nullptr == m_pGameInstance)
		return;

#ifdef _DEBUG
	m_fTimeAcc += fTimeDelta;
#endif // _DEBUG

	m_pGameInstance->Tick_Engine(fTimeDelta);
}

HRESULT CMainApp::Render()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	m_pGameInstance->Render_Begin();

	m_pGameInstance->Render_Engine();

	m_pGameInstance->Render_End();

	++m_iNumRender;

	if (m_fTimeAcc > 1.f)
	{
		wsprintf(m_szFPS, TEXT("FPS : %d \n"), m_iNumRender);
		SetWindowText(g_hWnd, m_szFPS);

		m_fTimeAcc = 0.f;
		m_iNumRender = 0;
	}
	return S_OK;
}

HRESULT CMainApp::Open_Level(LEVEL eLevel)
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	if (FAILED(m_pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, eLevel))))
		return E_FAIL;		

	return S_OK;
}

HRESULT CMainApp::Ready_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//m_pGraphic_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//m_pGraphic_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//m_pGraphic_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 0);


	return S_OK;
}

HRESULT CMainApp::Ready_Prototype_Component_Static()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	/* Prototype_Component_VIBuffer_Rect */
 	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"),
		CVIBuffer_Rect::Create(m_pGraphic_Device))))
		return E_FAIL;

	return S_OK;
}

CMainApp * CMainApp::Create()
{
	CMainApp*		pInstance = new CMainApp();

	if (FAILED(pInstance->NativeConstruct()))
	{		
		MSG_BOX("Failed to Created : CMainApp");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMainApp::Free()
{
	__super::Free();

	Safe_Release(m_pGameInstance);

	Safe_Release(m_pGraphic_Device);

	CGameInstance::Release_Engine();
}
