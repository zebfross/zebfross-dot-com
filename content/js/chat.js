$(document).ready(function() {
});

var socket = null;

function send(data, newCallback) {
	try {
		if (socket != null)
			socket.send(data);
	} catch (exc) {
		console.log("send error: " + exc);
	}
}

function initializeSocket(callback) {
	socket = new WebSocket("ws://zebfross.com:8080/");
	if (socket) {
		socket.onopen = callback;

		socket.onmessage = function(msg) {
			console.log(msg.data);
			var message = JSON.parse(msg.data);
			if (message.method == "getUsers") {
				refreshUsers(message.data);
			} else if (message.method == "getMessages") {
				appendMessages(message.data);
			} else {
				console.log("unknown method: " + message.method);
			}
		};

		socket.onerror = function(error) {
			console.log("socket error: " + error);
			$("#socketError").removeClass("hidden");
		}

		socket.onclose = function() {
			console.log("socket closed");
		}
	}
}

function registerClient() {
	if (socket == null) {
		initializeSocket(registerClient);
		return;
	}
	user = new User({"nick":$("#nick").val()});
	call = {"method":"registerClient", "data":user};
	send(JSON.stringify(call));
}

function getUsers() {
	call = {"method":"getUsers"};
	send(JSON.stringify(call));
} 

function refreshUsers(users) {
	$("#users").empty();
	var noUsers = true;
	for(nick in users) {
		$("#users").append("<li>" + nick + "</li>");
		noUsers = false;
	}
	if (noUsers) {
		$("#userAlert").html("There are currently no users online");
	} else {
		$("#userAlert").html("");
	}
}

function sendMessage() {
	call = {"method":"sendMessage"};
	call.data = {"message": $("#message").val()};
	send(JSON.stringify(call));
}

function appendMessages(chats) {
	var ta = document.getElementById("messages");
	for (c in chats) {
		var chat = chats[c];
		ta.value += "\n";
		ta.value += chat.user + ": ";
		ta.value += chat.message + "\n";
	}
	$("#messages").scrollTop($("#messages").height());
}

