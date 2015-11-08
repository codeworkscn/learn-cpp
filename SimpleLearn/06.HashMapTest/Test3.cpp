#include "Includes.h"



void Test3(void)
{
	typedef pair <string, long long> cName2ID;
	HashName2ID hm1;
	HashName2ID :: key_type key1;
	HashName2ID:: mapped_type mapped1;
	HashName2ID:: value_type value1;
	HashName2ID:: iterator pIter;

	// value_type can be used to pass the correct type
	// explicitely to avoid implicit type conversion
	hm1.insert ( HashName2ID :: value_type ( "haha", 10 ) );

	// Compare other ways to insert objects into a hash_map
	hm1.insert ( cName2ID ( "xixi", 20 ) );
	hm1["hehe"] = 30;
	hm1["hehe"] = 50;

	key1 = ( hm1.begin( ) -> first );
	mapped1 = ( hm1.begin( ) -> second );

	cout << "The key of first element in the hash_map is "
		<< key1.c_str() << "." << endl;

	cout << "The data value of first element in the hash_map is "
		<< mapped1 << "." << endl;

	// The following line would cause an error because
	// the value_type is not assignable
	// value1 = cInt2Int ( 4, 40 );

	cout  << "The keys of the mapped elements are:";
	for ( pIter = hm1.begin( ) ; pIter != hm1.end( ) ; pIter++ )
		cout << " " << pIter -> first.c_str();
	cout << "." << endl;

	cout  << "The values of the mapped elements are:";
	for ( pIter = hm1.begin( ) ; pIter != hm1.end( ) ; pIter++ )
		cout << " " << pIter -> second;
	cout << "." << endl;

	pIter = hm1.find("xixi");

	if ( pIter == hm1.end( ) )
		cout << "The hash_map hm1 doesn't have an element "
		<< "with a key of xixi." << endl;
	else
		cout << "The element of hash_map hm1 with a key of \"xixi\" is: "
		<< pIter -> second << "." << endl;


}
