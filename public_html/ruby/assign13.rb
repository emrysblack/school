#!/usr/bin/ruby -w
$stderr.reopen($stdout);
require "cgi"
cgi = CGI.new(level="html4");     # create cgi object for html4 strict
   
if (cgi.params.length != 0);      # hash length
  hash = cgi.params;             # returns a hash of key/value pairs
  keys = cgi.keys;               # returns an array of the key names
  type = cgi['pType'];
  name = cgi['fName'] + " " + cgi['lName'];
  id = cgi['sId'];
  skill = cgi['skill'];
  inst = cgi['inst'];
  name1 = cgi['fName1'] + " " + cgi['lName1'];
  id1 = cgi['sId1'];
  skill1 = cgi['skill1'];
  inst1 = cgi['inst1'];
  location = cgi['location'] + " " + cgi['room'];
  time = cgi['time'] + " " + cgi['am']; 
end
student = "<tr style='background:white'>\n" + "<td>#{name}</td>\n" + 
  "<td>#{id}</td>\n" + "<td>#{type}</td>\n" +"<td>#{skill}</td>\n" +
  "<td>#{inst}</td>\n" + "<td>#{location}</td>\n" + 
  "<td>#{time}</td>\n" + "</tr>\n";
if type == "Duet";
   student = student + "<tr style='background:white'>\n" + 
    "<td>#{name1}</td>\n" + "<td>#{id1}</td>\n" + "<td>#{type}</td>\n" +
    "<td>#{skill1}</td>\n" + "<td>#{inst1}</td>\n" + "<td>#{location}</td>\n" + 
    "<td>#{time}</td>\n" + "</tr>\n";
end
fileName = "../public_html/html/assign13/assign13.html";

file = File.open(fileName, "r+");
content = "";
while !file.eof?
   text = file.gets;
   if text != "</table>";
    content = content + text;
    end
end
file.close
file = File.open(fileName, "w");
file.syswrite(content);
file.syswrite(student);
file.syswrite("</table>");
file.close;

print "content-type: text/html\n\n";

puts "<html>";
puts "<head>";
puts "<link rel='stylesheet' type='text/css'"
puts " href = '/~emrys/html/css/style.css'></style>";
puts "</head>";
puts "<body>";
puts "<div style='margin:auto; border:2px";
puts "solid #a1a1a1; padding:10px 40px; background:#dddddd; width:300px;";
puts "border-radius:25px;'>";
puts "<p style='text-align:center'><span><i>Success</i></span></p>";
puts "</div>";
puts "</body>";
puts "</html>";
