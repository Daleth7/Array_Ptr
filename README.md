Array_Ptr
=========

A container-like class which combines attributes of std::shared_ptr and std::vector while preserving C-array/raw 
pointer semantics. This is to encourage the treatment of the instances not as just wrappers but to treat them as
raw pointers that manage themselves.

From array_ptr.h:

    array_ptr<T, Alloc> is a class template that is a combination
of std::vector<T, Alloc> and std::shared_ptr<T>, i.e. the class can be
treated as an array like std::vector<T, Alloc> but should be used as a
pointer to an array. Thus, as a pointer, array_ptr<T, Alloc>
shall use reference counting and shall be dereferenced like
std::shared_ptr<T>.

    Unique to array_ptr<T, Alloc>, to encourage treating its
instances like pointers, is that it shall allow comparison to
std::nullptr and shall allow pointer arithmetic.
For example:

array_ptr<char> myCharArray; //Default value is nullptr
bool isNull = myCharArray == std:nullptr; //Shall evaluate to true
array_ptr<int> myArray {1, 2, 3, 4};
bool eq = *(myArray + 2) == myArray[2]; //Shall evaluate to true

    In addition, the object as a pointer shall be restricted to pointer
to items within bounds. Any attempt at out-of-bounds access shall write
or read to junk storage which can be accessed with junk().

    Important in the use of array_ptr<T, Alloc> is that it
remembers an index as well, i.e. it is similar to:

const char* cptr = "Hello world.";
const char* cptr2 = cptr + 5; //cptr2 is now relative to index 5

array_ptr<int> myArray {1, 2, 3, 4};
myArray += 2; //myArray is now relative to index 2

All properties of array_ptr shall behave with respect to the current
index of the object, with the exception of change_index() and reset_index().
For example:

array_ptr<char> myArray(40, 'g');
auto copy = myArray;
copy.change_index(25);  //The pointer is now relative to index 25.
                        //  myArray's index does not change.
*copy = 'i';    //This sets the 26th element to 'i' and is equivalent to
                //  writing myArray[25] = 'i' or *(myArray+25) = 'i'.
copy[2] = 'l';  //This sets the 28th element to 'l' and is equivalent to
                //  writing myArray[27] = 'l' or *(myArray+27) = 'l'.
copy.change_index(15);  //copy is now relative to index 15 as if writing
                        //  copy = myArray + 15.

The index may be set back to 0 by calling reset_index().

    Note that since this shall be a pointer to array, the type T in
array_ptr<T, Alloc> must be default constructible.

    Also note that this class shall take ownership of pointers to
dynamically allocated memory.
