#!/bin/sh

################## NO NEED TO CHANGE ANYTHING IN THIS SCRIPT ##################

setupData()
{
   data="Enos,ninety,Cainan,eight hundred and fifteen,nine hundred and five:Cainan,seventy,Mahalaleel,eight hundred and forty,nine hundred and ten:Mahalaleel,sixty and five,Jared,eight hundred and thirty,eight hundred and ninety and five"
}

runProgram()
{
   java -ea -Ddata="$data" BegatOMatic
}

checkAndCompileProgram()
{
   if [ BegatOMatic.java -nt BegatOMatic.class ]
   then
      javac BegatOMatic.java || exit 1
   fi
}

createExpectedOutput()
{
   echo "9. And Enos lived ninety years, and begat Cainan:" > output.expected
   echo "10. And Enos lived after he begat Cainan eight hundred and fifteen years, and begat sons and daughters:" >> output.expected
   echo "11. And all the days of Enos were nine hundred and five years: and he died." >> output.expected
   echo "12. And Cainan lived seventy years, and begat Mahalaleel:" >> output.expected
   echo "13. And Cainan lived after he begat Mahalaleel eight hundred and forty years, and begat sons and daughters:" >> output.expected
   echo "14. And all the days of Cainan were nine hundred and ten years: and he died." >> output.expected
   echo "15. And Mahalaleel lived sixty and five years, and begat Jared:" >> output.expected
   echo "16. And Mahalaleel lived after he begat Jared eight hundred and thirty years, and begat sons and daughters:" >> output.expected
   echo "17. And all the days of Mahalaleel were eight hundred and ninety and five years: and he died." >> output.expected
}

diffActualWithExpectedOutput()
{
    echo "====================================================================="
    echo "diffing actual output with expected output..."
    echo "---------------------------------------------------------------------"
    if diff output.actual output.expected
    then
	echo "Congratulations, there were no differences!"
    fi
    echo "---------------------------------------------------------------------"
}

cleanup()
{
   rm -f output.*
}

checkAndCompileProgram
createExpectedOutput
setupData
runProgram | tee output.actual
diffActualWithExpectedOutput
cleanup
