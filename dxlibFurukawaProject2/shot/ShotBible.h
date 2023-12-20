#pragma once
#include "ShotBase.h"
class ShotBible : public ShotBase
{
public:
	ShotBible();
	virtual ~ShotBible();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() const override;

	/// <summary>
	/// �e���X�^�[�g������
	/// </summary>
	/// <param name="pos">���ˈʒu</param>
	virtual void Start(Vec2 pos) override;

private:
	// ��莞�Ԍo�߂�����������߂ɐ������Ă���̃t���[���𐔂���
	int m_frameCount;

	// �v���C���[���猩�Ăǂ̕����ɂ��邩
	float m_angle;
};

