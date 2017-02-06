#!/usr/bin/ruby -w
$stderr.reopen($stdout);
    require "cgi"
    cgi = CGI.new(level="html4");     # create cgi object for html4 strict
   
    if (cgi.params.length != 0);      # hash length
       name = cgi['fName'] + ' ' + cgi['lName'];
       address = cgi['address'] + ' ' + cgi['address1'];   
       phone = '(' + cgi['phone'] + ') ' + cgi['phone1'] + '-' + cgi['phone2'];
       items1 = cgi['shop1'];
       items2 = cgi['shop2'];
       items3 = cgi['shop3'];
       items4 = cgi['shop4'];
       cost = items1.to_f + items2.to_f + items3.to_f + items4.to_f;
       cType = cgi['cct'];
       cNum = cgi['ccn3'];
       cExp = cgi['expM'] + ' ' + cgi['expY'];
       hash = cgi.params;             # returns a hash of key/value pairs
       keys = cgi.keys;               # returns an array of the key names 
    end
    if (items1 != '')
      items1 = "<p style='text-align:center'>Baby Tiger</p>";
    end
    if (items2 != '')
      items2 = "<p style='text-align:center'>Baby Zebra</p>";
    end
    if (items3 != '')
      items3 = "<p style='text-align:center'>Baby Jaguar</p>";
    end
    if (items4 != '')
      items4 = "<p style='text-align:center'>Baby Hippo</p>";
    end
    items = items1 + items2 + items3 + items4;

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
puts "<p style='text-align:center'><span><i>Please confirm purchase</i></span></p>";
puts "<p style='text-align:center'>#{name}</p>";
puts "<p style='text-align:center'>#{address}</p>";
puts "<p style='text-align:center'>#{phone}</p>";
puts items;
puts "<p style='text-align:center'>$#{cost}</p>";
puts "<p style='text-align:center'>#{cType}</p>";
puts "<p style='text-align:center'>XXXX-XXXX-XXXX-#{cNum}</p>";
puts "<p style='text-align:center'>Expires: #{cExp}</p>";
puts "</div>";
puts "<form style='text-align:center' action='assign11_a.rb'>";
puts "<input type='Submit' name ='purchase' value='Confirm'/>";
puts "<input type='Submit' name='purchase' value='Cancel'/>";
puts "</form>";
puts "</body>";
puts "</html>";
