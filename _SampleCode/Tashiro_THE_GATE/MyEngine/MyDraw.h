#pragma once
namespace MyEngine
{
	/// <summary>
	/// DxLib::DrawGraph�Ɠ����Ԋu�ŃV�F�[�_��p���ĕ`��
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="psH">�g�p����s�N�Z���V�F�[�_</param>
	/// <param name="firstH">�g�p�摜�P</param>
	/// <param name="secondH">�g�p�摜�Q</param>
	/// <param name="thirdH">�g�p�摜�R</param>
	/// <param name="fourthH">�g�p�摜�S</param>
	/// <param name="fifthH">�g�p�摜�T</param>
	/// <param name="sixthH">�g�p�摜�U</param>
	/// <param name="isTrans">true:���߂��� /false:���߂��Ȃ�</param>
	void DrawGraph(int x, int y, int psH, int firstH, int secondH = -1, int thirdH = -1, int fourthH = -1, int fifthH = -1, int sixthH = -1, bool isTrans = false);
	/// <summary>
	/// DxLib::DrawRotaGraph�Ɠ����Ԋu�ŃV�F�[�_��p���ĕ`��
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="psH">�g�p����s�N�Z���V�F�[�_</param>
	/// <param name="firstH">�g�p�摜�P</param>
	/// <param name="secondH">�g�p�摜�Q</param>
	/// <param name="thirdH">�g�p�摜�R</param>
	/// <param name="fourthH">�g�p�摜�S</param>
	/// <param name="fifthH">�g�p�摜�T</param>
	/// <param name="sixthH">�g�p�摜�U</param>
	/// <param name="isTrans">true:���߂��� /false:���߂��Ȃ�</param>
	void DrawRotaGraph(int x, int y, float scale, float angle, int psH, int firstH, int secondH = -1, int thirdH = -1, int fourthH = -1, int fifthH = -1, int sixthH = -1, bool isTrans = false);
}


