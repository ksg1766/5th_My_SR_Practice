#include "Managers.h"



CLightManager::CLightManager()
{
}


CLightManager::~CLightManager()
{
}

void CLightManager::Update()
{
}

void CLightManager::LightOnOff(LIGHTID _eLightID)
{
	//CManagers::Management()->Get_Scene()->Get_Layer(L"Light")->Get_Map()->LightOnOff();
	//m_mapLight[_eLightID]->LightOnOff();
}

void CLightManager::PlaceLight(CGameObject * _pLight)
{
	//CManagers::Management()->Get_Scene()->Get_Layer(L"Light")->Add_GameObject(L"Light", dynamic_cast<CGameObject*>(_pLight));
	//TODO: Light Layer�� �ʿ����� �����غ��ô�. or m_mapLight�� �ʿ�����
	//m_mapLight.emplace(_pLight->GetLightID(), _pLight));
}

void CLightManager::Free()
{
}
