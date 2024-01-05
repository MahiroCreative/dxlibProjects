#pragma once
#include "GameCommon.h"
/// <summary>
/// �V�[���S�Ă��p�����钊�ۃN���X�B
/// ���ʏ����ȊO�͌p����ŃI�[�o�[���C�h���Ď����B 
/// </summary>
class SceneBase
{
public:
	/*�R���X�g���N�^�E�f�X�g���N�^*/
	SceneBase() {};//�R���X�g���N�^��virtual�t���Ȃ��B
	virtual ~SceneBase() {};//���Őe�̃f�X�g���N�^���Ă΂�Ȃ��悤��

	/*�����o�֐�*/
	//frame���̌v�Z����
	virtual void Update(SceneBase* nextScene) = 0;
	//frame���̕`�揈��
	virtual void Draw() const = 0;
	//frame���̉�������
	virtual void Sound() const = 0;
};

