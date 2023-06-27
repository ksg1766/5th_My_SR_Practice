#pragma once

#include "GameObject.h"

BEGIN(Engine)

class CRcCol;
class CTransform;
END

class CTerrain; // 엔진에 뭐가있는거같은데 폴더에 파일 있는지 봐바 잘못삭제해서 그런걸수있음.
class CPlayer : public Engine::CGameObject
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPlayer(const CPlayer& rhs);
	virtual ~CPlayer();

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void LateUpdate_Object(void) override;
	virtual void Render_Object(void) override;

public:
	void		LoadTerrain();

private:
	HRESULT		Add_Component(void);
	void		Key_Input(const _float& fTimeDelta);
	void		ForceHeight(_vec3 _vPos);
	void		NavMeshAgent();

private:
	CRcCol*			m_pBuffer = nullptr;
	CTransform*		m_pTransform = nullptr;

	_vec3			m_vDir;
	_float			m_fSpeed;

	// 어떤 오브젝트에 필요 할지
	CTerrain*		m_pTerrain;

public:
	static CPlayer*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;

};

