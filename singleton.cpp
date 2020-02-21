
/******************************************************************************
Implement the Singleton design pattern in C++.

Note:
	 - Feel free to use a text editor or IDE of your choice to do this instead.
	 - If you do, simply just copy-paste your code here when you're done.
******************************************************************************/
#include <memory>
// #include <iostream>
#include <string>

template< typename T >
class Singleton
{
private:
	Singleton() = default;

public:
	Singleton( const Singleton& ) = delete;
	Singleton& operator= ( const Singleton& ) = delete;
	~Singleton() = default;

	template< typename ...Args >
	static std::shared_ptr<T> instance( Args&&... args )
	{
		auto instance = std::make_shared<T>( std::forward<Args>(args)... );
		return instance;
	}
};


void single()
{
	// Singleton<int32_t> q; // error, can't just instantiate
	auto s = Singleton<int64_t>::instance();
	auto t = Singleton<std::string>::instance( "just a string" );
}
