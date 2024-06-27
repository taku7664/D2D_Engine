#pragma once
#include "../Helper/ReferenceCounter.h"

namespace Resource
{
	class Resource2D abstract
		: public ReferenceCounter
	{
	public:

		Resource2D();
		virtual ~Resource2D();

	protected:
		std::wstring m_key;   // Ű��
		ResourceType type;    // ���ҽ� Ÿ��
	};
}