#pragma once
/// <summary>
/// �V�[���S�Ă��p�����钊�ۃN���X�B
/// ���ʏ����ȊO�͌p����ŃI�[�o�[���C�h���Ď����B 
/// </summary>
class SceneBase
{
protected:
	/*�����o�ϐ�*/
	//���C���[�ԍ����m��(layer0���w�i)
	int m_layer=-1;
	/*�����o�֐�*/
	//frame���̌v�Z����
	virtual void Update();
	//frame���̕`�揈��
	virtual void Draw();
	//frame���̉�������
	virtual void Sound();
};

