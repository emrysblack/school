/***********************************************************************
 * Program:
 *    Exploration 4, Brightness
 *    Brother Neff, CS237
 *
 * Author:
 *    Brady Field
 *
 * Summary:
 *    A response to an essay on pigeons and pigeonholes.
 *
 ***********************************************************************/

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cassert>
using namespace std;

const int NUMALPHA = 26;

void whatIthinkAboutTheEssayInGeneral()
{
   cout << "It is an interesting essay. It is well done and demonstrates\n"
        << "the principle in simple ways that make sense, but then expands\n" 
        << "it to bigger application. I would recommend it to my mother who\n" 
        << "is mathematically challenged.";
}

void whatIthinkAboutTheCertaintyNotChanceFeatureOfThePigeonholePrinciple()
{
   cout << "At first met with a bit of resistance, it becomes intuitive really.\n" 
        << "It is simply division and a modulus. Once broken into the math, it\n" 
        << "becomes a property and not chance nor opinion.\n\n";
}

void whatIthinkAboutThePhilosophicalAspectOfThePigeonholePrinciplePerPage41()
{
   cout << "It made me think of Lehi speaking of the existence of a Creator.\n" 
        << "He says that if God does not exist, then we do not since there could\n" 
        << "be no creation of things. He does not go into the details of God in that\n" 
        << "verse, he simply argues using the pigeon hole principle that with what we\n" 
        << "know that He must exist. (2 Nephi 2:13)\n\n";
}

void howMyDiscussionWithAnonClassmateWent()
{
   cout << "I discussed it with my mother. She accepted most of it when I explained it\n" 
        << "to her and used a few examples, but she did resist that part of it being certainty\n" 
        << "and not simply opinion with bigger applications. I still don’t have her fully\n" 
        << "convinced of that.\n\n";
}

void howIgrappledWithTheProblemAtTheBottomOfPage40()
{
   cout << "I calculated that the total number of possible initials would be 18,252.\n" 
        << "I then multiplied this by 64 which is the total number of combinations for the\n" 
        << "qualifications. This yielded 1,168,128 pigeon holes to work with. Now I just had\n" 
        << "to figure out how many pigeons there are. According to the article there are over\n" 
        << "272,000 people in Eastern Idaho. This is actually the small part of Idaho. It is\n" 
        << "common knowledge that 3/4 of the entire population of Idaho resides in Boise. So,\n"  
        << "if we populate Western Idaho to a similar fashion as Eastern, we get 272,000 people\n" 
        << "there as well not including Boise. This yields 544,000 people. Now we multiply by 4\n" 
        << "to take into account the other ¾ population we are missing and we get 2,176,000 people.\n" 
        << "This is a lot more pigeons that pigeon holes. Even if we over-estimated that population of\n" 
        << "Western Idaho outside of Boise by a lot and we reduce it to 130,000 people (that’s less than half),\n" 
        << "we still get 1,608,000 pigeons. This still guarantees that our pigeon hole principle works\n" 
        << "for these assumptions on page 40 of the essay.\n\n";
}

int calculateNumberOfPossibleInitialsIncludingMiddleInitialIfAny(
   int howManyCharactersAreInTheAlphabet)
{
   int howManySquared = howManyCharactersAreInTheAlphabet *
      howManyCharactersAreInTheAlphabet;
   return howManySquared * (howManyCharactersAreInTheAlphabet + 1);
}

string pigeonholeFromPigeon(string pigeonRepresentedAsApersonWithTraits)
{
   string bitString;
   // get name
   int i;
   for (i = 0; pigeonRepresentedAsApersonWithTraits[i] != ':'; i++)
   {
      if (isupper(pigeonRepresentedAsApersonWithTraits[i]))
      {
         bitString += pigeonRepresentedAsApersonWithTraits[i];
      }
   }
   //handle middle initial
   if (bitString.length() < 3)
   {
      // if no middle name
      bitString.insert(1, "_");
   }
   int possibleInitials =
      calculateNumberOfPossibleInitialsIncludingMiddleInitialIfAny(NUMALPHA);
   cout << bitString << " is one of "
        << possibleInitials << " possible results\n";
   // build trait bools
   for (i++; i < pigeonRepresentedAsApersonWithTraits.length();i++)
   {
      if (pigeonRepresentedAsApersonWithTraits[i] == ' ')
      {
         if (pigeonRepresentedAsApersonWithTraits[i + 1] == 'N'
             && pigeonRepresentedAsApersonWithTraits[i + 2] == 'o')
         {
            bitString += '0';
         }
         else
         {
            bitString += '1';
         }
      }
   }
   assert(bitString.length() == 9);
   int numPossible = 2 * 2 * 2 * 2 * 2 * 2; // 2 ^ 6
   cout << "There are " << numPossible << " possible trait outcomes\n";
   cout << bitString << " is one of "
        << possibleInitials * numPossible << " possible results\n";
   return bitString;
}

void usage(const char * programName)
{
   cout << "USAGE: " << programName << " [test params]\n"
        << "e.g. " << programName << " all\n";
}

void runOne(string test)
{
   cout << "\nRunning test " << test << endl;
   if (test == "learned")
   {
      whatIthinkAboutTheEssayInGeneral();
      whatIthinkAboutTheCertaintyNotChanceFeatureOfThePigeonholePrinciple();
      whatIthinkAboutThePhilosophicalAspectOfThePigeonholePrinciplePerPage41();
      howMyDiscussionWithAnonClassmateWent();
      howIgrappledWithTheProblemAtTheBottomOfPage40();
   }
   else if (test == "calculateNumberOfPossibleInitialsIncludingMiddleInitialIfAny")
   {
      
      cout << "number of possible initials including middle if any: "
           << calculateNumberOfPossibleInitialsIncludingMiddleInitialIfAny(NUMALPHA);
   }
   else if (test == "pigeonholeFromPigeon")
   {
      string testString = "James Meldrum: LDS lovesCats NoBites NoContacts BornLate LivesClose";
      string ans = pigeonholeFromPigeon(testString);
      cout << "\npigeon hole from pigeon: " << ans << endl;
   }
   else
   {
      cout << "Unkown Test\n";
      usage("brightness");
   }
}

void runAll()
{
   cout << "Running all tests.\n";
   runOne("learned");
   runOne("calculateNumberOfPossibleInitialsIncludingMiddleInitialIfAny");
   runOne("pigeonholeFromPigeon");
}
