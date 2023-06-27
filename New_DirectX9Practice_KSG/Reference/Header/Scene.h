#pragma once

#include "Layer.h"

BEGIN(Engine)

class ENGINE_DLL CScene : public CBase
{
protected:
	explicit CScene(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene();

public:
	CComponent*			Get_Component(LAYERMASK pLayerTag,
									 const _tchar* pObjTag, 
									 const _tchar* pComponentTag, 
									 COMPONENTID eID);

	CGameObject*		Get_GameObject(LAYERMASK pLayerTag,
									 const _tchar* pObjTag);

	CLayer*				Get_Layer(LAYERMASK pLayerTag);

public:
	virtual HRESULT		Ready_Scene();
	virtual _int		Update_Scene(const _float& fTimeDelta);
	virtual void		LateUpdate_Scene();
	virtual void		Render_Scene() PURE;

protected:
	LPDIRECT3DDEVICE9				m_pGraphicDev;
	map<LAYERMASK, CLayer*>			m_mapLayer;

public:
	virtual void	Free();
};

END