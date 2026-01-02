#pragma once

#include <memory>
#include <mutex>

// 可继承单例模板类
template<typename T>
class SingletonBase
{
public:
	static std::shared_ptr<T> getInstance()
	{
		static std::once_flag flag;
		std::call_once(flag, [&]() {
			m_instance = std::shared_ptr<T>(new T);
		});

		return m_instance;
	}

private:
	static std::shared_ptr<T> m_instance;

protected:
	SingletonBase() = default;
	~SingletonBase() = default;
	SingletonBase(const SingletonBase<T>&) = delete;
	SingletonBase& operator=(const SingletonBase<T>&) = delete;
};

template<typename T>
std::shared_ptr<T> SingletonBase<T>::m_instance = nullptr;
