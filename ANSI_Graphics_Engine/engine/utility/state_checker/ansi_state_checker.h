#pragma once

namespace ansi
{
	template<typename T>
	class StateChecker
	{
	public:
		/* 생성자 */
		explicit StateChecker()
			: m_isFirstCheck(true)
			, m_curValue()
			, m_oldValue()
		{

		}

		/* 이전 초기화로부터 변화 여부를 검사하는 함수 */
		bool Check()
		{
			if (m_isFirstCheck) {
				m_isFirstCheck = false; return true;	/* 첫 번째 검사는 항상 true 값을 반환 */
			}
			return (m_curValue != m_oldValue);			/* 이후부터는 변화 여부 반환 */
		}

		
		void     Reset()				{ m_oldValue = m_curValue; }			/* 이전 값을 현재 값으로 초기화 하는 함수 */
		void     Set(const T& value)	{ m_curValue = value;	   }			/* Setter - 현재 값 */
		const T& Get()		  const		{ return   m_curValue;	   }			/* Getter - 현재 값 */
		const T* GetAddress() const		{ return  &m_curValue;	   }			/* Getter - 현재 값의 주소 */
	protected:
		bool m_isFirstCheck;		/* 첫 번째 검사 여부 */
		T m_curValue;			/* 현재 값 */
		T m_oldValue;			/* 이전 값 */
	};

	/* 상태 검사 배열 클래스 템플릿 */
	template <typename T, unsigned SIZE>
	class StateArrayChecker
	{
	public:
		/* 생성자 */
		explicit StateArrayChecker()
			: m_isFirstCheck(true)
			, m_curValues()
			, m_oldValues()
		{

		}

		/* 이전 초기화로부터 변화 여부를 검사하는 함수 */
		bool Check()
		{
			if (m_isFirstCheck) {
				m_isFirstCheck = false; return true;		/* 첫 번째 검사는 항상 true 값을 반환 */
			}

			for (int i{ 0 }; i < SIZE; ++i) {
				if (m_curValues[i] != m_oldValues) {
					return true;
				}
			}

			return false;
		}

		/* 이전 값을 현재 값으로 초기화하는 함수 */
		void Reset()
		{
			for (int i{ 0 }; i < SIZE; ++i) {
				m_oldValues[i] = m_curValues[i];
			}
		}

		/* Setter - 현재 값, 모든 현재 값*/
		void Set(int index, const T& value) { m_curValues[index] = value; }
		void SetAll(const T& value) { for (int i{ 0 }; i < SIZE; ++i) { m_curValues[i] = value; } }

		/* Getter - 현재 값, 현재 값의 주소, 현재 값 배열 */
		const T& Get	   (unsigned index) const { return m_curValues[index];	}
		const T* GetAddress(unsigned index) const { return &m_curValues[index]; }
		const T* GetArray()					const { return m_curValues;			}

	protected:
		bool m_isFirstCheck;		/* 첫 번째 검사 여부 */
		T	 m_curValues[SIZE];		/* 현재 값 배열 */
		T	 m_oldValues[SIZE];		/* 이전 값 배열 */
	};
}

