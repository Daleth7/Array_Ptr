//Dereference and subscript operator implementations


__APTR_TEMPL__
auto __APTR_INST__::operator*() const -> const_reference
    {return !is_valid_index(0) ? m_junk : m_data->m_array[m_index];}

__APTR_TEMPL__
auto __APTR_INST__::operator->() const -> const_pointer
    {return m_data->m_array+(m_data->m_array == null ? 0 : m_index);}

__APTR_TEMPL__
auto __APTR_INST__::operator[] (size_type offset) const -> const_reference
    {return !is_valid_index(offset) ? m_junk : this->at(offset);}

__APTR_TEMPL__
auto __APTR_INST__::operator*() -> reference
    {return !is_valid_index(0) ? m_junk : m_data->m_array[m_index];}

__APTR_TEMPL__
auto __APTR_INST__::operator->() -> pointer
    {return m_data->m_array == null ? null :( m_data->m_array+m_index);}

__APTR_TEMPL__
auto __APTR_INST__::operator[] (size_type offset) -> reference
{
    return is_valid_index(offset) ? m_data->m_array[m_index+offset] : m_junk;
}