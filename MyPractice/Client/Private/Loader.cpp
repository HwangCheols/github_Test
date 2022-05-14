#include "stdafx.h"
#include "..\Public\Loader.h"
#include "GameInstance.h"
#include "BackGround.h"

CLoader::CLoader(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}


/*
typedef unsigned (__stdcall  *_beginthreadex_proc_type)(void*);
*/

unsigned int APIENTRY ThreadEntryFunc(void* pArg)
{
	

	CLoader*		pLoader = (CLoader*)pArg;

	EnterCriticalSection(pLoader->Get_CriticalSection());

	/* 자원로드할꺼야. */
	switch (pLoader->Get_NextLevelID())
	{
	case LEVEL_LOGO:
		pLoader->Loading_ForLogoLevel();
		break;
	case LEVEL_GAMEPLAY:
		pLoader->Loading_ForGamePlayLevel();
		break;
	}	

	LeaveCriticalSection(pLoader->Get_CriticalSection());

	return 0;
}




HRESULT CLoader::NativeConstruct(LEVEL eNextLevel)
{
	m_eNextLevel = eNextLevel;

	InitializeCriticalSection(&m_CriticalSection);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadEntryFunc, this, 0, nullptr);
	if (0 == m_hThread)
		return E_FAIL;

	return S_OK;
}

HRESULT CLoader::Loading_ForLogoLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	if (nullptr == pGameInstance)
		return E_FAIL;

	Safe_AddRef(pGameInstance);

	wsprintf(m_szLoading, TEXT("로고용 텍스쳐를 로딩 중입니다. \n"));
	/* For.Prototype_Component_Texture_Logo */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_LOGO, TEXT("Prototype_Component_Texture_Logo"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Brush.png"), 1))))
		return E_FAIL;



	wsprintf(m_szLoading, TEXT("로고용 모델를 로딩 중입니다. \n"));
	

	wsprintf(m_szLoading, TEXT("로고용 객체원형 들을 생성 중입니다. \n"));

	/* For.Prototype_GameObject_BackGround*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BackGround"),
		CBackGround::Create(m_pGraphic_Device))))
		return E_FAIL;	

	wsprintf(m_szLoading, TEXT("로딩이 완료되었습니다. \n"));
	
	Safe_Release(pGameInstance);

	m_isFinished = true;
	
	return S_OK;
}

HRESULT CLoader::Loading_ForGamePlayLevel()
{

	wsprintf(m_szLoading, TEXT("게임플레이용 텍스쳐를 로딩 중입니다. \n"));
	
	wsprintf(m_szLoading, TEXT("게임플레이용 모델를 로딩 중입니다. \n"));
	

	wsprintf(m_szLoading, TEXT("게임플레이용 객체들을 생성 중입니다. \n"));
	

	wsprintf(m_szLoading, TEXT("게임플레이용 완료되었습니다. \n"));
	

	m_isFinished = true;

	return S_OK;
}

CLoader * CLoader::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel)
{
	CLoader*		pInstance = new CLoader(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct(eNextLevel)))
	{
		MSG_BOX("Failed to Created : CLoader");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoader::Free()
{
	Safe_Release(m_pGraphic_Device);

	WaitForSingleObject(m_hThread, INFINITE);

	DeleteCriticalSection(&m_CriticalSection);

	CloseHandle(m_hThread);
}

