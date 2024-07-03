#pragma once
#include "../Helper/ReferenceCounter.h"

namespace Resource
{
	class Resource abstract
		: public ReferenceCounter
	{
	public:

		Resource();
		virtual ~Resource();

	protected:
		std::wstring m_key;   // 키값
		ResourceType type;    // 리소스 타입
	};
}