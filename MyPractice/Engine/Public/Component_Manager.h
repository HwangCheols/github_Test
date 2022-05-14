#pragma once

#include "Texture.h"
#include "VIBuffer_Rect.h"

BEGIN(Engine)

class CComponent_Manager final : public CBase
{
	DECLARE_SINGLETON(CComponent_Manager)
private:
	CComponent_Manager();
	virtual ~CComponent_Manager() = default;

public:
	HRESULT Reserve_Container(_uint iNumLevels);
	HRESULT Add_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag, CComponent* pPrototype);
	CComponent* Clone_Component(_uint iLevelIndex, const _tchar* pPrototypeTag, void* pArg);

public:
	HRESULT Clear(_uint iLevelIndex);

private:
	_uint										m_iNumLevels = 0;

	map<const _tchar*, CComponent*>*			m_pPrototypes = nullptr;
	typedef map<const _tchar*, CComponent*>		PROTOTYPES;

private:
	CComponent* Find_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag);

public:
	virtual void Free() override;
};

END