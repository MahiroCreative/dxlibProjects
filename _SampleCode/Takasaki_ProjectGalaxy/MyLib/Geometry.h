//#pragma once
//#include"Vec2.h"
//#include"Vec3.h"
//
////�T�C�Y��\���\����
//struct Size {
//public:
//	Size() :w(0), h(0) {}
//	Size(float inw, float inh) :w(inw), h(inh) {}
//	float w;
//	float h;
//};
//
/////��`��\������\����
//class Rect {
//public:
//	Vec2 center;
//	Size size;
//	Rect();
//	Rect(float x, float y, float w,float h);
//	Rect(Vec2& pos, Size& sz);
//	const float Left()const;
//	const float Top()const;
//	const float Right() const;
//	const float Bottom()const;
//	const float Width()const { return size.w; }
//	const float Height()const { return size.h; }
//
//	///��`��`�悷��
//	///@param color �F��0x00000000�`0xffffffff�Ŏw�肷��(�f�t�H���g��)
//	void Draw(unsigned int color = 0xffffffff);
//
//	///��`��`�悷��(�I�t�Z�b�g��)
//	///@param offset ���炵���ʒu�ɕ\���������ꍇ�ɃI�t�Z�b�g�l���w��
//	///@param color �F��0x00000000�`0xffffffff�Ŏw�肷��(�f�t�H���g��)
//	void Draw(const Vec2& offset, unsigned int color = 0xffffffff);
//	
//	///���A�E�A��A�������`�����
//	///@param left ��
//	///@param right �E
//	///@param top ��
//	///@param bottom ��
//	static Rect CreateRectFromLRTB(float left, float right, float top, float bottom);
//
//	///��̋�`����d�Ȃ��`�����
//	///@param rcA ��`A
//	///@param rcB ��`B
//	static Rect CreateOverlappedRangeRect(const Rect& rcA, const Rect& rcB);
//};
//
//class Geometry
//{
//};
//
