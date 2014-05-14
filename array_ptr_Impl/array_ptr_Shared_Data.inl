//Shared_Data implementations


__APTR_TEMPL__
__APTR_INST__::Shared_Data::Shared_Data(size_type newsize)
    : m_array(nullptr)
    , m_length(newsize)
    , m_capacity((newsize*9)/8+1)
    , m_pcount(1)
{
    allocator_type alloc;
    m_array = alloc.allocate(m_capacity, nullptr);
    for(size_type i(0); i < m_capacity; ++i)
        alloc.construct(m_array+i, value_type());
}

__APTR_TEMPL__
__APTR_INST__::Shared_Data::~Shared_Data(){
    allocator_type dealloc;
    for(size_type i(0); i < m_capacity; ++i)
        dealloc.destroy(m_array+i);
    dealloc.deallocate(m_array, m_capacity);
    m_array = null;
}