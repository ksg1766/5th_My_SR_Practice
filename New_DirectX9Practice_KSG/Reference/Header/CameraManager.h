#pragma once
#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)

class CGameObject;
class ENGINE_DLL CCameraManager :
	public CBase
{
public:
	explicit CCameraManager();
	virtual ~CCameraManager();

	void	Update();

	void	RegistCamera(CAMERAID _eCameraID, CGameObject* _pCamera) { m_mapCamera.emplace(_eCameraID, _pCamera); }
	void	SetViewProjection(CAMERAID _eCam);
	void	BackupViewPort();
	void	ReturnViewPort();

private:
	map<CAMERAID, CGameObject*> m_mapCamera;
	D3DVIEWPORT9 m_backupViewPort;

	// CBase을(를) 통해 상속됨
	virtual void Free() override;
	// TODO : 카메라 클래스 이상한 상속 구조 없애고 하나로 합칠 것
};

END