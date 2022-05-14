#include "..\Public\Texture.h"

CTexture::CTexture(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
}

CTexture::CTexture(const CTexture & Prototype)
	: CComponent(Prototype)
	, m_Textures(Prototype.m_Textures)
{
	for (auto& pTexture : m_Textures)
		Safe_AddRef(pTexture);


}

//TEXT("../Bin/Resources/Textures/Tmp.png"), 1
//
//TEXT("../Bin/Resources/Textures/Tmp%d.png"), 3

HRESULT CTexture::NativeConstruct_Prototype(TYPE eType, const _tchar * pTextureFilePath, _uint iNumTextures)
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	_tchar		szFullPath[MAX_PATH] = TEXT("");

	LPDIRECT3DBASETEXTURE9			pTexture = nullptr;

	for (_uint i = 0; i < iNumTextures; ++i)
	{
		wsprintf(szFullPath, pTextureFilePath, i);

		if (TYPE_DEFAULT == eType)
		{
			if (FAILED(D3DXCreateTextureFromFile(m_pGraphic_Device, szFullPath, (LPDIRECT3DTEXTURE9*)&pTexture)))
				return E_FAIL;
		}
		else
		{
			if (FAILED(D3DXCreateCubeTextureFromFile(m_pGraphic_Device, szFullPath, (LPDIRECT3DCUBETEXTURE9*)&pTexture)))
				return E_FAIL;
		}

		m_Textures.push_back(pTexture);
	}

	return S_OK;
}

HRESULT CTexture::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	return S_OK;
}

HRESULT CTexture::Bind_Texture(_uint iIndex)
{
	if (iIndex >= m_Textures.size())        
		return E_FAIL;

	m_pGraphic_Device->SetTexture(0, m_Textures[iIndex]);	

	return S_OK;
}

CTexture * CTexture::Create(LPDIRECT3DDEVICE9 pGraphic_Device, TYPE eType, const _tchar * pTextureFilePath, _uint iNumTextures)
{
	CTexture*		pInstance = new CTexture(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype(eType, pTextureFilePath, iNumTextures)))
	{
		MSG_BOX("Failed to Created : CTexture");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CTexture::Clone(void * pArg)
{
	CTexture*		pInstance = new CTexture(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX("Failed to Created : CTexture");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTexture::Free()
{
	__super::Free();

	for (auto& pTexture : m_Textures)
		Safe_Release(pTexture);

	m_Textures.clear();
}
