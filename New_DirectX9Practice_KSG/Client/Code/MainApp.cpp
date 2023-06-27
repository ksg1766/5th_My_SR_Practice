#include "stdafx.h"
#include "..\Header\MainApp.h"

#include "Engine_Define.h"
#include "Export_Function.h"
#include "Logo.h"

CMainApp::CMainApp() : m_pDeviceClass(nullptr), m_pManagers(nullptr)
{
	
}

CMainApp::~CMainApp()
{
}

HRESULT CMainApp::Ready_MainApp(void)
{
	FAILED_CHECK_RETURN(SetUp_DefaultSetting(&m_pGraphicDev), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Scene(m_pGraphicDev, &m_pManagers), E_FAIL);

	return S_OK;
}

int CMainApp::Update_MainApp(const float & fTimeDelta)
{
	NULL_CHECK_RETURN(m_pManagers, -1);
	m_pManagers->Input()->Update_InputDev();
	m_pManagers->Management()->Update_Scene(fTimeDelta);

	return 0;
}

void CMainApp::LateUpdate_MainApp()
{
	NULL_CHECK(m_pManagers);
	m_pManagers->Management()->LateUpdate_Scene();
}

void CMainApp::Render_MainApp()
{
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);

	Engine::Render_Begin(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));

	CCamera* pCamera = dynamic_cast<CCamera*>(Engine::Get_GameObject(LAYERMASK::LAYER_GAMELOGIC, L"Camera"));
	CMiniCamera* pMiniCamera = dynamic_cast<CMiniCamera*>(Engine::Get_GameObject(LAYERMASK::LAYER_GAMELOGIC, L"MiniCamera"));
	pCamera->SetViewSpcae();
	pCamera->SetProjection();

	m_pManagers->Management()->Render_Scene(m_pGraphicDev);

	pMiniCamera->SetViewSpcae();
	pMiniCamera->SetProjection();

	m_pManagers->Management()->Render_Scene(m_pGraphicDev);

	pMiniCamera->ReturnViewPort();
	Engine::Managers()->Renderer()->Clear_RenderGroup();

	Engine::Render_End();
}

HRESULT CMainApp::SetUp_DefaultSetting(LPDIRECT3DDEVICE9* ppGraphicDev)
{
	FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(g_hWnd, MODE_WIN, WINCX, WINCY, &m_pDeviceClass), E_FAIL);
	m_pDeviceClass->AddRef();

	(*ppGraphicDev) = m_pDeviceClass->Get_GraphicDev();
	(*ppGraphicDev)->AddRef();

	return S_OK;
}

HRESULT CMainApp::Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagers ** ppManagersClass)
{
	FAILED_CHECK_RETURN(Engine::Create_Managers(pGraphicDev, ppManagersClass), E_FAIL);
	(*ppManagersClass)->AddRef();

	FAILED_CHECK_RETURN(Engine::CManagers::Input()->Ready_InputDev(g_hInst, g_hWnd), E_FAIL);

	Engine::CScene*		pScene = nullptr;

	pScene = CLogo::Create(pGraphicDev);
	NULL_CHECK_RETURN(pScene, E_FAIL);

	FAILED_CHECK_RETURN((*ppManagersClass)->Management()->Set_Scene(pScene), E_FAIL);
	dynamic_cast<CCamera*>(Engine::Get_GameObject(LAYERMASK::LAYER_GAMELOGIC, L"Camera"))
		->SetTarget(Engine::Get_GameObject(LAYERMASK::LAYER_ENVIRONMENT, L"Player"));
	dynamic_cast<CMiniCamera*>(Engine::Get_GameObject(LAYERMASK::LAYER_GAMELOGIC, L"MiniCamera"))
		->SetTarget(Engine::Get_GameObject(LAYERMASK::LAYER_ENVIRONMENT, L"Player"));
	dynamic_cast<CPlayer*>(Engine::Get_GameObject(LAYERMASK::LAYER_ENVIRONMENT, L"Player"))->LoadTerrain();

	return S_OK;
}

CMainApp * CMainApp::Create()
{
	CMainApp *	pInstance = new	CMainApp;

	if (FAILED(pInstance->Ready_MainApp()))
	{
		delete pInstance;
		pInstance = nullptr;

		return pInstance;
	}
	
	return pInstance;
}

void CMainApp::Free()
{
	Safe_Release(m_pGraphicDev);

	Safe_Release(m_pDeviceClass);
	//Safe_Release(m_pManagers);
		
	Engine::Release_Utility();
	Engine::Release_System();
}
