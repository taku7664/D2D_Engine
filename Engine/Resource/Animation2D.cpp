#include "pch.h"
#include "Animation2D.h"

Resource::Animation2D::Animation2D(std::wstring _key, Resource::Sprite2D* _sprite, std::wstring _csvPath)
{
	m_key = _key;
	type = ResourceType::Animation2D;
	m_sprite = _sprite;

	std::wifstream file(_csvPath);
	if (!file.is_open()) {
		assert(false);
	}
	std::wstring line;			// ������ ���ڿ�	
	int FrameCount = 0;			// �������� ����
	{
		std::getline(file, line);		// ù��° �� �б�
		std::wstringstream wss(line);
		wss >> FrameCount;
	}
	m_frameData.reserve(FrameCount);
	for (int j = 0; j < FrameCount; j++)
	{
		getline(file, line);		// ���� �б�
		std::wstringstream wss(line);    // ������ �о wstringstream�� ����
		std::wstring token;
		{
			getline(wss, token, L',');	// wss�� ������ ,�� �������� ���ڿ��� �и�
			m_frameData[j].rect.left = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_frameData[j].rect.top = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_frameData[j].rect.right = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_frameData[j].rect.bottom = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_frameData[j].center.x = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_frameData[j].center.y = (float)_wtoi(token.c_str());
		}
	}
}

Resource::Animation2D::~Animation2D()
{
}
