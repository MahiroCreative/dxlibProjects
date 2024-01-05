#pragma once
#include "GameCommon.h"
/// <summary>
/// �Q�[���I�u�W�F�N�g�S�Ă��p�����钊�ۃN���X�B
/// ���ʏ����ȊO�͌p����ŃI�[�o�[���C�h���Ď����B 
/// </summary>
class GameObjectBase
{
public:
	/*�����o�ϐ�*/
	//���C���[�ԍ����m��(layer0���w�i)
	int Layer = -1;

	/*�R���X�g���N�^�E�f�X�g���N�^*/
	GameObjectBase() {};//�R���X�g���N�^��virtual�t���Ȃ��B
	virtual ~GameObjectBase() {};//���Őe�̃f�X�g���N�^���Ă΂�Ȃ��悤��

	/*�����o�֐�*/
	//frame���̌v�Z����
	virtual void Update() = 0;
	//frame���̕`�揈��
	virtual void Draw() const = 0;
	//frame���̉�������
	virtual void Sound() const = 0;
private:
	/*�����o�ϐ�*/
	int _drawHandle=-1;//�摜�n���h��
	IntVector _pos;//���W
};

