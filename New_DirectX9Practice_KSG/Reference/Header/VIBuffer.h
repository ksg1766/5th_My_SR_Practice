#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer : public CComponent
{
protected:
	explicit CVIBuffer();
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CVIBuffer(const CVIBuffer& rhs);
	virtual ~CVIBuffer();

public:
	virtual HRESULT			Ready_Buffer(void);
	virtual void			Render_Buffer(void);

public:
	LPDIRECT3DVERTEXBUFFER9			m_pVB;
	LPDIRECT3DINDEXBUFFER9			m_pIB;

	vector<VTXPOS>					m_vecVerteices;
	vector<WORD>					m_vecIndices;

	_ulong					m_dwVtxCnt;
	_ulong					m_dwVtxSize;
	_ulong					m_dwIdxCnt;
	_ulong					m_dwFVF;


public:
	virtual	void	Free(void);
};

END