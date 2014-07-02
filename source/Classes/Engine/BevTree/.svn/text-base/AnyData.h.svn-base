#ifndef __TUTILITY_ANYDATA_H__
#define __TUTILITY_ANYDATA_H__

#include <assert.h>

namespace BehaviorTree{
	class AnyData
	{
	public:
		template<typename RealDataType>
		AnyData(RealDataType* data)
			: m_RealData(data)
		{}
		template<typename RealDataType>
		RealDataType& GetRealDataType(){
			assert(m_RealData);
			return *reinterpret_cast<RealDataType*>(m_RealData);
		}
		template<typename RealDataType>
		const RealDataType& GetRealDataType() const{
			assert(m_RealData);
			return *reinterpret_cast<const RealDataType*>(m_RealData);
		}
		template<typename RealDataType>
		AnyData& operator =(RealDataType* _Data)
		{
			Set<RealDataType>(_Data);
			return *this;
		}
	private:
		template<typename RealDataType>
		void Set(RealDataType* _Data)
		{
			m_RealData = reinterpret_cast<void*>(_Data);
		}

	private:
		void*				m_RealData;
	};
}
#endif