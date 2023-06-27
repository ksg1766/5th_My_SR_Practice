#pragma once

#include "Base.h"
#include "Engine_Define.h"
#include "Export_Function.h"

BEGIN(Engine)

class CGraphicDev;
class CManagers;

END
class CMainApp : public CBase 
{
private:		// 持失切, 社瑚切
	explicit CMainApp();
	virtual ~CMainApp();

public:
	HRESULT		Ready_MainApp(void);
	int			Update_MainApp(const float& fTimeDelta);
	void		LateUpdate_MainApp();
	void		Render_MainApp();

private:
	HRESULT				SetUp_DefaultSetting(LPDIRECT3DDEVICE9* ppGraphicDev);
	HRESULT				Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagers** ppManagersClass);

private:
	CGraphicDev*			m_pDeviceClass;
	CManagers*				m_pManagers;

	LPDIRECT3DDEVICE9		m_pGraphicDev;

public:
	static CMainApp*		Create();

private:
	virtual void		Free();

};

