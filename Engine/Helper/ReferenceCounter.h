#pragma once

class ReferenceCounter
{
private:
	unsigned int m_refCount;
public:
	ReferenceCounter() : m_refCount(0) {}
	virtual ~ReferenceCounter() { }

	unsigned int AddRef() {
		m_refCount++;
		return m_refCount;
	}

	unsigned int Release() {
		m_refCount--;
		if (m_refCount == 0) {
			// 파괴자에 virtual 키워드를 사용했으므로 자식클래스의 파괴자가 호출된다. 		
			delete this;
			return 0;
		}
		return m_refCount;
	}
	unsigned int GetRefCount() {
		return m_refCount;
	}
};