/*********************************************************
* PROJECT: Servicing Stations for ESOF322
* 
* FILE: ServiceStationsRAR.cpp
*
* DEV ENVIRONMENTS: Windows 10 using Programmer's Notepad
*
* EXECUTION ENVIRONMENTS: Windows 10 command line
*
* HISTORY:
* Date		Author			Description
* ====      ======          ===========
* 10/17/16  Alex Reid       Initial implementation and test
* 
* DESCRIPTION:
* Determines the minimum number of service stations needed 
* for a set of twon configurations. Conforms to the MTM
* Standard for C++ Source Files.
*/

//-------------
// C++ Includes
//-------------
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#ifdef __ELAPSED_TIME__
#include <ctime> 
#endif

//-----------------
// Using Statements
//-----------------
using namespace std;

void dominatingSet(const vector<int>& townsPR, 
					int nmbrTownsPR, 
					int ndxTownsPR, 
					int nmbrTownsUsedPR  /*number of towns to get service stations*/ , 
					const vector<unsigned long long>& adjMatrixPtrPR,
					const vector<unsigned long long>& coverMatrixPtrPR,
					const unsigned long long allCoveredPR, 
					unsigned long long coveredPR, 
					int& minCoveredPtrPR){
						
/*L01*/		if(minCoveredPtrPR <= nmbrTownsUsedPR + 1 || ndxTownsPR == nmbrTownsPR){
/*L02*/			return;
/*L03*/		}//no need to further search
/*L04*/		if( (coveredPR | coverMatrixPtrPR[ndxTownsPR]) != allCoveredPR ){
/*L05*/			return;
			}//endif	
		
/*L06*/		int crrntTownNdx = townsPR[ndxTownsPR];
/*L07*/		unsigned long long crrntTown = static_cast<unsigned long long>(1) << crrntTownNdx;
/*L08*/		unsigned long long whichIsCoveredPR = coveredPR | adjMatrixPtrPR[crrntTownNdx] | crrntTown;	
		
/*L09*/		if(whichIsCoveredPR == allCoveredPR){
	#ifdef DEBUG
/*L10*/			cout << nmbrTownsUsedPR + 1 << endl;
	#endif
/*L11*/			minCoveredPtrPR = nmbrTownsUsedPR + 1;
/*L12*/			return;
			}//endif
		
		   /*
			* recursive calls updating ndxTownsPR, nmbrTownsUsedPR, and use of either coveredPR or
			* whichIsCoveredPR.
			*/
/*L13*/		dominatingSet(townsPR, nmbrTownsPR, ndxTownsPR + 1, nmbrTownsUsedPR + 1,
					adjMatrixPtrPR, coverMatrixPtrPR, allCoveredPR, whichIsCoveredPR, minCoveredPtrPR);
/*L14*/		dominatingSet(townsPR, nmbrTownsPR, ndxTownsPR + 1, nmbrTownsUsedPR,
					adjMatrixPtrPR, coverMatrixPtrPR, allCoveredPR, coveredPR, minCoveredPtrPR);
}//dominatingSet()




int main(int /* argc */, char** /* argv */){
#ifdef __ELAPSED_TIME__
/*L01*/	clock_t startTime = clock();
#endif	
/*L02*/	int nmbrTownsPR, nmbrConnects;	
	
/*L03*/	while(cin >> nmbrTownsPR >> nmbrConnects){
/*L04*/		if(!nmbrTownsPR && !nmbrConnects){
/*L05*/			break;
			}//endif	
		
/*L06*/		vector<unsigned long long> adjMatrixPtrPR(nmbrTownsPR, 0);
			//adjacency bitmap of nmbrTownsPR vertices or "towns"
		
/*L07*/		for(int ndx = 0; ndx < nmbrConnects; ndx++){
/*L08*/			int thisTown, connectsTo;
/*L09*/			cin >> thisTown >> connectsTo;
/*L10*/			thisTown--;
/*L11*/			connectsTo--;
/*L12*/			adjMatrixPtrPR[thisTown] |= static_cast<unsigned long long>(1) << connectsTo;
/*L13*/			adjMatrixPtrPR[connectsTo] |= static_cast<unsigned long long>(1) << thisTown;
				//symmetrical bitwise assignments using pairs of towns as indeces to build adjacency matrix
			}//endfor
		
/*L14*/		multimap<int, int, greater<int> > connections;
			//value is a town, key is its number of connections
		
/*L15*/		for(int ndx = 0; ndx < nmbrTownsPR; ndx++){		
/*L16*/			int nmbrConnections = 0;			
/*L17*/			for(int ndy = 0; ndy < nmbrTownsPR; ndy++){
/*L18*/				if(adjMatrixPtrPR[ndx] & 
/*L19*/				(static_cast<unsigned long long>(1) << ndy)){
/*L20*/					nmbrConnections++; //nested loops add up connections
					}//endif
				}//endfor
/*L21*/			connections.insert( pair <int, int> (nmbrConnections, ndx) );
				//towns and their connections are inserted into connections multimap
			}//endfor
		
/*L22*/		vector<int> townsPR( nmbrTownsPR );
/*L23*/		//vector of town in descending order of their connections
/*L24*/		vector<int>::iterator ndx = townsPR.begin();
		
			/*
			 * Loops through, increments this ^^^  ndx's pointer, and then allows townsPR pointers 
			 * to also point to what index ndy points to in the connections multimap.
			 * This allows for townsPR and connections to associate which town is connected to which.
			 */
/*L25*/		for(multimap<int, int, greater<int> >::const_iterator ndy = connections.begin();
				ndy != connections.end(); ndy++){				
#ifdef DEBUG
			cout << ndy->first << ' ' << ndy->second << endl;
#endif
/*L26*/			*ndx++ = ndy->second;
		}//endfor				
#ifdef DEBUG
			count << endl;
#endif			
/*L27*/		vector<unsigned long long> coverMatrixPtrPR(nmbrTownsPR);
			//coverMatrixPtrPR[towns] is the bitmap covered by the set of towns
			// from townsPR[towns] - townsPR[nmbrTownsPR - 1]		
	
/*L28*/		unsigned long long isCovered = 0;	
		
			/*
			 * looping backwards relative to previous code, 
			 * assign result of bitwise or operator, indicating if a town is covered,
			 * into coverMatrix.
			 */
/*L29*/		for(int ndxTownsPR = nmbrTownsPR - 1; ndxTownsPR >= 0; ndxTownsPR-- ){
/*L30*/			int towns = townsPR[ndxTownsPR];
/*L31*/			isCovered |= adjMatrixPtrPR[towns] | 
							(static_cast<unsigned long long>(1) << towns);
/*L32*/			coverMatrixPtrPR[ndxTownsPR] = isCovered;
				}//endfor			
		
/*L33*/		unsigned long long allCoveredPR = 
			(static_cast<unsigned long long>(1) << nmbrTownsPR) - 1, coveredPR = 0;
			
/*L34*/		int minCoveredPtrPR = nmbrTownsPR;
		
/*L35*/		dominatingSet(townsPR, nmbrTownsPR, 0, 0, adjMatrixPtrPR, 
					  coverMatrixPtrPR, allCoveredPR, coveredPR, minCoveredPtrPR);	
		
/*L36*/		cout << minCoveredPtrPR << endl;
	}//endwhile		
#ifdef __ELAPSED_TIME__
/*L37*/		cerr << "elapsed time = " << 
/*L38*/		static_cast<double>(clock()- startTime) / CLOCKS_PER_SEC << " sec. \n";
#endif
/*L39*/		return 0;
}//main()