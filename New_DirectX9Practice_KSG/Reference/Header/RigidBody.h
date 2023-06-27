#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CRigidBody :
	public CComponent
{
public:
	CRigidBody();
	CRigidBody(LPDIRECT3DDEVICE9 pGraphicDev);
	CRigidBody(const CRigidBody& rhs);
	virtual ~CRigidBody();


	HRESULT			Ready_CRigidBody();

private:
	_bool	m_IsKinematic;

public:
	static CRigidBody*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone(void);

private:
	virtual void			Free();
};

END