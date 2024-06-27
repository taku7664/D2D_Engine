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
	std::wstring line;			// 한줄의 문자열	
	int FrameCount = 0;			// 프레임의 개수
	{
		std::getline(file, line);		// 첫번째 줄 읽기
		std::wstringstream wss(line);
		wss >> FrameCount;
	}
	m_frameData.reserve(FrameCount);
	for (int j = 0; j < FrameCount; j++)
	{
		getline(file, line);		// 한줄 읽기
		std::wstringstream wss(line);    // 한줄을 읽어서 wstringstream에 저장
		std::wstring token;
		{
			getline(wss, token, L',');	// wss의 내용을 ,를 기준으로 문자열을 분리
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
