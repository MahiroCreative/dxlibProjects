#include <iostream>
#include "MyDxlib.h"

using namespace std;

//Vector3のテスト用
void TestVector3();

int main()
{
	//Vector3のテスト
	TestVector3();
}

void TestVector3()
{
	/*変数作成*/
	Vector3 ans;
	Vector3 left{ 1,2,3 };
	Vector3 right{ 0.1f,0.2f,0.3f };
	float k = 1.2;

	/*確認*/
	//+
	ans = left + right;
	cout << ans.ToString() << std::endl;
	//+
	ans = left - right;
	cout << ans.ToString() << std::endl;
	//+=
	ans += left;
	cout << ans.ToString() << std::endl;
	//-=
	ans -= right;
	cout << ans.ToString() << std::endl;
	//*
}