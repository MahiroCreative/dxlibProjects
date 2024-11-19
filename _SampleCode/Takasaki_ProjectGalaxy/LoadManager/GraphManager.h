#pragma once
#include<map>
#include<string>
#include"DxLib.h"
struct GraphInfo {
	int handle;//�n���h��
	bool used;//��x�ȏ�g�p�ς݂��H
};
class GraphManager
{
private:
	std::map<std::string, GraphInfo> m_pathAndGraphInfoes;

public:
	GraphManager();
	~GraphManager();

	static GraphManager& GetInstance();

	int GetGraphData(const char* filepath);
	void DeleteGraphData(const char* filepath);
};

