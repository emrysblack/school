#!/usr/bin/ruby -w
$stderr.reopen($stdout);
    require "cgi"
    cgi = CGI.new(level="html4");     # create cgi object for html4 strict
   
    if (cgi.params.length != 0);      # hash length
      message = "Thank You for your Order";
     if (cgi['purchase'] == 'Cancel')
         message = "Purchase Cancelled";
     end
    end

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
puts "<p style='text-align:center'><span><i>#{message}</i></span></p>";
puts "</body>";
puts "</html>";
