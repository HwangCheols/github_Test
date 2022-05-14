#pragma once

#include "Client_Defines.h"
#include "Base.h"


BEGIN(Engine)
class CGameInstance;
END

BEGIN(Client)
class CMainApp final : public CBase
{
private:
	CMainApp();
	virtual ~CMainApp() = default;

public:
	HRESULT NativeConstruct();
	void Tick(float fTimeDelta);
	HRESULT Render();

private:
	CGameInstance*				m_pGameInstance = nullptr;
	LPDIRECT3DDEVICE9			m_pGraphic_Device = nullptr;

#ifdef _DEBUG
private:
	_tchar					m_szFPS[MAX_PATH];
	_uint					m_iNumRender = 0;
	_float					m_fTimeAcc = 0.f;
#endif // _DEBUG


private:
	HRESULT Open_Level(LEVEL eLevel);
	HRESULT Ready_RenderState();
	HRESULT Ready_Prototype_Component_Static();

public:
	static CMainApp* Create();
	virtual void Free() override;
};

END