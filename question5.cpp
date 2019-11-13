/*
Step 1) Load the following URL:
        https://rextester.com/XOH95613

Step 2) When you're done, press "Fork it", enter your name as the title and paste the new URL into the textbox below:
        https://rextester.com/AMDXCP22430
*/

/******************************************************************************
Implement the Singleton design pattern in C++.

Note:
     - Feel free to use a text editor or IDE of your choice to do this instead.
     - If you do, simply just copy-paste your code here when you're done.
******************************************************************************/
#include <memory>

class Singleton
{
private:
    struct create_tag{};
    Singleton() = default;
    static std::shared_ptr<Singleton> _instance;

public:
    explicit Singleton( create_tag ){};
    Singleton( const Singleton& ) = delete;
    Singleton& operator= ( const Singleton& ) = delete;
    ~Singleton() = default;

    static std::shared_ptr<Singleton> instance() {
        if( !_instance )
            _instance = std::make_shared<Singleton>(create_tag());

        return _instance;
    }
};


std::shared_ptr<Singleton> Singleton::_instance;


void question5()
{
    // Singleton q; // error, can't create
    // Singleton q( create_tag{} );  // error - secret tag is private
    auto s = Singleton::instance();
    auto t = Singleton::instance();
    // *s = *t; // error, can't assign
    // auto u( *(Singleton::create()) ); // error, can't copy
}
