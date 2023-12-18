#include"Enemy8.h"
#include <cassert>

//----------------------------//
// ������.
//----------------------------//
void Enemy::Init()
{
	// �G�l�~�[�̃O���t�B�b�N���������Ƀ��[�h���\�����W��������
	const char* enemyGlaphStr = "Resources/EpicEnemy.png";
	Graph = LoadGraph(enemyGlaphStr);
	DamageGraph = LoadGraph(enemyGlaphStr);
	GraphFilter(DamageGraph, DX_GRAPH_FILTER_HSB, 0, 0, 0, 256);//��������
	X = 0;
	Y = 50;
	Life = ENEMY_LIFE;

	// �G�l�~�[�����c�߂Ă��邩�ǂ����̕ϐ��Ɂw�c�߂Ă��Ȃ��x��\��FALSE����
	DamageFlag = false;

	// �G�l�~�[�̃O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(Graph, &W, &H);

	RightMove = true;
}

//----------------------------//
// �A�b�v�f�[�g.
//----------------------------//
void Enemy::Update()
{
	// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����
	if (RightMove == true)
	{
		X += 3;
	}
	else
	{
		X -= 3;
	}

	// �G�l�~�[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
	if (X > SCREEN_W - W)
	{
		X = SCREEN_W - W;
		RightMove = false;
	}
	else if (X < 0)
	{
		X = 0;
		RightMove = true;
	}

	// �G�l�~�[��`��
	// �_���[�W���󂯂Ă��邩�ǂ����ŏ����𕪊�
	if (DamageFlag == true)
	{
		DamageCounter++;

		if (DamageCounter == 5)
		{
			// �w�_���[�W�������Ă��Ȃ��x��\��FALSE����
			DamageFlag = false;
		}
	}
}

//----------------------------//
// �`��.
//----------------------------//
void Enemy::Draw()
{
	//�̗͂�����ꍇ�̂ݕ\��
	if (Life > 0)
	{
		// �_���[�W���󂯂Ă���ꍇ�̓_���[�W���̃O���t�B�b�N��`�悷��
		if (DamageFlag == true)
		{
			DrawGraph(X, Y, DamageGraph, TRUE);
		}
		else
		{
			DrawGraph(X, Y, Graph, TRUE);
		}
	}
}

void Enemy::OnDamage()
{
	// �G�l�~�[�̊��c�߂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�c�߂Ă���x��\��TRUE����
	DamageFlag = true;

	// �G�l�~�[�̊��c�߂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
	DamageCounter = 0;

	Life -= 1;
}
