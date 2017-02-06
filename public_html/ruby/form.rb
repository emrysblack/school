#!/usr/bin/ruby -w

#
#  This function reads the form "query string"
#  It returns a hash consisting of the form elements "name/value" pairs.
#  This function handles both an http "get" or "post" method.

# ********************************************************************************
# Get form data values
# ********************************************************************************
    require "cgi"
    cgi = CGI.new(level="html4")     # create cgi object for html4 strict
   
    if (cgi.params.length != 0)      # hash length
       field1 = cgi['apr'].to_f      # convert to float
       field2 = cgi['term'].to_i     # convert to integer
       field3 = cgi['amount'].to_f   # convert to float
       hash = cgi.params             # returns a hash of key/value pairs
       keys = cgi.keys               # returns an array of the key names           
    end


print "Content-type: text/html\n\n"
print "<html>"
print "<title>Read Form!</title>\n"
print "<body>"
print "<h3>"
print "\nThis values of the form elements are:\n <br /> "
puts "Apr: #{field1}<br />"
print "Term: #{field2}<br />"
print "Amount: #{field3}<br />"
print "</h3>"
puts "Apr =  " 
print "#{hash['apr']}<br /><br/>" 
puts "<h3>Prints the entire hash! <h3>"
print "#{hash}<br />" 
puts "<br/>Prints the keys array! <br />"
print "#{keys}<br />" 
print "</h3>"

print "<br/>Prints hash using for-in<br/>"
for value in hash
  print value
  print "<br/>"

end

print "<br/>Prints the hash values by looping through the array of the keys using for-in<br/>"
for value in keys
  print hash[value]
  print "<br/>"
end

print "</body>"
print "</html>"

