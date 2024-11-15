#include <iostream>
#include "GameMath.h"
#include <vector>
#include <algorithm>

using namespace std;

//Vector3のテスト用
void TestVector3();
//vectorのテスト用

int main()
{

	std::vector<int> y = { 0, 1, 2, 3, 4 };

	// std::count_if は条件を満たすコンテナ要素の個数を数える処理
	//   - 第1引数と第2引数で範囲を指定
	//   - 第3引数で関数オブジェクトで条件を指定
	auto n = std::count_if(y.begin(), y.end(), [](const int v) {
		// 0 より大きい 2 の倍数
		if (v <= 0) {
			return false;
		}
		if (v % 1 != 0) {
			return false;
		}
		return true;
	});
	std::cout << n << std::endl;  // 2


	//Vector3のテスト
	//TestVector3();
}

void TestVector3()
{
	/*変数作成*/
	Vector3 ans;
	Vector3 left{ 1,2,3 };
	Vector3 right{ 0.1f,0.2f,0.3f };
	float k = 1.2;
	float fans = 0;

	/*確認*/
	//[+]
	ans = left + right;
	cout << ans.ToString() << std::endl;
	//[+]
	ans = left - right;
	cout << ans.ToString() << std::endl;
	//[+=]
	ans += left;
	cout << ans.ToString() << std::endl;
	//[-=]
	ans -= right;
	cout << ans.ToString() << std::endl;
	//[*]
	ans = left * k;
	cout << ans.ToString() << std::endl;
	//[/]
	ans = left / k;
	cout << ans.ToString() << std::endl;
	//長さ
	cout << left.Length() << endl;
	//内積
	fans = Vector3::Dot(left,right);
	cout << fans << endl;
	//外積
	ans = Vector3::Cross(left,right);
	cout << ans.ToString() << endl;
}