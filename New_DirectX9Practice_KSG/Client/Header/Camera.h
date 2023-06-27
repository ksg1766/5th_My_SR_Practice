#pragma once

#include "GameObject.h"

BEGIN(Engine)

class CTransform;

END

class CCamera :
	public Engine::CGameObject
{
protected:
	explicit CCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCamera(const CCamera& rhs);
	virtual ~CCamera();

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta)	override;

	virtual void	SetViewSpcae();
	virtual void	SetProjection();

	virtual void	SetTarget(CGameObject* _pTarget);

protected:
	virtual void	TraceTarget();
	void	InitOffset();

protected:
	CAMERAID	m_eCamID;
	
	CGameObject*	m_pTarget;
	//D3DXVECTOR3	m_vTargetPos;

	_vec3	m_vOffset;
	_matrix	m_matView;
	_matrix	m_matProj;

private:
	HRESULT		Add_Component(void);
	void		Key_Input(const _float& fTimeDelta);

	_matrix*		CustomMatrixLookAtLH(_matrix* _pOut, const _vec3* _pEye, const _vec3* _pAt, const _vec3* _pUp);
	_matrix*		CustomMatrixPerspectiveFovLH(_matrix* _pOut, const _float _fovy, const _float _Aspect, const _float _zn, const _float _zf);

	BOOL		RayCast(CGameObject* pObj, const _vec2& vMouse);


protected:
	CTransform*		m_pTransform = nullptr;
	_bool			m_bCinematic = false;

public:
	static CCamera*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void Free() override;
};

