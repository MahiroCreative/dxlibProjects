#pragma once

class Rect
{
public:
	Rect();
	~Rect();

	void Init();
	void Update();
	void Draw() const;

	// ��ʓ��̃����_���Ȉʒu�Ƀ����_���ȑ傫���̋�`�f�[�^��ݒ肷��
	void SetRandom();

	// �ق��̋�`�Ƃ̓����蔻��
	// ���g�Ǝw�肵���ق��̋�`�̓����蔻������
	bool IsCollision(const Rect& target) const;

	// public�Ȋ֐��o�R�Ń����o�[�ϐ��ύX
	void SetColor(unsigned int color) { m_color = color; }
	void SetFill(bool isFill) { m_isFill = isFill; }
	void SetMouseTrase(bool isTrase) { m_isMouseTrase = isTrase; }

	// �����蔻������p�ɏ㉺���E�̍��W���擾�ł���悤�ɂ���
	int GetLeft() const { return m_posX - m_width / 2; }
	int GetTop() const { return m_posY - m_height / 2; }
	int GetRight() const { return m_posX + m_width / 2; }
	int GetBottom() const { return m_posY + m_height / 2; }

private:
	// ���S���W�ƕ��A�����ŊǗ�����
	int m_posX;		// m_centerX�݂����Ȃ̂��ǂ�
	int m_posY;
	int m_width;
	int m_height;

	// �F
	unsigned int m_color;
	// �h��Ԃ��t���O
	bool m_isFill;

	// �}�E�X�Ǐ]�t���O
	bool m_isMouseTrase;
};