function assertForm()
{
   var temp1 = document.getElementById("apr").value;
   var temp2 = document.getElementById("term").value;
   var temp3 = document.getElementById("amt").value;

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
         document.getElementById("amt").select();
      error = error + "ERROR: Enter a valid number in Loan Amount\n";      
   }

   if (error != '')
   {
      alert(error);
      return false;
   }
   return true;
}