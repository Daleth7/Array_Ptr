//Non-member array creator implementations

    //Create via size and constructor arguments
template <
    typename T,
    class Alloc,
    class Deleter,
    typename... ConArgs
>
    __APTR_INST__ make_array(
        typename __APTR_INST__::size_type pop,
        ConArgs&&... c_args
    )
{return __APTR_INST__(pop, std::forward(c_args)...);}

    //Create via size and pointer to dynamically allocated memory.
__APTR_TEMPL__
    __APTR_INST__ make_array(
        typename __APTR_INST__::size_type pop,
        typename __APTR_INST__::pointer src
    )
{return __APTR_INST__(pop, src);}

    //Create via a pointer to static array
template <
    typename T,
    class Alloc,
    class Deleter,
    typename __APTR_INST__::size_type N
>
    __APTR_INST__ make_array(typename __APTR_INST__::value_type arr[N])
{return __APTR_INST__(std::forward(arr));}

    //Create via size and a generator (callback) of type
    //  array_ptr::value_type(array_ptr::size_type)
template <
    typename T,
    class Alloc,
    class Deleter,
    typename Generator
>
    __APTR_INST__ make_array(
        typename __APTR_INST__::size_type pop,
        const Generator& gen
    )
{
    __APTR_INST__ toreturn(pop);
    typename __APTR_INST__::size_type i(0);
    while(pop-- > 0 && i < pop){
        toreturn[pop] = gen(pop);
        toreturn[i] = gen[i];
        ++i;
    }
    return toreturn;
}