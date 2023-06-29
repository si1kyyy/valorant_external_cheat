#pragma once
#include "Tool.h"

CHAR* Tool::GetSelfPhyPath() {

	CHAR* path = (CHAR*)malloc(0x10000);
	memset(path, 0, 0x10000);
	CHAR path1[0x1000];
	HMODULE hm = GetModuleHandle(NULL);
	GetModuleFileNameA(hm, path1, sizeof(path1));
	sprintf(path, "\\??\\%s", path1);
	return path;
}

void Tool::Log(const char* msg, LONG code) {
	if (code != 0 && code != 0xF3000002)
	{
		CHAR txt[1000] = { 0 };
		sprintf(txt, "%s  错误码：%08x",msg,code);
		MessageBoxA(NULL, txt, "SK提示：", 0);
	}
	else
	{
		MessageBoxA(NULL, msg, "SK提示：", 0);
	}
}

POS Tool::random_point_on_sphere(float radius) {
	static std::uniform_real_distribution<float> uniform(0, 1);
	static std::mt19937 rng(std::random_device{}());

	float theta = acos(1 - 2 * uniform(rng));  // 生成 θ
	float phi = 2 * 3.1415926 * uniform(rng);  // 生成 φ

	float x = radius * sin(theta) * cos(phi);  // 转换为笛卡尔坐标系
	float y = radius * sin(theta) * sin(phi);
	float z = radius * cos(theta);

	return { x, y, z };
}


