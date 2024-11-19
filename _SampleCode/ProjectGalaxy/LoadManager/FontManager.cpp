#include "FontManager.h"
#include<string>
#include<vector>

using namespace std;

FontManager::FontManager()
{
}

FontManager::~FontManager()
{

}

FontManager& FontManager::GetInstance()
{
	static FontManager info;
	return info;
}

int FontManager::GetFontData(const char* fontfilename,const char* fontname,int size,int thick,int fonttype)
{
	string fileName = "Font/";
	//�g�p����t�H���g����������
	if (AddFontResourceEx((fileName+fontfilename).c_str(), FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}
	if (m_pathAndFontInfoes.find(fontname) == m_pathAndFontInfoes.end())
	{
		FontInfo m = FontInfo();
		
		m.handle = DxLib::CreateFontToHandle(static_cast<string>(fontname).c_str(), size, thick,fonttype);
		m.used = false;
		m_pathAndFontInfoes[fontname] = m;
		return m.handle;
	}
	else {
		m_pathAndFontInfoes[fontname].used = true;
		return m_pathAndFontInfoes[fontname].handle;
	}
}
