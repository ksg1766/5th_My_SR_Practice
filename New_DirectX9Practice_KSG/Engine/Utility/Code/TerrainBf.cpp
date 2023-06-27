#include "..\..\Header\TerrainBf.h"
#include <random>


CTerrainBf::CTerrainBf()
{
}

CTerrainBf::CTerrainBf(LPDIRECT3DDEVICE9 pGraphicDev) : CVIBuffer(pGraphicDev)
{
}

CTerrainBf::CTerrainBf(const CTerrainBf & rhs) : CVIBuffer(rhs)
{
}


CTerrainBf::~CTerrainBf()
{
}

HRESULT CTerrainBf::Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv)
{
	if (FAILED(D3DXCreateTextureFromFileEx(m_pGraphicDev,
		L"height.bmp", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, 0,
		D3DFMT_X8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, 0,
		NULL, NULL, &m_pHeightMap
	))) {
		MessageBox(NULL, L"Can't not open the HeightMap file.", L"Error", MB_OK);
		return E_FAIL;
	}

	//
	// D3D에서 텍스처에 대한 정보를 저장하기 위한 구조체
	D3DSURFACE_DESC ddsd;
	// 텍스처 메모리의 포인터를 저장하기 위한 구조체
	D3DLOCKED_RECT d3drc;

	// 텍스처 정보를 읽어온다.
	m_pHeightMap->GetLevelDesc(0, &ddsd);
	// 텍스처의 가로, 세로 크기를 저장한다.
	UINT iWidth = ddsd.Width;
	UINT iHeight = ddsd.Height;

	m_dwFVF = FVF_NTX;
	m_dwIdxCnt = (iWidth-1)*(iHeight-1) * 6;

	vector<VTXNTX> vecVertices;
	vecVertices.reserve(iWidth * iHeight);

	m_pHeightMap->LockRect(0, &d3drc, NULL, D3DLOCK_READONLY);

	for (DWORD z = 0; z < iHeight; ++z)
	{
		for (DWORD x = 0; x < iWidth; ++x)
		{
			VTXNTX v;

			v.vPosition.x = ((float)x - iWidth / 2.f);
			v.vPosition.y = ((float)(*((LPDWORD)d3drc.pBits + x + z * (d3drc.Pitch / 4)) & 0x000000ff)) / 20.f;
			v.vPosition.z = -((float)z - iHeight / 2.f);

			v.vNormal = _vec3(0.f, 0.f, 0.f);

			v.vTexture.x = (float)x / iWidth;
			v.vTexture.y = (float)z / iHeight;

			vecVertices.push_back(v);
		}
	}

	m_dwVtxCnt = vecVertices.size();
	m_dwVtxSize = sizeof(VTXNTX);

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	vector<DWORD> vecIndices;
	vecVertices.reserve(m_dwIdxCnt);

	vector<_uint> vecVertexCount;
	vecVertexCount.resize((iWidth) * (iHeight), 0);

	for (INT32 row = 0; row < iHeight-1; ++row)
	{
		for (INT32 col = 0; col < iWidth-1; ++col)
		{
			D3DXVECTOR3 vNormal;

			INT32 baseIdx = (row + 1) * (iWidth) + col;
			INT32 firstIdx = (row + 1) * (iWidth) + col + 1;
			INT32 secondIdx = row * (iWidth) + col;

			// 첫번째 인덱스(현재 열의 첫번째 기준 위치)
			vecIndices.push_back(secondIdx);

			// 두번째 인덱스(다음 행의 두번째 기준 위치)
			vecIndices.push_back(firstIdx);

			// 세번째 인덱스(다음 행의 첫번째 기준 위치)
			vecIndices.push_back(baseIdx);

			vNormal = CalculateNormal(vecVertices[baseIdx].vPosition,
				vecVertices[firstIdx].vPosition, vecVertices[secondIdx].vPosition);

			vecVertices[baseIdx].vNormal += vNormal;
			vecVertices[firstIdx].vNormal += vNormal;
			vecVertices[secondIdx].vNormal += vNormal;
			++vecVertexCount[baseIdx];
			++vecVertexCount[firstIdx];
			++vecVertexCount[secondIdx];

			baseIdx = row * (iWidth) + col + 1;
			firstIdx = row * (iWidth) + col;
			secondIdx = (row + 1) * (iWidth) + col + 1;

			// 네번째 인덱스(현재 열의 첫번째 기준 위치)
			vecIndices.push_back(firstIdx);

			// 다섯번째 인덱스(현재 열의 두번째 기준 위치)
			vecIndices.push_back(baseIdx);

			// 여섯번째 인덱스(다음 행의 두번째 기준 위치)
			vecIndices.push_back(secondIdx);

			vNormal = CalculateNormal(vecVertices[baseIdx].vPosition,
				vecVertices[firstIdx].vPosition, vecVertices[secondIdx].vPosition);

			vecVertices[baseIdx].vNormal += vNormal;
			vecVertices[firstIdx].vNormal += vNormal;
			vecVertices[secondIdx].vNormal += vNormal;
			++vecVertexCount[baseIdx];
			++vecVertexCount[firstIdx];
			++vecVertexCount[secondIdx];
		}
	}

	for (int i = 0; i < (iWidth) * (iHeight); ++i)
	{
		if (!vecVertexCount[i])
			continue;
		vecVertices[i].vNormal /= vecVertexCount[i];
		D3DXVec3Normalize(&vecVertices[i].vNormal, &vecVertices[i].vNormal);
	}

	void*		pVertices = nullptr;

	m_pVB->Lock(0, m_dwVtxCnt * m_dwVtxSize, &pVertices, 0);

	::CopyMemory(pVertices, &vecVertices[0], m_dwVtxCnt * m_dwVtxSize);

	m_pVB->Unlock();
	m_pHeightMap->UnlockRect(0);

	m_pGraphicDev->CreateIndexBuffer(m_dwIdxCnt * sizeof(DWORD), 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_pIB, nullptr);

	void* pIndices = nullptr;
	m_pIB->Lock(0, m_dwIdxCnt * sizeof(DWORD), &pIndices, D3DLOCK_READONLY);
	::CopyMemory(pIndices, &vecIndices[0], m_dwIdxCnt * sizeof(DWORD));
	m_pIB->Unlock();

	return S_OK;
}

void CTerrainBf::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

CTerrainBf * CTerrainBf::Create(LPDIRECT3DDEVICE9 pGraphicDev,
								const _ulong& dwCntX,
								const _ulong& dwCntZ,
								const _ulong& dwVtxItv)
{
	CTerrainBf *	pInstance = new CTerrainBf(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer(dwCntX, dwCntZ, dwVtxItv)))
	{
		Safe_Release(pInstance);
		MSG_BOX("TerrainBf Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent * CTerrainBf::Clone(void)
{
	return new CTerrainBf(*this);
}

D3DXVECTOR3 CTerrainBf::CalculateNormal(D3DXVECTOR3 & v0, D3DXVECTOR3 & v1, D3DXVECTOR3 & v2)
{
	D3DXVECTOR3 v;
	D3DXVec3Cross(&v, &(v2 - v0), &(v1 - v0));
	D3DXVec3Normalize(&v, &v);

	return v;
}

void CTerrainBf::Free(void)
{
	CVIBuffer::Free();
}
