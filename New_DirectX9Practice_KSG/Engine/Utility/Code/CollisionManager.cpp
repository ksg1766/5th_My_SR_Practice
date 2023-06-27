#include "Managers.h"
#include "Collider.h"
#include "Scene.h"


CCollisionManager::CCollisionManager()
{
	Reset();
	//CheckGroup(LAYERMASK::LAYER_PLAYER, LAYERMASK::LAYER_WALL);
	CheckGroup(LAYERMASK::LAYER_ENVIRONMENT, LAYERMASK::LAYER_ENVIRONMENT);
}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::LateUpdate()
{
	for (UINT iRow = 0; iRow < (UINT)LAYERMASK::LAYER_END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)LAYERMASK::LAYER_END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CheckCollisionByType((LAYERMASK)iRow, (LAYERMASK)iCol);
			}
		}
	}
}

void CCollisionManager::CheckGroup(LAYERMASK _eLeft, LAYERMASK _eRight)
{
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
}

void CCollisionManager::Reset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)LAYERMASK::LAYER_END);
}

bool CCollisionManager::IsCollision(CCollider * _pLeft, CCollider * _pRight)
{
	//struct ST_OBB // OBB����ü
	//{
	//	D3DXVECTOR3 vCenterPos; // ���� �߾��� ��ǥ
	//	D3DXVECTOR3 vAxisDir[3]; //���ڿ� ������ �� ���� ��������
	//	float  fAxisLen[3]; // ������ ������ �� ���� ���� fAxisLen[n]�� vAxisDir[n]�� ���� �����Ѵ�.
	//};

	// ST_OBB ����ü �ΰ��� �����͸� ���� ���ڷ� �޾�, �� OBB�� �浹 ���θ� üũ�ϴ� �Լ�

	// �浹 �� TRUE����, �浹���� ������ FALSE ����
	float c[3][3];
	float absC[3][3];
	float d[3];

	float r0, r1, r;
	int i;

	const float cutoff = 0.999999f;
	bool existsParallelPair = false;

	D3DXVECTOR3 diff = _pLeft->GetCenterPos() - _pRight->GetCenterPos();

	for (i = 0; i < 3; ++i)
	{
		c[0][i] = D3DXVec3Dot(&_pLeft->GetAxisDir()[0], &_pRight->GetAxisDir()[i]);
		absC[0][i] = abs(c[0][i]);
		if (absC[0][i] > cutoff)
			existsParallelPair = true;
	}
	d[0] = D3DXVec3Dot(&diff, &_pLeft->GetAxisDir()[0]);
	r = abs(d[0]);
	r0 = _pLeft->GetAxisLen()[0];
	r1 = _pRight->GetAxisLen()[0] * absC[0][0] + _pRight->GetAxisLen()[1] * absC[0][1] + _pRight->GetAxisLen()[2] * absC[0][2];

	if (r > r0 + r1)
		return FALSE;

	for (i = 0; i < 3; ++i)
	{
		c[1][i] = D3DXVec3Dot(&_pLeft->GetAxisDir()[1], &_pRight->GetAxisDir()[i]);
		absC[1][i] = abs(c[1][i]);
		if (absC[1][i] > cutoff)
			existsParallelPair = true;
	}
	d[1] = D3DXVec3Dot(&diff, &_pLeft->GetAxisDir()[1]);
	r = abs(d[1]);
	r0 = _pLeft->GetAxisLen()[1];
	r1 = _pRight->GetAxisLen()[0] * absC[1][0] + _pRight->GetAxisLen()[1] * absC[1][1] + _pRight->GetAxisLen()[2] * absC[1][2];

	if (r > r0 + r1)
		return FALSE;

	for (i = 0; i < 3; ++i)
	{
		c[2][i] = D3DXVec3Dot(&_pLeft->GetAxisDir()[2], &_pRight->GetAxisDir()[i]);
		absC[2][i] = abs(c[2][i]);
		if (absC[2][i] > cutoff)
			existsParallelPair = true;
	}
	d[2] = D3DXVec3Dot(&diff, &_pLeft->GetAxisDir()[2]);
	r = abs(d[2]);
	r0 = _pLeft->GetAxisLen()[2];
	r1 = _pRight->GetAxisLen()[0] * absC[2][0] + _pRight->GetAxisLen()[1] * absC[2][1] + _pRight->GetAxisLen()[2] * absC[2][2];

	if (r > r0 + r1)
		return FALSE;

	r = abs(D3DXVec3Dot(&diff, &_pRight->GetAxisDir()[0]));
	r0 = _pLeft->GetAxisLen()[0] * absC[0][0] + _pLeft->GetAxisLen()[1] * absC[1][0] + _pLeft->GetAxisLen()[2] * absC[2][0];
	r1 = _pRight->GetAxisLen()[0];

	if (r > r0 + r1)
		return FALSE;

	r = abs(D3DXVec3Dot(&diff, &_pRight->GetAxisDir()[1]));
	r0 = _pLeft->GetAxisLen()[0] * absC[0][1] + _pLeft->GetAxisLen()[1] * absC[1][1] + _pLeft->GetAxisLen()[2] * absC[2][1];
	r1 = _pRight->GetAxisLen()[1];

	if (r > r0 + r1)
		return FALSE;

	r = abs(D3DXVec3Dot(&diff, &_pRight->GetAxisDir()[2]));
	r0 = _pLeft->GetAxisLen()[0] * absC[0][2] + _pLeft->GetAxisLen()[1] * absC[1][2] + _pLeft->GetAxisLen()[2] * absC[2][2];
	r1 = _pRight->GetAxisLen()[2];

	if (r > r0 + r1)
		return FALSE;

	if (existsParallelPair == true)
		return TRUE;

	r = abs(d[2] * c[1][0] - d[1] * c[2][0]);
	r0 = _pLeft->GetAxisLen()[1] * absC[2][0] + _pLeft->GetAxisLen()[2] * absC[1][0];
	r1 = _pRight->GetAxisLen()[1] * absC[0][2] + _pRight->GetAxisLen()[2] * absC[0][1];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[2] * c[1][1] - d[1] * c[2][1]);
	r0 = _pLeft->GetAxisLen()[1] * absC[2][1] + _pLeft->GetAxisLen()[2] * absC[1][1];
	r1 = _pRight->GetAxisLen()[0] * absC[0][2] + _pRight->GetAxisLen()[2] * absC[0][0];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[2] * c[1][2] - d[1] * c[2][2]);
	r0 = _pLeft->GetAxisLen()[1] * absC[2][2] + _pLeft->GetAxisLen()[2] * absC[1][2];
	r1 = _pRight->GetAxisLen()[0] * absC[0][1] + _pRight->GetAxisLen()[1] * absC[0][0];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[0] * c[2][0] - d[2] * c[0][0]);
	r0 = _pLeft->GetAxisLen()[0] * absC[2][0] + _pLeft->GetAxisLen()[2] * absC[0][0];
	r1 = _pRight->GetAxisLen()[1] * absC[1][2] + _pRight->GetAxisLen()[2] * absC[1][1];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[0] * c[2][1] - d[2] * c[0][1]);
	r0 = _pLeft->GetAxisLen()[0] * absC[2][1] + _pLeft->GetAxisLen()[2] * absC[0][1];
	r1 = _pRight->GetAxisLen()[0] * absC[1][2] + _pRight->GetAxisLen()[2] * absC[1][0];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[0] * c[2][2] - d[2] * c[0][2]);
	r0 = _pLeft->GetAxisLen()[0] * absC[2][2] + _pLeft->GetAxisLen()[2] * absC[0][2];
	r1 = _pRight->GetAxisLen()[0] * absC[1][1] + _pRight->GetAxisLen()[1] * absC[1][0];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[1] * c[0][0] - d[0] * c[1][0]);
	r0 = _pLeft->GetAxisLen()[0] * absC[1][0] + _pLeft->GetAxisLen()[1] * absC[0][0];
	r1 = _pRight->GetAxisLen()[1] * absC[2][2] + _pRight->GetAxisLen()[2] * absC[2][1];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[1] * c[0][1] - d[0] * c[1][1]);
	r0 = _pLeft->GetAxisLen()[0] * absC[1][1] + _pLeft->GetAxisLen()[1] * absC[0][1];
	r1 = _pRight->GetAxisLen()[0] * absC[2][2] + _pRight->GetAxisLen()[2] * absC[2][0];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[1] * c[0][2] - d[0] * c[1][2]);
	r0 = _pLeft->GetAxisLen()[0] * absC[1][2] + _pLeft->GetAxisLen()[1] * absC[0][2];
	r1 = _pRight->GetAxisLen()[0] * absC[2][1] + _pRight->GetAxisLen()[1] * absC[2][0];
	if (r > r0 + r1)
		return FALSE;

	return TRUE;
}

