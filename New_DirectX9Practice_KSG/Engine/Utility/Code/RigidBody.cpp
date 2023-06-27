#include "..\..\Header\RigidBody.h"

CRigidBody::CRigidBody():m_IsKinematic(false)
{
}

CRigidBody::CRigidBody(LPDIRECT3DDEVICE9 pGraphicDev): CComponent(pGraphicDev), m_IsKinematic(false)
{
}

CRigidBody::CRigidBody(const CRigidBody & rhs): CComponent(rhs), m_IsKinematic(rhs.m_IsKinematic)
{
}


CRigidBody::~CRigidBody()
{
}

HRESULT CRigidBody::Ready_CRigidBody()
{
	return S_OK;
}

CRigidBody * CRigidBody::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRigidBody*		pInstance = new CRigidBody(pGraphicDev);

	if (FAILED(pInstance->Ready_CRigidBody()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Transform Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent * CRigidBody::Clone(void)
{
	return nullptr;
}

void CRigidBody::Free()
{
}
