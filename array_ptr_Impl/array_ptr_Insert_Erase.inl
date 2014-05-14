//Insertion and removal implementations

#include <stdexcept>

__APTR_TEMPL__
auto __APTR_INST__::insert(size_type pos, const_reference filler) -> iterator
    {return this->insert(pos, 1u, filler);}

__APTR_TEMPL__
auto __APTR_INST__::insert(size_type pos, size_type pop, const_reference filler)
    -> iterator
{
    if(!is_valid_index(pos))
        throw std::out_of_range(__func__);

    if((pop + m_data->m_length) >= m_data->m_capacity)
        this->reserve(calc_new_capacity(pop));

    pos += m_index;
    for(size_type i(1); i < (m_data->m_length-pos+1); ++i){
        m_data->m_array[m_data->m_length+pop-i]
            =  m_data->m_array[m_data->m_length-i];
    }
    for(size_type i(0); i < pop; ++i)
        m_data->m_array[pos+i] = filler;

    m_data->m_length += pop;

    iterator toreturn(*this);
    toreturn.change_index(pos+pop);

    return toreturn;
}

__APTR_TEMPL__
auto __APTR_INST__::insert(const iterator& it, const_reference filler) -> iterator
    {return this->insert(it.m_index, 1, filler);}

__APTR_TEMPL__
auto __APTR_INST__::insert(const iterator& it, size_type pop, const_reference filler)
    -> iterator
{return this->insert(it.m_index, pop, filler);}

__APTR_TEMPL__
auto __APTR_INST__::erase(size_type pos) -> iterator
    {return this->erase(pos, 1);}

__APTR_TEMPL__
auto __APTR_INST__::erase(size_type pos, size_type pop) -> iterator
{
    if(!is_valid_index(pos))
        throw std::out_of_range(__func__);

    if(pop >= (this->size()-pos)){
        m_data->m_length = pos+m_index;
        return *this;
    }

    pos += m_index;
    for(size_type i(0); i < (m_data->m_length-pos-1); ++i)
        m_data->m_array[pos+i] = m_data->m_array[pos+i+pop];
    m_data->m_length -= pop;

    if(m_index >= m_data->m_length)
        m_index = m_data->m_length-1;

    iterator toreturn(*this);
    toreturn.m_index = pos;
    return toreturn;
}

__APTR_TEMPL__
auto __APTR_INST__::erase(const iterator& it) -> iterator
    {return this->erase(it.m_index, 1);}

__APTR_TEMPL__
auto __APTR_INST__::erase(const iterator& it, size_type pop) -> iterator
    {return this->erase(it.m_index, pop);}

__APTR_TEMPL__
auto __APTR_INST__::push_back(const_reference filler, size_type pop) -> iterator
{
    if(m_data->m_length + pop >= m_data->m_capacity)
        this->reserve(calc_new_capacity(pop));

    for(size_type i(0); i < pop; ++i)
        m_data->m_array[i+m_data->m_length] = filler;

    m_data->m_length += pop;

    return this->end()-1;
}

__APTR_TEMPL__
auto __APTR_INST__::push_front(const_reference filler, size_type pop) -> iterator
    {return this->insert(0, pop, filler);}

__APTR_TEMPL__
auto __APTR_INST__::pop_back(size_type pop) -> iterator
{
    if(pop >= m_data->m_length){
        this->clear();
        return *this;
    }
    m_data->m_length -= pop;
    if(m_index >= m_data->m_length)
        m_index = m_data->m_length-1;

    return this->end()-1;
}

__APTR_TEMPL__
auto __APTR_INST__::pop_front(size_type pop) -> iterator
    {return this->erase(0, pop);}

__APTR_TEMPL__
template <typename... ConArgs>
    auto __APTR_INST__::emplace(size_type pos, ConArgs&&... c_args) -> iterator
{
    if(!is_valid_index(pos))
        throw std::out_of_range(__func__);

    if(this->size() >= m_data->m_capacity)
        this->reserve(calc_new_capacity());

    pos += m_index;
    for(size_type i(1); i < (m_data->m_length-pos+1); ++i){
        m_data->m_array[m_data->m_length+1-i]
            =  m_data->m_array[m_data->m_length-i];
    }

    m_data->m_array[pos] = value_type(std::forward<ConArgs&&>(c_args)...);
    ++m_data->m_length;

    iterator toreturn(*this);
    toreturn.m_index = pos;
    return toreturn;
}

__APTR_TEMPL__
template <typename... ConArgs>
    auto __APTR_INST__::emplace(const iterator& it, ConArgs&&... c_args) -> iterator
{return this->emplace(it.m_index, std::forward(c_args)...);}

__APTR_TEMPL__
template <typename... ConArgs>
    auto __APTR_INST__::emplace_back(ConArgs&&... c_args) -> iterator
{
    if(this->size() >= m_data->m_capacity)
        this->reserve(calc_new_capacity());

    m_data->m_array[m_data->m_length] = value_type(std::forward(c_args)...);
    ++m_data->m_length;

    return this->end()-1;
}

__APTR_TEMPL__
template <typename... ConArgs>
    auto __APTR_INST__::emplace_front(ConArgs&&... c_args) -> iterator
{return this->emplace(0, std::forward(c_args)...);}
