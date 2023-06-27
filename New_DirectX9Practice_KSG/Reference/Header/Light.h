#pragma once
#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CLight :
	public CGameObject
{
public:
	explicit CLight(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CLight(const CLight& rhs);
	virtual ~CLight();

	// CGameObject��(��) ���� ��ӵ�
	virtual HRESULT	Ready_Object(void)	override;
	virtual void	Render_Object(void)	override;

	void	LightOnOff() { m_bOn = !m_bOn; }	// ���� �̱���

	LIGHTID	GetLightID() { return m_eLightID; }
	void	SetLightID(LIGHTID _eLightID) { m_eLightID = _eLightID; }

private:
	bool		m_bOn;
	D3DLIGHT9	m_tLight;
	LIGHTID		m_eLightID;

public:
	static CLight*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;

};

END