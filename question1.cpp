
// https://rextester.com/UQVAE43209
// When you're done, press "Fork it", enter your name as the title and paste the new URL into the textbox below:
// https://rextester.com/RVW84318

/******************************************************************************
Write a function that takes three integers as parameters (N, a, and b) and
behaves as follows:

For every integer between 1 and N (inclusive), print "X: cat" if said integer
is cleanly divisible by a, where X is said integer.

Similarly, for every integer between 1 and N (inclusive), print "X: dog" if
said integer is cleanly divisible by b, where X is said integer.

Note:
     - Feel free to use a text editor or IDE of your choice to do this instead.
     - If you do, simply just copy-paste your code here when you're done.
******************************************************************************/
#include <cstdint>
#include <iostream>


void question1( std::int64_t N, std::int64_t a, std::int64_t b )
{
    for( std::int64_t x = 1; x <= N; ++x )
    {
        if( x % a == 0 )
            std::cout << x << ": cat\n";
        
        if( x % b == 0 )
            std::cout << x << ": dog\n";
    }
}
