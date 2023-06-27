#include "stdafx.h"
#include "..\Header\Player.h"

#include "Export_Function.h"
#include "Terrain.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{

}
CPlayer::CPlayer(const CPlayer& rhs)
	: Engine::CGameObject(rhs)
{

}
CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_pTransform->Translate(D3DXVECTOR3(0.f, 2.f, 0.f));

	//m_pTerrain->
	//m_pTransformCom->m_vScale = { 2.f, 1.f, 1.f };
	//m_fSpeed = 10.f;

	return S_OK;
}

Engine::_int CPlayer::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Key_Input(fTimeDelta);

	/*
	RigidBody의 IsKinematic이 fasle일때 아래 지형 타기를 적용하는 것을 고려
	*/
	_vec3 vCurPos = m_pTransform->Position();
	ForceHeight(vCurPos);

	Engine::Managers()->Renderer()->Add_RenderGroup(RENDER_NONALPHA, this);

	return iExit;
}

void CPlayer::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
}

void CPlayer::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransform->WorldMatrix());
//	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
//	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));

	mtrl.Diffuse = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
	mtrl.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.f);
	mtrl.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.f);
	mtrl.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.f);
	m_pGraphicDev->SetMaterial(&mtrl);

	m_pBuffer->Render_Buffer();

//	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CPlayer::LoadTerrain()
{
	m_pTerrain = dynamic_cast<CTerrain*>(Engine::Get_GameObject(LAYERMASK::LAYER_ENVIRONMENT, L"Terrain"));
}

HRESULT CPlayer::Add_Component(void)
{
	CComponent*	pComponent = nullptr;

/*	pComponent = m_pBufferCom = dynamic_cast<CTriCol*>(Engine::Clone_Proto(L"Proto_TriCol"));*/
	pComponent = m_pBuffer = dynamic_cast<CRcCol*>(Engine::Clone_Proto(L"Proto_Buffer"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->SetHost(this);
	m_mapComponent[ID_STATIC].emplace(L"Buffer", pComponent);

	pComponent = m_pTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->SetHost(this);
	m_mapComponent[ID_DYNAMIC].emplace(L"Transform", pComponent);

	pComponent = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Proto_Collider"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->SetHost(this);
	m_mapComponent[ID_DYNAMIC].emplace(L"Collider", pComponent);

	return S_OK;
}

void CPlayer::Key_Input(const _float& fTimeDelta)
{
	if (GetKeyState('W') & 0x8000)
	{
		const D3DXVECTOR3& vDir = m_pTransform->GetDir();
		//if(방향에 있는 타일이 CanGo)
		m_pTransform->Translate(0.3f * vDir);
	}

	if (GetKeyState('S') & 0x8000)
	{
		const D3DXVECTOR3& vDir = m_pTransform->GetDir();
		//if(CanGo)
		m_pTransform->Translate(0.3f * -vDir);
	}

	if (GetKeyState('A') & 0x8000)
	{
		D3DXQUATERNION quat;
		D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(0.f, 1.f, 0.f), D3DXToRadian(-1.f));
		m_pTransform->Rotate(quat);
	}

	if (GetKeyState('D') & 0x8000)
	{
		D3DXQUATERNION quat;
		D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(0.f, 1.f, 0.f), D3DXToRadian(1.f));
		m_pTransform->Rotate(quat);
	}

	if (GetKeyState('Z') & 0x8000)
	{
		D3DXQUATERNION quat;
		D3DXQuaternionRotationAxis(&quat, &m_pTransform->GetRight(), D3DXToRadian(-1.f));
		m_pTransform->Rotate(quat);
	}

	if (GetKeyState('C') & 0x8000)
	{
		D3DXQUATERNION quat;
		D3DXQuaternionRotationAxis(&quat, &m_pTransform->GetRight(), D3DXToRadian(1.f));
		m_pTransform->Rotate(quat);
	}
}

void CPlayer::ForceHeight(_vec3 _vPos)
{
	_float x = (VTXCNTX / 2.f) + _vPos.x;
	_float z = (VTXCNTZ / 2.f) - _vPos.z;

	x /= (_float)VTXITV;
	z /= (_float)VTXITV;

	_int col = ::floorf(x);
	_int row = ::floorf(z);

	_vec3 A = m_pTerrain->LoadTerrainVertex()[row * VTXCNTX + col];
	_vec3 B = m_pTerrain->LoadTerrainVertex()[row * VTXCNTX + col + 1];
	_vec3 C = m_pTerrain->LoadTerrainVertex()[(row + 1) * VTXCNTX + col];
	_vec3 D = m_pTerrain->LoadTerrainVertex()[(row + 1) * VTXCNTX + col + 1];

	_float dx = x - col;
	_float dz = z - row;

	_float height;

	//D3DXPLANE tPlane;

	if (dz < 1.0f - dx)
	{
		_vec3 uy = B - A;
		_vec3 vy = C - A;

		/*_vec3 vN;
		D3DXVec3Cross(&vN, &uy, &vy);
		D3DXVec3Normalize(&vN, &vN);

		_vec3 vUp;
		CopyMemory(&vUp, &m_pTransform->WorldMatrix().m[2][0], 3 * sizeof(float));
		_float fTheta = D3DXToDegree(acos(D3DXVec3Dot(&vN, &vUp)));

		if (60.f < fTheta && 91.f > fTheta)
			m_pTransform->Translate(-0.3f * m_pTransform->GetDir());*/

		/*D3DXPlaneFromPoints(&tPlane, &A, &B, &C);
		height = (-tPlane.a * _vPos.x - tPlane.c * _vPos.z - tPlane.d) / tPlane.b + 1.f;*/


		height = A.y + (uy.y * dx) + (vy.y * dz) + 1.f;
		m_pTransform->SetPos(_vec3(_vPos.x, height, _vPos.z));
		// m_pTransform->SetPos(_vec3(m_pTransform->Position().x, height, m_pTransform->Position().z));
	}
	else
	{
		_vec3 uy = C - D;
		_vec3 vy = B - D;

		/*_vec3 vN;
		D3DXVec3Cross(&vN, &uy, &vy);
		D3DXVec3Normalize(&vN, &vN);

		_vec3 vUp;
		CopyMemory(&vUp, &m_pTransform->WorldMatrix().m[2][0], 3 * sizeof(float));
		_float fTheta = D3DXToDegree(acos(D3DXVec3Dot(&vN, &vUp)));

		if (60.f < fTheta && 91.f > fTheta)
			m_pTransform->Translate(-0.3f * m_pTransform->GetDir());*/

		// D3DXPlaneFromPoints(&tPlane, &B, &C, &D);
		// height = (-tPlane.a * _vPos.x - tPlane.c * _vPos.z - tPlane.d) / tPlane.b + 1.f;

		height = D.y + (uy.y * (1.f - dx)) + (vy.y * (1.f - dz)) + 1.f;
		m_pTransform->SetPos(_vec3(_vPos.x, height, _vPos.z));
		// m_pTransform->SetPos(_vec3(m_pTransform->Position().x, height, m_pTransform->Position().z));
	}
}

void CPlayer::NavMeshAgent()
{
}

void CPlayer::Free()
{
	__super::Free();
}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer*	pInstance = new CPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Player Create Failed");
		return nullptr;
	}

	return pInstance;
}
