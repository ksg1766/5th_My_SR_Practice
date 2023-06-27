#include "..\..\Header\Managers.h"

IMPLEMENT_SINGLETON(CManagers)

CManagers::CManagers()
{
	m_pManagement = new CManagement;
	m_pPrototype = new CPrototypeManager;
	m_pCollision = new CCollisionManager;
	m_pCamera = new CCameraManager;
	m_pLight = new CLightManager;
	m_pInput = new CInputDev;
	m_pRenderer = new CRenderer;
	//m_pEvent = new CEventManager;
	//m_pResource = new CResourceManager;
}

CManagers::~CManagers()
{
	Safe_Delete(m_pManagement);
	Safe_Delete(m_pPrototype);
	Safe_Delete(m_pCollision);
	Safe_Delete(m_pCamera);
	Safe_Delete(m_pLight);
	Safe_Delete(m_pInput);
	Safe_Delete(m_pRenderer);
}

void CManagers::Free()
{
}
