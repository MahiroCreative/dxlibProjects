#pragma once
#include <string>

class FileManager;

/// <summary>
/// �t�@�C���x�[�X
/// </summary>
class FileBase
{
friend FileManager;

public:
	FileBase(FileManager& mgr);
	virtual ~FileBase();

	/// <summary>
	/// �n���h���̎擾
	/// </summary>
	/// <returns>�n���h��</returns>
	int GetHandle() const { return m_handle; }
	/// <summary>
	/// �t�@�C�����̎擾(�p�X�łȂ��ג���)
	/// </summary>
	/// <returns>�t�@�C����</returns>
	const std::wstring& GetName() const { return m_name; }

private:
	/// <summary>
	/// �n���h���̍폜
	/// </summary>
	virtual void Delete() abstract;
	void End() { m_isEnd = true; }

protected:
	FileManager& m_mgr;
	std::wstring m_name;
	int m_handle;
	int m_refCount;
	bool m_isEternal;
	bool m_isEnd;
};