void CCollisionManager::CheckCollisionByType(LAYERMASK _pTagLeft, LAYERMASK _pTagRight)
{
	CScene* pScene = CManagers::Management()->Get_Scene();

	const map<const _tchar*, CGameObject*>& mapLeft = pScene->Get_Layer(_pTagLeft)->Get_Map();
	const map<const _tchar*, CGameObject*>& mapRight = pScene->Get_Layer(_pTagRight)->Get_Map();
	map<ULONGLONG, bool>::iterator iter;

	for (auto& iterL = mapLeft.begin(); iterL != mapLeft.end(); ++iterL)
	{
		if (nullptr == iterL->second->Get_Component(L"Collider", ID_DYNAMIC))
			continue;

		for (auto& iterR = mapLeft.begin(); iterR != mapLeft.end(); ++iterR)
		{
			if (nullptr == iterR->second->Get_Component(L"Collider", ID_DYNAMIC) || iterL == iterR)
			{
				continue;
			}

			CCollider* pLeftCol = dynamic_cast<CCollider*>(iterL->second->Get_Component(L"Collider", ID_DYNAMIC));
			CCollider* pRightCol = dynamic_cast<CCollider*>(iterR->second->Get_Component(L"Collider", ID_DYNAMIC));

			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);

			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			if (IsCollision(pLeftCol, pRightCol))
			{	// ���� �浹 ��
				if (iter->second)
				{	// �������� �浹
					if (iterL->second->IsDead() || iterR->second->IsDead())
					{	// �� �� �ϳ� ���� �����̸� �浹 ����
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollisionStay(pRightCol);
						pRightCol->OnCollisionStay(pLeftCol);
					}
				}
				else
				{	// �������� �浹 x	// �ٵ� �� �� �ϳ� ���� �����̸� �浹���� ���� ������ ���
					if (!iterL->second->IsDead() && !iterR->second->IsDead())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
					else
					{
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
				}
			}
			else
			{		// ���� �浹 x��
				if (iter->second)
				{	//�������� �浹�ϰ� �־���.
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

void CCollisionManager::Free()
{
}
