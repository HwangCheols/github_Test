#pragma once

#include "Graphic_Device.h"
#include "Level_Manager.h"
#include "Timer_Manager.h"
#include "Object_Manager.h"
#include "Component_Manager.h"
#include "Renderer.h"

/* 클라이언트로 정말 보여줘야할 함수만 모아놓는다. */
/* ㄴ클라이언트 입장에서는 엔진에 기능을 쓰고싶으면 GameIsntance만 생각하면된다. */

BEGIN(Engine)
class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance);
private:
	CGameInstance();
	virtual ~CGameInstance() = default;

public: /* For.GameInstance */
	HRESULT Initialize_Engine(_uint iNumLevels, const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut); /* 엔진의 기능을 사용하기위해 초기화가 필요한 녀석들을 초기화한다. */
	void Tick_Engine(_float fTimeDelta); /* 매프레임마다 갱신이 필요한 매니져들의 동작. */
	HRESULT Render_Engine();
	HRESULT Clear_Container(_uint iLevelIndex);

public: /* For.Graphic_Device */	
	void Render_Begin();
	void Render_End();

public: /* For.Level_Manager */
	HRESULT Open_Level(_uint iCurrentLevelIndex, class CLevel* pNextLevel);

public: /* For.Timer_Manager */
	_float Get_TimeDelta(const _tchar* pTimerTag);
	HRESULT Add_Timer(const _tchar* pTimerTag);
	void Update_Timer(const _tchar* pTimerTag);

public: /*For.Object_Manager */
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pGameObject);	
	HRESULT Clone_GameObject(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg = nullptr);

public: /* For.Component_Manager */
	HRESULT Add_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag, CComponent* pPrototype);
	CComponent* Clone_Component(_uint iLevelIndex, const _tchar* pPrototypeTag, void* pArg = nullptr);

public: /* For.Renderer */
	HRESULT Add_RenderGroup(CRenderer::RENDERGROUP eRenderGroup, class CGameObject* pGameObject);


private:
	CGraphic_Device*				m_pGraphic_Device = nullptr;
	CLevel_Manager*					m_pLevel_Manager = nullptr;
	CTimer_Manager*					m_pTimer_Manager = nullptr;
	CObject_Manager*				m_pObject_Manager = nullptr;
	CComponent_Manager*				m_pComponent_Manager = nullptr;
	CRenderer*						m_pRenderer = nullptr;

public:
	static void Release_Engine(); /* 엔진에서 사용된 각종 매니져의 메모리 정리. */

public:
	virtual void Free() override;
};

END