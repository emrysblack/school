#!/bin/sh

docX=http://emp.byui.edu/neffr/docs/UML%20for%20Java%20Programmers.docx

catDocXprogram=CatDocX

unpackDocXFile()
{
   zipFileEquivalentToDocXFile=UML_for_Java_Programmers.zip
   curl $docX > $zipFileEquivalentToDocXFile
   mkdir -p delete_me
   cd delete_me
   unzip ../$zipFileEquivalentToDocXFile
   cd ..
   echo $docX file unpacked in delete_me
   ls -l delete_me
   rm $zipFileEquivalentToDocXFile 
}

buildCode()
{
   javac *.java || exit 1
}

runProgramWithDefaultWrap()
{
   java $catDocXprogram $docX
}

runProgramWithWrapProperty()
{
   java -Dwrap=$wrap $catDocXprogram $docX
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
   rm -f output.* notwrapped.expected wrapped*.expected *.class
}

createExpectedNotWrappedOutput()
{
   echo "Here's a plug for \"Uncle Bob's\" book. See if it intrigues you! (This is the Foreword written by Pete McBreen, author of Software Craftmanship.)" > notwrapped.expected
   echo "" >> notwrapped.expected
   echo "Ho-hum, just what we need, another book about the UML. Doesn't UML Distilled cover everything a developer really needs to know about the UML? UML Distilled covers all of the UML diagram types; this book doesn't even cover all of the different diagrams." >> notwrapped.expected
   echo "" >> notwrapped.expected
   echo "Hang on a minute, this book covers all of the diagrams I use on real projects. It omits all of the diagrams I have to remind teams not to use. Maybe Robert Martin has written something that will surpass UML Distilled..." >> notwrapped.expected
   echo "" >> notwrapped.expected
   echo "Uh-oh, first glances can be deceptive. This is a great book that deserves to become a classic. UML for Java Programmers is the first book I have ever read that treats the UML as a tool for programmers to help them make their day job easier. A welcome change from all of the UML books that assume you want to become a language lawyer." >> notwrapped.expected
   echo "" >> notwrapped.expected
   echo "I really like the way that this book focuses on the specification and implementation level use of the UML, to communicate precise, unambiguous descriptions of a proposed design and existing code. Uncle Bob promotes the idea that an occasional UML diagram can save time by prescreening ideas before going to the expense of writing the code and that sometimes a UML diagram can be a great way of explaining how a part of an existing application works." >> notwrapped.expected
   echo "" >> notwrapped.expected
   echo "This is a book that explains how to use the UML on real projects, one that focuses on getting practical value out of using the UML. Simple things that make a big difference, like using UML diagrams to choose between alternatives, explaining design ideas on a white board using the UML, and the need to erase diagrams once they have achieved their purpose." >> notwrapped.expected
   echo "" >> notwrapped.expected
   echo "Having seen all too many shelfware CASE tools, I appreciate Robert's warnings about CASE tools. Personally I'd rather see organizations invest in decent meeting rooms with photocopying white boards rather than waste money on CASE tools. Yes, CASE tools can be kind of cool, but there are many other investment opportunities that will give much better payback in terms of developer productivity." >> notwrapped.expected
   echo "" >> notwrapped.expected
   echo "This book challenges developers to understand the value that can derive from drawing UML diagrams, and encourages developers to push back against the language lawyers and the UML police who encourage the inappropriate use of precision in UML diagrams." >> notwrapped.expected
   echo "" >> notwrapped.expected
   echo "Uncle Bob has done a great job in not only showing how to use the UML effectively, but in also explaining how to recognize when the UML diagrams are depicting bad design ideas. After all you can have a beautiful diagram that would make a language lawyer happy, but if the design stinks, you need to fix it." >> notwrapped.expected
   echo "" >> notwrapped.expected
   echo "The design guidelines and heuristics in this book transform it from a simple guide to the UML to a great book on how to do OO design. This book demonstrates that there is much more to OO design than simply drawing UML diagrams. The diagrams do not really make much of a difference; what matters is the critical thinking about the consequences of each of the design decisions. Yes, the diagrams can make it easier to see these consequences, but what really matters is that people know how to look for and deal with these consequences." >> notwrapped.expected
   echo "" >> notwrapped.expected
   echo "This book deserves to become a classic because it exposes the dirty little secret of software development: good design evolves out of many iterations of hard work on a problem." >> notwrapped.expected
   echo "" >> notwrapped.expected
   echo "This also explains why this book uses Java. Java has been through enough iterations that it is now useful. We have been through the hype and come out the other side. Uncle Bob does a great job of showing lots of straightforward Java code that is a massive step beyond the normal, toy code samples that many books show." >> notwrapped.expected
   echo "" >> notwrapped.expected
   echo "The combination of Java and the UML works well to show what good OO design looks like. Uncle Bob, many thanks for a great book." >> notwrapped.expected
   echo "" >> notwrapped.expected
   echo "As an example of UML language lawyer-speak, here is a figure from the book Learning UML 2.0." >> notwrapped.expected
   echo "" >> notwrapped.expected
   echo "" >> notwrapped.expected
   echo ' Note that this is the kind of thing that causes Uncle Bob to "rant"!' >> notwrapped.expected
}

