#pragma once

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CLayer : public CBase
{
private:
	explicit CLayer();
	virtual ~CLayer();

public:
	CComponent*			Get_Component(const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID);
	CGameObject*		Get_GameObject(const _tchar* pObjTag);
	map<const _tchar*, CGameObject*>&	Get_Map() { return m_mapObject; }

public:
	HRESULT			Add_GameObject(const _tchar* pObjTag, CGameObject* pGameObject);

	HRESULT			Ready_Layer();
	_int			Update_Layer(const _float& fTimeDelta);
	void			LateUpdate_Layer();
	void			Render_Layer();

private:
	map<const _tchar*, CGameObject*>		m_mapObject;

public:
	static		CLayer*		Create();
	virtual		void		Free();
};

END