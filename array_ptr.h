#ifndef POINTERARRAY_H
#define POINTERARRAY_H

/*
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
*/

#include <memory>
#include <functional>
#include <cstddef>

#define __APTR_TEMPL__  \
    template <          \
        typename T,     \
        class Alloc     \
    >

#define __APTR_INST__ array_ptr<T, Alloc>

template <
    typename T,
    class Alloc = std::allocator<T>
>
class array_ptr{
    public:
//Type aliases
        using value_type        = T;
        using allocator_type    = Alloc;
        using pointer           = value_type*;
        using const_pointer     = value_type const *;
        using reference         = value_type&;
        using const_reference   = value_type const &;
        using difference_type   = std::ptrdiff_t;
        using null_type         = std::nullptr_t;
        using size_type         = std::size_t;

        static constexpr null_type null = nullptr;

//Read-only
        size_type size()                        const;
        size_type capacity()                    const;
        size_type index()                       const;
    //count() returns how many instances of array_ptr
    //  are pointing to the same data.
        size_type count()                       const;
        bool shared_with(const __APTR_INST__&)  const;
        const_reference at(size_type)           const;
        const_reference front()                 const;
        const_reference back()                  const;
        const_pointer get()                     const;
        const_pointer data()                    const;
        const_reference junk()                  const;
        const_reference operator*()             const;
        const_pointer operator->()              const;
        const_reference operator[] (size_type)  const;
        bool unique()                           const;
        short compare(const __APTR_INST__&)     const;

//Type casts
        operator void*()                        const;
        explicit operator value_type*();
        explicit operator value_type const*()   const;

//Dereference and subscript operators
        reference operator*();
        pointer operator->();
        reference operator[] (size_type);

//Arithmetic operators  
        __APTR_INST__& operator+=(size_type);
        __APTR_INST__& operator-=(size_type);
        __APTR_INST__& operator++();
        __APTR_INST__& operator--();
        __APTR_INST__ operator++(int);
        __APTR_INST__ operator--(int);

//Size related
        void resize(size_type, const_reference = value_type());
        template <typename... ConArgs>
            void resize(size_type, ConArgs&&...);
            //Return the new capacity
        size_type reserve(size_type);

//Iterators
        using iterator          = __APTR_INST__;
        using const_iterator    = iterator const;

        const_iterator cbegin()const;
        const_iterator cend()const;
        const_iterator begin()const;
        const_iterator end()const;
        iterator begin();
        iterator end();

//Inserting or removing elements
            //Warnings:
            //  - Similarly to std::vector, these are slow operations
            //  - Inserting elements may change what values other array_ptr
            //      instances will point to but will never invalidate them.
            //  - Erasing elements may invalidate other instances of
            //      array_ptr if enough elements are removed.
        iterator insert(size_type, const_reference);
        iterator insert(size_type, size_type, const_reference);
        iterator insert(const iterator&, const_reference);
        iterator insert(const iterator&, size_type, const_reference);
        iterator erase(size_type);
        iterator erase(size_type, size_type);
        iterator erase(const iterator&);
        iterator erase(const iterator&, size_type);
        iterator push_back(const_reference, size_type = 1);
        iterator push_front(const_reference, size_type = 1);
        iterator pop_back(size_type = 1);
        iterator pop_front(size_type = 1);
        template <typename... ConArgs>
            iterator emplace(size_type, ConArgs&&...);
        template <typename... ConArgs>
            iterator emplace(const iterator&, ConArgs&&...);
        template <typename... ConArgs>
            iterator emplace_back(ConArgs&&...);
        template <typename... ConArgs>
            iterator emplace_front(ConArgs&&...);

//Other modifiers
        reference front();
        reference back();
        pointer get();
        pointer data();
        reference junk();
        void reset_index();
        size_type change_index(size_type);
            //Note that when clear() is called array_ptr
            //  will not be set to nullptr.
        void clear();
        void reset(const __APTR_INST__&);
            //U* shall be convertible to pointer
        template <typename U>
            void reset(size_type = 0, U* = null);

//Constructors and destructor
        array_ptr();
        array_ptr(null_type);
        array_ptr(size_type, const_reference = value_type());
        array_ptr(size_type, pointer&);
        template <typename... ConArgs>
            array_ptr(size_type, ConArgs&&...);
        template <size_type N>
            array_ptr(const value_type (&)[N]);
        array_ptr(const __APTR_INST__&);
        __APTR_INST__& operator=(const __APTR_INST__&);
        array_ptr(__APTR_INST__&&);
        __APTR_INST__& operator=(__APTR_INST__&&);
        ~array_ptr();

