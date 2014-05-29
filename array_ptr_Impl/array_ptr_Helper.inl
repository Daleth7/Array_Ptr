//Helper implementations

__APTR_TEMPL__
void __APTR_INST__::copy_data(Shared_Data*const & update){
    this->free();
    m_data = update;
    ++(m_data->m_pcount);
}

__APTR_TEMPL__
void __APTR_INST__::free(){
    if(m_data == null) return;
    if(m_data->m_pcount <= 1)
        delete m_data;
    else --(m_data->m_pcount);
    m_data = null;
}

__APTR_TEMPL__
auto __APTR_INST__::calc_new_capacity(size_type offset) const -> size_type
    {return Shared_Data::calc_new_capacity(m_data->m_capacity, offset);}

__APTR_TEMPL__
bool __APTR_INST__::is_valid_index(size_type pos)const
    {return (m_data->m_array != null) && (pos+m_index < m_data->m_length);}