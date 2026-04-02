// 5 minutes = 300 seconds
let timeLeft = 300;
let timerInterval;

// Reset inactivity timer
function resetTimer() {
    timeLeft = 300;

    // Tell server user is still active
    fetch("cgi-bin/refreshSession.cgi", {
        method: "POST",
        credentials: "include"
    });
}

// ountdown logic
function startTimer() {
    timerInterval = setInterval(() => {
        timeLeft--;

        if (timeLeft <= 0) {
            clearInterval(timerInterval);
            alert("Session expired due to inactivity.");
            window.location.href = "login.html";
        }
    }, 1000);
}

// Validate session on page load
function validateSession() {
    fetch("cgi-bin/validateSession.cgi", {
        method: "GET",
        credentials: "include"
    })
    .then(response => response.text())
    .then(data => {
        if (data.trim() !== "VALID") {
            alert("Session expired. Please log in again.");
            window.location.href = "login.html";
        }
    });
}

// Detect user activity
function setupActivityListeners() {
    document.addEventListener("mousemove", resetTimer);
    document.addEventListener("keydown", resetTimer);
    document.addEventListener("click", resetTimer);
    document.addEventListener("scroll", resetTimer);
}

// Logout function
function logout() {
    document.cookie = "session_id=; Max-Age=0; path=/";
    window.location.href = "login.html";
}

// Initialize everything
window.onload = function () {
    validateSession();
    startTimer();
    setupActivityListeners();
};
