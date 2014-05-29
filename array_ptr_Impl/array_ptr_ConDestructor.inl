//Constructors and destructor implementations

#include <utility>

__APTR_TEMPL__
__APTR_INST__::array_ptr()
    : m_index(0)
    , m_junk()
    , m_data(new Shared_Data())
{}

__APTR_TEMPL__
__APTR_INST__::array_ptr(null_type)
    : array_ptr()
{}

__APTR_TEMPL__
__APTR_INST__::array_ptr(size_type N, const_reference filler)
    : m_index(0)
    , m_junk()
    , m_data(new Shared_Data(N))
{
    for(size_type i(0); i < m_data->m_length; ++i)
        m_data->m_array[i] = filler;
}

__APTR_TEMPL__
__APTR_INST__::array_ptr(size_type N, pointer& Tptr)
    : m_index(0)
    , m_junk()
    , m_data(new Shared_Data())
{
    m_data->m_array = Tptr;
    m_data->m_length = m_data->m_capacity = N;
    Tptr = null;
}

__APTR_TEMPL__
__APTR_INST__::array_ptr(std::initializer_list<value_type>& li)
    : m_index(0)
    , m_junk()
    , m_data(new Shared_Data(li.size()))
{
    auto iter = li.cbegin();
    for(size_type i(0); i < m_data->m_length; ++i, ++iter)
        m_data->m_array[i] = std::move(*iter);
}

__APTR_TEMPL__
template <typename... ConArgs>
    __APTR_INST__::array_ptr(size_type N, ConArgs&&... c_args)
    : m_index(0)
    , m_junk()
    , m_data(new Shared_Data(N))
{
    for(size_type i(0); i < m_data->m_length; ++i)
        m_data->m_array[i] = value_type(std::forward<ConArgs&&>(c_args)...);
}

__APTR_TEMPL__
template <typename __APTR_INST__::size_type N>
    __APTR_INST__::array_ptr(const value_type (&static_arr)[N])
    : m_index(0)
    , m_junk()
    , m_data(new Shared_Data(N))
{
    for(size_type i(0); i < m_data->m_length; ++i)
        m_data->m_array[i] = static_arr[i];
}

__APTR_TEMPL__
__APTR_INST__::array_ptr(const __APTR_INST__& orig)
    : m_index(orig.m_index)
    , m_junk()
    , m_data(null)
{copy_data(orig.m_data);}

__APTR_TEMPL__
__APTR_INST__& __APTR_INST__::operator=(const __APTR_INST__& orig){
    if(this == &orig ||m_data == orig.m_data) return *this;
    copy_data(orig.m_data);
    m_index = orig.m_index;
    return *this;
}

__APTR_TEMPL__
__APTR_INST__::array_ptr(__APTR_INST__&& orig)
    : m_index(orig.m_index)
    , m_junk()
    , m_data(orig.m_data)
{orig.m_data = null;}

__APTR_TEMPL__
__APTR_INST__& __APTR_INST__::operator=(__APTR_INST__&& orig){
    if(m_data == orig.m_data) return *this;
    m_index = orig.m_index;
    m_data = orig.m_data;
    orig.m_data = null;
    return *this;
}

__APTR_TEMPL__
__APTR_INST__::~array_ptr()
    {this->free();}