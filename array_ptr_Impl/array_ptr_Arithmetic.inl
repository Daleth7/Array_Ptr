//Arithmetic operators

__APTR_TEMPL__ 
__APTR_INST__& __APTR_INST__::operator+=(size_type offset){
    if(m_data->m_array == null)  return *this;
    if(m_index + offset > m_data->m_length)
        m_index = m_data->m_length-1;
    else m_index += offset;
    return *this;
}

__APTR_TEMPL__
__APTR_INST__& __APTR_INST__::operator-=(size_type offset){
    if(m_data->m_array == null)  return *this;
    if(m_index < offset) this->reset_index();
    else m_index -= offset;
    return *this;
}

__APTR_TEMPL__
__APTR_INST__& __APTR_INST__::operator++()
    {return *this += 1;}

__APTR_TEMPL__
__APTR_INST__& __APTR_INST__::operator--()
    {return *this -= 1;}

__APTR_TEMPL__
__APTR_INST__ __APTR_INST__::operator++(int)
    {return (*this += 1) - 1;}

__APTR_TEMPL__
__APTR_INST__ __APTR_INST__::operator--(int)
    {return (*this -= 1) + 1;}