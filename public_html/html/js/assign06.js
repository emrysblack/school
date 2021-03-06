function calc()
{
      var temp1 = document.getElementById("i1").checked; 
      var temp2 = document.getElementById("i2").checked;
      var temp3 = document.getElementById("i3").checked;
      var temp4 = document.getElementById("i4").checked;
      var total = 0;
      if(temp1)
         total = total + 2000;
      if(temp2)
         total = total + 1000;
      if(temp3)
         total = total + 1500;
      if(temp4)
         total = total + 1200;
      document.getElementById("ttl").innerHTML =  "Total: $" + total.toFixed(2);
      if (total > 0)
      {
         document.getElementById("ttl").style.color="green";
         return true;
      }
      else
      {
         document.getElementById("ttl").style.color="red";
         return false;
      }
}

function rst()
{
   document.getElementById("fn").style.border="thin solid black";
   document.getElementById("ln").style.border="thin solid black";
   document.getElementById("add1").style.border="thin solid black";
   document.getElementById("add2").style.border="thin solid black";
   document.getElementById("zip").style.border="thin solid black";
   document.getElementById("p1").style.border="thin solid black";
   document.getElementById("p2").style.border="thin solid black";
   document.getElementById("p3").style.border="thin solid black";
   document.getElementById("ccn1").style.border="thin solid black";
   document.getElementById("ccn2").style.border="thin solid black";
   document.getElementById("ccn3").style.border="thin solid black";
   document.getElementById("ccn4").style.border="thin solid black";
   document.getElementById("ttl").style.color="black";
   document.getElementById("ttl").innerHTML =  "Total: $ 0.00";
   document.getElementById("fn").focus();
}

