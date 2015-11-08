#include "Includes.h"

void Test1(void)
{

	typedef pair <int, int> cInt2Int;
	hash_map <int, int> hm1;
	hash_map <int, int> :: key_type key1;
	hash_map <int, int> :: mapped_type mapped1;
	hash_map <int, int> :: value_type value1;
	hash_map <int, int> :: iterator pIter;

	// value_type can be used to pass the correct type
	// explicitely to avoid implicit type conversion
	hm1.insert ( hash_map <int, int> :: value_type ( 1, 10 ) );

	// Compare other ways to insert objects into a hash_map
	hm1.insert ( cInt2Int ( 2, 20 ) );
	hm1[ 3 ] = 30;
	hm1[ 3 ] = 50;

// 	for (long i=4;i<100000;i++)
// 	{
// 		hm1[ i ] = i*10;
// 	}

	// Initializing key1 and mapped1
	key1 = ( hm1.begin( ) -> first );
	mapped1 = ( hm1.begin( ) -> second );

	cout << "The key of first element in the hash_map is "
		<< key1 << "." << endl;

	cout << "The data value of first element in the hash_map is "
		<< mapped1 << "." << endl;

	// The following line would cause an error because
	// the value_type is not assignable
	// value1 = cInt2Int ( 4, 40 );

	cout  << "The keys of the mapped elements are:";
	for ( pIter = hm1.begin( ) ; pIter != hm1.end( ) ; pIter++ )
		cout << " " << pIter -> first;
	cout << "." << endl;

	cout  << "The values of the mapped elements are:";
	for ( pIter = hm1.begin( ) ; pIter != hm1.end( ) ; pIter++ )
		cout << " " << pIter -> second;
	cout << "." << endl;

	pIter = hm1.find(2);

	if ( pIter == hm1.end( ) )
		cout << "The hash_map hm1 doesn't have an element "
		<< "with a key of xixi." << endl;
	else
		cout << "The element of hash_map hm1 with a key of 2 is: "
		<< pIter -> second << "." << endl;
}