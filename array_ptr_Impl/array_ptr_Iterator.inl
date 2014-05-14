//Iterator implementations

__APTR_TEMPL__
auto __APTR_INST__::cbegin()const -> const_iterator
    {return *this;}

__APTR_TEMPL__
auto __APTR_INST__::cend()const -> const_iterator
{
    iterator toreturn(*this);
    toreturn.m_index = m_data->m_length;
    return toreturn;
}

__APTR_TEMPL__
auto __APTR_INST__::begin()const -> const_iterator
    {return *this;}

__APTR_TEMPL__
auto __APTR_INST__::end()const -> const_iterator
    {return this->cend();}

__APTR_TEMPL__
auto __APTR_INST__::begin() -> iterator
    {return *this;}

__APTR_TEMPL__
auto __APTR_INST__::end() -> iterator
{
    iterator toreturn(*this);
    toreturn.m_index = this->size();
    return toreturn;
}