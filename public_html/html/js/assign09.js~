function loadXMLDoc(caller, file)
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
         if(caller == "txt")
            document.getElementById("text").value=xmlhttp.responseText;
         else
            document.getElementById("wPage").innerHTML=xmlhttp.responseText;
      }
   }
   xmlhttp.open("GET",file,true);
   xmlhttp.send(null);
}

function loadTxt()
{
   loadXMLDoc("txt", "../../../~ercanbracks/" + document.getElementById("select").options[document.getElementById("select").selectedIndex].id)
}
function loadHTML()
{
   var link = document.getElementById("url").value;
   loadXMLDoc("html", link)
}