#include "..\Public\GameInstance.h"

IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()
	: m_pGraphic_Device(CGraphic_Device::Get_Instance())
	, m_pLevel_Manager(CLevel_Manager::Get_Instance())
	, m_pTimer_Manager(CTimer_Manager::Get_Instance())
	, m_pObject_Manager(CObject_Manager::Get_Instance())
	, m_pComponent_Manager(CComponent_Manager::Get_Instance())
	, m_pRenderer(CRenderer::Get_Instance())
{
	Safe_AddRef(m_pRenderer);
	Safe_AddRef(m_pComponent_Manager);
	Safe_AddRef(m_pObject_Manager);
	Safe_AddRef(m_pTimer_Manager);
	Safe_AddRef(m_pLevel_Manager);
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CGameInstance::Initialize_Engine(_uint iNumLevels, const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut)
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	/* 그래픽 디바이스 초기화. */
	if (FAILED(m_pGraphic_Device->InitDevice(GraphicDesc, ppOut)))
		return E_FAIL;


	/* 입력 디바이스 초기화. */

	/* 사운드 디바이스 초기화. */

	/* 오브젝트 매니져 준비 */
	if (FAILED(m_pObject_Manager->Reserve_Container(iNumLevels)))
		return E_FAIL;

	/* 컴포넌트 매니져 준비 */
	if (FAILED(m_pComponent_Manager->Reserve_Container(iNumLevels)))
		return E_FAIL; 

	return S_OK;
}

void CGameInstance::Tick_Engine(_float fTimeDelta)
{
	if (nullptr == m_pLevel_Manager || 
		nullptr == m_pObject_Manager)
		return;

	/* 입력장치의 상태 조사. */
	/* 오브젝트들의 업데이트를 수행한다. */
	m_pObject_Manager->Tick(fTimeDelta);
	m_pLevel_Manager->Tick(fTimeDelta);




	m_pObject_Manager->LateTick(fTimeDelta);
	m_pLevel_Manager->LateTick(fTimeDelta);	
}

HRESULT CGameInstance::Render_Engine()
{
	if (nullptr == m_pRenderer)
		return E_FAIL;

	m_pRenderer->Draw_RenderGroup();

	return S_OK;
}

HRESULT CGameInstance::Clear_Container(_uint iLevelIndex)
{
	if (nullptr == m_pObject_Manager ||
		nullptr == m_pComponent_Manager)
		return E_FAIL;

	m_pObject_Manager->Clear(iLevelIndex);
	m_pComponent_Manager->Clear(iLevelIndex);


	return S_OK;
}

void CGameInstance::Render_Begin()
{
	if (nullptr == m_pGraphic_Device)
		return;

	m_pGraphic_Device->Render_Begin();
}

void CGameInstance::Render_End()
{
	if (nullptr == m_pGraphic_Device)
		return;

	m_pGraphic_Device->Render_End();
}

HRESULT CGameInstance::Open_Level(_uint iCurrentLevelIndex, CLevel * pNextLevel)
{
	if (nullptr == m_pLevel_Manager)
		return E_FAIL;

	return m_pLevel_Manager->Change_Level(iCurrentLevelIndex, pNextLevel);	
}

_float CGameInstance::Get_TimeDelta(const _tchar * pTimerTag)
{
	if (nullptr == m_pTimer_Manager)
		return 0.f;

	return m_pTimer_Manager->Get_TimeDelta(pTimerTag);	
}

HRESULT CGameInstance::Add_Timer(const _tchar * pTimerTag)
{
	if (nullptr == m_pTimer_Manager)
		return E_FAIL;

	return m_pTimer_Manager->Add_Timer(pTimerTag);
}

void CGameInstance::Update_Timer(const _tchar * pTimerTag)
{
	if (nullptr == m_pTimer_Manager)
		return;

	m_pTimer_Manager->Update(pTimerTag);
}

HRESULT CGameInstance::Add_Prototype(const _tchar * pPrototypeTag, CGameObject * pGameObject)
{
	if (nullptr == m_pObject_Manager)
		return E_FAIL;

	return m_pObject_Manager->Add_Prototype(pPrototypeTag, pGameObject);	
}

HRESULT CGameInstance::Clone_GameObject(_uint iLevelIndex, const _tchar * pLayerTag, const _tchar * pPrototypeTag, void * pArg)
{
	if (nullptr == m_pObject_Manager)
		return E_FAIL;

	return m_pObject_Manager->Clone_GameObject(iLevelIndex, pLayerTag, pPrototypeTag, pArg);
}

HRESULT CGameInstance::Add_Prototype(_uint iLevelIndex, const _tchar * pPrototypeTag, CComponent * pPrototype)
{
	if(nullptr == m_pComponent_Manager)
		return E_FAIL;	

	return m_pComponent_Manager->Add_Prototype(iLevelIndex, pPrototypeTag, pPrototype);
}

CComponent * CGameInstance::Clone_Component(_uint iLevelIndex, const _tchar * pPrototypeTag, void * pArg)
{
	if (nullptr == m_pComponent_Manager)
		return nullptr;

	return m_pComponent_Manager->Clone_Component(iLevelIndex, pPrototypeTag, pArg);
}

HRESULT CGameInstance::Add_RenderGroup(CRenderer::RENDERGROUP eRenderGroup, CGameObject * pGameObject)
{
	if (nullptr == m_pRenderer)
		return E_FAIL;

	return m_pRenderer->Add_RenderGroup(eRenderGroup, pGameObject);	
}

void CGameInstance::Release_Engine()
{	
	CGameInstance::Get_Instance()->Destroy_Instance();

	CRenderer::Get_Instance()->Destroy_Instance();

	CObject_Manager::Get_Instance()->Destroy_Instance();

	CComponent_Manager::Get_Instance()->Destroy_Instance();

	CLevel_Manager::Get_Instance()->Destroy_Instance();

	CTimer_Manager::Get_Instance()->Destroy_Instance();

	CGraphic_Device::Get_Instance()->Destroy_Instance();

}

void CGameInstance::Free()
{
	Safe_Release(m_pRenderer);
	Safe_Release(m_pComponent_Manager);
	Safe_Release(m_pObject_Manager);
	Safe_Release(m_pTimer_Manager);
	Safe_Release(m_pLevel_Manager);
	Safe_Release(m_pGraphic_Device);
}



