#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9math.h>
#include <math.h>
#include <tchar.h>


typedef struct _BOX {
	float x;
	float y;
	float z;
	float Y2;
	float W;
}BOX,*PBOX;
typedef struct _POS {
	float x;
	float y;
	float z;
}POS, * PPOS;




EXTERN_C typedef DWORD(WINAPI* gExpLoadDriver)(const char * key);
EXTERN_C typedef DWORD(WINAPI* gExpGetPidByName)(const char* name, ULONG64 ppid);
EXTERN_C typedef DWORD(WINAPI* gExpGetModuleBase)(ULONG64 pid, const char* name, PULONG64 base);
EXTERN_C typedef DWORD(WINAPI* gExpReadProcMemory)(ULONG64 pid, ULONG64 dst, ULONG64 buf, ULONG64 len, ULONG64 way);
EXTERN_C typedef DWORD(WINAPI* gExpWriteProcMemory)(ULONG64 pid, ULONG64 dst, ULONG64 buf, ULONG64 len, ULONG64 way);
EXTERN_C typedef DWORD(WINAPI* gExpHideProcessByPid)(ULONG64 pid, ULONG64 dstpid, ULONG64 needClearObj);
EXTERN_C typedef DWORD(WINAPI* gExpKmInstall)();
EXTERN_C typedef DWORD(WINAPI* gExpKmKeyDown)(ULONG64 kVal);
EXTERN_C typedef DWORD(WINAPI* gExpKmKeyUp)(ULONG64 kVal);
EXTERN_C typedef DWORD(WINAPI* gExpKmMouseLeftDown)();
EXTERN_C typedef DWORD(WINAPI* gExpKmMouseLeftUp)();
EXTERN_C typedef DWORD(WINAPI* gExpKmMouseRightDown)();
EXTERN_C typedef DWORD(WINAPI* gExpKmMouseRightUp)();
EXTERN_C typedef DWORD(WINAPI* gExpKmMouseMoveRelative)(LONG64 dx, LONG64 dy);
EXTERN_C typedef DWORD(WINAPI* gExpKmMouseMoveTo)(LONG64 dx, LONG64 dy);
EXTERN_C typedef DWORD(WINAPI* gExpDeleteFileForce)(const char* path);
EXTERN_C typedef DWORD(WINAPI* gExpSendGeneral)(ULONG64 p1, ULONG64 p2, ULONG64 p3, ULONG64 p4, ULONG64 p5, ULONG64 p6, ULONG64 p7, ULONG64 p8, ULONG64 p9);
EXTERN_C typedef DWORD(WINAPI* gExpDeleteFileForce)(const char* path);


class TArrayDrink {

public:
	TArrayDrink() {
		Data = NULL;
		Count = 0;
		Max = 0;
	};

	ULONG64 operator[](ULONG64 i) const {
		return 0;
	};

	ULONG64* Data;
	unsigned int Count;
	unsigned int Max;
};


class FVector
{
public:
	FVector() : x(0.f), y(0.f), z(0.f)
	{

	}

	FVector(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{

	}
	~FVector()
	{

	}

	float x;
	float y;
	float z;

	inline float Dot(FVector v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(FVector v)
	{
		float x = this->x - v.x;
		float y = this->y - v.y;
		float z = this->z - v.z;

		return sqrtf((x * x) + (y * y) + (z * z)) * 0.03048f;
	}

	FVector operator+(FVector v)
	{
		return FVector(x + v.x, y + v.y, z + v.z);
	}

	FVector operator-(FVector v)
	{
		return FVector(x - v.x, y - v.y, z - v.z);
	}

	FVector operator*(float number) const {
		return FVector(x * number, y * number, z * number);
	}

	__forceinline float Magnitude() const {
		return sqrtf(x * x + y * y + z * z);
	}

	inline float Length()
	{
		return sqrtf((x * x) + (y * y) + (z * z));
	}

	__forceinline FVector Normalize() {
		FVector vector;
		float length = this->Magnitude();

		if (length != 0) {
			vector.x = x / length;
			vector.y = y / length;
			vector.z = z / length;
		}
		else {
			vector.x = vector.y = 0.0f;
			vector.z = 1.0f;
		}
		return vector;
	}

	__forceinline FVector& operator+=(const FVector& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
};

struct FMinimalViewInfo {
	FVector Location; // 0x00(0x0c)
	FVector Rotation; // 0x0c(0x0c)
	float FOV; // 0x18(0x04)
};
struct FQuat
{
	float x;
	float y;
	float z;
	float w;
};
struct FTransform
{
	FQuat rot;
	FVector translation;
	char pad[4];
	FVector scale;
	char pad1[4];

	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;

		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};