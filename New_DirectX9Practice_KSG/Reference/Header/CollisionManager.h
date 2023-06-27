#pragma once
#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class CCollider;
class ENGINE_DLL CCollisionManager :
	public CBase
{
public:
	explicit CCollisionManager();
	virtual ~CCollisionManager();

public:
	void LateUpdate();

public:
	map<ULONGLONG, bool>& GetMapColInfo() { return m_mapColInfo; }
	void SetMapColInfo(ULONGLONG ID, bool bCollision) { m_mapColInfo[ID] = bCollision; }

	void CheckGroup(LAYERMASK _eLeft, LAYERMASK _eRight);
	void Reset();

private:
	map<ULONGLONG, bool> m_mapColInfo;
	UINT	m_arrCheck[(UINT)LAYERMASK::LAYER_END];

	bool IsCollision(CCollider* _pLeft, CCollider* _pRight);
	void CheckCollisionByType(LAYERMASK pLayerLeft, LAYERMASK pLayerRight);

public:
	virtual void Free() override;
};

END