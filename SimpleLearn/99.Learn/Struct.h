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
			//�жϲ��Ǻ�����Ƚϣ�����Ǻ�����Ƚϣ�����ȣ�����false
			if (this != &bRight)
			{
				//����Ƚ�С
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