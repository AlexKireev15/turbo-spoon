#pragma once
#include <mutex>


template <class T>
class Singleton
{
private:
	inline static std::mutex instanceMutex;
	inline static T* objectInstance = nullptr;
	inline static Singleton<T>* instance = nullptr;

	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	void operator=(const Singleton&) = delete;
	void operator=(Singleton&&) = delete;

protected:
	Singleton() { }
	virtual ~Singleton()
	{
		delete objectInstance;
		objectInstance = nullptr;
	}

public:
	static T* getInstance()
	{
		if (instance == nullptr)
		{
			std::lock_guard<std::mutex> lock(instanceMutex);
			if (instance == nullptr)
			{
				instance = new Singleton<T>();
				objectInstance = new T();
			}
		}
		return objectInstance;
	}

	static void resetInstance()
	{
		if (instance != nullptr)
		{
			std::lock_guard<std::mutex> lock(instanceMutex);
			if (instance != nullptr)
			{
				Singleton<T>* instanceToDelete = instance;
				instance = nullptr;
				delete instanceToDelete;
			}
		}
	}
};


//template<class T>
//class Singleton
//{
//private:
//	inline static std::mutex instanceMutex;
//	inline static T* instance = nullptr;
//
//
//	Singleton(const Singleton&) = delete;
//	Singleton(Singleton&&) = delete;
//	void operator=(const Singleton&) = delete;
//	void operator=(Singleton&&) = delete;
//
//protected:
//	Singleton() { }
//	virtual ~Singleton() { }
//
//public:
//	static T* getInstance()
//	{
//		if (instance == nullptr)
//		{
//			std::lock_guard<std::mutex> lock(instanceMutex);
//			if (instance == nullptr)
//			{
//				instance = new T();
//			}
//		}
//		return instance;
//	}
//
//	static void resetInstance()
//	{
//		if (instance != nullptr)
//		{
//			std::lock_guard<std::mutex> lock(instanceMutex);
//			if (instance != nullptr)
//			{
//				T* instanceToDelete = instance;
//				instance = nullptr;
//				delete instanceToDelete;
//			}
//		}
//	}
//};