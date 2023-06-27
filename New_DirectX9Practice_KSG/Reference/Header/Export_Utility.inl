#include "Export_Utility.h"
inline CManagers * Managers()
{
	return CManagers::GetInstance();
}

CComponent*	Get_Component(LAYERMASK pLayerTag,
							const _tchar* pObjTag,
							const _tchar* pComponentTag,
							COMPONENTID eID)
{
	return CManagers::Management()->Get_Component(pLayerTag, pObjTag, pComponentTag, eID);
}

inline CGameObject * Get_GameObject(LAYERMASK pLayerTag, const _tchar * pObjTag)
{
	return CManagers::Management()->Get_GameObject(pLayerTag, pObjTag);
}

inline CLayer * Get_Layer(LAYERMASK pLayerTag)
{
	return CManagers::Management()->Get_Layer(pLayerTag);
}

HRESULT		Create_Managers(LPDIRECT3DDEVICE9 pGraphicDev, CManagers** ppInstance)
{
	CManagers*	pManagers = CManagers::GetInstance();
	NULL_CHECK_RETURN(pManagers, E_FAIL);

	*ppInstance = pManagers;

	return S_OK;
}

HRESULT		Set_Scene(CScene* pScene)
{
	return CManagers::Management()->Set_Scene(pScene);
}
_int		Update_Scene(const _float& fTimeDelta)
{
	return CManagers::Management()->Update_Scene(fTimeDelta);
}
void		LateUpdate_Scene()
{
	CManagers::Management()->LateUpdate_Scene();
}
void		Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CManagers::Management()->Render_Scene(pGraphicDev);
}

HRESULT		Ready_Proto(const _tchar* pProtoTag, CComponent* pComponent)
{
	return CManagers::Prototype()->Ready_Proto(pProtoTag, pComponent);
}
CComponent*	Clone_Proto(const _tchar* pProtoTag)
{
	return CManagers::Prototype()->Clone_Proto(pProtoTag);
}

void		Release_Utility()
{
	/*CProtoMgr::GetInstance()->DestroyInstance();
	CManagement::GetInstance()->DestroyInstance();*/
	CManagers::DestroyInstance();
}