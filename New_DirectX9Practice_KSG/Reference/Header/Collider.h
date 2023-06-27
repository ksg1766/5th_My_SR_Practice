#pragma once
#include "Component.h"

BEGIN(Engine)

class CGameObject;
class ENGINE_DLL CCollider :
	public CComponent
{
public:
	CCollider();
	CCollider(LPDIRECT3DDEVICE9 pGraphicDev);
	CCollider(const CCollider& rhs);

	virtual ~CCollider();

	HRESULT			Ready_CCollider();
	virtual void	LateUpdate_Component()	override;

	void			InitOBB(_vec3& _vCenter, _vec3* _vAxisDir, float* _fAxisLen);

	_vec3&			GetCenterPos()	{ return m_vCenterPos; }
	_vec3*			GetAxisDir()	{ return m_vAxisDir; }
	float*			GetAxisLen()	{ return m_fAxisLen; }

	CGameObject*	GetHost()		{ return m_pHost; }
	UINT			GetID()			{ return m_iID; }

public:
	virtual void	OnCollisionEnter(CCollider* _pOther);
	virtual void	OnCollisionStay(CCollider* _pOther);
	virtual void	OnCollisionExit(CCollider* _pOther);


private:
	_vec3			m_vCenterPos;	// ���� �߾��� ��ǥ
	_vec3			m_vAxisDir[3];	//���ڿ� ������ �� ���� ��������
	_float			m_fAxisLen[3];	// ������ ������ �� ���� ���� fAxisLen[n]�� vAxisDir[n]�� ���� �����Ѵ�.

	_uint			m_iID;
	static _uint	g_iNextID;

	int				m_iCol;

public:
	static CCollider*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone(void);

private:
	virtual void			Free();
};

END