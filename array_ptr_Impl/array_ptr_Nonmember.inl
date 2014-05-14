//Related non-member implementations

//Other arithmetic operators
__APTR_TEMPL__
__APTR_INST__ operator+(
    const __APTR_INST__& lhs,
    typename __APTR_INST__::size_type rhs
){return __APTR_INST__(lhs) += rhs;}

__APTR_TEMPL__
__APTR_INST__ operator-(
    const __APTR_INST__& lhs,
    typename __APTR_INST__::size_type rhs
){return __APTR_INST__(lhs) -= rhs;}

__APTR_TEMPL__
__APTR_INST__ operator+(
    typename __APTR_INST__::size_type lhs,
    const __APTR_INST__& rhs
){return __APTR_INST__(rhs) += lhs;}

__APTR_TEMPL__
__APTR_INST__ operator-(
    typename __APTR_INST__::size_type lhs,
    const __APTR_INST__& rhs
)
    {return __APTR_INST__(rhs) -= lhs;}
__APTR_TEMPL__
typename __APTR_INST__::size_type operator-(
    const __APTR_INST__& lhs,
    const __APTR_INST__& rhs
){return lhs.index() - rhs.index();}

    
//Comparison
__APTR_TEMPL__
bool operator==(const __APTR_INST__& lhs, const __APTR_INST__& rhs)
    {return lhs.compare(rhs) == 0;}

__APTR_TEMPL__
bool operator!=(const __APTR_INST__& lhs, const __APTR_INST__& rhs)
    {return !(lhs == rhs);}

__APTR_TEMPL__
bool operator<(const __APTR_INST__& lhs, const __APTR_INST__& rhs)
    {return lhs.compare(rhs) < 0;}

__APTR_TEMPL__
bool operator>(const __APTR_INST__& lhs, const __APTR_INST__& rhs)
    {return lhs.compare(rhs) == 1;}

__APTR_TEMPL__
bool operator<=(const __APTR_INST__& lhs, const __APTR_INST__& rhs)
    {return lhs.compare(rhs) <= 0;}

__APTR_TEMPL__
bool operator>=(const __APTR_INST__& lhs, const __APTR_INST__& rhs)
{
    switch(lhs.compare(rhs)){
        case 0:
        case 1:     return true;
        default:    return false;
    }
}

__APTR_TEMPL__
bool operator==(
    const __APTR_INST__& lhs,
    const typename __APTR_INST__::null_type& rhs
){return lhs.get() == rhs;}

__APTR_TEMPL__
bool operator!=(
    const __APTR_INST__& lhs,
    const typename __APTR_INST__::null_type& rhs
){return !(lhs == rhs);}

__APTR_TEMPL__
bool operator==(
    const typename __APTR_INST__::null_type& lhs,
    const __APTR_INST__& rhs
){return rhs.get() == lhs;}

__APTR_TEMPL__
bool operator!=(
    const typename __APTR_INST__::null_type& lhs,
    const __APTR_INST__& rhs
){return !(lhs == rhs);}