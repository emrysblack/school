function getMileage()
{
   var rStyle = "margin:auto; border:2px solid #a1a1a1; padding:10px 40px;" +
      "background:#dddddd; width:300px; border-radius:25px";
   document.getElementById("req").style = rStyle;
   var reqString = "startCity=" + document.getElementById("startCity").value +
      "&startState=" + document.getElementById("startState").value + "&endCity="
      + document.getElementById("endCity").value + "&endState="
      + document.getElementById("endState").value;
   loadXMLDoc(reqString);
}
function loadXMLDoc(reqString)
{
   var xmlhttp;
   if (window.XMLHttpRequest)
   {// code for IE7+, Firefox, Chrome, Opera, Safari
      xmlhttp=new XMLHttpRequest();
   }
   else
   {// code for IE6, IE5
      xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
   }
   xmlhttp.onreadystatechange=function()
   {
      if (xmlhttp.readyState==4 && xmlhttp.status==200)
      {          
         var XML=xmlhttp.responseXML.getElementsByTagName("trip")[0];
         var response = document.getElementById("startCity").value + " to " + document.getElementById("endCity").value +"<br/>";
         response = response + "Miles: " + XML.getElementsByTagName("miles")[0].childNodes[0].nodeValue + "<br/>" + "Travel Modes<hr/>";
         x = XML.getElementsByTagName("tmode");
         for (i = 0; i < x.length; i++)
         {
            response = response + x[i].childNodes[0].nodeValue + "<br/>";
         }
         document.getElementById("req").innerHTML = response;
      }
   }
   xmlhttp.open("GET","/cgi-bin/ercanbracks/mileage/mileageAjaxXML?"+
                reqString,true);
   xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
   xmlhttp.send(null);
}