createExpectedWrapped12Output()
{
   echo "Here's a" > wrapped12.expected
   echo "plug for" >> wrapped12.expected
   echo "\"Uncle" >> wrapped12.expected
   echo "Bob's\" book." >> wrapped12.expected
   echo "See if it" >> wrapped12.expected
   echo "intrigues" >> wrapped12.expected
   echo "you! (This" >> wrapped12.expected
   echo "is the" >> wrapped12.expected
   echo "Foreword" >> wrapped12.expected
   echo "written by" >> wrapped12.expected
   echo "Pete" >> wrapped12.expected
   echo "McBreen," >> wrapped12.expected
   echo "author of" >> wrapped12.expected
   echo "Software" >> wrapped12.expected
   echo "Craftmanship.)" >> wrapped12.expected
   echo "" >> wrapped12.expected
   echo "Ho-hum, just" >> wrapped12.expected
   echo "what we" >> wrapped12.expected
   echo "need," >> wrapped12.expected
   echo "another book" >> wrapped12.expected
   echo "about the" >> wrapped12.expected
   echo "UML. Doesn't" >> wrapped12.expected
   echo "UML" >> wrapped12.expected
   echo "Distilled" >> wrapped12.expected
   echo "cover" >> wrapped12.expected
   echo "everything a" >> wrapped12.expected
   echo "developer" >> wrapped12.expected
   echo "really needs" >> wrapped12.expected
   echo "to know" >> wrapped12.expected
   echo "about the" >> wrapped12.expected
   echo "UML? UML" >> wrapped12.expected
   echo "Distilled" >> wrapped12.expected
   echo "covers all" >> wrapped12.expected
   echo "of the UML" >> wrapped12.expected
   echo "diagram" >> wrapped12.expected
   echo "types; this" >> wrapped12.expected
   echo "book doesn't" >> wrapped12.expected
   echo "even cover" >> wrapped12.expected
   echo "all of the" >> wrapped12.expected
   echo "different" >> wrapped12.expected
   echo "diagrams." >> wrapped12.expected
   echo "" >> wrapped12.expected
   echo "Hang on a" >> wrapped12.expected
   echo "minute, this" >> wrapped12.expected
   echo "book covers" >> wrapped12.expected
   echo "all of the" >> wrapped12.expected
   echo "diagrams I" >> wrapped12.expected
   echo "use on real" >> wrapped12.expected
   echo "projects. It" >> wrapped12.expected
   echo "omits all of" >> wrapped12.expected
   echo "the diagrams" >> wrapped12.expected
   echo "I have to" >> wrapped12.expected
   echo "remind teams" >> wrapped12.expected
   echo "not to use." >> wrapped12.expected
   echo "Maybe Robert" >> wrapped12.expected
   echo "Martin has" >> wrapped12.expected
   echo "written" >> wrapped12.expected
   echo "something" >> wrapped12.expected
   echo "that will" >> wrapped12.expected
   echo "surpass UML" >> wrapped12.expected
   echo "Distilled..." >> wrapped12.expected
   echo "" >> wrapped12.expected
   echo "Uh-oh, first" >> wrapped12.expected
   echo "glances can" >> wrapped12.expected
   echo "be" >> wrapped12.expected
   echo "deceptive." >> wrapped12.expected
   echo "This is a" >> wrapped12.expected
   echo "great book" >> wrapped12.expected
   echo "that" >> wrapped12.expected
   echo "deserves to" >> wrapped12.expected
   echo "become a" >> wrapped12.expected
   echo "classic. UML" >> wrapped12.expected
   echo "for Java" >> wrapped12.expected
   echo "Programmers" >> wrapped12.expected
   echo "is the first" >> wrapped12.expected
   echo "book I have" >> wrapped12.expected
   echo "ever read" >> wrapped12.expected
   echo "that treats" >> wrapped12.expected
   echo "the UML as a" >> wrapped12.expected
   echo "tool for" >> wrapped12.expected
   echo "programmers" >> wrapped12.expected
   echo "to help them" >> wrapped12.expected
   echo "make their" >> wrapped12.expected
   echo "day job" >> wrapped12.expected
   echo "easier. A" >> wrapped12.expected
   echo "welcome" >> wrapped12.expected
   echo "change from" >> wrapped12.expected
   echo "all of the" >> wrapped12.expected
   echo "UML books" >> wrapped12.expected
   echo "that assume" >> wrapped12.expected
   echo "you want to" >> wrapped12.expected
   echo "become a" >> wrapped12.expected
   echo "language" >> wrapped12.expected
   echo "lawyer." >> wrapped12.expected
   echo "" >> wrapped12.expected
   echo "I really" >> wrapped12.expected
   echo "like the way" >> wrapped12.expected
   echo "that this" >> wrapped12.expected
   echo "book focuses" >> wrapped12.expected
   echo "on the" >> wrapped12.expected
   echo "specification" >> wrapped12.expected
   echo "and" >> wrapped12.expected
   echo "implementation" >> wrapped12.expected
   echo "level use of" >> wrapped12.expected
   echo "the UML, to" >> wrapped12.expected
   echo "communicate" >> wrapped12.expected
   echo "precise," >> wrapped12.expected
   echo "unambiguous" >> wrapped12.expected
   echo "descriptions" >> wrapped12.expected
   echo "of a" >> wrapped12.expected
   echo "proposed" >> wrapped12.expected
   echo "design and" >> wrapped12.expected
   echo "existing" >> wrapped12.expected
   echo "code. Uncle" >> wrapped12.expected
   echo "Bob promotes" >> wrapped12.expected
   echo "the idea" >> wrapped12.expected
   echo "that an" >> wrapped12.expected
   echo "occasional" >> wrapped12.expected
   echo "UML diagram" >> wrapped12.expected
   echo "can save" >> wrapped12.expected
   echo "time by" >> wrapped12.expected
   echo "prescreening" >> wrapped12.expected
   echo "ideas before" >> wrapped12.expected
   echo "going to the" >> wrapped12.expected
   echo "expense of" >> wrapped12.expected
   echo "writing the" >> wrapped12.expected
   echo "code and" >> wrapped12.expected
   echo "that" >> wrapped12.expected
   echo "sometimes a" >> wrapped12.expected
   echo "UML diagram" >> wrapped12.expected
   echo "can be a" >> wrapped12.expected
   echo "great way of" >> wrapped12.expected
   echo "explaining" >> wrapped12.expected
   echo "how a part" >> wrapped12.expected
   echo "of an" >> wrapped12.expected
   echo "existing" >> wrapped12.expected
   echo "application" >> wrapped12.expected
   echo "works." >> wrapped12.expected
   echo "" >> wrapped12.expected
   echo "This is a" >> wrapped12.expected
   echo "book that" >> wrapped12.expected
   echo "explains how" >> wrapped12.expected
   echo "to use the" >> wrapped12.expected
   echo "UML on real" >> wrapped12.expected
   echo "projects," >> wrapped12.expected
   echo "one that" >> wrapped12.expected
   echo "focuses on" >> wrapped12.expected
   echo "getting" >> wrapped12.expected
   echo "practical" >> wrapped12.expected
   echo "value out of" >> wrapped12.expected
   echo "using the" >> wrapped12.expected
   echo "UML. Simple" >> wrapped12.expected
   echo "things that" >> wrapped12.expected
   echo "make a big" >> wrapped12.expected
   echo "difference," >> wrapped12.expected
   echo "like using" >> wrapped12.expected
   echo "UML diagrams" >> wrapped12.expected
   echo "to choose" >> wrapped12.expected
   echo "between" >> wrapped12.expected
   echo "alternatives," >> wrapped12.expected
   echo "explaining" >> wrapped12.expected
   echo "design ideas" >> wrapped12.expected
   echo "on a white" >> wrapped12.expected
   echo "board using" >> wrapped12.expected
   echo "the UML, and" >> wrapped12.expected
   echo "the need to" >> wrapped12.expected
   echo "erase" >> wrapped12.expected
   echo "diagrams" >> wrapped12.expected
   echo "once they" >> wrapped12.expected
   echo "have" >> wrapped12.expected
   echo "achieved" >> wrapped12.expected
   echo "their" >> wrapped12.expected
   echo "purpose." >> wrapped12.expected
   echo "" >> wrapped12.expected
   echo "Having seen" >> wrapped12.expected
   echo "all too many" >> wrapped12.expected
   echo "shelfware" >> wrapped12.expected
   echo "CASE tools," >> wrapped12.expected
   echo "I appreciate" >> wrapped12.expected
   echo "Robert's" >> wrapped12.expected
   echo "warnings" >> wrapped12.expected
   echo "about CASE" >> wrapped12.expected
   echo "tools." >> wrapped12.expected
   echo "Personally" >> wrapped12.expected
   echo "I'd rather" >> wrapped12.expected
   echo "see" >> wrapped12.expected
   echo "organizations" >> wrapped12.expected
   echo "invest in" >> wrapped12.expected
   echo "decent" >> wrapped12.expected
   echo "meeting" >> wrapped12.expected
   echo "rooms with" >> wrapped12.expected
   echo "photocopying" >> wrapped12.expected
   echo "white boards" >> wrapped12.expected
   echo "rather than" >> wrapped12.expected
   echo "waste money" >> wrapped12.expected
   echo "on CASE" >> wrapped12.expected
   echo "tools. Yes," >> wrapped12.expected
   echo "CASE tools" >> wrapped12.expected
   echo "can be kind" >> wrapped12.expected
   echo "of cool, but" >> wrapped12.expected
   echo "there are" >> wrapped12.expected
   echo "many other" >> wrapped12.expected
   echo "investment" >> wrapped12.expected
   echo "opportunities" >> wrapped12.expected
   echo "that will" >> wrapped12.expected
   echo "give much" >> wrapped12.expected
   echo "better" >> wrapped12.expected
   echo "payback in" >> wrapped12.expected
   echo "terms of" >> wrapped12.expected
   echo "developer" >> wrapped12.expected
   echo "productivity." >> wrapped12.expected
   echo "" >> wrapped12.expected
   echo "This book" >> wrapped12.expected
   echo "challenges" >> wrapped12.expected
   echo "developers" >> wrapped12.expected
   echo "to" >> wrapped12.expected
   echo "understand" >> wrapped12.expected
   echo "the value" >> wrapped12.expected
   echo "that can" >> wrapped12.expected
   echo "derive from" >> wrapped12.expected
   echo "drawing UML" >> wrapped12.expected
   echo "diagrams," >> wrapped12.expected
   echo "and" >> wrapped12.expected
   echo "encourages" >> wrapped12.expected
   echo "developers" >> wrapped12.expected
   echo "to push back" >> wrapped12.expected
   echo "against the" >> wrapped12.expected
   echo "language" >> wrapped12.expected
   echo "lawyers and" >> wrapped12.expected
   echo "the UML" >> wrapped12.expected
   echo "police who" >> wrapped12.expected
   echo "encourage" >> wrapped12.expected
   echo "the" >> wrapped12.expected
   echo "inappropriate" >> wrapped12.expected
   echo "use of" >> wrapped12.expected
   echo "precision in" >> wrapped12.expected
   echo "UML" >> wrapped12.expected
   echo "diagrams." >> wrapped12.expected
   echo "" >> wrapped12.expected
   echo "Uncle Bob" >> wrapped12.expected
   echo "has done a" >> wrapped12.expected
   echo "great job in" >> wrapped12.expected
   echo "not only" >> wrapped12.expected
   echo "showing how" >> wrapped12.expected
   echo "to use the" >> wrapped12.expected
   echo "UML" >> wrapped12.expected
   echo "effectively," >> wrapped12.expected
   echo "but in also" >> wrapped12.expected
   echo "explaining" >> wrapped12.expected
   echo "how to" >> wrapped12.expected
   echo "recognize" >> wrapped12.expected
   echo "when the UML" >> wrapped12.expected
   echo "diagrams are" >> wrapped12.expected
   echo "depicting" >> wrapped12.expected
   echo "bad design" >> wrapped12.expected
   echo "ideas. After" >> wrapped12.expected
   echo "all you can" >> wrapped12.expected
   echo "have a" >> wrapped12.expected
   echo "beautiful" >> wrapped12.expected
   echo "diagram that" >> wrapped12.expected
   echo "would make a" >> wrapped12.expected
   echo "language" >> wrapped12.expected
   echo "lawyer" >> wrapped12.expected
   echo "happy, but" >> wrapped12.expected
   echo "if the" >> wrapped12.expected
   echo "design" >> wrapped12.expected
   echo "stinks, you" >> wrapped12.expected
   echo "need to fix" >> wrapped12.expected
   echo "it." >> wrapped12.expected
   echo "" >> wrapped12.expected
   echo "The design" >> wrapped12.expected
   echo "guidelines" >> wrapped12.expected
   echo "and" >> wrapped12.expected
   echo "heuristics" >> wrapped12.expected
   echo "in this book" >> wrapped12.expected
   echo "transform it" >> wrapped12.expected
   echo "from a" >> wrapped12.expected
   echo "simple guide" >> wrapped12.expected
   echo "to the UML" >> wrapped12.expected
   echo "to a great" >> wrapped12.expected
   echo "book on how" >> wrapped12.expected
   echo "to do OO" >> wrapped12.expected
   echo "design. This" >> wrapped12.expected
   echo "book" >> wrapped12.expected
   echo "demonstrates" >> wrapped12.expected
   echo "that there" >> wrapped12.expected
   echo "is much more" >> wrapped12.expected
   echo "to OO design" >> wrapped12.expected
   echo "than simply" >> wrapped12.expected
   echo "drawing UML" >> wrapped12.expected
   echo "diagrams." >> wrapped12.expected
   echo "The diagrams" >> wrapped12.expected
   echo "do not" >> wrapped12.expected
   echo "really make" >> wrapped12.expected
   echo "much of a" >> wrapped12.expected
   echo "difference;" >> wrapped12.expected
   echo "what matters" >> wrapped12.expected
   echo "is the" >> wrapped12.expected
   echo "critical" >> wrapped12.expected
   echo "thinking" >> wrapped12.expected
   echo "about the" >> wrapped12.expected
   echo "consequences" >> wrapped12.expected
   echo "of each of" >> wrapped12.expected
   echo "the design" >> wrapped12.expected
   echo "decisions." >> wrapped12.expected
   echo "Yes, the" >> wrapped12.expected
   echo "diagrams can" >> wrapped12.expected
   echo "make it" >> wrapped12.expected
   echo "easier to" >> wrapped12.expected
   echo "see these" >> wrapped12.expected
   echo "consequences," >> wrapped12.expected
   echo "but what" >> wrapped12.expected
   echo "really" >> wrapped12.expected
   echo "matters is" >> wrapped12.expected
   echo "that people" >> wrapped12.expected
   echo "know how to" >> wrapped12.expected
   echo "look for and" >> wrapped12.expected
   echo "deal with" >> wrapped12.expected
   echo "these" >> wrapped12.expected
   echo "consequences." >> wrapped12.expected
   echo "" >> wrapped12.expected
   echo "This book" >> wrapped12.expected
   echo "deserves to" >> wrapped12.expected
   echo "become a" >> wrapped12.expected
   echo "classic" >> wrapped12.expected
   echo "because it" >> wrapped12.expected
   echo "exposes the" >> wrapped12.expected
   echo "dirty little" >> wrapped12.expected
   echo "secret of" >> wrapped12.expected
   echo "software" >> wrapped12.expected
   echo "development:" >> wrapped12.expected
   echo "good design" >> wrapped12.expected
   echo "evolves out" >> wrapped12.expected
   echo "of many" >> wrapped12.expected
   echo "iterations" >> wrapped12.expected
   echo "of hard work" >> wrapped12.expected
   echo "on a" >> wrapped12.expected
   echo "problem." >> wrapped12.expected
   echo "" >> wrapped12.expected
   echo "This also" >> wrapped12.expected
   echo "explains why" >> wrapped12.expected
   echo "this book" >> wrapped12.expected
   echo "uses Java." >> wrapped12.expected
   echo "Java has" >> wrapped12.expected
   echo "been through" >> wrapped12.expected
   echo "enough" >> wrapped12.expected
   echo "iterations" >> wrapped12.expected
   echo "that it is" >> wrapped12.expected
   echo "now useful." >> wrapped12.expected
   echo "We have been" >> wrapped12.expected
   echo "through the" >> wrapped12.expected
   echo "hype and" >> wrapped12.expected
   echo "come out the" >> wrapped12.expected
   echo "other side." >> wrapped12.expected
   echo "Uncle Bob" >> wrapped12.expected
   echo "does a great" >> wrapped12.expected
   echo "job of" >> wrapped12.expected
   echo "showing lots" >> wrapped12.expected
   echo "of" >> wrapped12.expected
   echo "straightforward" >> wrapped12.expected
   echo "Java code" >> wrapped12.expected
   echo "that is a" >> wrapped12.expected
   echo "massive step" >> wrapped12.expected
   echo "beyond the" >> wrapped12.expected
   echo "normal, toy" >> wrapped12.expected
   echo "code samples" >> wrapped12.expected
   echo "that many" >> wrapped12.expected
   echo "books show." >> wrapped12.expected
   echo "" >> wrapped12.expected
   echo "The" >> wrapped12.expected
   echo "combination" >> wrapped12.expected
   echo "of Java and" >> wrapped12.expected
   echo "the UML" >> wrapped12.expected
   echo "works well" >> wrapped12.expected
   echo "to show what" >> wrapped12.expected
   echo "good OO" >> wrapped12.expected
   echo "design looks" >> wrapped12.expected
   echo "like. Uncle" >> wrapped12.expected
   echo "Bob, many" >> wrapped12.expected
   echo "thanks for a" >> wrapped12.expected
   echo "great book." >> wrapped12.expected
   echo "" >> wrapped12.expected
   echo "As an" >> wrapped12.expected
   echo "example of" >> wrapped12.expected
   echo "UML language" >> wrapped12.expected
   echo "lawyer-speak," >> wrapped12.expected
   echo "here is a" >> wrapped12.expected
   echo "figure from" >> wrapped12.expected
   echo "the book" >> wrapped12.expected
   echo "Learning UML" >> wrapped12.expected
   echo "2.0." >> wrapped12.expected
   echo "" >> wrapped12.expected
   echo "" >> wrapped12.expected
   echo " Note that" >> wrapped12.expected
   echo "this is the" >> wrapped12.expected
   echo "kind of" >> wrapped12.expected
   echo "thing that" >> wrapped12.expected
   echo "causes Uncle" >> wrapped12.expected
   echo "Bob to" >> wrapped12.expected
   echo "\"rant\"!" >> wrapped12.expected
}

