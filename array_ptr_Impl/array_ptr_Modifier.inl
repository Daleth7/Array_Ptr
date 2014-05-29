//Other modifiers

__APTR_TEMPL__
auto __APTR_INST__::back() -> reference
{
    return !is_valid_index(0)? m_junk : m_data->m_array[m_data->m_length-1];
}

__APTR_TEMPL__
auto __APTR_INST__::front() -> reference
    {return !is_valid_index(0) ? m_junk : m_data->m_array[0];}

__APTR_TEMPL__
auto __APTR_INST__::get() -> pointer
    {return m_data->m_array+(m_data->m_array == null ? 0 : m_index);}

__APTR_TEMPL__
auto __APTR_INST__::data() -> pointer
    {return m_data->m_array+(m_data->m_array == null ? 0 : m_index);}

__APTR_TEMPL__
auto __APTR_INST__::junk() -> reference
    {return m_junk;}

__APTR_TEMPL__
void __APTR_INST__::reset_index()
    {m_index = 0;}

__APTR_TEMPL__
auto __APTR_INST__::change_index(size_type newindex) -> size_type
    {return m_index = (newindex < m_data->m_length ? newindex : m_data->m_length-1);}

__APTR_TEMPL__
void __APTR_INST__::clear()
    {m_data->m_length = m_index;}

__APTR_TEMPL__
void __APTR_INST__::reset(const __APTR_INST__& src)
    {this->operator=(src);}

__APTR_TEMPL__
template <typename U>
void __APTR_INST__::reset(size_type new_size, U* src){
    if(src == m_data->m_array)
        return;
    this->free();
    m_data = new Shared_Data();
    m_data->m_array = static_cast<pointer>(src);
    m_data->m_length = m_data->m_capacity = new_size;
}
