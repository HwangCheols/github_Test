#pragma once

#include "Base.h"

BEGIN(Engine)

class CLayer final : public CBase
{
public:
	CLayer();	
	virtual ~CLayer() = default;

public:
	HRESULT Add_GameObject(class CGameObject* pGameObject);

public:
	HRESULT NativeConstruct();
	void Tick(_float fTimeDelta);
	void LateTick(_float fTimeDelta);


private:
	list<class CGameObject*>			m_ObjectList;
	typedef list<class CGameObject*>	OBJECTS;

public:
	static CLayer* Create();
	virtual void Free() override;
};

END