    protected:
        struct Shared_Data{
            pointer     m_array;
            size_type
                        m_length,
                        m_capacity,
                        m_pcount
            ;

            static size_type calc_new_capacity(size_type, size_type);

            Shared_Data();
            Shared_Data(size_type);
            ~Shared_Data();
            Shared_Data(const Shared_Data&)             = delete;
            Shared_Data(Shared_Data&&)                  = delete;
            Shared_Data& operator=(const Shared_Data&)  = delete;
            Shared_Data& operator=(Shared_Data&&)       = delete;
        };
//Helpers
        void copy_data(Shared_Data*const &);
        void free();
        size_type calc_new_capacity(size_type = 1)const;
        bool is_valid_index(size_type)const;
        
    private:
        size_type       m_index;
        value_type      m_junk;
        Shared_Data*    m_data;
};

//Other arithmetic operators
__APTR_TEMPL__
__APTR_INST__ operator+(
    const __APTR_INST__&,
    typename __APTR_INST__::size_type
);
__APTR_TEMPL__
__APTR_INST__ operator-(
    const __APTR_INST__&,
    typename __APTR_INST__::size_type
);
__APTR_TEMPL__
__APTR_INST__ operator+(
    typename __APTR_INST__::size_type,
    const __APTR_INST__&
);
__APTR_TEMPL__
__APTR_INST__ operator-(
    typename __APTR_INST__::size_type,
    const __APTR_INST__&
);
__APTR_TEMPL__
typename __APTR_INST__::size_type
    operator-(const __APTR_INST__&, const __APTR_INST__&);

//Comparison
__APTR_TEMPL__
bool operator==(const __APTR_INST__&, const __APTR_INST__&);
__APTR_TEMPL__
bool operator!=(const __APTR_INST__&, const __APTR_INST__&);
__APTR_TEMPL__
bool operator<(const __APTR_INST__&, const __APTR_INST__&);
__APTR_TEMPL__
bool operator>(const __APTR_INST__&, const __APTR_INST__&);
__APTR_TEMPL__
bool operator<=(const __APTR_INST__&, const __APTR_INST__&);
__APTR_TEMPL__
bool operator>=(const __APTR_INST__&, const __APTR_INST__&);
__APTR_TEMPL__
bool operator==(
    const __APTR_INST__&,
    const typename __APTR_INST__::null_type&
);
__APTR_TEMPL__
bool operator!=(
    const __APTR_INST__&,
    const typename __APTR_INST__::null_type&
);
__APTR_TEMPL__
bool operator==(
    const typename __APTR_INST__::null_type&,
    const __APTR_INST__&
);
__APTR_TEMPL__
bool operator!=(
    const typename __APTR_INST__::null_type&,
    const __APTR_INST__&
);


//Non-member array creators
    //Create via size and constructor arguments

template <
    typename T,
    class Alloc,
    class Deleter,
    typename... ConArgs
>
    __APTR_INST__ make_array(typename __APTR_INST__::size_type, ConArgs&&...);
    //Create via size and pointer to dynamically allocated memory.
__APTR_TEMPL__
    __APTR_INST__ make_array(
        typename __APTR_INST__::size_type,
        typename __APTR_INST__::pointer
    );
    //Create via a pointer to static array
template <
    typename T,
    class Alloc,
    class Deleter,
    typename __APTR_INST__::size_type N
>
    __APTR_INST__ make_array(typename __APTR_INST__::value_type[N]);
    //Create via size and a generator (callback) of type
    //  array_ptr::value_type(array_ptr::size_type)
template <
    typename T,
    class Alloc,
    class Deleter,
    typename Generator
>
    __APTR_INST__ make_array(typename __APTR_INST__::size_type, const Generator&);

#include "array_ptr_Impl/array_ptr_Read_Only.inl"
#include "array_ptr_Impl/array_ptr_Dereference.inl"
#include "array_ptr_Impl/array_ptr_Arithmetic.inl"
#include "array_ptr_Impl/array_ptr_Size.inl"
#include "array_ptr_Impl/array_ptr_Iterator.inl"
#include "array_ptr_Impl/array_ptr_Insert_Erase.inl"
#include "array_ptr_Impl/array_ptr_Modifier.inl"
#include "array_ptr_Impl/array_ptr_ConDestructor.inl"
#include "array_ptr_Impl/array_ptr_Shared_Data.inl"
#include "array_ptr_Impl/array_ptr_Helper.inl"
#include "array_ptr_Impl/array_ptr_Nonmember.inl"
#include "array_ptr_Impl/array_ptr_Array_Creators.inl"
#include "array_ptr_Impl/array_ptr_Type_Cast.inl"

#undef __APTR_TEMPL__
#undef __APTR_INST__
    
#endif