/*********************************************************
* PROJECT: Mirror, Mirror for ESOF322
*
* FILE: MirrorAMD.cpp
*
* DEV ENVIRONMENTS: Windows 10 using Notepad++
*
* EXECUTION ENVIRONMENTS: Windows 10 command line
*
* HISTORY:
* Date		Author			Description
* ====      ======          ===========
* 12/07/16  Max Austin     	Initial implementation
* 12/08/16	Max Austin	   	Initial testing
* 12/09/16	Max Austin		
*
* DESCRIPTION:
* Determines the transformations performed on an initial
* pattern to obtain the pre defined secondary pattern.
* Conforms to the MTM Standard for C++ Source Fles.
*/

//-------------
// C++ Includes
//-------------
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//-----------------
// Using Statements
//-----------------
using namespace std;

//-----------------
// Global variables
//-----------------
int const MAX_DIMENSION = 10;

//--------------------
// Function prototypes
//--------------------
bool isSame(char origPatt[][MAX_DIMENSION], 
			char modPatt[][MAX_DIMENSION], 
			int dimSize);
	   
void rotate(char origPatt[][MAX_DIMENSION], int dimSize);

void reflect(char origPatt[][MAX_DIMENSION], int dimSize);

/*********************************************************
* DESCRIPTION - main
* States the transformation that has to be performed on one pattern
* to get the other one.
*
* REQUIREMENTS
* R01.	Input will consist of an unknown number of pattern datasets
* R02.	Input begins with an integer on a line by itself dimSize where 
*		dimSize is the dimensions of the square pattern.
* R03.	The restrictions on dimSize are 1 <= dimSize <= 10.
* R04.	The following dimSize lines will contain the original and new 
* 		patterns side by side separated by a single space.
* R05.	Light squares in the patterns are to represented by “.” and 
*		dark squares are to be represented by “X”.
* R06.	Patterns can go through multiple transformations.
* R07.	End of input is represented by EOF
* R08.	The output will state what the type of transformation that 
*		each pattern goes through.
*	
* Sample Runs
* ------------
* input:
* 
* 5
* X...X ....X
* .X... ...X.
* ...X. .X...
* ..X.X ..X..
* ....X  XX..X
*
* output:
* 
* Pattern 1 was rotated 90 degrees.
*
* DESIGN
* 
* Significant variables
* ---------------------
* dimSize									//Dimension of the square pattern
* MAX_DIMENSION								//The max dimension and size of the 2D array
*											//representations of the patterns
* origPatt[][]								//The first pattern in the input 
* modPatt[][]								//The first pattern after transformed in some
*											//way
*
* Solution analysis
* -----------------
* To find the transformations on the pattern, the pattern must first be rotated all 
* the way around in increments of 90 degrees.  After each rotation, the original 
* pattern is compared to the modified pattern to see if that rotation is the 
* transformation that the pattern goes through.  After this, the pattern must be 
* reflected vertically and compared to determine if that reflection is ultimately 
* the transformation.  After this reflection, the pattern must then be rotated all 
* the way around again to determine if there are more than one transformations. If 
* a transformation still hasn’t been found, it is assumed that the pattern was 
* improperly transformed.
*
* Algorithm
* ---------
* A00 *****************************************************************************
*	  * DESCRIPTION – bool isSame()
*	  * Returns true if the two 2D arrays representing the patterns are the same.
*	  * 
*	  * REQUIREMENTS
*	  * R01		Input consists of 
*	  *				- char origPatt[][]
*	  *				- The 2D array representation of a pattern
*	  *				- char modPatt[][]
*	  *				- The pattern to be compared to origPatt[][]
*	  *				- int dimSize
*	  *				- The dimensions of the patterns
*	  * R02		2D array inputs must both be square with dimensions of dimSize
*     *****************************************************************************
*	bool isSame(char origPatt[][], char modPatt[][], int dimSize){
*	}//isSame
*
* A01 *****************************************************************************
*	  * DESCRIPTION – void rotate()
*	  * Rotates a 2D array representation of a pattern by 90 degrees.
*	  * 
*	  * REQUIREMENTS
*	  * R01		Input consists of 
*	  *				- char origPatt[][]
*	  *				- The 2D array representation of the pattern being rotated
*	  *				- int dimSize
*	  *				- The dimensions of the pattern
*	  * R02		2D array input must both be square with dimensions of dimSize
*     *****************************************************************************
*	void rotate(char origPatt[][], int dimSize){
*	}//rotate
*
* A02 *****************************************************************************
*	  * DESCRIPTION – void reflect()
*	  * Reflects a 2D array representation of a pattern vertically.
*	  * 
*	  * REQUIREMENTS
*	  * R01		Input consists of 
*	  *				- char origPatt[][]
*	  *				- The 2D array representation of the pattern being reflected
*	  *				- int dimSize
*	  *				- The dimensions of the pattern
*	  * R02		2D array input must both be square with dimensions of dimSize
*     *****************************************************************************
*	void reflect(char origPatt[][], int dimSize){
*	}//relect()
*
* A03	Define:
*			int 	patternNmbr = 0;
*				dimSize;
*				MAX_DIMENSION = 10;
*			char	origPatt[MAX_DIMENSION][MAX_DIMENSION];
*				modPatt[MAX_DIMENSION][MAX_DIMENSION];
* A04	While (true){
* A05		Increment patternNmbr;
* A06		Read dimSize;
* A07		If(dimSize < 1 OR dimSize > 10){
* A08 			Write that the pattern isn’t the correct dimensions;
*				Break;
*		}//If
* A09		For (indx from 1 to dimSize){
* A10			For (indy from 1 to dimSize){
* A11				Read origPatt[indx][indy];
*			}//For
* A12			For(indy from 1 to dimSize){
* A13				Read modPatt[indx][indy];
*			}//For
*		}//For
* A14		If(Call isSame(origPatt,modPatt,dimSize) is true){
* A15			Write “Pattern ” + patternNmbr + “ was preserved.” on its own line;
*			Continue;
*		}//If
*
*
* A16		Call rotate(origPatt,dimSize);
* A17		If(Call isSame(origPatt,modPatt,dimSize) is true){
* A18	Write “Pattern “ + patternNmbr + “ was rotated 90 degrees.” on its own line;
*	Continue;
*		//If
* A19		Call rotate(origPatt,dimSize);
* A20		If(Call isSame(origPatt,modPatt,dimSize) is true){
* A21	Write “Pattern “ + patternNmbr + “ was rotated 180 degrees.” on its own line;
*			Continue;
* 		}//If
* A22		Call rotate(origPatt,dimSize);
* A23		If(Call isSame(origPatt,modPatt,dimSize) is true){
* A24	Write “Pattern “ + patternNmbr + “ was rotated 270 degrees.” on its own line;
*	Continue;
*		}//If
* A25		Call rotate(origPatt,dimSize);
* A26		Call reflect(origPatt,dimSize);
* A27		If(Call isSame(origPatt,modPatt,dimSize) is true){
* A28	Write “Pattern “ + patternNmbr + “ was reflected vertically.” 
*			   on its own line;
*			Continue;
*		}//If
* A29		Call rotate(origPatt,dimSize);
* A30		If(Call isSame(origPatt,modPatt,dimSize) is true){
* A31	Write “Pattern “ + patternNmbr + “ was reflected vertically and rotated 90 
*			   degrees.” on its own line;
*			Continue;
*		}//If
* A32		Call rotate(origPatt,dimSize);
* A33		If(Call isSame(origPatt,modPatt,dimSize) is true){
* A34	Write “Pattern “ + patternNmbr + “ was reflected vertically and rotated 180 
*			   degrees.” on its own line;
*			Continue;
*		}//If
* A35		Call rotate(origPatt,dimSize);
* A36		If(Call isSame(origPatt,modPatt,dimSize) is true){
* A37	Write “Pattern “ + patternNmbr + “ was reflected vertically and rotated 270
*			   degrees.” on its own line;
* 			Continue;
*		}//If
* A38	Write “Pattern “ + patternNmbr + “ was improperly transformed.” on its own 
*			   line;
*	}//While there is still input in the file
*
* ALGORITHM CORRECTNESS ARGUMENT
* ------------------------------
* CR05 By While in A04
* CR06 By Read in A06
* CR07 The restrictions on dimSize allows a two dimensional representation of the 
*	   patterns to be easily defined. A07 checks to make sure that this restriction
*	   is met
* CR08 Each pattern set is read in by A11 and A13 where the original and modified 
*	   patterns are guaranteed to be separated by a single space
* CR09 By Set in A11 and A13 where input is guaranteed to consist of “.”’s and “X”’s
* CR10 By A26 – A37
* 	A26 Reflects the original pattern vertically
* 	A27 Checks if the modified original pattern is the same as the transformation 
*		pattern
* 	A28 If A27 is true, output that the pattern was vertically transformed
* 	A29 Rotates the vertically reflected pattern by 90 degrees
* 	A30 Checks if the modified original pattern is the same as the transformation 
*		pattern
* 	A31 If A30 is true, output that the pattern was vertically transformed and 
*		rotated by 90 degrees
* 	A32 – A37 Repeats this process to check the other rotation transformations
* CR11 By While started in A04
* CR12 By A14 – A38
* 	A14 Checks if the original and the transformation pattern are the same to begin 
*		with
* 	A15 If A14 is true, output that the pattern was preserved
* 	A16 Rotate the original pattern by 90 degrees
* 	A17 Checks if the modified original pattern is the same as the transformation 
*		pattern
* 	A18 If A17 is true, output that the pattern was rotated by 90 degrees
* 	A19 Rotate the modified original pattern by 90 degrees
* 	A20 Checks if the modified original pattern is the same as the transformation 
*		pattern
* 	A21 If A20 is true, output that the pattern was rotated by 180 degrees
* 	A22 Rotate the modified original pattern by 90 degrees
* 	A23 Checks if the modified original pattern is the same as the transformation 
*		pattern
* 	A24 If A23 is true, output that the pattern was rotated by 270 degrees
* 	A25 Rotate the modified original pattern by 90 degrees to get back to its 
*		original 
*		orientation
* 	A26 – A37 Defines in CR11
* 	A38 Output that the pattern was improperly transformed because it did not match 
*		with any of the other transformations
* 
* CODE CORRECTNESS ARGUMENT
* -------------------------
* CA04 By L02
* CA05 By L03
* CA06 By L02
* CA07 By L04
* CA08 By L05
* CA09 By L07
* CA10 By L08
* CA11 By L08
* CA12 By L09
* CA13 By L09
* CA14 By L10
* CA15 By L11
* CA16 By L12
* CA17 By L13
* CA18 By L14
* CA19 By L15
* CA20 By L16
* CA21 By L17
* CA22 By L18
* CA23 By L19
* CA24 By L20
* CA25 By L21
* CA26 By L22
* CA27 By L23
* CA28 By L24
* CA29 By L25
* CA30 By L26
* CA31 By L27
* CA32 By L28
* CA33 By L29
* CA34 By L30
* CA35 By L31
* CA36 By L32
* CA37 By L33
* CA38 By L34
* 
* CALLING TREE
* ------------
* isSame()
* rotate()
* reflect()
*********************************************************/

