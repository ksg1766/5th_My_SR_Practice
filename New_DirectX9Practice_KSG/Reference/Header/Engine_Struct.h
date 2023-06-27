#ifndef Engine_Struct_h__
#define Engine_Struct_h__

#include "Engine_Typedef.h"

namespace Engine
{
	union COLLIDER_ID
	{
		struct
		{
			UINT Left_id;
			UINT Right_id;
		};
		ULONGLONG ID;
	};

	typedef struct tagVertexPosition
	{
		_vec3		vPosition;
	}VTXPOS;

	const _ulong	FVF_POS = D3DFVF_XYZ;

	typedef struct tagVertexColor
	{
		_vec3		vPosition;		
		_ulong		dwColor;

	}VTXCOL;
	const _ulong	FVF_COL = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;

	typedef struct tagVertexTexture
	{
		_vec3		vPosition;
		_vec2		vTexUV;

	}VTXTEX;
	const _ulong	FVF_TEX = D3DFVF_XYZ | D3DFVF_TEX1;

	typedef struct tagVertexCubeTexture
	{
		_vec3		vPosition;
		_vec3		vTexUV;

	}VTXCUBE;

	typedef struct tagVertexNormal
	{
		_vec3		vPosition;
		_vec3		vNormal;

	}VTXNOM;

	const _ulong	FVF_NOM = D3DFVF_XYZ | D3DFVF_NORMAL;

	typedef struct tagVertexNormalColor
	{
		_vec3		vPosition;
		_vec3		vNormal;
		_ulong		dwColor;

	}VTXNCO;

	const _ulong	FVF_NCO = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;

	typedef struct tagVertexNormalTexture
	{
		_vec3		vPosition;
		_vec3		vNormal;
		_vec2		vTexture;

	}VTXNTX;

	const _ulong	FVF_NTX = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

	const _ulong	FVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0); // �ؽ�ó�� UV ��ǥ ���� FLOAT�� 3���� ǥ���ϰڴٴ� ��ũ��(��ȣ���� ���� 0�� �ǹ̴� ���� ���ؽ��� �ؽ��� UV���� �������� �� �� �ִµ� ���� 0��° ���� �����ϰڴٴ� �ǹ�)

	typedef struct tagIndex16
	{
		_ushort  _0;
		_ushort  _1;
		_ushort  _2;

	}INDEX16;

	typedef struct tagIndex32
	{
		_ulong	_0;
		_ulong	_1;
		_ulong	_2;

	}INDEX32;
	
}


#endif // Engine_Struct_h__
