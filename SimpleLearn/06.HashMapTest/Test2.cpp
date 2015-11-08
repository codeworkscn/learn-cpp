#include "Includes.h"


void Test2(void)
{
	typedef pair <long long, int> cLongLong2Int;
	hash_map <long long ,long> hm1;
// 	hash_map <long long ,long> :: key_type key1;
// 	hash_map <long long ,long> :: mapped_type mapped1;
	hash_map <long long ,long> :: value_type value1;
	hash_map <long long ,long> :: iterator pIter;

	// value_type can be used to pass the correct type
	// explicitely to avoid implicit type conversion
// 	hm1.insert ( hash_map <long long, long> :: value_type ( 1, 10 ) );
// 
// 	// Compare other ways to insert objects into a hash_map
// 	hm1.insert ( cLongLong2Int ( 2, 20 ) );
// 	hm1[ 3 ] = 30;
	//time_t timestat 


}