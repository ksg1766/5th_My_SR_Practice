#include "stdafx.h"
#include "..\Header\Terrain.h"
#include "Export_Function.h"

CTerrain::CTerrain(LPDIRECT3DDEVICE9 pGraphicDev):CGameObject(pGraphicDev)
{
	m_eLayerMask = LAYERMASK::LAYER_ENVIRONMENT;
}

CTerrain::CTerrain(const CTerrain & rhs) : CGameObject(rhs), m_pTexture(m_pTexture)
{
	m_eLayerMask = rhs.m_eLayerMask;
}

CTerrain::~CTerrain()
{
}

HRESULT CTerrain::Ready_Object(void)
{
	/*if (FAILED(D3DXCreateTextureFromFile(m_pGraphicDev, L"terrain.png", &m_pTexture)))
		return E_FAIL;*/
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//
	m_vecTerrainVertex.reserve(m_pBuffer->m_dwVtxCnt);

	void*		pVertices = nullptr;
	m_pBuffer->m_pVB->Lock(0, m_pBuffer->m_dwVtxCnt * m_pBuffer->m_dwVtxSize, &pVertices, 0);
	for (UINT i = 0; i < m_pBuffer->m_dwVtxCnt; ++i)
	{
		m_vecTerrainVertex.push_back((((VTXNTX*)pVertices) + i)->vPosition);
	}
	m_pBuffer->m_pVB->Unlock();
	//

	return S_OK;
}

_int CTerrain::Update_Object(const _float & fTimeDelta)
{
	Engine::Managers()->Renderer()->Add_RenderGroup(RENDER_NONALPHA, this);

	return _int();
}

void CTerrain::Render_Object(void)
{
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));

	mtrl.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	mtrl.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.f);
	mtrl.Specular = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.f);
	mtrl.Emissive = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.f);
	m_pGraphicDev->SetMaterial(&mtrl);

	//m_pGraphicDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);  /// 0번 텍스처 : 확대 필터 사용
	//m_pGraphicDev->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);  /// 0번 텍스처 : 0번 텍스처 좌표계 사용
	
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &mat);

	m_pTexture->Render_Texture(0);
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pBuffer->Render_Buffer();
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	
	//m_pGraphicDev->SetTexture(0, m_pTexture);       /// 0번 텍스쳐 스테이지에 텍스쳐 고정(색깔맵)
}

//LPDIRECT3DVERTEXBUFFER9 CTerrain::GetVB()
//{
//	return m_pBuffer->m_pVB;
//}

HRESULT CTerrain::Add_Component(void)
{
	CComponent*	pComponent = nullptr;

	/*	pComponent = m_pBufferCom = dynamic_cast<CTriCol*>(Engine::Clone_Proto(L"Proto_TriCol"));*/
	pComponent = m_pBuffer = dynamic_cast<CTerrainBf*>(Engine::Clone_Proto(L"Proto_TerrainBf"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->SetHost(this);
	m_mapComponent[ID_STATIC].emplace(L"Buffer", pComponent);

	pComponent = m_pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_Texture_Terrain"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->SetHost(this);
	m_mapComponent[ID_STATIC].emplace(L"Proto_Texture_Terrain", pComponent);

	return S_OK;
}

CTerrain * CTerrain::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerrain*	pInstance = new CTerrain(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Terrain Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTerrain::Free()
{
	__super::Free();
}
