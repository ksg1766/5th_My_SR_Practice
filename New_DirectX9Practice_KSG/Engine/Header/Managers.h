#pragma once
#include "Engine_Define.h"
#include "Base.h"
#include "Management.h"
#include "PrototypeManager.h"
#include "CollisionManager.h"
#include "LightManager.h"
#include "CameraManager.h"
#include "InputDev.h"
#include "Renderer.h"

BEGIN(Engine)

class ENGINE_DLL CManagers :
	public CBase
{
	DECLARE_SINGLETON(CManagers)

private:
	CManagers();
	virtual ~CManagers();

public:
	void Initialize();
	void Release();

	static CManagement*				Management()	{ return m_pInstance->m_pManagement; }
	static CPrototypeManager*		Prototype()		{ return m_pInstance->m_pPrototype; }
	static CCollisionManager*		Collision()		{ return m_pInstance->m_pCollision; }
	static CCameraManager*			Camera()		{ return m_pInstance->m_pCamera; }
	static CLightManager*			Light()			{ return m_pInstance->m_pLight; }
	static CInputDev*				Input()			{ return m_pInstance->m_pInput; }
	static CRenderer*				Renderer()		{ return m_pInstance->m_pRenderer; }
	//static CEventManager*			Event()			{ return m_pInstance->m_pEvent; }
	//static CResourceManager*		Resource()		{ return m_pInstance->m_pResource; }
	//static CSoundManager*			Sound()			{ return m_pInstance->m_pSound; }

private:
	CManagement*		m_pManagement;
	CPrototypeManager*	m_pPrototype;
	CCollisionManager*	m_pCollision;
	CCameraManager*		m_pCamera;
	CLightManager*		m_pLight;
	CInputDev*			m_pInput;
	CRenderer*			m_pRenderer;
	//CEventManager*	m_pEvent;
	//CResourceManager*	m_pResource;
	//CSoundManager*	m_pSound;

	virtual void Free() override;

};

END