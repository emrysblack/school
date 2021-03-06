function duet(show)
{
   if (show)
      document.getElementById("duet").style="display:inline";
   else
      document.getElementById("duet").style="display:none";
}

function register()
{
   // build request string
   var pType;
   var type = document.getElementsByName("pType");
   for (var i=0;i<type.length;i++)
   {
      if(type[i].checked)
         pType = type[i].value;       
   }
   var skill;
   type = document.getElementsByName("skill");
   for (var i=0;i<type.length;i++)
   {
      if(type[i].selected)
         skill = type[i].value;       
   }  
   var skill1;
   type = document.getElementsByName("skill1");
   for (var i=0;i<type.length;i++)
   {
      if(type[i].selected)
         skill1 = type[i].value;       
   }
   var inst;
   type = document.getElementsByName("inst");
   for (var i=0;i<type.length;i++)
   {
      if(type[i].selected)
         inst = type[i].value;       
   }
   var inst1;
   type = document.getElementsByName("inst1");
   for (var i=0;i<type.length;i++)
   {
      if(type[i].selected)
         inst1 = type[i].value;
   }
   var time;
   type = document.getElementsByName("time");
   for (var i=0;i<type.length;i++)
   {
      if(type[i].selected)
         time = type[i].value;
   }
   var am = time.substr(4);
   if (am == "a")
      am = "A.M.";
   else
      am = "P.M.";
   time = time.substr(0,2) + ":" + time.substr(2,2);
   if (time.substr(0,1) == "0")
      time = time.substr(1);
   var reqString = "pType=" +  pType +
      "&fName=" + document.getElementById("fName").value +
      "&lName=" + document.getElementById("lName").value +
      "&sId=" + document.getElementById("sId").value +
      "&skill=" + skill +
      "&inst=" + inst +
      "&fName1=" + document.getElementById("fName1").value +
      "&lName1=" + document.getElementById("lName1").value +
      "&sId1=" + document.getElementById("sId1").value +
      "&skill1=" + skill1 +
      "&inst1=" + inst1 +
      "&location=" + document.getElementById("location").value +
      "&room=" + document.getElementById("room").value +
      "&time=" + time +
      "&am=" + am;
   
   // call ruby code
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
         ;//alert(xmlhttp.responseText);
      }
   }
   xmlhttp.open("GET","/cgi-bin/fie05004/assign13.rb?"
                + reqString,false);
   xmlhttp.send(null);
   loadStudents();
}

function loadStudents()
{
   // keep table in sync with file
   var file = "assign13/assign13.html";
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
         document.getElementById("registered").innerHTML=xmlhttp.responseText;
      }
   }
   xmlhttp.open("GET",file,true);
   xmlhttp.send(null);
}