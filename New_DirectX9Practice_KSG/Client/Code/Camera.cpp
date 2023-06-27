#include "stdafx.h"
#include "../Header/Camera.h"

#include "Export_Function.h"

CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphicDev) :Engine::CGameObject(pGraphicDev), m_pTarget(nullptr)
{
	//m_eLayerMask = LAYERMASK::LAYER_CAMERA;
	m_eLayerMask = LAYERMASK::LAYER_GAMELOGIC;
	m_eCamID = CAMERAID::CAM_0;
	D3DXMatrixIdentity(&m_matView);
}

CCamera::CCamera(const CCamera& rhs) :Engine::CGameObject(rhs), m_pTarget(nullptr)
{
	//m_eLayerMask = LAYERMASK::LAYER_CAMERA;
	m_eLayerMask = LAYERMASK::LAYER_GAMELOGIC;
	m_eCamID = CAMERAID::CAM_0;
	D3DXMatrixIdentity(&m_matView);
}

CCamera::~CCamera()
{
}

HRESULT CCamera::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CCamera::Update_Object(const _float & fTimeDelta)
{
	if (m_pTarget)
		TraceTarget();
	//else
	//	Key_Input(fTimeDelta);
	POINT		pt{ WINCX >> 1, WINCY >> 1 };

	ClientToScreen(g_hWnd, &pt);
	SetCursorPos(pt.x, pt.y);

	return _int();
}

void CCamera::SetViewSpcae()
{
	if (m_pTarget)
		D3DXMatrixLookAtLH(&m_matView, &m_pTransform->Position(),
			&dynamic_cast<CTransform*>(m_pTarget->Get_Component(L"Transform", ID_DYNAMIC))->Position(), &_vec3(0.f, 1.f, 0.f));
		//CustomMatrixLookAtLH(&m_matView, &m_pTransform->Position(),
		//	&dynamic_cast<CTransform*>(m_pTarget->Get_Component(L"Transform", ID_DYNAMIC))->Position(), &_vec3(0.f, 1.f, 0.f));
	else
		CustomMatrixLookAtLH(&m_matView, &m_pTransform->Position(),
			&(m_pTransform->Position() + m_pTransform->GetDir()), &_vec3(0.f, 1.f, 0.f));
		/*D3DXMatrixLookAtLH(&m_matView, &m_pTransform->Position(),
			&(m_pTransform->Position() + m_pTransform->GetDir()), &_vec3(0.f, 1.f, 0.f));*/

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
}

void CCamera::SetProjection()
{
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4, WINCX / (float)WINCY, 1.0f, 1000.0f);
	//CustomMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4, WINCX / (float)WINCY, 1.0f, 1000.0f);

	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void CCamera::SetTarget(CGameObject * _pTarget)
{
	m_pTarget = _pTarget;
	m_pTransform->Translate(-m_pTransform->Position());
	InitOffset();
	CTransform* pTargetTransform = dynamic_cast<CTransform*>(m_pTarget->Get_Component(L"Transform", ID_DYNAMIC));
}

void CCamera::TraceTarget()
{
	CTransform* pTargetTransform = dynamic_cast<CTransform*>(m_pTarget->Get_Component(L"Transform", ID_DYNAMIC));

	_quat quat = _quat(0.f, 0.f, 0.f, 0.f);
	_vec3 vAxis;
	_matrix matRotate;

	m_pTransform->Translate(-m_pTransform->Position());

	if (CManagers::Input()->Get_DIMouseMove(DIMS_X))
	{
		D3DXQuaternionRotationAxis(&quat, D3DXVec3Cross(&_vec3(), &m_pTransform->GetRight(), &m_pTransform->GetDir()), (D3DX_PI / 4) * (CManagers::Input()->Get_DIMouseMove(DIMS_X) / (float)WINCX));
		D3DXMatrixRotationQuaternion(&matRotate, &quat);
		D3DXVec3TransformNormal(&m_vOffset, &m_vOffset, &matRotate);
	}

	if (CManagers::Input()->Get_DIMouseMove(DIMS_Y))
	{
		D3DXQuaternionRotationAxis(&quat, &m_pTransform->GetRight(), -(D3DX_PI / 4) * (CManagers::Input()->Get_DIMouseMove(DIMS_Y) / (float)WINCY));
		D3DXMatrixRotationQuaternion(&matRotate, &quat);
		D3DXVec3TransformNormal(&m_vOffset, &m_vOffset, &matRotate);
	}

	m_pTransform->Translate(pTargetTransform->Position() + m_vOffset);
}

void CCamera::InitOffset()
{
	CTransform* pTargetTransform = dynamic_cast<CTransform*>(m_pTarget->Get_Component(L"Transform", ID_DYNAMIC));
	m_vOffset = pTargetTransform->Position() - 20.f * pTargetTransform->GetDir() + _vec3(0.f, 10.f, 0.f);
}

HRESULT CCamera::Add_Component(void)
{
	CComponent*	pComponent = nullptr;
	pComponent = m_pTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->SetHost(this);
	m_mapComponent[ID_DYNAMIC].emplace(L"Transform", pComponent);
	return S_OK;
}

