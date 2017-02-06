function calc()
{
   if (assertForm())
   {
      var compute = computePmt();
      document.getElementById("pmt").innerHTML =  "$" + compute.toFixed(2);
   }
}

function rst()
{
   document.getElementById("pmt").innerHTML = "$0.00";
   setFocus();
}

function computePmt()
{
   var p = document.getElementById("loan").value;
   var i = document.getElementById("apr").value/100/12;
   var n = document.getElementById("term").value * 12;
   var n2 = Math.pow((1 + i),n);
   return p * ((i * n2)/(n2 - 1));
}

function assertForm()
{
   var temp1 = document.getElementById("apr").value;
   var temp2 = document.getElementById("term").value;
   var temp3 = document.getElementById("loan").value;

   var error = '';

   if (temp1 == '' || isNaN(temp1))
   {
      error = error + "ERROR: Enter a valid number in APR\n";
      document.getElementById("apr").select();
   }
   if (temp2 == '' || isNaN(temp2))
   {
      if (error == '')
         document.getElementById("term").select();     
      error = error + "ERROR: Enter a valid number in Term\n";
   }
   if (temp3 == '' || isNaN(temp3))
   {
      if (error == '')
         document.getElementById("loan").select();
      error = error + "ERROR: Enter a valid number in Loan Amount\n";      
   }

   if (error != '')
   {
      alert(error);
      return false;
   }
   return true;
}

function setFocus()
{
document.getElementById("apr").focus();
}