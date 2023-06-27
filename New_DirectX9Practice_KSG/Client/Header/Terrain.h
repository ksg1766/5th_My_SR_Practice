#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CTerrainBf;
class CTexture;
END

class CTerrain :
	public Engine::CGameObject
{
private:
	explicit CTerrain(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTerrain(const CTerrain& rhs);
	virtual ~CTerrain();

	virtual HRESULT	Ready_Object(void)	override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	Render_Object(void) override;

public:
	vector<_vec3>&	LoadTerrainVertex() { return m_vecTerrainVertex; }
	//LPDIRECT3DVERTEXBUFFER9 GetVB();

private:
	HRESULT		Add_Component(void);

private:
	CTerrainBf*			m_pBuffer = nullptr;
	CTexture*			m_pTexture = nullptr;
	//LPDIRECT3DTEXTURE9	m_pTexture;
	vector<_vec3>	m_vecTerrainVertex;
	//LPDIRECT3DTEXTURE9	m_pHeightMap;

public:
	static CTerrain*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

