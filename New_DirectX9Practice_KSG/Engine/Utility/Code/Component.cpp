#include "..\..\Header\Component.h"

CComponent::CComponent()
	: m_pGraphicDev(nullptr), m_bClone(false), m_pHost(nullptr)
{
}

//CComponent::CComponent(CGameObject * _pHost)
//	: m_pGraphicDev(nullptr), m_bClone(false), m_pHost(_pHost)
//{
//}
//
//CComponent::CComponent(CGameObject * _pHost, LPDIRECT3DDEVICE9 pGraphicDev)
//	: m_pGraphicDev(pGraphicDev), m_bClone(false), m_pHost(_pHost)
//{
//	if (m_pGraphicDev)
//		m_pGraphicDev->AddRef();
//}

CComponent::CComponent(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev), m_bClone(false)
{
	if (m_pGraphicDev)
		m_pGraphicDev->AddRef();
}

CComponent::CComponent(const CComponent & rhs)
	: m_pGraphicDev(rhs.m_pGraphicDev), m_bClone(true), m_pHost(nullptr)//
{
	if (m_pGraphicDev)
		m_pGraphicDev->AddRef();
}

CComponent::~CComponent()
{
}

void CComponent::Free(void)
{
	Safe_Release(m_pGraphicDev);
}
