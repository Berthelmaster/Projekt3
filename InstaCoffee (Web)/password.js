var password = "12345"
var pass1;


function clickOnLogin()
{ 
 
 pass1= document.getElementById("pwd").value;
  
 if (password==pass1) {
 	console.log("Korrekt kode")
 	window.location = "insta.html";
  }
  console.log("clickOnLogin kaldt")
}