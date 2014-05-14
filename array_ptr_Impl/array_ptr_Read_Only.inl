//Read-only implementations

__APTR_TEMPL__
auto __APTR_INST__::size() const -> size_type
    {return m_data->m_length-m_index;}

__APTR_TEMPL__
auto __APTR_INST__::capacity() const -> size_type
    {return m_data->m_capacity;}

__APTR_TEMPL__
auto __APTR_INST__::index() const -> size_type
    {return m_index;}

__APTR_TEMPL__
auto __APTR_INST__::count() const -> size_type
    {return m_data->m_pcount;}

__APTR_TEMPL__
auto __APTR_INST__::at(size_type offset) const -> const_reference
    {return is_valid_index(offset) ? m_data->m_array[m_index+offset] : m_junk;}

__APTR_TEMPL__
auto __APTR_INST__::back() const -> const_reference
    {return is_valid_index(0) ? m_data->m_array[m_data->m_length-1] : m_junk;}

__APTR_TEMPL__
auto __APTR_INST__::front() const -> const_reference
    {return is_valid_index(0) ? m_data->m_array[m_index] : m_junk;}

__APTR_TEMPL__
auto __APTR_INST__::get() const -> const_pointer
    {return m_data->m_array+(m_data->m_array == null ? 0 : m_index);}

__APTR_TEMPL__
auto __APTR_INST__::data() const -> const_pointer
    {return m_data->m_array+(m_data->m_array == null ? 0 : m_index);}

__APTR_TEMPL__
auto __APTR_INST__::junk() const -> const_reference
    {return m_junk;}

__APTR_TEMPL__
bool __APTR_INST__::unique() const
    {return this->count() == 1;}

__APTR_TEMPL__
short __APTR_INST__::compare(const __APTR_INST__& s) const
{
    if(this == &s)
        return 0;
    else if(m_data != s.m_data)
        return 2;
    else if(m_index < s.m_index)
        return -1;
    else if(m_index > s.m_index)
        return 1;
    else
        return 0;
}