int main(void){
	
	/*L01*/
	int patternNmbr = 0;
	int dimSize;
	char origPatt[MAX_DIMENSION][MAX_DIMENSION];
	char modPatt[MAX_DIMENSION][MAX_DIMENSION];
	
	while(cin >> dimSize){/*L02*/		
		patternNmbr++;/*L03*/
		if(dimSize < 1 || dimSize > 10){/*L04*/
			cout << "Pattern " << patternNmbr << " has an improper dimension size." 
					<< endl;/*L05*/
			cout << "Exiting program." << endl;
			break;/*L06*/
		}//if
		
		for(int indx = 0; indx < dimSize; indx++){/*L07*/			
			for(int indy = 0; indy < dimSize; indy++){/*L08*/
				cin >> origPatt[indx][indy];
			}//for
			
			for(int indy = 0; indy < dimSize; indy++){/*L09*/
				cin >> modPatt[indx][indy];
			}//for
		}//for
		
		if(isSame(origPatt,modPatt,dimSize)){/*L10*/
			cout << "Pattern " << patternNmbr << " was preserved." << endl;/*L11*/
			continue;
		}//if preserved
		
		rotate(origPatt,dimSize);/*L12*/
		if(isSame(origPatt,modPatt,dimSize)){/*L13*/
			cout << "Pattern " << patternNmbr << " was rotated 90 degrees." 
					<< endl;/*L14*/
			continue;
		}//if rotated 90
		
		rotate(origPatt,dimSize);/*L15*/
		if(isSame(origPatt,modPatt,dimSize)){/*L16*/
			cout << "Pattern " << patternNmbr << " was rotated 180 degrees." 
					<< endl;/*L17*/
			continue;
		}//if rotated 180
		
		rotate(origPatt,dimSize);/*L18*/
		if(isSame(origPatt,modPatt,dimSize)){/*L19*/
			cout << "Pattern " << patternNmbr << " was rotated 270 degrees." 
					<< endl;/*L20*/
			continue;
		}//if rotated 270
		
		rotate(origPatt,dimSize);/*L21*/
		reflect(origPatt,dimSize);/*L22*/
		if(isSame(origPatt,modPatt,dimSize)){/*L23*/
			cout << "Pattern " << patternNmbr << " was reflected vertically." 
					<< endl;/*L24*/
			continue;
		}//if reflected
		
		rotate(origPatt,dimSize);/*L25*/
		if(isSame(origPatt,modPatt,dimSize)){/*L26*/
			cout << "Pattern " << patternNmbr << " was reflected vertically ";/*L27*/
			cout << "and rotated 90 degrees." << endl;
			continue;
		}//if reflected 90
		
		rotate(origPatt,dimSize);/*L28*/
		if(isSame(origPatt,modPatt,dimSize)){/*L29*/
			cout << "Pattern " << patternNmbr << " was reflected vertically ";/*L30*/
			cout << "and rotated 180 degrees." << endl;
			continue;
		}//if reflected 180
		
		rotate(origPatt,dimSize);/*L31*/
		if(isSame(origPatt,modPatt,dimSize)){/*L32*/
			cout << "Pattern " << patternNmbr << " was reflected vertically ";/*L33*/
			cout << "and rotated 270 degrees." << endl;
			continue;
		}//if reflected 270
		
		cout << "Pattern " << patternNmbr << " was improperly transformed." 
				<< endl;/*L34*/
		
	}//while there is data in the input file
	
	return 0;	
	
}//main()

