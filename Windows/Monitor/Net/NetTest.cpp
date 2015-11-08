 #include <iostream>
 #include "NetTraffic.h"
 
 using namespace std;
 
 
 
 int main(void)
 {
 	NetTraffic netTraffic;

	int i = netTraffic.getNetInfo ();

	cout << "i = " << i << endl;
 
 
 	system ("pause");
 	return 0;
 }

