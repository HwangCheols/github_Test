#include "..\Public\Layer.h"
#include "GameObject.h"

CLayer::CLayer()
{
}

HRESULT CLayer::Add_GameObject(CGameObject * pGameObject)
{
	m_ObjectList.push_back(pGameObject);

	return S_OK;
}

HRESULT CLayer::NativeConstruct()
{

	return S_OK;
}

void CLayer::Tick(_float fTimeDelta)
{
	for (auto& pGameObject : m_ObjectList)
	{
		if (nullptr != pGameObject)
			pGameObject->Tick(fTimeDelta);
	}
}

void CLayer::LateTick(_float fTimeDelta)
{
	for (auto& pGameObject : m_ObjectList)
	{
		if (nullptr != pGameObject)
			pGameObject->LateTick(fTimeDelta);
	}
}

CLayer * CLayer::Create()
{
	CLayer*		pInstance = new CLayer();

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX("Failed to Created : CLayer");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLayer::Free()
{
	for (auto& pGameObject : m_ObjectList)
		Safe_Release(pGameObject);

	m_ObjectList.clear();

}

