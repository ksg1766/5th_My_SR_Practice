#pragma once
#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)

class CLight;
class ENGINE_DLL CLightManager :
	public CBase
{
public:
	CLightManager();
	~CLightManager();

	void	Update();
	void	LightOnOff(LIGHTID _eLightID);

public:
	void	PlaceLight(CGameObject* _pLight);

private:
	//map<LIGHTID, CLight*> m_mapLight;
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
	// TODO: Value�� vector��
};

END