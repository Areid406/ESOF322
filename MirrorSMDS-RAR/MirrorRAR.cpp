/*********************************************************
* PROJECT: Mirror Mirror for ESOF322
* 
* FILE: MirrorsRAR.cpp
*
* DEV ENVIRONMENTS: TextWrangler on MacOS
*
* EXECUTION ENVIRONMENTS: Linux command line
*
* HISTORY:
* Date		Author			Description
* ====      ======          ===========
* 12/9/16  Alex Reid       Initial implementation and test
* 
* DESCRIPTION:
* Determines the minimal transformation (if properly transformed)
* needed to go from the original to new pattern. Will return either
* that the pattern was preserved, the degree of rotations, 
* a vertical reflection, or the pattern was improperly transformed.
* For purposes of evaluation, a 180 degree rotation is considered less
* work than a vertical reflection.
*/

//-------------
// C++ Includes
//-------------
#include<iostream>
#include<algorithm>

//-----------------
// Using Statements
//-----------------
using namespace std;

/*L00*/ char pattern[3][12][12];
/*L01*/ int dimSize, dimSize2, patternNmbr = 0;

bool same(){ /*L42*/
	for(int ndx = 0; ndx < dimSize; ndx++)/*L43*/
	for(int ndy = 0; ndy < dimSize; ndy++)/*L44*/
	if(pattern[0][ndx][ndy] != pattern[1][ndx][ndy])/*L45*/ 
		return false;/*L46*/
	return true;/*L47*/
}
bool rotate(){ /*L48*/
	for(int ndx = 0; ndx < dimSize; ndx++)/*L49*/
	for(int ndy = 0; ndy < dimSize; ndy++)/*L50*/
	if(pattern[0][ndx][ndy] != pattern[2][ndx][ndy])/*L51*/ 
		return false;/*L52*/
	return true;/*L53*/
}
void reflect(){ /*L54*/
	for(int ndx = 0; ndx < dimSize2; ndx++)/*L55*/
	for(int ndy = 0; ndy < dimSize; ndy++)/*L56*/
	swap(pattern[2][ndx][ndy], pattern[2][dimSize-ndx-1][ndy]);/*L57*/
}
const char* evaluate(){ /*L07*/ 
	//preserve
	if(same()) return "preserved."; /*L08*/ 
	
	//90 deg
	for(int ndx = 0; ndx < dimSize; ndx++) /*L09*/ 
	for(int ndy = 0; ndy < dimSize; ndy++) /*L10*/ 
	pattern[2][ndx][ndy] = pattern[1][ndy][dimSize-ndx-1];/*L11*/ 
	if(rotate()) return "rotated 90 degrees."; /*L12*/ 
	
	//180 deg
	for(int ndx = 0; ndx < dimSize; ndx++) /*L13*/ 
	for(int ndy = 0; ndy < dimSize; ndy++) /*L14*/ 
	pattern[2][ndx][ndy] = pattern[1][dimSize-ndx-1][dimSize-ndy-1];/*L15*/ 
	if(rotate()) return "rotated 180 degrees."; /*L16*/ 
	
	//270 deg
	for(int ndx = 0; ndx < dimSize; ndx++) /*L17*/ 
	for(int ndy = 0; ndy < dimSize; ndy++) /*L18*/ 
	pattern[2][ndx][ndy] = pattern[1][dimSize-ndy-1][ndx];/*L19*/ 
	if(rotate()) return "rotated 270 degrees.";/*L20*/ 
	
	//vertical reflect
	for(int ndx = 0; ndx < dimSize; ndx++) /*L21*/
	for(int ndy = 0; ndy < dimSize; ndy++) /*L22*/
	pattern[2][ndx][ndy] = pattern[1][dimSize-ndx-1][ndy];/*L23*/
	if(rotate()) return "reflected vertically.";/*L24*/
	
	dimSize2 = dimSize/2;/*L25*/
	//v90 deg
	for(int ndx = 0; ndx < dimSize; ndx++) /*L26*/
	for(int ndy = 0; ndy < dimSize; ndy++) /*L27*/
	pattern[2][ndx][ndy] = pattern[1][ndy][dimSize-ndx-1];/*L28*/
	reflect();/*L29*/
	if(rotate()) return "reflected vertically and rotated 90 degrees.";/*L30*/
	
	//v180 deg
	for(int ndx = 0; ndx < dimSize; ndx++) /*L31*/
	for(int ndy = 0; ndy < dimSize; ndy++) /*L32*/
	pattern[2][ndx][ndy] = pattern[1][dimSize-ndx-1][dimSize-ndy-1];/*L33*/
	reflect();/*L34*/
	if(rotate()) return "reflected vertically and rotated 180 degrees.";/*L35*/
	
	//v270 deg
	for(int ndx = 0; ndx < dimSize; ndx++)/*L36*/
	for(int ndy = 0; ndy < dimSize; ndy++)/*L37*/
	pattern[2][ndx][ndy] = pattern[1][dimSize-ndy-1][ndx];/*L38*/
	reflect();/*L39*/
	if(rotate()) return "reflected vertically and rotated 270 degrees.";/*L40*/
	
	return "improperly transformed.";/*L41*/
}
int main(){ /*L02*/ 
	while(cin >> dimSize){ /*L03*/ 
		for(int ndx = 0; ndx < dimSize; ndx++) /*L04*/ 
			cin >> pattern[0][ndx] >> pattern[1][ndx];/*L05*/ 
	/*L06*/ cout << "Pattern " << ++patternNmbr << " was " << evaluate() << endl;
	}
}