/*****************************************************************************
* DESCRIPTION – isSame()
* Returns true if the two 2D arrays representing the patterns are the same.
* 
* REQUIREMENTS
* R01		Input consists of 
*				- char origPatt[][]
*					- The 2D array representation of a pattern
*				- char modPatt[][]
*					- The pattern to be compared to origPatt[][]
*				- int dimSize
*					- The dimensions of the patterns
* R02		2D array inputs must both be square with dimensions of dimSize
* 
* SAMPLE INVOCATION
* See main() Sample Runs
* 
* DESIGN
* Significant variables
* ---------------------
* int dimSize
* char origPatt[][]
* 	   modPatt[][]
*
* Solution analysis
* -----------------
* Checks if each position in both arrays are equivalent
*
* Algorithm
* ---------
* A01 For(indx from 1 to dimSize){
* A02 	For(indy from 1 to dimSize){
* A03 		If (origPatt[indx][indy] != modPatt[indx][indx]){
* 	  			Return false;
*	  		}//If
*		}//For
*	  }//For
* A04 Return true;
********************************************************************************/
bool isSame(char origPatt[][MAX_DIMENSION],char modPatt[][MAX_DIMENSION], 
			int dimSize){
	
for(int indx = 0; indx < dimSize; indx++){/*L01*/
		for(int indy = 0; indy < dimSize; indy++){/*L02*/
			if(origPatt[indx][indy] != modPatt[indx][indy]){/*L03*/
				return false;
			}//if
		}//for
	}//for
	return true;/*L04*/
}//isSame()