createExpectedWrapped42Output()
{
   echo "Here's a plug for \"Uncle Bob's\" book. See" > wrapped42.expected
   echo "if it intrigues you! (This is the Foreword" >> wrapped42.expected
   echo "written by Pete McBreen, author of" >> wrapped42.expected
   echo "Software Craftmanship.)" >> wrapped42.expected
   echo "" >> wrapped42.expected
   echo "Ho-hum, just what we need, another book" >> wrapped42.expected
   echo "about the UML. Doesn't UML Distilled cover" >> wrapped42.expected
   echo "everything a developer really needs to" >> wrapped42.expected
   echo "know about the UML? UML Distilled covers" >> wrapped42.expected
   echo "all of the UML diagram types; this book" >> wrapped42.expected
   echo "doesn't even cover all of the different" >> wrapped42.expected
   echo "diagrams." >> wrapped42.expected
   echo "" >> wrapped42.expected
   echo "Hang on a minute, this book covers all of" >> wrapped42.expected
   echo "the diagrams I use on real projects. It" >> wrapped42.expected
   echo "omits all of the diagrams I have to remind" >> wrapped42.expected
   echo "teams not to use. Maybe Robert Martin has" >> wrapped42.expected
   echo "written something that will surpass UML" >> wrapped42.expected
   echo "Distilled..." >> wrapped42.expected
   echo "" >> wrapped42.expected
   echo "Uh-oh, first glances can be deceptive." >> wrapped42.expected
   echo "This is a great book that deserves to" >> wrapped42.expected
   echo "become a classic. UML for Java Programmers" >> wrapped42.expected
   echo "is the first book I have ever read that" >> wrapped42.expected
   echo "treats the UML as a tool for programmers" >> wrapped42.expected
   echo "to help them make their day job easier. A" >> wrapped42.expected
   echo "welcome change from all of the UML books" >> wrapped42.expected
   echo "that assume you want to become a language" >> wrapped42.expected
   echo "lawyer." >> wrapped42.expected
   echo "" >> wrapped42.expected
   echo "I really like the way that this book" >> wrapped42.expected
   echo "focuses on the specification and" >> wrapped42.expected
   echo "implementation level use of the UML, to" >> wrapped42.expected
   echo "communicate precise, unambiguous" >> wrapped42.expected
   echo "descriptions of a proposed design and" >> wrapped42.expected
   echo "existing code. Uncle Bob promotes the idea" >> wrapped42.expected
   echo "that an occasional UML diagram can save" >> wrapped42.expected
   echo "time by prescreening ideas before going to" >> wrapped42.expected
   echo "the expense of writing the code and that" >> wrapped42.expected
   echo "sometimes a UML diagram can be a great way" >> wrapped42.expected
   echo "of explaining how a part of an existing" >> wrapped42.expected
   echo "application works." >> wrapped42.expected
   echo "" >> wrapped42.expected
   echo "This is a book that explains how to use" >> wrapped42.expected
   echo "the UML on real projects, one that focuses" >> wrapped42.expected
   echo "on getting practical value out of using" >> wrapped42.expected
   echo "the UML. Simple things that make a big" >> wrapped42.expected
   echo "difference, like using UML diagrams to" >> wrapped42.expected
   echo "choose between alternatives, explaining" >> wrapped42.expected
   echo "design ideas on a white board using the" >> wrapped42.expected
   echo "UML, and the need to erase diagrams once" >> wrapped42.expected
   echo "they have achieved their purpose." >> wrapped42.expected
   echo "" >> wrapped42.expected
   echo "Having seen all too many shelfware CASE" >> wrapped42.expected
   echo "tools, I appreciate Robert's warnings" >> wrapped42.expected
   echo "about CASE tools. Personally I'd rather" >> wrapped42.expected
   echo "see organizations invest in decent meeting" >> wrapped42.expected
   echo "rooms with photocopying white boards" >> wrapped42.expected
   echo "rather than waste money on CASE tools." >> wrapped42.expected
   echo "Yes, CASE tools can be kind of cool, but" >> wrapped42.expected
   echo "there are many other investment" >> wrapped42.expected
   echo "opportunities that will give much better" >> wrapped42.expected
   echo "payback in terms of developer" >> wrapped42.expected
   echo "productivity." >> wrapped42.expected
   echo "" >> wrapped42.expected
   echo "This book challenges developers to" >> wrapped42.expected
   echo "understand the value that can derive from" >> wrapped42.expected
   echo "drawing UML diagrams, and encourages" >> wrapped42.expected
   echo "developers to push back against the" >> wrapped42.expected
   echo "language lawyers and the UML police who" >> wrapped42.expected
   echo "encourage the inappropriate use of" >> wrapped42.expected
   echo "precision in UML diagrams." >> wrapped42.expected
   echo "" >> wrapped42.expected
   echo "Uncle Bob has done a great job in not only" >> wrapped42.expected
   echo "showing how to use the UML effectively," >> wrapped42.expected
   echo "but in also explaining how to recognize" >> wrapped42.expected
   echo "when the UML diagrams are depicting bad" >> wrapped42.expected
   echo "design ideas. After all you can have a" >> wrapped42.expected
   echo "beautiful diagram that would make a" >> wrapped42.expected
   echo "language lawyer happy, but if the design" >> wrapped42.expected
   echo "stinks, you need to fix it." >> wrapped42.expected
   echo "" >> wrapped42.expected
   echo "The design guidelines and heuristics in" >> wrapped42.expected
   echo "this book transform it from a simple guide" >> wrapped42.expected
   echo "to the UML to a great book on how to do OO" >> wrapped42.expected
   echo "design. This book demonstrates that there" >> wrapped42.expected
   echo "is much more to OO design than simply" >> wrapped42.expected
   echo "drawing UML diagrams. The diagrams do not" >> wrapped42.expected
   echo "really make much of a difference; what" >> wrapped42.expected
   echo "matters is the critical thinking about the" >> wrapped42.expected
   echo "consequences of each of the design" >> wrapped42.expected
   echo "decisions. Yes, the diagrams can make it" >> wrapped42.expected
   echo "easier to see these consequences, but what" >> wrapped42.expected
   echo "really matters is that people know how to" >> wrapped42.expected
   echo "look for and deal with these consequences." >> wrapped42.expected
   echo "" >> wrapped42.expected
   echo "This book deserves to become a classic" >> wrapped42.expected
   echo "because it exposes the dirty little secret" >> wrapped42.expected
   echo "of software development: good design" >> wrapped42.expected
   echo "evolves out of many iterations of hard" >> wrapped42.expected
   echo "work on a problem." >> wrapped42.expected
   echo "" >> wrapped42.expected
   echo "This also explains why this book uses" >> wrapped42.expected
   echo "Java. Java has been through enough" >> wrapped42.expected
   echo "iterations that it is now useful. We have" >> wrapped42.expected
   echo "been through the hype and come out the" >> wrapped42.expected
   echo "other side. Uncle Bob does a great job of" >> wrapped42.expected
   echo "showing lots of straightforward Java code" >> wrapped42.expected
   echo "that is a massive step beyond the normal," >> wrapped42.expected
   echo "toy code samples that many books show." >> wrapped42.expected
   echo "" >> wrapped42.expected
   echo "The combination of Java and the UML works" >> wrapped42.expected
   echo "well to show what good OO design looks" >> wrapped42.expected
   echo "like. Uncle Bob, many thanks for a great" >> wrapped42.expected
   echo "book." >> wrapped42.expected
   echo "" >> wrapped42.expected
   echo "As an example of UML language" >> wrapped42.expected
   echo "lawyer-speak, here is a figure from the" >> wrapped42.expected
   echo "book Learning UML 2.0." >> wrapped42.expected
   echo "" >> wrapped42.expected
   echo "" >> wrapped42.expected
   echo " Note that this is the kind of thing that" >> wrapped42.expected
   echo "causes Uncle Bob to \"rant\"!" >> wrapped42.expected
}

