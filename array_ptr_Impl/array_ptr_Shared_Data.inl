//Shared_Data implementations

__APTR_TEMPL__
auto __APTR_INST__::Shared_Data::calc_new_capacity
    (size_type old_cap, size_type offset) -> size_type
{return (old_cap*9)/8 + offset;}

__APTR_TEMPL__
__APTR_INST__::Shared_Data::Shared_Data()
    : m_array(null)
    , m_length(0)
    , m_capacity(0)
    , m_pcount(1)
{}

__APTR_TEMPL__
__APTR_INST__::Shared_Data::Shared_Data(size_type newsize)
    : m_array(null)
    , m_length(newsize)
    , m_capacity(calc_new_capacity(newsize, 1))
    , m_pcount(1)
{
    allocator_type alloc;
    m_array = alloc.allocate(m_capacity, null);
    for(size_type i(0); i < m_capacity; ++i)
        alloc.construct(m_array+i, value_type());
}

__APTR_TEMPL__
__APTR_INST__::Shared_Data::~Shared_Data(){
    if(m_array != null){
        allocator_type dealloc;
        for(size_type i(0); i < m_capacity; ++i)
            dealloc.destroy(m_array+i);
        dealloc.deallocate(m_array, m_capacity);
    }
    m_array = null;
}