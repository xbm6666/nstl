#pragma once

namespace nstl
{
template<typename T>
T max(T t1, T t2)
{
	if (t1 < t2)
		return t2;
	return t1;
}

template<typename T1,typename T2>
	requires requires(T1 t1, T2 t2)
{
	t1 < t2;
}
T1 max(T1 t1, T2 t2)
//返回类型固定为T1，极其危险
{
	if (t1 < t2)
		return t2;
	return t1;
}

}