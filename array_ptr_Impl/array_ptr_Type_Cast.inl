__APTR_TEMPL__
__APTR_INST__::operator void*() const
    {return m_data->m_array+m_index;}

__APTR_TEMPL__
__APTR_INST__::operator value_type*()
    {return m_data->m_array+m_index;}

__APTR_TEMPL__
__APTR_INST__::operator value_type const*() const
    {return m_data->m_array+m_index;}