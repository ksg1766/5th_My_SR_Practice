#pragma once

#include "Engine_Define.h"
#include "Base.h"
#include "Scene.h"

BEGIN(Engine)

class ENGINE_DLL CManagement : public CBase
{
public:
	explicit CManagement();
	virtual ~CManagement();

public:
	CComponent*			Get_Component(LAYERMASK pLayerTag,
		const _tchar* pObjTag,
		const _tchar* pComponentTag,
		COMPONENTID eID);

	CGameObject*		Get_GameObject(LAYERMASK pLayerTag,
		const _tchar* pObjTag);

	CLayer*				Get_Layer(LAYERMASK pLayerTag);

	CScene*				Get_Scene() { return m_pScene ? m_pScene : nullptr; }


public:
	HRESULT			Set_Scene(CScene* pScene);

	_int			Update_Scene(const _float& fTimeDelta);
	void			LateUpdate_Scene();
	void			Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	CScene*			m_pScene;

public:
	virtual void		Free();
};

END