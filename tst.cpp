#include<bits/stdc++.h>

#define lb(i) (i&-i)

using namespace std;

void work()
{
	vector<int> a = {1,2,3,4,5,6};
	auto it = lower_bound(a.begin(),a.end(),2);
	cout<<*it<<'\n';
	cout<< it - a.begin()<<'\n';

}

struct Node{
	int id,val;
};

  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    _GLIBCXX20_CONSTEXPR
    _ForwardIterator
    __lower_bound(_ForwardIterator __first, _ForwardIterator __last,
		  const _Tp& __val, _Compare __comp)
    {
      typedef typename iterator_traits<_ForwardIterator>::difference_type
	_DistanceType;

      _DistanceType __len = std::distance(__first, __last);

      while (__len > 0)
	{
	  _DistanceType __half = __len >> 1;
	  _ForwardIterator __middle = __first;
	  std::advance(__middle, __half);
	  if (__comp(__middle, __val))
	    {
	      __first = __middle;
	      ++__first;
	      __len = __len - __half - 1;
	    }
	  else
	    __len = __half;
	}
      return __first;
    }






signed main()
{
	work();

	
	return 0;
}
