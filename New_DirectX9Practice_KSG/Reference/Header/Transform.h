#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTransform : public CComponent
{
private:
	explicit CTransform();
	explicit CTransform(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTransform(const CTransform& rhs);
	virtual ~CTransform();

public:
	void	Translate(_vec3& _vTrans);
	void	Translate(const _vec3& _vTrans);

	void	SetPos(_vec3& _vPos);
	void	SetPos(const _vec3& _vPos);

	void	Rotate(_quat& _quat);
	void	Rotate(const _quat& _quat);

	void	RotateLook(_quat& _quat);
	void	RotateLook(const _quat& _quat);

	void	Scale(_vec3& _vScale);
	void	Scale(const _vec3& _vScale);

	const _vec3		Position()		const { return _vec3(m_matWorld._41, m_matWorld._42, m_matWorld._43); }
	const _vec3&	Rotation()		const { return m_vDir; }
	const _vec3		LocalScale()	const { return _vec3(m_matWorld._11, m_matWorld._22, m_matWorld._33); }//이게 아닌가...
	const _matrix&	WorldMatrix()	const { return m_matWorld; }

	const _vec3&	GetLook()		const { return m_vLook; }
	const _vec3&	GetDir()		const { return m_vDir; }
	const _vec3&	GetRight()		const { return m_vRight; }

public:
	HRESULT			Ready_Transform();
	virtual _int	Update_Component(const _float& fTimeDelta);

public:
	_vec3		m_vLook;
	_vec3		m_vDir;
	_vec3		m_vRight;
	_matrix		m_matWorld;

public:
	static CTransform*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone(void);
private:
	virtual void			Free();

};

END