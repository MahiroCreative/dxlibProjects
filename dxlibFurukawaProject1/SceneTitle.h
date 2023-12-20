#pragma once
class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	void Update();
	void Draw() const;

	void End();

	// �V�[�����I������������
	bool IsSceneEnd() const { return m_isSceneEnd && (m_fadeAlpha >= 255); }

private:
	// �w�i�n���h��
	int m_bgHandle;

	// BGM�n���h��
	int m_bgmHandle;

	// ���ʉ��n���h��
	int m_decideSe;


	bool m_isSceneEnd;	// �V�[���I���t���O
	// true :�^�C�g�����I�����ăQ�[����

// �t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;
};