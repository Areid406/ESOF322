#@Title:	mirrorCoverageTestRAR.sh
#@Author:	Alex Reid
#@Date:		12/10/2016

#@Run Instructions:	Simply type "bash mirrorCoverageTestRAR.sh" in the katie terminal
#@Preconditions:	In order for this program to work successfully, all input and output
#			test files must be in the same directory as this shell program and
#			the "MirrorRAR.cpp" file

#Bash program to compile and run tests for MirrorRAR.cpp
#This program will work for any file named "smtst_*_in" and "smtst_*_out" as long as * is in {1-34}
#It will output the coverage test results to a file named "mirrorCoverageTestRsltsRAR.txt"

#Compile the current version
g++ -fprofile-arcs -ftest-coverage MirrorRAR.cpp -o testExecutable

for i in smtst_*_in.txt
do
	testNum=$(echo $i| cut -d'_' -f 2)
	outExp="smtst_"$testNum"_out.txt"
	outTest="smtst_"$testNum"_outRun.txt"
	./testExecutable < $i > $outTest
done	

rm smtst*outRun

#Create mirrorCoverageTestRsltsAMD.txt file
gcov MirrorRAR.cpp > mirrorCoverageTestRsltsRAR.txt
cat MirrorRAR.cpp.gcov >> mirrorCoverageTestRsltsRAR.txt