createExpectedWrapped72Output()
{
   echo "Here's a plug for \"Uncle Bob's\" book. See if it intrigues you! (This is" > wrapped72.expected
   echo "the Foreword written by Pete McBreen, author of Software Craftmanship.)" >> wrapped72.expected
   echo "" >> wrapped72.expected
   echo "Ho-hum, just what we need, another book about the UML. Doesn't UML" >> wrapped72.expected
   echo "Distilled cover everything a developer really needs to know about the" >> wrapped72.expected
   echo "UML? UML Distilled covers all of the UML diagram types; this book" >> wrapped72.expected
   echo "doesn't even cover all of the different diagrams." >> wrapped72.expected
   echo "" >> wrapped72.expected
   echo "Hang on a minute, this book covers all of the diagrams I use on real" >> wrapped72.expected
   echo "projects. It omits all of the diagrams I have to remind teams not to" >> wrapped72.expected
   echo "use. Maybe Robert Martin has written something that will surpass UML" >> wrapped72.expected
   echo "Distilled..." >> wrapped72.expected
   echo "" >> wrapped72.expected
   echo "Uh-oh, first glances can be deceptive. This is a great book that" >> wrapped72.expected
   echo "deserves to become a classic. UML for Java Programmers is the first book" >> wrapped72.expected
   echo "I have ever read that treats the UML as a tool for programmers to help" >> wrapped72.expected
   echo "them make their day job easier. A welcome change from all of the UML" >> wrapped72.expected
   echo "books that assume you want to become a language lawyer." >> wrapped72.expected
   echo "" >> wrapped72.expected
   echo "I really like the way that this book focuses on the specification and" >> wrapped72.expected
   echo "implementation level use of the UML, to communicate precise, unambiguous" >> wrapped72.expected
   echo "descriptions of a proposed design and existing code. Uncle Bob promotes" >> wrapped72.expected
   echo "the idea that an occasional UML diagram can save time by prescreening" >> wrapped72.expected
   echo "ideas before going to the expense of writing the code and that sometimes" >> wrapped72.expected
   echo "a UML diagram can be a great way of explaining how a part of an existing" >> wrapped72.expected
   echo "application works." >> wrapped72.expected
   echo "" >> wrapped72.expected
   echo "This is a book that explains how to use the UML on real projects, one" >> wrapped72.expected
   echo "that focuses on getting practical value out of using the UML. Simple" >> wrapped72.expected
   echo "things that make a big difference, like using UML diagrams to choose" >> wrapped72.expected
   echo "between alternatives, explaining design ideas on a white board using the" >> wrapped72.expected
   echo "UML, and the need to erase diagrams once they have achieved their" >> wrapped72.expected
   echo "purpose." >> wrapped72.expected
   echo "" >> wrapped72.expected
   echo "Having seen all too many shelfware CASE tools, I appreciate Robert's" >> wrapped72.expected
   echo "warnings about CASE tools. Personally I'd rather see organizations" >> wrapped72.expected
   echo "invest in decent meeting rooms with photocopying white boards rather" >> wrapped72.expected
   echo "than waste money on CASE tools. Yes, CASE tools can be kind of cool, but" >> wrapped72.expected
   echo "there are many other investment opportunities that will give much better" >> wrapped72.expected
   echo "payback in terms of developer productivity." >> wrapped72.expected
   echo "" >> wrapped72.expected
   echo "This book challenges developers to understand the value that can derive" >> wrapped72.expected
   echo "from drawing UML diagrams, and encourages developers to push back" >> wrapped72.expected
   echo "against the language lawyers and the UML police who encourage the" >> wrapped72.expected
   echo "inappropriate use of precision in UML diagrams." >> wrapped72.expected
   echo "" >> wrapped72.expected
   echo "Uncle Bob has done a great job in not only showing how to use the UML" >> wrapped72.expected
   echo "effectively, but in also explaining how to recognize when the UML" >> wrapped72.expected
   echo "diagrams are depicting bad design ideas. After all you can have a" >> wrapped72.expected
   echo "beautiful diagram that would make a language lawyer happy, but if the" >> wrapped72.expected
   echo "design stinks, you need to fix it." >> wrapped72.expected
   echo "" >> wrapped72.expected
   echo "The design guidelines and heuristics in this book transform it from a" >> wrapped72.expected
   echo "simple guide to the UML to a great book on how to do OO design. This" >> wrapped72.expected
   echo "book demonstrates that there is much more to OO design than simply" >> wrapped72.expected
   echo "drawing UML diagrams. The diagrams do not really make much of a" >> wrapped72.expected
   echo "difference; what matters is the critical thinking about the consequences" >> wrapped72.expected
   echo "of each of the design decisions. Yes, the diagrams can make it easier to" >> wrapped72.expected
   echo "see these consequences, but what really matters is that people know how" >> wrapped72.expected
   echo "to look for and deal with these consequences." >> wrapped72.expected
   echo "" >> wrapped72.expected
   echo "This book deserves to become a classic because it exposes the dirty" >> wrapped72.expected
   echo "little secret of software development: good design evolves out of many" >> wrapped72.expected
   echo "iterations of hard work on a problem." >> wrapped72.expected
   echo "" >> wrapped72.expected
   echo "This also explains why this book uses Java. Java has been through enough" >> wrapped72.expected
   echo "iterations that it is now useful. We have been through the hype and come" >> wrapped72.expected
   echo "out the other side. Uncle Bob does a great job of showing lots of" >> wrapped72.expected
   echo "straightforward Java code that is a massive step beyond the normal, toy" >> wrapped72.expected
   echo "code samples that many books show." >> wrapped72.expected
   echo "" >> wrapped72.expected
   echo "The combination of Java and the UML works well to show what good OO" >> wrapped72.expected
   echo "design looks like. Uncle Bob, many thanks for a great book." >> wrapped72.expected
   echo "" >> wrapped72.expected
   echo "As an example of UML language lawyer-speak, here is a figure from the" >> wrapped72.expected
   echo "book Learning UML 2.0." >> wrapped72.expected
   echo "" >> wrapped72.expected
   echo "" >> wrapped72.expected
   echo " Note that this is the kind of thing that causes Uncle Bob to \"rant\"!" >> wrapped72.expected
}

