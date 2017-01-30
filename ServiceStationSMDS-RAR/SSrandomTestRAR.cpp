/*********************************************************
* PROJECT: Servicing Stations for ESOF322
* 
* FILE: SSrandomTestRAR.cpp
*
* DEV ENVIRONMENTS: Windows 10 using Notepad++
*
* EXECUTION ENVIRONMENTS: Windows 10 command line
*
* HISTORY:
* Date		Author			Description
* ====      ======          ===========
* 11/15/16   Alex Reid     	Full implementation and test
* 
* DESCRIPTION:
* Creates 9 random test cases for ServiceStationAMD.cpp
*
*/

//-------------
// C++ Includes
//-------------

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <time.h>

//-----------------
// Using Statements
//-----------------

using namespace std;

/*********************************************************
* DESCRIPTION - main
* Creates 9 random test case input files for ServiceStationAMD.cpp
*
* REQUIREMENTS
* R01	ServiceStationRAR is developed using MTM SMDS template version 4.2
* R02.	Is coded in C++ and adheres to the MTM Standard for C++ Source Files
* R03.	The directory containing ServiceStationRAR executable 
*	must also contain input text files
* R04.	ServiceStationRAR will be invoked from the Windows 
*	command line: ./ServiceStationRAR 
*
* R05.	ServiceStationRAR will be supplied an input text file input.txt 
*	from which to read in configurations of town clusters.
* R06.	The input consists of up to nine configurations of clusters of towns.
* R07.	Each configuration begins with two positive integers, N and M, 
*	separated by a space, where N is the number of towns 
*	and M is the number of connections between said towns.
* R08.	M number of connections follows, each connection is on a single line.
* R09.	For each connection, there will be two positive integers separated 
*	by a single whitespace. The first integer will be a town and the
*	second integer is the town it connects to.
* R10.	Input is guaranteed to have an EOF after the last line, 
*	indicated by a connection of       N = 0, M = 0.
* R11.	The only output is the minimum number of stations that need to be built
*	so that for any town, there is a service station in it or directly adjacent



* 
* DESIGN
* Significant variables
* ----------------------
* nmbrTests		//Number of tests being created
* outFile		//The tool writing to the output files
* test[]		//A string array storing all of the output files
* 
* Problem analysis
* -----------------
* To create the random test cases the program simply loops for every test case
* wanted and utilizes the rand() function to create random numbers with 
* respective parameters.
* 
* Algorithm
* ----------
*       main(){
* A00 Define   nmbrTownsPR, nmbrConnects;
* A01   While( cin << nmbrTownsPR <<  nmbrConnects){
* A02		If( !nmbrTownsPR && !nmbrConnects)
* A03				Break;
*		//If
* A04		For(ndx from 0 to nmbrConnects){
* A05 			Define  thisTown, connectsTo;
* A06			Read thisTown, connectsTo;
* A07 			Decrement thisTown, connectsTo;	
* A08			Set adjMatrixPtrPR [thisTown] = connectsTo;
* A09			Set adjMatrixPtrPR [connectsTo] = thisTown;
*		}//For
* A09		Define connections;
* A10		For(ndx from 0 to nmbrTownsPR){
* A11			Define nmbrConnections = 0;
* A12			For(ndy from 0 to nmbrTownsPR){
* A13			If(adjMatrixPtrPR[ndx] & 
* A14 				Convert<unsigned long long>(1) << ndy)
* A15				Increment nmbrConnections;
*			//If
*		}//For		
* A16		Set connections(pair<int, int> (nmbrConnections, ndx));
* 		}//For
* A17		Define townsPR[nmbrTownsPR];
* A18		Define iterator ndx = townsPR.begin();
* A19		For(Define iterator ndy; 
				from connections.begin() to connections.end()){
* A20			Set *ndx++ = ndy -> second;
*		}//For
* A21		Define coverMatrixPtrPR(nmbrTownsPR);
* A22		Define isCovered = 0;
* A23		For(Define ndxTownsPR = nmbrTownsPR - 1; from ndxTownsPR to 0 ){
* A24			Define towns = townsPR[ndxTownsPR];
* A25			Set isCovered |= adjMatrixPtrPR[towns] | 
*				(static_cast<unsigned long long>(1) << towns);
* A26			Set coverMatrixPtrPR[ndxTownsPR] = isCovered;
*		}//For
* A27		Define allCoveredPR = 
* 		(static_cast<unsigned long long>(1) << nmbrTownsPR) - 1;
* A28		Define coveredPR = 0;
* A29		Define minCoveredPtrPR = nmbrTownsPR;
* A30	Call dominatingSet(townsPR, nmbrTownsPR, 0, 0, 
*			   adjMatrixPtrPR, coverMatrixPtrPR, allCoveredPR, 	
*			   coveredPR, minCoveredPtrPR);	
*              }//while
*       }//main()
*
* A31 dominatingSet(){
* A32          If(minCoveredPtrPR <= nmbrTownsUsedPR + 1 
		   || ndxTownsPR == nmbrTowns)
* A33		return;
*             //If
* A34         If(coveredPR | coverMatrixPtrPR[ndxTownsPR]) != allCoveredPR)
* A35		return;
*             //If
* A36         Define & Set crrntTownNdx = townsPR[ndxTownsPR];
* A37         Define & Set crrntTown=static_cast<unsigned long long>(1)<<crrntTownNdx;
* A38         Define & Set whichIsCoveredPR =
				 coveredPR | adjMatrixPtrPR[crrntTownNdx] | crrntTown;
* A39         If(whichIsCoveredPR == allCoveredPR){
* A40		Set minCoveredPtrPR = nmbrTownsUsedPR + 1;
* A41		return;
*            //If
* A42        Call dominatingSet(townsPR, nmbrTownsPR, ndxTownsPR + 1,
*				nmbrTownsUsedPR + 1, adjMatrixPtrPR, coverMatrixPtrPR, 
*				allCoveredPR, whichIsCoveredPR, minCoveredPtrPR);
*
* A43        Call dominatingSet(townsPR, nmbrTownsPR, ndxTownsPR + 1, 
*				nmbrTownsUsedPR + 1, adjMatrixPtrPR, coverMatrixPtrPR,
*				allCoveredPR, coveredPR, minCoveredPtrPR);
*        }//dominatingSet
*
*
* ALGORITHM CORRECTNESS ARGUMENT
* -------------------------------
* CR07	By While loop which will only continue as long as there exists an N and M 
*	to read in; in A01 and A02
* CR08	By The For Loop which populates adjMatricPtrPR using the number of 
*	connections ; in A04	
* CR09	By A05 defines thisTown and connectsTo,
*	A06 then reads in thisTown and connectsTo.
* CR10	By If statement If(!nmbrTowns && !nmbrConnects) checks to make sure both 
*	variables are not zero. If they are zero, a break statement is issued 
*	and the while loop ends. 
* CR11	By A32 – A43
*
* dominatingSet works by checking to see first if the minimal coverage needed to
* service a set of towns matches the current number of towns designated 
* as service stations. If this case is met, then the minimal number of 
* service stations has been found. 
*
* Otherwise, dominatingSet does a bitwise
* or comparison between coveredPR and coverMatrixPtrPR[] at ndxTownsPR
* and sees if they are not equal to allCoveredPR.
* If this case is met, the minimal number of service stations has been found.
*
* Otherwise, dominatingSet checks if whichIsCoveredPR equals allCoveredPR.
* If this case is met, minCoveredPtrPR is set to nmbrTownsUsedPR + 1;
*
* If neither of the first two if statements is triggered, 
* dominatingSet will recursively call on itself twice to reduce the problem 
* by feeding covered and allCovered into the parameters. 
*/

int main(){

	int nmbrTests = 9;/*L00*/

	string tests[nmbrTests + 1];/*L01*/
	
	for(int indx = 0; indx < nmbrTests; indx++){/*L02*/
		
		tests[indx + 1] = "ssIn0" + to_string(indx + 1) + ".txt";/*L03*/
	}//for all of the test cases
	
	srand(time(NULL));/*L04*/
	
	for (int indx = 1; indx <= nmbrTests; indx++) {/*L05*/

		
		ofstream outFile;/*L06*/
		outFile.open(tests[indx]);/*L07*/
		
		int nmbrTowns = rand() % 35 + 3;/*L08*/
		int nmbrPairs = rand() % nmbrTowns;/*L09*/

		outFile << nmbrTowns << " " << nmbrPairs << endl;/*L10*/
		
		for (int indy = 0; indy < nmbrPairs; indy++) {/*L11*/
			
			outFile << rand() % nmbrTowns + 1 << " " 
			<< rand() % nmbrTowns + 1 << endl;/*L12*/
		}//for the number of pairs generated
		
		outFile << "0 0" << endl;/*L13*/
		outFile.close();/*L14*/
	}//for all of the test cases

    return 0;
}//main

//SSrandomTestRAR.cpp

