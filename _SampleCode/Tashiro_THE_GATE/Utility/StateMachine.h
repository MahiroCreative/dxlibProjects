#pragma once
#include <cassert>
#include <functional>
#include <unordered_map>

template<class State_t> class StateMachine
{
public:
	using Delegate_t = std::function<void(void)>;

private:
	struct StateDelegateData
	{
		Delegate_t entry;
		Delegate_t update;
		Delegate_t exit;
	};

public:
	StateMachine() :
		m_isInit(true)
	{
	}

	/// <summary>
	/// �X�e�[�g�̒ǉ�
	/// </summary>
	/// <param name="state">�X�e�[�g</param>
	/// <param name="entry">�������Ƃ��ɌĂԊ֐�</param>
	/// <param name="update">���t���[���ĂԊ֐�</param>
	/// <param name="exit">�I������Ƃ��ɌĂԊ֐�</param>
	void AddState(State_t state, Delegate_t entry, Delegate_t update, Delegate_t exit)
	{
		// �d������
		if (m_stateFuncMap.find(state) != m_stateFuncMap.end())
		{
			assert(false && "���ɃX�e�[�g���ǉ�����Ă��܂�");
			return;
		}

		StateDelegateData data;
		data.entry = entry;
		data.update = update;
		data.exit = exit;
		m_stateFuncMap.emplace(state, data);
	}

	/// <summary>
	/// �X�e�[�g�̕ύX
	/// </summary>
	/// <typeparam name="State_t">�X�e�[�g</typeparam>
	void ChangeState(State_t state)
	{
		// ����Ȃ�Entry�����Ă�
		if (m_isInit)
		{
			// nullptr�łȂ���ΌĂ�
			if (m_stateFuncMap.at(state).entry)
			{
				m_stateFuncMap.at(state).entry();
			}
			m_nowState = state;
			m_isInit = false;
		}
		// �Ⴄ�X�e�[�g�������Ă�����X�V
		else if (m_nowState != state)
		{
			if (m_stateFuncMap.at(m_nowState).exit)
			{
				m_stateFuncMap.at(m_nowState).exit();
			}
			if (m_stateFuncMap.at(state).entry)
			{
				m_stateFuncMap.at(state).entry();
			}
			m_nowState = state;
		}
	}

	/// <summary>
	/// �X�V
	/// </summary>
	void Update()
	{
		m_stateFuncMap.at(m_nowState).update();
	}

	/// <summary>
	/// �X�e�[�g�̎擾
	/// </summary>
	/// <returns>���݂̃X�e�[�g</returns>
	State_t GetNowState() const { return m_nowState; }

private:
	State_t m_nowState;
	std::unordered_map<State_t, StateDelegateData> m_stateFuncMap;
	bool m_isInit;
};