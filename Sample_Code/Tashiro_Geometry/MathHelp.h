#pragma once
#include "Vec3.h"
#include "Quaternion.h"

// FIXME: �����̃T�}���[������

// �������m�����s������
bool IsParallelOnLine(const Vec3& startA, const Vec3& endA, const Vec3& startB, const Vec3& endB);
// �������ʂ��܂����ł��邩����
bool IsCrossSurfaceOnLine(const Vec3& start, const Vec3& end, const Vec3& center, const Vec3& norm);

// �ŋߐړ_���擾
Vec3 GetNearestPtOnLine(const Vec3& point, const Vec3& start, const Vec3& end);
Vec3 GetNearestPtOnLine(const Vec3& point, const Vec3& start, const Vec3& end, float& rate);
// �������m�̍ŋߐړ_���擾
void GetNearestPtOnLine(const Vec3& centerA, const Vec3& dirA, const Vec3& centerB, const Vec3& dirB, Vec3& outPtA, Vec3& outPtB);
// �{�b�N�X��ł̍ŋߐړ_���擾
Vec3 GetNearestPtOnBox(const Vec3& pos, const Vec3& boxPos, const Vec3& boxScale, const Quaternion& rot);
// ������ɍŋߐړ_�����邩�̔���
bool IsNearestPointOnLine(const Vec3& point, const Vec3& start, const Vec3& end);


// ���Ɩʂ̌�_���擾
Vec3 GetCrossPtSurfaceAndLine(const Vec3& start, const Vec3& end, const Vec3& center, const Vec3& norm);
// �_�Ɩʂ̌�_���擾
Vec3 GetCrossPtSurfaceAndPt(const Vec3& pt, const Vec3& center, const Vec3& norm);

// 2�̐����̉�]�N�I�[�^�I�����擾
Quaternion GetQuaternion(const Vec3& v1, const Vec3& v2);