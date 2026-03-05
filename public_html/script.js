function login() {
	var username=document.getElementById('username').value;
	var password=document.getElementById('password').value;
	if(username == "Username" && password == "Password") {
		window.location.assign("login.html");
	}
}
