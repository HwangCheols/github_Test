#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CBackGround final : public CGameObject
{
private:
	explicit CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBackGround(const CBackGround& Prototype);
	virtual ~CBackGround() = default;
public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT  Render() override;

private:

	/*상태*/

	/*모델*/
	CVIBuffer_Rect*			m_pVIBufferCom = nullptr;

	/*텍스쳐*/
	CTexture*				m_pTextureCom = nullptr;


private:
	_float3					m_vPosition = _float3(0.f, 0.f, 0.f);



private:
	/* 객체가 가지고 있어야할 컴포넌트들을 얻어(원형객체를 복제해)온다. */
	HRESULT SetUp_Components();


public:
	static CBackGround* Create(LPDIRECT3DDEVICE9 pGraphic_Device); /* 원형객체를 만든다. */
	virtual CGameObject* Clone(void* pArg) override; /* 사본객체를 만들어 리턴한다. */
	virtual void Free() override;

};

END