/*****************************************************************************
* DESCRIPTION – rotate()
* Rotates a 2D array representation of a pattern by 90 degrees.
* 
* REQUIREMENTS
* R01		Input consists of 
*				- char origPatt[][]
*					- The 2D array representation of the pattern being rotated
*				- int dimSize
*					- The dimensions of the pattern
* R02		2D array input must both be square with dimensions of dimSize
*
* SAMPLE INVOCATION
* See main() for Sample Runs
* 
* DESIGN
* Significant variables
* ---------------------
* int dimSize
* char origPatt[][]
* 	   tempPatt[][]
*
* Solution analysis
* -----------------
* Create a temporary 2 dimensional array and fill it with the 
* pattern to rotate. Populate the original pattern with the 
* altered indices of [dimSize-indy-1][indx]
* 
* Algorithm
* ---------
* A01 char tempPatt[MAX_DIMENSION][MAX_DIMENSION];
* A02 For(indx from 1 to dimSize){
* A03 	For(indy form 1 to dimSize){
* 			tempPatt[indx][indy] = origPatt[indx][indy];
*		}//For
*	  }//For
* A04 For(indx from 1 to dimSize){
* 	  	For(indy from 1 to dimSize){
*			origPatt[indx][indy]=tempPatt[dimSize-indy-1][indx];
*		}//For
*	  }//For
********************************************************************************/
void rotate(char origPatt[][MAX_DIMENSION], int dimSize){
	
	char tempPatt[MAX_DIMENSION][MAX_DIMENSION];/*L01*/
	
	for(int indx = 0; indx < dimSize; indx++){/*L02*/
		for(int indy = 0; indy < dimSize; indy++){/*L03*/
			tempPatt[indx][indy] = origPatt[indx][indy];
		}//for
	}//for
	
	for(int indx = 0; indx < dimSize; indx++){/*L04*/
		for(int indy = 0; indy < dimSize; indy++){/*L05*/
			origPatt[indx][indy] = tempPatt[dimSize - indy - 1][indx];
		}//for
	}//for
}//rotate()

