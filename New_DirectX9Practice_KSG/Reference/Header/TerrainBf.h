#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTerrainBf :
	public CVIBuffer
{
public:
	explicit CTerrainBf();
	explicit CTerrainBf(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTerrainBf(const CTerrainBf& rhs);
	virtual ~CTerrainBf();

public:
	virtual HRESULT			Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv);
	virtual void			Render_Buffer(void);

public:
	static CTerrainBf*		Create(LPDIRECT3DDEVICE9 pGraphicDev,
										const _ulong& dwCntX = VTXCNTX,
										const _ulong& dwCntZ = VTXCNTZ,
										const _ulong& dwVtxItv = VTXITV);
	virtual CComponent*		Clone(void);

private:
	D3DXVECTOR3 CalculateNormal(D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2);

public:
	LPDIRECT3DTEXTURE9	m_pHeightMap;

private:
	virtual	void	Free(void);
};

END