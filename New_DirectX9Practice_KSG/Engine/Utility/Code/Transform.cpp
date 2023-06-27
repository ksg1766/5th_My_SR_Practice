#include "..\..\Header\Transform.h"

CTransform::CTransform()
	:CComponent(), m_vDir(_vec3(0.f, 0.f, 1.f)), m_vLook(_vec3(0.f, 0.f, 1.f))
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXVec3Cross(&m_vRight, &m_vDir, &_vec3(0.f, 1.f, 0.f));
}

CTransform::CTransform(LPDIRECT3DDEVICE9 pGraphicDev)
	:CComponent(pGraphicDev), m_vDir(_vec3(0.f, 0.f, 1.f)), m_vLook(_vec3(0.f, 0.f, 1.f))
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXVec3Cross(&m_vRight, &m_vDir, &_vec3(0.f, 1.f, 0.f));
}

CTransform::CTransform(const CTransform & rhs)
	: CComponent(rhs)
{
	m_vLook = rhs.m_vLook;
	m_vDir = rhs.m_vDir;
	m_vRight = rhs.m_vRight;
	m_matWorld = rhs.m_matWorld;
}

CTransform::~CTransform()
{
}

void CTransform::Translate(_vec3 & _vTrans)
{
	m_matWorld._41 += _vTrans.x;
	m_matWorld._42 += _vTrans.y;
	m_matWorld._43 += _vTrans.z;
}

void CTransform::SetPos(_vec3 & _vPos)
{
	CopyMemory(&m_matWorld.m[3][0], &_vPos, 3 * sizeof(_float));
}

void CTransform::Rotate(_quat & _quat)
{
	_matrix	matRotate;
	D3DXMatrixRotationQuaternion(&matRotate, &_quat);

	D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matRotate);
	D3DXVec3Cross(&m_vRight, &_vec3(0.f, 1.f, 0.f), &m_vDir);

	_vec3 vOriginPos;
	CopyMemory(&vOriginPos, &m_matWorld._41, 3 * sizeof(float));

	ZeroMemory(&m_matWorld._41, 3*sizeof(float));
	m_matWorld *= matRotate;
	CopyMemory(&m_matWorld._41, &vOriginPos, 3 * sizeof(float));
}

void CTransform::RotateLook(_quat & _quat)
{
	_matrix	matRotate;
	D3DXMatrixRotationQuaternion(&matRotate, &_quat);

	D3DXVec3TransformNormal(&m_vLook, &m_vLook, &matRotate);
}

void CTransform::Scale(_vec3 & _vScale)
{
	// 오브젝트의 정점 받아서 변환	// 힙 오버플로우
	/*D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, _vScale.x, _vScale.y, _vScale.z);
	
	WORD wVertexNum = m_pHost->GetNumOfVertices();
	void* pVertices;
	m_pHost->GetVB()->Lock(0, wVertexNum * sizeof(VTXNTX), &pVertices, 0);
	
	VTXNTX* pVertex = (VTXNTX*)pVertices;
	for(WORD i = 0; i < wVertexNum; ++i)
	D3DXVec3TransformCoord(&pVertex[i].vPosition, &pVertex[i].vPosition, &matScale);
	
	m_pHost->GetVB()->Unlock();*/
	// TODO: 월드 매트릭스에 직접 접근해서 변경 할 수 있는지 생각해보자.
}

void CTransform::Translate(const _vec3& _vTrans)
{
	Translate(const_cast<_vec3&>(_vTrans));
}

void CTransform::SetPos(const _vec3 & _vPos)
{
	SetPos(const_cast<_vec3&>(_vPos));
}

void CTransform::Rotate(const _quat& _quat)
{
	Rotate(const_cast<D3DXQUATERNION&>(_quat));
}

void CTransform::RotateLook(const _quat & _quat)
{
	RotateLook(const_cast<D3DXQUATERNION&>(_quat));
}

void CTransform::Scale(const _vec3& _vScale)
{
	Scale(const_cast<_vec3&>(_vScale));
}

HRESULT CTransform::Ready_Transform()
{
	return S_OK;
}

_int CTransform::Update_Component(const _float & fTimeDelta)
{
	return 0;
}

CTransform * CTransform::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTransform*		pInstance = new CTransform(pGraphicDev);

	if (FAILED(pInstance->Ready_Transform()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Transform Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent * CTransform::Clone(void)
{
	return new CTransform(*this);
}

void CTransform::Free()
{
	CComponent::Free();
}
