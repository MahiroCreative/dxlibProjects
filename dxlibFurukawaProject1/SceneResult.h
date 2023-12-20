#pragma once

class SceneResult
{
public:
	SceneResult();
	~SceneResult();

	void Init();
	void Update();
	void Draw();

	void End();

	// �V�[�����I������������
	bool IsSceneEnd() const { return m_isSceneEnd && (m_fadeAlpha >= 255); }

private:
	// �摜�̃n���h��
	int m_gameOverHandle;
	int m_bgHandle;
	// �T�E���h�n���h��
	int m_bgmHandle;
	int m_decideSe;

	// �摜�T�C�Y
	int m_graphWidth;
	int m_graphHeight;

	int m_lastPad;		// �O��̃p�b�h���
	bool m_isSceneEnd;	// �V�[���I���t���O

	// �t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;
};