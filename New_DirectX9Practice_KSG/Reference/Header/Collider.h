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
	_vec3			m_vCenterPos;	// 상자 중앙의 좌표
	_vec3			m_vAxisDir[3];	//상자에 평행한 세 축의 단위벡터
	_float			m_fAxisLen[3];	// 상자의 평행한 세 축의 길이 fAxisLen[n]은 vAxisDir[n]에 각각 대응한다.

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