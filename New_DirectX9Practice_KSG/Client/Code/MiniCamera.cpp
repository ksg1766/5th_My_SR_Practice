#include "stdafx.h"
#include "..\Header\MiniCamera.h"

#include "Export_Function.h"

CMiniCamera::CMiniCamera(LPDIRECT3DDEVICE9 pGraphicDev):CCamera(pGraphicDev)
{
	ZeroMemory(&m_backupViewPort, sizeof(D3DVIEWPORT9));
	m_eLayerMask = LAYERMASK::LAYER_GAMELOGIC;
	m_eCamID = CAMERAID::CAM_1;
	//D3DXMatrixIdentity(&m_matView);
	//D3DXMatrixIdentity(&m_matProj);
}

CMiniCamera::CMiniCamera(const CCamera & rhs): CCamera(rhs)
{
	ZeroMemory(&m_backupViewPort, sizeof(D3DVIEWPORT9));
	m_eLayerMask = LAYERMASK::LAYER_GAMELOGIC;
	m_eCamID = CAMERAID::CAM_1;
	//D3DXMatrixIdentity(&m_matView);
	//D3DXMatrixIdentity(&m_matProj);
}

CMiniCamera::~CMiniCamera()
{
}

HRESULT CMiniCamera::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CMiniCamera::Update_Object(const _float & fTimeDelta)
{
	if (m_pTarget)
	//	TraceTarget();

	return _int();
}

void CMiniCamera::SetViewSpcae()
{
	D3DVIEWPORT9 viewPort;
	//BackupViewPort();
	m_pGraphicDev->GetViewport(&m_backupViewPort);

	viewPort.Width = WINCX * 0.2f;
	viewPort.Height = WINCX * 0.2f;

	viewPort.X = WINCX * 0.8f;
	viewPort.Y = 0.f;
	m_pGraphicDev->SetViewport(&viewPort);

	_vec3 vTargetPos = dynamic_cast<CTransform*>(m_pTarget->Get_Component(L"Transform", ID_DYNAMIC))->Position();
	vTargetPos.y = 0.f;
	_vec3 vEyePos = _vec3(vTargetPos.x, 100.f, vTargetPos.z);

	D3DXMatrixLookAtLH(&m_matView, &vEyePos, &vTargetPos,
		&D3DXVECTOR3(0.f, 0.f, 1.f));

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
}

void CMiniCamera::SetProjection()
{
	D3DXMatrixOrthoLH(&m_matProj, 50.f, 50.f, 1.0f, 500.0f);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void CMiniCamera::BackupViewPort()
{
	m_pGraphicDev->GetViewport(&m_backupViewPort);
}

void CMiniCamera::ReturnViewPort()
{
	m_pGraphicDev->SetViewport(&m_backupViewPort);
}

void CMiniCamera::TraceTarget()
{
	_vec3 vTargetPos = dynamic_cast<CTransform*>(m_pTarget->Get_Component(L"Transform", ID_DYNAMIC))->Position();
	vTargetPos.y = 0.f;
	_vec3 vDistance = m_pTransform->Position() - 
		dynamic_cast<CTransform*>(m_pTarget->Get_Component(L"Transform", ID_DYNAMIC))->Position();
	m_pTransform->Translate(-m_pTransform->Position());
	m_pTransform->Translate(_vec3(vDistance.x, 100.f, vDistance.z));
}

HRESULT CMiniCamera::Add_Component(void)
{

	return S_OK;
}

CMiniCamera * CMiniCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMiniCamera*	pInstance = new CMiniCamera(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("MiniCamera Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CMiniCamera::Free()
{
	__super::Free();
}
