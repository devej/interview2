/*
Step 1) Load the following URL:
        https://rextester.com/DZN55603

Step 2) When you're done, press "Fork it", enter your name as the title and paste the new URL into the textbox below:
        https://rextester.com/BFLW81313
*/

/******************************************************************************
Implement a queue. There are two methods, Push and Pop.

Push places an item at the end of the queue.

The Pop() method removes and returns the first item in the queue.

If the queue is empty, it blocks until it is not empty and then proceeds to
remove and return the first item in the queue.

Note:
     - Feel free to use a text editor or IDE of your choice to do this instead.
     - If you do, simply just copy-paste your code here when you're done.
******************************************************************************/
#include <mutex>
#include <chrono>
#include <thread>
#include <iostream>
#include <atomic>
using namespace std::chrono_literals;


// global ID counter
std::int64_t ID = 0;


struct Item
{
    Item() : _id(++ID){}
    Item* _prev = nullptr;
    Item* _next = nullptr;
    std::int64_t _id;
};

//
// Queue assumes no ownership of Items.
// Caller must ensure proper allocation and cleanup.
//

class Queue
{
private:
    Item* _head = nullptr;
    Item* _tail = nullptr;
    std::atomic<int64_t> _size = 0;
    std::mutex _mutex;

public:
    void Print()
    {
        std::cout << "Printing " << _size;
        std::scoped_lock lock( _mutex );
        Item* i = _head;
        while( i )
        {
            std::cout << ", Item " << i->_id;
            i = i->_next;
        }
        std::cout << std::endl;
    }

    std::int64_t Size()
    {
        return _size;
    }

    void Push( Item* i )
    {
        if( !i ) {
            throw std::runtime_error( "Cannot push nullptr item" );
        }

        std::scoped_lock lock( _mutex );
        i->_prev = _tail;
        i->_next = nullptr;

        if( _tail )
            _tail->_next = i;

        _tail = i;

        if( !_head )
            _head = i;

        ++_size;
    }

    Item* Pop()
    {
        while( _size == 0 )
        {
            std::this_thread::sleep_for( 1s ); // just being nice for this exercise
        }

        std::lock_guard<std::mutex> lock( _mutex );
        Item* p = _head;
        _head = p->_next;
        --_size;
        return p;
    }
};


void question6()
{
    auto q = Queue();
    auto i1 = std::make_unique<Item>();
    auto i2 = std::make_unique<Item>();
    q.Push( i1.get() ); // id 1
    q.Push( i2.get() ); // id 2

    if( q.Size() != 2 ) {
        std::cout << "got size " << q.Size() << '\n';
        throw std::logic_error( "bad size" );        
    }

    auto r = q.Pop();
    if( r->_id != 1 ) {
        std::cout << "got id " << r->_id << '\n';
        throw std::logic_error( "unexpected item id" );
    }

    auto s = q.Pop();
    if( s->_id != 2 ) {
        std::cout << "got id " << s->_id << '\n';
        throw std::logic_error( "unexpected item id" );
    }

    auto i3 = std::make_unique<Item>();
    q.Push( i3.get() );
    auto t = q.Pop();
    if( t->_id != 3 ) {
        std::cout << "got id " << t->_id << '\n';
        throw std::logic_error( "Unexpected item id" );
    }
}
