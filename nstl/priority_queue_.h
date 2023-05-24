#pragma once
#include"heap_.h"

namespace nstl
{
template<typename T, typename Container = vector<T>, typename Compare = std::less<T> >
using priority_queue= heap<T, Container, Compare>;
}