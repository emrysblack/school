#!/bin/bash
# runs sorting tests and outputs them to the proper files

# make sure we are using the current versions of the files
g++ -o sortTest sortTest.cpp
g++ -O1 -o sortTest1 sortTest.cpp
g++ -O2 -o sortTest2 sortTest.cpp
g++ -O3 -o sortTest3 sortTest.cpp
javac sortTest.java

# clean out old results
rm *.txt

# run C++ sorts
echo "running C++ tests"
./sortTest 60000 >> sortTest.txt
./sortTest 70000 >> sortTest.txt
./sortTest 80000 >> sortTest.txt
./sortTest 90000 >> sortTest.txt
./sortTest 100000 >> sortTest.txt

# run C++ optimize 1 sorts
echo "running C++ optimize 1 tests"
./sortTest1 60000 >> sortTest1.txt
./sortTest1 70000 >> sortTest1.txt
./sortTest1 80000 >> sortTest1.txt
./sortTest1 90000 >> sortTest1.txt
./sortTest1 100000 >> sortTest1.txt

# run C++ optimize 2 sorts
echo "running C++ optimize 2 tests"
./sortTest2 60000 >> sortTest2.txt
./sortTest2 70000 >> sortTest2.txt
./sortTest2 80000 >> sortTest2.txt
./sortTest2 90000 >> sortTest2.txt
./sortTest2 100000 >> sortTest2.txt

# run C++ optimize 3 sorts
echo "running C++ optimize 3 tests"
./sortTest3 60000 >> sortTest3.txt
./sortTest3 70000 >> sortTest3.txt
./sortTest3 80000 >> sortTest3.txt
./sortTest3 90000 >> sortTest3.txt
./sortTest3 100000 >> sortTest3.txt

# run Java sorts
echo "running Java tests"
java sortTest 60000 >> sortTestJ.txt
java sortTest 70000 >> sortTestJ.txt
java sortTest 80000 >> sortTestJ.txt
java sortTest 90000 >> sortTestJ.txt
java sortTest 100000 >> sortTestJ.txt