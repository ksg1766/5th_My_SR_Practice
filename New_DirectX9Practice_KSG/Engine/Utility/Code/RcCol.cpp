#include "..\..\Header\RcCol.h"

CRcCol::CRcCol()
{
}

CRcCol::CRcCol(LPDIRECT3DDEVICE9 pGraphicDev)
	:  CVIBuffer(pGraphicDev)
{
}

CRcCol::CRcCol(const CRcCol & rhs)
	: CVIBuffer(rhs)
{
}


CRcCol::~CRcCol()
{
}

HRESULT CRcCol::Ready_Buffer(void)
{
	//m_dwFVF = FVF_NCO;
	m_dwFVF = FVF_NOM;
	m_dwIdxCnt = 12;

	//VTXNCO vertices[] =
	VTXNOM vertices[] =
	{
		{ D3DXVECTOR3{ -1.f,  1.f,  1.f }, D3DXVECTOR3{ 0.f,  0.f,  0.f }} , //D3DCOLOR_ARGB(0, 255, 255, 255) },
		{ D3DXVECTOR3{  1.f,  1.f,  1.f }, D3DXVECTOR3{ 0.f,  0.f,  0.f }} , //D3DCOLOR_ARGB(0, 255, 255, 255) },
		{ D3DXVECTOR3{  1.f,  1.f, -1.f }, D3DXVECTOR3{ 0.f,  0.f,  0.f }} , //D3DCOLOR_ARGB(0, 255, 255, 255) },
		{ D3DXVECTOR3{ -1.f,  1.f, -1.f }, D3DXVECTOR3{ 0.f,  0.f,  0.f }} , //D3DCOLOR_ARGB(0, 255, 255, 255) },
		{ D3DXVECTOR3{ -1.f, -1.f,  1.f }, D3DXVECTOR3{ 0.f,  0.f,  0.f }} , //D3DCOLOR_ARGB(0, 255, 255, 255) },
		{ D3DXVECTOR3{  1.f, -1.f,  1.f }, D3DXVECTOR3{ 0.f,  0.f,  0.f }} , //D3DCOLOR_ARGB(0, 255, 255, 255) },
		{ D3DXVECTOR3{  1.f, -1.f, -1.f }, D3DXVECTOR3{ 0.f,  0.f,  0.f }} , //D3DCOLOR_ARGB(0, 255, 255, 255) },
		{ D3DXVECTOR3{ -1.f, -1.f, -1.f }, D3DXVECTOR3{ 0.f,  0.f,  0.f }} , //D3DCOLOR_ARGB(0, 255, 255, 255) }
	};

	for (_uint i = 0; i < sizeof(vertices) / sizeof(VTXNOM); ++i)
		m_vecVerteices.push_back(VTXPOS{vertices[i].vPosition});

	WORD indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		4, 6, 5,
		4, 7, 6,
		0, 3, 7,
		0, 7, 4,
		1, 5, 6,
		1, 6, 2,
		3, 2, 6,
		3, 6, 7,
		0, 4, 5,
		0, 5, 1
	};

	for (_uint i = 0; i < sizeof(indices) / sizeof(WORD); ++i)
		m_vecIndices.push_back(indices[i]);

	int iVertexCount[8] = { 0 };

	for (int i = 0; i < 12; ++i)
	{
		D3DXVECTOR3 v1 = vertices[indices[i * 3 + 1]].vPosition - vertices[indices[i * 3]].vPosition;
		D3DXVECTOR3 v2 = vertices[indices[i * 3 + 2]].vPosition - vertices[indices[i * 3]].vPosition;
		D3DXVECTOR3 v;
		D3DXVec3Cross(&v, &v1, &v2);
		//D3DXVec3Normalize(&v, &v);

		for (int j = 0; j < 3; ++j)
		{
			vertices[indices[i * 3 + j]].vNormal += v;
			++iVertexCount[indices[i * 3 + j]];
		}
	}

	for (int i = 0; i < 8; ++i)
	{
		vertices[i].vNormal /= iVertexCount[i];
		D3DXVec3Normalize(&vertices[i].vNormal, &vertices[i].vNormal);
	}

	//m_dwVtxCnt = sizeof(vertices) / sizeof(VTXNCO);
	//m_dwVtxSize = sizeof(VTXNCO);
	m_dwVtxCnt = sizeof(vertices) / sizeof(VTXNOM);
	m_dwVtxSize = sizeof(VTXNOM);

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	void*		pVertices = nullptr;

	m_pVB->Lock(0, sizeof(vertices), &pVertices, 0);
	
	::CopyMemory(pVertices, vertices, sizeof(vertices));

	m_pVB->Unlock();

	FAILED_CHECK_RETURN(m_pGraphicDev->CreateIndexBuffer(sizeof(indices), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, nullptr), E_FAIL);

	void* pIndices = nullptr;
	m_pIB->Lock(0, sizeof(indices), &pIndices, 0);
	::CopyMemory(pIndices, indices, sizeof(indices));
	m_pIB->Unlock();

	return S_OK;
}

void CRcCol::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

CRcCol * CRcCol::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRcCol *	pInstance = new CRcCol(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
	{
		Safe_Release(pInstance);
		MSG_BOX("RcCol Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent * CRcCol::Clone(void)
{
	return new CRcCol(*this);
}

void CRcCol::Free(void)
{
	CVIBuffer::Free();
}