/*****************************************************************************
* DESCRIPTION – reflect()
* Reflects a 2D array representation of a pattern vertically.
* 
* REQUIREMENTS
* R01		Input consists of 
*				- char origPatt[][]
*					- The 2D array representation of the pattern being reflected
*				- int dimSize
*					- The dimensions of the pattern
* R02		2D array input must both be square with dimensions of dimSize
*
* DESIGN
* Significant variables
* ---------------------
* int dimSize
* char origPatt[][]
* 	   tempPatt[][]
*
* Solution analysis
* -----------------
* Create a temporary 2 dimensional array and fill it with the 
* pattern to reflect. Populate the original pattern with the 
* altered indices of [dimSize-indy-1][indy]
*
* Algorithm
* ---------
* A01 char tempPatt[MAX_DIMENSION][MAX_DIMENSION];
* A02 For(indx from 1 to dimSize){
* A03 	For(indy form 1 to dimSize){
* 			tempPatt[indx][indy] = origPatt[indx][indy];
*		}//For
*	  }//For
* A04 For(indx from 1 to dimSize){
* 	  	For(indy from 1 to dimSize){
*			origPatt[indx][indy]=tempPatt[dimSize-indy-1][indy];
*		}//For
*	  }//For
********************************************************************************/
void reflect(char origPatt[][MAX_DIMENSION], int dimSize){
	
	char tempPatt[MAX_DIMENSION][MAX_DIMENSION];/*L01*/
	
	for(int indx = 0; indx < dimSize; indx++){/*L02*/
		for(int indy = 0; indy < dimSize; indy++){/*L03*/
			tempPatt[indx][indy] = origPatt[indx][indy];
		}//for
	}//for
	
	for(int indx = 0; indx < dimSize; indx++){/*L04*/
		for(int indy = 0; indy < dimSize; indy++){/*L05*/
			origPatt[indx][indy] = tempPatt[dimSize - indx - 1][indy];
		}//for
	}//for
}//reflect()

//end MirrorAMD.cppp
