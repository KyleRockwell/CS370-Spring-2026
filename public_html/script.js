function login() {
	var username=document.getElementById('username').value;
	var password=document.getElementById('password').value;
	console.log(username); //for testing
	if(username == "Username" && password == "Password") {
		window.location.assign("login.html");
	}
}
