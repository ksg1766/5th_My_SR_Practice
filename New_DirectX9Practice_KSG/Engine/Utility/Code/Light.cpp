#include "..\..\Header\Light.h"
#include "Export_Function.h"

CLight::CLight(LPDIRECT3DDEVICE9 pGraphicDev):CGameObject(pGraphicDev), m_bOn(true), m_eLightID(LIGHTID::LIGHT_END)
{
	m_eLayerMask = LAYERMASK::LAYER_GAMELOGIC;
}

CLight::CLight(const CLight & rhs): CGameObject(rhs), m_bOn(rhs.m_bOn), m_eLightID(LIGHTID::LIGHT_END)
{
	m_eLayerMask = LAYERMASK::LAYER_GAMELOGIC;
}

CLight::~CLight()
{
}

HRESULT CLight::Ready_Object(void)
{
	// TODO : Update나 다른 곳에서 on/off 체크해서 한번만 실행하도록.
	D3DXVECTOR3	vDir;
	ZeroMemory(&m_tLight, sizeof(D3DLIGHT9));
	/*m_tLight.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	m_tLight.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	m_tLight.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);*/
	//
	m_tLight.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	m_tLight.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	m_tLight.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);

	m_tLight.Type = D3DLIGHT_POINT;
	m_tLight.Attenuation0 = 0.02f;
	m_tLight.Attenuation1 = 0.02f;
	m_tLight.Attenuation2 = 0.f;
	m_tLight.Theta = D3DXToRadian(200.f);
	m_tLight.Phi = D3DXToRadian(400.f);
	m_tLight.Falloff = 1.f;
	m_tLight.Range = 1000.f;
	m_tLight.Position = D3DXVECTOR3(0.f, 10.f, 0.f);

	//vDir = D3DXVECTOR3(0.0f, 0.f, 0.f) - m_tLight.Position;
	//D3DXVec3Normalize((D3DXVECTOR3*)&m_tLight.Direction, &vDir);
	//
	vDir = D3DXVECTOR3(0.f, -1.f, 0.f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_tLight.Direction, &vDir);
	m_pGraphicDev->SetLight(0, &m_tLight);
	m_pGraphicDev->LightEnable(0, TRUE);

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	/*m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);*/
	//m_pGraphicDev->SetRenderState(D3DRS_AMBIENT, 0x00202020);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

void CLight::Render_Object(void)
{
}

CLight * CLight::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLight*	pInstance = new CLight(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Light Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLight::Free()
{
}
