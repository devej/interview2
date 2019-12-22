
/******************************************************************************
Implement the Singleton design pattern in C++.

Note:
	 - Feel free to use a text editor or IDE of your choice to do this instead.
	 - If you do, simply just copy-paste your code here when you're done.
******************************************************************************/
#include <memory>

template< typename T >
class Singleton
{
private:
	Singleton() = default;

public:
	Singleton( const Singleton& ) = delete;
	Singleton& operator= ( const Singleton& ) = delete;
	~Singleton() = default;

	static std::shared_ptr<T> instance()
	{
		auto instance = std::make_shared<T>();
		return instance;
	}
};



void single()
{
	// Singleton<int32_t> q; // error, can't just instantiate
	auto s = Singleton<int64_t>::instance();
	auto t = Singleton<std::string>::instance();
}
