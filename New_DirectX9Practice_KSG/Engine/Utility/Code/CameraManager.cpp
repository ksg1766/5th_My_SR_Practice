//#include "..\..\Header\CameraManager.h"
#include "Export_System.h"


CCameraManager::CCameraManager()
{
}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::Update()
{
//	m_mapCamera[CAMERAID::CAM_0]->Update();	// CAM_0 : MainCamera
}

void CCameraManager::SetViewProjection(CAMERAID _eCam)
{
	//CCamera* pCamera = m_mapCamera[_eCam];

	//pCamera->SetViewSpcae();
	//pCamera->SetProjection();
}

void CCameraManager::BackupViewPort()
{
	//Engine::CGraphicDev->Ge
	//Engine::Get_Device()->GetViewport(&m_backupViewPort);
}

void CCameraManager::ReturnViewPort()
{
}

void CCameraManager::Free()
{
}
