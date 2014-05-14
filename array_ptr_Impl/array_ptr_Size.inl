//Size related implementations

#include <utility>
#include <algorithm>

__APTR_TEMPL__
void __APTR_INST__::resize(size_type newsize, const_reference filler)
{
    if(newsize <= m_data->m_length){
        while(m_data->m_length > newsize)
            m_data->m_array[--m_data->m_length] = value_type();
    }
    if(newsize >= m_data->m_capacity)
        this->reserve(calc_new_capacity());
    while(m_data->m_length < newsize)
        m_data->m_array[m_data->m_length++] = filler;
}

__APTR_TEMPL__
template <typename... ConArgs>
    void __APTR_INST__::resize(size_type newsize, ConArgs&&... params)
{
    if(newsize <= m_data->m_length){
        while(m_data->m_length > newsize)
            m_data->m_array[--m_data->m_length] = value_type();
    }
    if(newsize >= m_data->m_capacity)
        this->reserve(calc_new_capacity());
    while(m_data->m_length < newsize)
        m_data->m_array[m_data->m_length++] = value_type(params...);
}

__APTR_TEMPL__
auto __APTR_INST__::reserve(size_type newcapacity) -> size_type
{
    if(newcapacity <= m_data->m_capacity)
        return m_data->m_capacity;

    pointer new_array = new value_type[m_data->m_capacity = newcapacity];
    if(m_data->m_array != null){
        while(newcapacity-- > 0){
            new_array[newcapacity]
                = (newcapacity < m_data->m_length && m_data->m_array != null)
                ? m_data->m_array[newcapacity]
                : value_type()
            ;
        }
    }
    std::swap(m_data->m_array, new_array);
    delete[] new_array;

    return m_data->m_capacity;
}