// What is wrong, if anything, with the following function prototype?

// MyStruct& operator+(const MyStruct& myStruct1, const MyStruct& myStruct2);

// Returning a reference is (almost certainly) wrong.  It is likely a ref to a temp that will
// be out of scope immediately.  Return a value type.
// e.g.  MyStruct operator+(const MyStruct& myStruct1, const MyStruct& myStruct2);

void question2()
{
    
}