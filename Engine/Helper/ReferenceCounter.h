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
			// �ı��ڿ� virtual Ű���带 ��������Ƿ� �ڽ�Ŭ������ �ı��ڰ� ȣ��ȴ�. 		
			delete this;
			return 0;
		}
		return m_refCount;
	}
	unsigned int GetRefCount() {
		return m_refCount;
	}
};