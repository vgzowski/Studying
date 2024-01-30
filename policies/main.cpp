#include "StoragePolicies.h"

template <
	class A,
	class B,
	typename ReplacementPolicy,
	typename SizePolicy,
>
class Cache
{
public:
private:
	CachePolicy <A, B> cache;
	SizePolicy sizer;
};

Cache <
	int,
	int,
	LRU_Policy,
	FixedSize<10>
> my_cache;