createExpectedOutput()
{
   if [ "$wrap" = 0 ]
   then
      createExpectedNotWrappedOutput
      cp notwrapped.expected wrapped0.expected
   elif [ "$wrap" = 12 ]
   then
      createExpectedWrapped12Output
   elif [ "$wrap" = 42 ]
   then
      createExpectedWrapped42Output
   elif [ "$wrap" = 72 ]
   then
      createExpectedWrapped72Output
   else
      touch badWrap
   fi
}

test -d delete_me || \
read -p "Do you want to unpack the .docx file? " yesOrNo
if [ "$yesOrNo" = "y" ]
then
    unpackDocXFile
fi

buildCode
createExpectedNotWrappedOutput
cp notwrapped.expected output.expected
echo
echo "Running program with default wrap..."
echo
runProgramWithDefaultWrap | tee output.actual
diffActualWithExpectedOutput

read -p "Do you want to run the wrap tests? " yesOrNo
if [ "$yesOrNo" = "n" ]
then
   cleanup
   exit
fi

for wrap in 0 12 42 72
do
   createExpectedOutput $wrap
   cp wrapped$wrap.expected output.expected
   echo
   echo "Running program with wrap=$wrap..."
   echo
   runProgramWithWrapProperty | tee output.actual
   diffActualWithExpectedOutput
done
cleanup
