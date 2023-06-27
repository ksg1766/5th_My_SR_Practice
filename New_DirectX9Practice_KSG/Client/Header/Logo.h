#pragma once

#include "Scene.h"
#include "BackGround.h"

#include "Player.h"
#include "Monster.h"
#include "MiniCamera.h"
#include "Terrain.h"
#include "Light.h"

class CLogo : public Engine::CScene
{
private:
	explicit CLogo(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLogo();

public:
	virtual HRESULT Ready_Scene() override;
	virtual _int	Update_Scene(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Scene() override;
	virtual void	Render_Scene() override;

private:
	HRESULT			Ready_Prototype();
	HRESULT			Ready_Layer_Environment(LAYERMASK pLayerTag);
	HRESULT			Ready_Layer_GameLogic(LAYERMASK pLayerTag);
	HRESULT			Ready_Layer_UI(LAYERMASK pLayerTag) { return S_OK; }

public:
	static CLogo*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;

};

