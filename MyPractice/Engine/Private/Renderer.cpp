#include "..\Public\Renderer.h"
#include "GameObject.h"

IMPLEMENT_SINGLETON(CRenderer)

CRenderer::CRenderer()
{
}

HRESULT CRenderer::Add_RenderGroup(RENDERGROUP eRenderGroup, CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	m_RenderList[eRenderGroup].push_back(pGameObject);

	Safe_AddRef(pGameObject);

	return S_OK;
}

HRESULT CRenderer::Draw_RenderGroup()
{
	for (_uint i = 0; i < RENDER_END; ++i)
	{
		for (auto& pGameObject : m_RenderList[i])
		{
			if (nullptr != pGameObject)
				pGameObject->Render();

			Safe_Release(pGameObject);
		}

		m_RenderList[i].clear();
	}

	return S_OK;
}

void CRenderer::Free()
{
	for (_uint i = 0; i < RENDER_END; ++i)
	{
		for (auto& pGameObject : m_RenderList[i])
			Safe_Release(pGameObject);

		m_RenderList[i].clear();
	}
}

	