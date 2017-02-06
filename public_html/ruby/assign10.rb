#!/usr/bin/ruby -w
$stderr.reopen($stdout);
print "content-type: text/xml\n\n";

print "<?xml version = \"1.0\" encoding = \"utf-8\"?>\n";
#Stylesheet
print "<?xml-stylesheet href=\"/~emrys/html/assign10/assign10.xsl\" type=\"text/xsl\" ?>\n";
#Inline DTD
print "<!DOCTYPE studentList\n"; 
print "[\n";
print "<!ELEMENT studentList (student+)>\n";
print "<!ELEMENT student (name, location, college?)>\n";
print "<!ELEMENT  name (first, middle?, last)>\n";
print "<!ELEMENT  first (#PCDATA)>\n";
print "<!ELEMENT  middle (#PCDATA)>\n";
print "<!ELEMENT  last (#PCDATA)>\n";
print "<!ELEMENT  location (city,state)>\n";         
print "<!ELEMENT  city (#PCDATA)>\n";
print "<!ELEMENT  state (#PCDATA)>\n";
print "<!ELEMENT college (department?)>\n";
print "<!ELEMENT department (major*)>\n";
print "<!ELEMENT  major (#PCDATA)>\n";

print "<!ATTLIST college name CDATA #IMPLIED>\n";
print "<!ATTLIST department name CDATA \"#REQUIRED\">\n";
print "<!ATTLIST  major id CDATA \"399\">\n";
print "]>";

print "<studentList>";

#Student 1
print "<student>";
print "<name>";
print "<first>Clark</first>";
print "<middle>Superman</middle>";
print "<last>Kent</last>";
print "</name>";
print "<location>";
print "<city>Smallville</city>";
print "<state>Kansas</state>";
print "</location>";
print "<college name = \"Metropolis University\">";
print "<department name = \"Super Hero Sciences\">";
print "<major id = \"200\">Meta Human Physiology</major>";
print "</department>";
print "</college>";
print "</student>";

#Student 2
print "<student>";
print "<name>";
print "<first>Bruce</first>";
print "<middle>Batman</middle>";
print "<last>Wayne</last>";
print "</name>";
print "<location>";
print "<city>Gotham</city>";
print "<state>New York</state>";
print "</location>";
print "<college name = \"University of Gotham\">";
print "<department name = \"Super Hero Sciences\">";
print "<major id = \"347\">Gadget Engineering</major>";
print "</department>";
print "</college>";
print "</student>";

#Student 3
print "<student>";
print "<name>";
print "<first>Sam</first>";
print "<last>Winchester</last>";
print "</name>";
print "<location>";
print "<city>Lawrence</city>";
print "<state>Kansas</state>";
print "</location>";
print "<college name = \"School of Hardknocks\">";
print "<department name = \"Monster Physiology\">";
print "<major id = \"164\">Monster Hunting</major>";
print "</department>";
print "</college>";
print "</student>";

#Student 4
print "<student>";
print "<name>";
print "<first>Dean</first>";
print "<last>Winchester</last>";
print "</name>";
print "<location>";
print "<city>Lawrence</city>";
print "<state>Kansas</state>";
print "</location>";
print "<college name = \"School of Hardknocks\">";
print "<department name = \"Monster Physiology\">";
print "<major id = \"164\">Monster Hunting</major>";
print "</department>";
print "</college>";
print "</student>";

#Student 5
print "<student>";
print "<name>";
print "<first>Peter</first>";
print "<last>Pan</last>";
print "</name>";
print "<location>";
print "<city>Lost Boy Hideout</city>";
print "<state>Neverland</state>";
print "</location>";
print "<college name = \"Never Never University\">";
print "<department name = \"Super Hero Sciences\">";
print "<major id = \"200\">Meta Human Physiology - Flight Emphasis</major>";
print "</department>";
print "</college>";
print "</student>";

print "</studentList>";
