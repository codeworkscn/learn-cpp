#include <iostream>
using namespace std;

namespace HAHA
{


	struct Bijiao 
	{
		long a;
		long b;


		bool operator<(const Bijiao& bRight)const
		{
			//判断不是和自身比较，如果是和自身比较，则相等，返回false
			if (this != &bRight)
			{
				//这个比较小
				if (this->a < bRight.a)
				{
					return true;
				}
				if (this->a == bRight.a)
				{
					if (this->b < bRight.b)
					{
						return true;
					}
				}
			}
			return false;
		};
	};
}


namespace DAIS
{

	typedef ::HAHA::Bijiao Bijiao;
}