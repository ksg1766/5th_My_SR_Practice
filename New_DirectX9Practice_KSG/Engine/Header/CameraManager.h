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

	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
	// TODO : ī�޶� Ŭ���� �̻��� ��� ���� ���ְ� �ϳ��� ��ĥ ��
};

END