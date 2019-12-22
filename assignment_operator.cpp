
/******************************************************************************
Implement the assignment operator for Foo.

Note:
	 - Feel free to use a text editor or IDE of your choice to do this instead.
	 - If you do, simply just copy-paste your code here when you're done.
******************************************************************************/

class Bar;

struct FooParent
{
	FooParent& operator=( const FooParent& /*rhs*/ ) { return *this; }
};


class Foo : public FooParent
{
public:
	Foo& operator=( const Foo& rhs )
	{
		FooParent::operator=( rhs ); // assumes FooParent _has_ an operator=
		
		// one possible implementation, both objects will point to the same b1 & b2.
		b1 = rhs.b1;
		b2 = rhs.b2;

		// alternate implementation - rely on Bar's assignment operator
		// *b1 = *rhs.b1;
		// *b2 = *rhs.b2;
		return *this;
	}

private:
	Bar *b1, *b2;
};

void assignment_operator()
{
	
}