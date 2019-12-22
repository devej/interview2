
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
#include <queue>
#include <atomic>
#include <condition_variable>


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
	std::condition_variable _cond;
	std::mutex _mutex;

public:
	~Queue() {
		_cond.notify_all();
	}

	void print()
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

	bool empty() {
		return _size == 0;
	}

	std::int64_t size() {
		return _size;
	}

	void push( Item* i )
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
		_cond.notify_one();
	}

	Item* pop()
	{
		std::unique_lock mlock( _mutex );
		_cond.wait( mlock, [this] { return _size > 0; } );

		Item* p = _head;
		_head = p->_next;
		--_size;
		return p;
	}
};

template< typename T >
class ConcurrentQueue
{
private:
	std::queue< T > _queue;
	std::condition_variable _cond;
	std::mutex _mutex;

public:
	~ConcurrentQueue()
	{
		_cond.notify_all();
	}

	void print()
	{
		std::cout << "Printing " << _queue.size();
		std::scoped_lock lock(_mutex);
		for( auto& i : _queue )
		{
			std::cout << ", " << i;
		}
		std::cout << std::endl;
	}

	bool empty()
	{
		std::scoped_lock lock( _mutex );
		return _queue.empty();
	}

	void clear()
	{
		std::scoped_lock lock( _mutex );
		while( !_queue.empty() )
		{
			_queue.pop();
		}
	}

	typename std::queue<T>::size_type size()
	{
		std::scoped_lock lock( _mutex );
		return _queue.size();
	}

	void push( T v )
	{
		{
			std::scoped_lock lock( _mutex );
			_queue.emplace( std::move(v) );
		}
		_cond.notify_one();
	}

	T pop()
	{
		std::unique_lock mlock( _mutex );
		_cond.wait( mlock, [this] { return !_queue.empty(); } );
		auto r = std::move( _queue.front() );
		_queue.pop();
		return r;
	}
};

void queue()
{
	auto q = ConcurrentQueue<int64_t>();
	q.push( 1 );
	q.push( 2 );

	if( q.size() != 2 ) {
		std::cout << "got size " << q.size() << '\n';
		throw std::logic_error( "bad size" );        
	}

	auto r = q.pop();
	if( r != 1 ) {
		std::cout << "got " << r << '\n';
		throw std::logic_error( "expected 1" );
	}

	auto s = q.pop();
	if( s != 2 ) {
		std::cout << "got " << s << '\n';
		throw std::logic_error( "expected 2" );
	}

	q.push( 3 );
	auto t = q.pop();
	if( t != 3 ) {
		std::cout << "got " << t << '\n';
		throw std::logic_error( "expected 3" );
	}

	q.clear();
	if( !q.empty() )
	{
		std::cout << "expected empty\n";
		throw std::logic_error( "not empty" );
	}
}
