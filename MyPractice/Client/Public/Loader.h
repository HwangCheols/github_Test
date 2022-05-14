#pragma once

#include "Client_Defines.h"
#include "Base.h"

/* 생성한 스레드로 */
/* 다음할당될 레벨의 자원들을 로드한다.  */

BEGIN(Client)

class CLoader final : public CBase
{
private:
	CLoader(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLoader() = default;

public:
	LEVEL Get_NextLevelID() {
		return m_eNextLevel;
	}

	CRITICAL_SECTION* Get_CriticalSection() {
		return &m_CriticalSection;
	}

	const _tchar* Get_LoadingText() {
		return m_szLoading;
	}

	_bool isFinished() {
		return m_isFinished;
	}

public:
	HRESULT NativeConstruct(LEVEL eNextLevel);

public:
	HRESULT Loading_ForLogoLevel();
	HRESULT Loading_ForGamePlayLevel();

private:
	LPDIRECT3DDEVICE9	m_pGraphic_Device = nullptr;
	_bool				m_isFinished = false;
	LEVEL				m_eNextLevel = LEVEL_END;
	_tchar				m_szLoading[MAX_PATH] = TEXT("");
	
private:
	HANDLE				m_hThread = 0;
	CRITICAL_SECTION	m_CriticalSection;




public:
	static CLoader* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel);
	virtual void Free() override;
};

END