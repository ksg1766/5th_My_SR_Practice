#ifndef Export_Utility_h__
#define Export_Utility_h__

#include "Managers.h"
#include "TriCol.h"
#include "RcCol.h"
#include "TerrainBf.h"
#include "Transform.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Texture.h"

BEGIN(Engine)

inline	CManagers*		Managers();

inline CComponent*		Get_Component(LAYERMASK pLayerTag,
									  const _tchar* pObjTag,
									  const _tchar* pComponentTag,
									  COMPONENTID eID);

inline CGameObject*		Get_GameObject(LAYERMASK pLayerTag,
									  const _tchar* pObjTag);

inline CLayer*			Get_Layer(LAYERMASK pLayerTag);

inline HRESULT			Create_Managers(LPDIRECT3DDEVICE9 pGraphicDev, CManagers** ppInstance);

inline HRESULT			Set_Scene(CScene* pScene);
inline _int				Update_Scene(const _float& fTimeDelta);
inline void				LateUpdate_Scene();
inline void				Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev);

// ProtoMgr
inline HRESULT			Ready_Proto(const _tchar* pProtoTag, CComponent* pComponent);
inline CComponent*		Clone_Proto(const _tchar* pProtoTag);

inline void				Release_Utility();

#include "Export_Utility.inl"

END

#endif // Export_Utility_h__