void CCamera::Key_Input(const _float & fTimeDelta)
{
	if (CManagers::Input()->Get_DIKeyState(DIK_W))
	{
		const _vec3& vDir = m_pTransform->GetDir();
		m_pTransform->Translate(0.2f * vDir);
	}

	if (CManagers::Input()->Get_DIKeyState(DIK_S))
	{
		const _vec3& vDir = m_pTransform->GetDir();
		m_pTransform->Translate(0.2f * -vDir);
	}

	if (CManagers::Input()->Get_DIKeyState(DIK_A))
	{
		_quat quat;
		D3DXQuaternionRotationAxis(&quat, &_vec3(0.f, 1.f, 0.f), D3DXToRadian(-1.f));
		m_pTransform->Rotate(quat);
	}

	if (CManagers::Input()->Get_DIKeyState(DIK_D))
	{
		_quat quat;
		D3DXQuaternionRotationAxis(&quat, &_vec3(0.f, 1.f, 0.f), D3DXToRadian(1.f));
		m_pTransform->Rotate(quat);
	}

	if (CManagers::Input()->Get_DIKeyState(DIK_Z))
	{
		_quat quat;
		D3DXQuaternionRotationAxis(&quat, &m_pTransform->GetRight(), D3DXToRadian(-1.f));
		m_pTransform->Rotate(quat);
	}

	if (CManagers::Input()->Get_DIKeyState(DIK_C))
	{
		_quat quat;
		D3DXQuaternionRotationAxis(&quat, &m_pTransform->GetRight(), D3DXToRadian(1.f));
		m_pTransform->Rotate(quat);
	}

	//if (CManagers::Input()->Key_Down(DIK_V))
	//{
	//	if (!m_pTarget)
	//	{
	//		SetTarget(Engine::Get_GameObject(LAYERMASK::LAYER_ENVIRONMENT, L"Player"));
	//		//InitOffset();
	//	}
	//	return;
	//}

	if (CManagers::Input()->Get_DIMouseMove(DIMS_X))
	{
		_quat quat;
		D3DXQuaternionRotationAxis(&quat, D3DXVec3Cross(&_vec3(), &m_pTransform->GetRight(), &m_pTransform->GetDir()), -(D3DX_PI / 4) * (CManagers::Input()->Get_DIMouseMove(DIMS_X) / (float)WINCX));
		m_pTransform->Rotate(quat);
	}

	if (CManagers::Input()->Get_DIMouseMove(DIMS_Y))
	{
		_quat quat;
		D3DXQuaternionRotationAxis(&quat, &m_pTransform->GetRight(), (D3DX_PI / 4) * (CManagers::Input()->Get_DIMouseMove(DIMS_Y) / (float)WINCY));
		m_pTransform->Rotate(quat);
	}

	//if (CManagers::Input()->Get_DIMouseMove(DIMS_Z))
	//{
	//	D3DXQUATERNION quat;
	//	D3DXQuaternionRotationAxis(&quat, &m_pTransform->GetRight(), D3DXToRadian(1.f));
	//	m_pTransform->Rotate(quat);
	//}
}

_matrix* CCamera::CustomMatrixLookAtLH(_matrix* _pOut, const _vec3* _pEye, const _vec3* _pAt, const _vec3* _pUp)
{
	_vec3 xAxis;
	_vec3 yAxis;
	_vec3 zAxis;
	
	zAxis = *_pAt - *_pEye;
	D3DXVec3Normalize(&zAxis, &zAxis);
	D3DXVec3Cross(&xAxis, _pUp, &zAxis);
	D3DXVec3Cross(&yAxis, &zAxis, &xAxis);

	*_pOut = _matrix(
		xAxis.x,						yAxis.x,						zAxis.x,						0.f,
		xAxis.y,						yAxis.y,						zAxis.y,						0.f,
		xAxis.z,						yAxis.z,						zAxis.z,						0.f,
		-D3DXVec3Dot(&xAxis, _pEye),	-D3DXVec3Dot(&yAxis, _pEye),	-D3DXVec3Dot(&zAxis, _pEye),	1.f
	);

	return _pOut;
}

_matrix * CCamera::CustomMatrixPerspectiveFovLH(_matrix* _pOut, const _float _fovy, const _float _Aspect, const _float _zn, const _float _zf)
{
	_float h = 1.f / tan(_fovy / 2.f);
	_float w = h / _Aspect;

	*_pOut = _matrix(
		w,								0.f,							0.f,							0.f,
		0.f,							h,								0.f,							0.f,
		0.f,							0.f,							_zf / (_zf - _zn),				1.f,
		0.f,							0.f,							-_zn * _zf / (_zf - _zn),		0.f
	);

	return _pOut;
}

BOOL CCamera::RayCast(CGameObject * pObj, const _vec2 & vMouse)
{
	//pObj

	//const vector<VTXPOS>&	vecVerteices = dynamic_cast<CVIBuffer*>(pObj->Get_Component(L"Buffer", ID_DYNAMIC))->m_vecVerteices;
	//const vector<WORD>&		vecIndices = dynamic_cast<CVIBuffer*>(pObj->Get_Component(L"Buffer", ID_DYNAMIC))->m_vecIndices;

	//float fDist = 1000.f;

	////_vec3 vRayDir, vRayOrigin;

	////Compute_LocalRayInfo(vRayOrigin, vRayDir, pRay, pObj);
	////D3DXVec3Normalize(&vRayDir, &vRayDir);

	//for (UINT i = 0; i < vecIndices.size(); i += 3)
	//{
	//	float fU, fV;
	//	if (D3DXIntersectTri(&vecVerteices[vecIndices[i]].vPosition,
	//		&vecVerteices[vecIndices[i + 1]].vPosition,
	//		&vecVerteices[vecIndices[i + 2]].vPosition,
	//		&m_pTransform->Position(),
	//		&m_pTransform->GetDir(),
	//		//dynamic_cast<CTransform*>(m_pTarget->Get_Component(L"Transform", ID_DYNAMIC))->Position()
	//		&fU, &fV, &fDist))
	//		return TRUE;
	//}

	return 0;
}


CCamera * CCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCamera*	pInstance = new CCamera(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Camera Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CCamera::Free()
{
	__super::Free();
}