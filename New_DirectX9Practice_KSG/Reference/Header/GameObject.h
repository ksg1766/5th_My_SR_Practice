#pragma once

#include "Component.h"

BEGIN(Engine)

class CCollider;
class ENGINE_DLL CGameObject : public CBase
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CGameObject(const CGameObject& rhs);
	virtual ~CGameObject();

public:
	CComponent*			Get_Component(const _tchar* pComponentTag, COMPONENTID eID);

public:
	virtual HRESULT		Ready_Object(void);
	virtual _int		Update_Object(const _float& fTimeDelta);
	virtual void		LateUpdate_Object(void);
	virtual void		Render_Object(void);

	virtual void		OnCollisionEnter(CCollider* _pOther) {};
	virtual void		OnCollisionStay(CCollider* _pOther) {};
	virtual void		OnCollisionExit(CCollider* _pOther) {};
	
	LAYERMASK			GetLayerMask() { return m_eLayerMask; }
	_bool				IsDead() { return m_IsDead; }

private:
	CComponent*			Find_Component(const _tchar* pComponentTag, COMPONENTID eID);

protected:
	map<const _tchar*, CComponent*>		m_mapComponent[ID_END];
	LPDIRECT3DDEVICE9					m_pGraphicDev;

	LAYERMASK							m_eLayerMask;
	_bool								m_IsDead;

public:
	virtual void		Free();
};

END