/*
What is the difference, if any, between the following? (assume u is of type SomeType)

SomeType t = u;
SomeType t(u);
SomeType t();
SomeType t;
*/

/*
SomeType t = u;
// Assignment constructs t from u ( SomeType& operator= ( const SomeType& ) )

SomeType t(u);
// copy constructs t from u ( SomeType( const SomeType& ) )

SomeType t();
// A function named t that takes no parameters and returns a SomeType

SomeType t;
// default constructs a SomeType named t ( SomeType() )
*/


void sigs()
{

}
