#pragma once
#include "Camera.h"
class CMiniCamera :
	public CCamera
{
public:
	explicit CMiniCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMiniCamera(const CCamera& rhs);
	virtual ~CMiniCamera();

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta)	override;
	//void	TraceTarget();

	virtual void	SetViewSpcae()	override;
	virtual void	SetProjection()	override;
	void			BackupViewPort();
	void			ReturnViewPort();

	virtual void	SetTarget(CGameObject* _pTarget) { m_pTarget = _pTarget; }

protected:
	virtual void	TraceTarget();

private:
	HRESULT			Add_Component(void);
	D3DVIEWPORT9	m_backupViewPort;

public:
	static CMiniCamera*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};