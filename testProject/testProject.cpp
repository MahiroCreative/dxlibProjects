#include <iostream>
#include "MyDxlib.h"

void TestVector3();

int main()
{
	//Vector3のテスト
	TestVector3();
}

void TestVector3()
{
	/*Vector3*/
	Vector3 ans1, ans2, ans3, ans4, ans5, ans6;
	float ans7,ans8;
	Vector3 left{ 1,2,3 };
	Vector3 right{ 0.8f,1.6f,2.4f };
	Vector3 right2{ 2,3,4 };
	float kRight = 1.2f;

	/*作成*/
	ans1 = left + right;
	ans2 = left - right;
	ans3 = left * kRight;
	ans4 = left / kRight;
	ans5 += left;
	ans6 -= right;
	ans7 = Vector3::Dot(left,right2);
	ans8 = left.Length();

	/*出力テスト*/
	std::cout << ans1.ToString() << std::endl;
	std::cout << ans2.ToString() << std::endl;
	std::cout << ans3.ToString() << std::endl;
	std::cout << ans4.ToString() << std::endl;
	std::cout << ans5.ToString() << std::endl;
	std::cout << ans6.ToString() << std::endl;
	std::cout << ans7 << std::endl;
	std::cout << ans8 << std::endl;
}