function assertForm()
{
   // first and last name
   var temp1 = document.getElementById("fn").value;
   var valid = true;
   var green = true;
   var patt = /^[A-Za-z]+$/;
   green = patt.test(temp1);
   if(!green)
   {
      valid = false;
      if (temp1 != '')
         document.getElementById("fn").style.border="thin solid red";   
   }  
   else if (green)
   {
      document.getElementById("fn").style.border="thin solid green";
      document.getElementById("fnHint").style.visibility="hidden";
   }
   temp1 = document.getElementById("ln").value;
   green = patt.test(temp1);
   if(!green)
   {
      valid = false;
      if (temp1 != '')
         document.getElementById("ln").style.border="thin solid red";   
   } 
   else if (green)
   {
      document.getElementById("ln").style.border="thin solid green";
      document.getElementById("lnHint").style.visibility="hidden";
   }
   // address
   temp1 = document.getElementById("add1").value;
   // patt = /(^\d+$)|(^\d+ [nsew]$)/i;
   patt = /^\d+/i;
   green = patt.test(temp1);
   if(!green)
   {
      valid = false;
      if (temp1 != '')
         document.getElementById("add1").style.border="thin solid red";   
   } 
   else if (green)
   {
      document.getElementById("add1").style.border="thin solid green";
      document.getElementById("add1Hint").style.visibility="hidden";
   }  
   temp1 = document.getElementById("add2").value;
   // patt = /(^\w+)|(^\d+ [nsew]$)/i;
   // green = patt.test(temp1);
   if(!green)
   {
      valid = false;
      if (temp1 != '')
         document.getElementById("add2").style.border="thin solid red";   
   } 
   else if (green)
   {
      document.getElementById("add2").style.border="thin solid green";
      document.getElementById("add2Hint").style.visibility="hidden";      
   }
   temp1 = document.getElementById("zip").value;
   patt = /^\d{5}$/;
   green = patt.test(temp1);
   if(!green)
   {
      valid = false;
      if (temp1 != '')
         document.getElementById("zip").style.border="thin solid red";   
   }  
   else if (green)
   {
      document.getElementById("zip").style.border="thin solid green";
      document.getElementById("zipHint").style.visibility="hidden";
   }
      // phone number
   temp1 = document.getElementById("p1").value;
   patt = /^\d{3}$/;
   green = patt.test(temp1);
   var phone = true;
   if(!green)
   {
      valid = false;
      if (temp1 != '')
      {
         document.getElementById("p1").style.border="thin solid red";
         phone = false;
      }
   }  
   else if (green)
   {
      document.getElementById("p1").style.border="thin solid green";
      if (phone)
         document.getElementById("p1Hint").style.visibility="hidden";
   }
   temp1 = document.getElementById("p2").value;
   patt = /^\d{3}$/;
   green = patt.test(temp1);
   if(!green)
   {
      valid = false;
      if (temp1 != '')
      {
         document.getElementById("p2").style.border="thin solid red";
         phone = false;
      }
   }  
   else if (green)
   {
      document.getElementById("p2").style.border="thin solid green";
      if (phone)
         document.getElementById("p1Hint").style.visibility="hidden";
   }
   temp1 = document.getElementById("p3").value;
   patt = /^\d{4}$/;
   green = patt.test(temp1);
   if(!green)
   {
      valid = false;
      if (temp1 != '')
      {
         document.getElementById("p3").style.border="thin solid red";
         phone = false;
      }
   } 
   else if (green)
   {
      document.getElementById("p3").style.border="thin solid green";
      if (phone)
         document.getElementById("p1Hint").style.visibility="hidden";
   }
   // shop
   temp1 = calc();
   if (!temp1)
      valid = false;
   // ccn
   temp1 = document.getElementById("ccn1").value;
   patt = /^\d{4}$/;
   green = patt.test(temp1);
   ccn = true;
   if(!green)
   {
      valid = false;
      if (temp1 != '')
      {
         document.getElementById("ccn1").style.border="thin solid red";
         ccn = false;
      }
   }  
   else if (green)
   {
      document.getElementById("ccn1").style.border="thin solid green";
      if (ccn)
         document.getElementById("ccn1Hint").style.visibility="hidden";
   }
   temp1 = document.getElementById("ccn2").value;
   patt = /^\d{4}$/;
   green = patt.test(temp1);
   if(!green)
   {
      valid = false;
      if (temp1 != '')
      {
         document.getElementById("ccn2").style.border="thin solid red";
         ccn = false;
      }
   }  
   else if (green)
   {
      document.getElementById("ccn2").style.border="thin solid green";
      if (ccn)
         document.getElementById("ccn1Hint").style.visibility="hidden";
   }
   temp1 = document.getElementById("ccn3").value;
   patt = /^\d{4}$/;
   green = patt.test(temp1);
   if(!green)
   {
      valid = false;
      if (temp1 != '')
      {
         document.getElementById("ccn3").style.border="thin solid red";
         ccn = false;
      }
   } 
   else if (green)
   {
      document.getElementById("ccn3").style.border="thin solid green";
      if (ccn)
         document.getElementById("ccn1Hint").style.visibility="hidden";
   }
   temp1 = document.getElementById("ccn4").value;
   patt = /^\d{4}$/;
   green = patt.test(temp1);
   if(!green)
   {
      valid = false;
      if (temp1 != '')
      {
         document.getElementById("ccn4").style.border="thin solid red";
         ccn = false;
      }
   } 
   else if (green)
   {
      document.getElementById("ccn4").style.border="thin solid green";
      if (ccn)
         document.getElementById("ccn1Hint").style.visibility="hidden";   
   }
   if(valid)
      document.getElementById("sub").disabled = false;
   else if (!valid)
      document.getElementById("sub").disabled = true;
}

function hint(x)
{
   var temp1 = document.getElementById(x +"Hint");
   temp1.style.visibility="visible";
}

function autoJump(event,x,y,z)
{
   
   if ((y.length==x.maxLength)&& event.keyCode != 9)
   {
      if (z == 'blur')
         x.blur();
      else
         document.getElementById(z).select();
   }
}