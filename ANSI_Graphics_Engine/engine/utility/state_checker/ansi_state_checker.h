#pragma once

namespace ansi
{
	template<typename T>
	class StateChecker
	{
	public:
		/* ������ */
		explicit StateChecker()
			: m_isFirstCheck(true)
			, m_curValue()
			, m_oldValue()
		{

		}

		/* ���� �ʱ�ȭ�κ��� ��ȭ ���θ� �˻��ϴ� �Լ� */
		bool Check()
		{
			if (m_isFirstCheck) {
				m_isFirstCheck = false; return true;	/* ù ��° �˻�� �׻� true ���� ��ȯ */
			}
			return (m_curValue != m_oldValue);			/* ���ĺ��ʹ� ��ȭ ���� ��ȯ */
		}

		
		void     Reset()				{ m_oldValue = m_curValue; }			/* ���� ���� ���� ������ �ʱ�ȭ �ϴ� �Լ� */
		void     Set(const T& value)	{ m_curValue = value;	   }			/* Setter - ���� �� */
		const T& Get()		  const		{ return   m_curValue;	   }			/* Getter - ���� �� */
		const T* GetAddress() const		{ return  &m_curValue;	   }			/* Getter - ���� ���� �ּ� */
	protected:
		bool m_isFirstCheck;		/* ù ��° �˻� ���� */
		T m_curValue;			/* ���� �� */
		T m_oldValue;			/* ���� �� */
	};

	/* ���� �˻� �迭 Ŭ���� ���ø� */
	template <typename T, unsigned SIZE>
	class StateArrayChecker
	{
	public:
		/* ������ */
		explicit StateArrayChecker()
			: m_isFirstCheck(true)
			, m_curValues()
			, m_oldValues()
		{

		}

		/* ���� �ʱ�ȭ�κ��� ��ȭ ���θ� �˻��ϴ� �Լ� */
		bool Check()
		{
			if (m_isFirstCheck) {
				m_isFirstCheck = false; return true;		/* ù ��° �˻�� �׻� true ���� ��ȯ */
			}

			for (int i{ 0 }; i < SIZE; ++i) {
				if (m_curValues[i] != m_oldValues) {
					return true;
				}
			}

			return false;
		}

		/* ���� ���� ���� ������ �ʱ�ȭ�ϴ� �Լ� */
		void Reset()
		{
			for (int i{ 0 }; i < SIZE; ++i) {
				m_oldValues[i] = m_curValues[i];
			}
		}

		/* Setter - ���� ��, ��� ���� ��*/
		void Set(int index, const T& value) { m_curValues[index] = value; }
		void SetAll(const T& value) { for (int i{ 0 }; i < SIZE; ++i) { m_curValues[i] = value; } }

		/* Getter - ���� ��, ���� ���� �ּ�, ���� �� �迭 */
		const T& Get	   (unsigned index) const { return m_curValues[index];	}
		const T* GetAddress(unsigned index) const { return &m_curValues[index]; }
		const T* GetArray()					const { return m_curValues;			}

	protected:
		bool m_isFirstCheck;		/* ù ��° �˻� ���� */
		T	 m_curValues[SIZE];		/* ���� �� �迭 */
		T	 m_oldValues[SIZE];		/* ���� �� �迭 */
	};
}

