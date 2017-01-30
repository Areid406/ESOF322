#@Title:	mirrorRARtestRun.sh
#@Author:	Alex Reid
#@Date:		12/10/2016

#@Run Instructions:	Simply type "bash mirrorRARtestRun.sh" in the katie terminal
#@Preconditions:	In order for this program to work successfully, all input and output
#                   test files must be in the same directory as this shell program and
#                   the "MirrorRAR.cpp" file

#Bash program to compile and run tests for MirrorAMD.cpp
#This program will work for any file named "smtst_*_in" and "smtst_*_out" as long as * is in {1-34}
#It will output the test results to a file named "MirrorRARtestResults.txt"

#Compile the current version
g++ -std=c++11 MirrorRAR.cpp -o testRAR
g++ -std=c++11 MirrorAMD.cpp -o testAMD

#Test output file
outFile=MirrorRARrandomtTestRslts.txt

#Formatting for output file Header
printf "+++MirrorRAR Test Run+++\n" > $outFile
printf "Testing the file MirrorRAR.cpp against MirrorAMD.cpp\n" >> $outFile
printf "\n-----------------------------------------\n" >> $outFile
#Count how many tests failed
numFailed=0
for i in smtst_*_in.txt
do
	testNum=$(echo $i| cut -d'_' -f 2)
	outTestRAR="smtst_"$testNum"_outRunRAR.txt"
	outTestAMD="smtst_"$testNum"_outRunAMD.txt"
	./testRAR < $i > $outTestRAR
	./testAMD < $i > $outTestAMD
	printf "Input File:\t%s\t" $i >> $outFile

	diff -w $outTestRAR $outTestAMD > /dev/null
	if [[ $? -eq 0 ]]
	then
		printf "Passed\n" >> $outFile
	else
		printf "Failed\n" >> $outFile
		let "numFailed++"
	fi
	printf "\n-----------------------------------------\n" >> $outFile
done

rm smtst*outRunRAR.txt
rm smtst*outRunAMD.txt

#Print out how many test failed or All tests passed
if [[ $numFailed -eq 0 ]]
then
	printf "All tests passed" >> $outFile
else
	printf "\n%s tests FAILED" $numFailed >> $outFile
fi


#Mark the end of file for the test results
printf "\n\n---MirrorRAR Test Run---\n" >> $outFile

