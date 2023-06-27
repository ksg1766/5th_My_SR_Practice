#include "..\..\Header\Scene.h"

CScene::CScene(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
{
	m_pGraphicDev->AddRef();
}

CScene::~CScene()
{
}

CComponent * CScene::Get_Component(LAYERMASK pLayerTag, const _tchar * pObjTag, const _tchar * pComponentTag, COMPONENTID eID)
{
	//auto		iter = find_if(m_mapLayer.begin(), m_mapLayer.end(), CTag_Finder(pLayerTag));

	//if (iter == m_mapLayer.end())
	//	return nullptr;
	
	return m_mapLayer[pLayerTag]->Get_Component(pObjTag, pComponentTag, eID);
}

CGameObject * CScene::Get_GameObject(LAYERMASK pLayerTag, const _tchar * pObjTag)
{
	return m_mapLayer[pLayerTag]->Get_GameObject(pObjTag);
}

CLayer * CScene::Get_Layer(LAYERMASK pLayerTag)
{
	//auto	iter = find_if(m_mapLayer.begin(), m_mapLayer.end(), CTag_Finder(pLayerTag));

	//if (iter == m_mapLayer.end())
	//	return nullptr;

	return m_mapLayer[pLayerTag];
}

HRESULT CScene::Ready_Scene()
{
	return S_OK;
}

_int CScene::Update_Scene(const _float & fTimeDelta)
{
	_int		iResult = 0;

	for (auto& iter : m_mapLayer)
	{
		iResult = iter.second->Update_Layer(fTimeDelta);

		if (iResult & 0x80000000)
			return iResult;
	}
	
	return iResult;
}

void CScene::LateUpdate_Scene()
{
	for (auto& iter : m_mapLayer)
		iter.second->LateUpdate_Layer();
}

void CScene::Free()
{
	for_each(m_mapLayer.begin(), m_mapLayer.end(), CDeleteMap());
	m_mapLayer.clear();

	Safe_Release(m_pGraphicDev);
}
