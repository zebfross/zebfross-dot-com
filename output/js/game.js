$(document).ready(function() {
	initializeSocket();
});

tabSwitch = function(new_tab, new_content) {
	$(".tab_content").css("display", "none");
	$("#signedin_tab").removeClass("active");
	$("#inlobby_tab").removeClass("active");
	$(new_tab).addClass("active");
	$(new_content).css("display", "block");
};

var users = {};
var socket = null;

sendMessage = function() {
	var message = $("#message").val();
	sendRequest(new Response("sendMessage", message));
};

addNewUser = function(user) {
	users[user.id] = user;
	console.log("registering user with id: " + user.id);
	$("<li id='" + user.id + "' />")
		.text(user.nick).appendTo("#signedin_list");
};

addUserToLobby = function(userId) {
	var user = users[userId];
	if (user == null) console.log("user undefined for id: " + userId);
	$("<li id='lobby_" + user.id + "' />")
		.text(user.nick).appendTo("#inlobby_list");
};

updateAllGames = function(games) {
	for (gameId in games) {
		var game = games[gameId];
		addOpenGame(game);
	}
};

updateActiveGames = function(data) {

};

receiveMessage = function(chat) {
	var ta = document.getElementById("messages");
	ta.value += chat.user.nick + ": " + chat.message + "\n";
};

removeUserFromLobby = function(userId) {
	console.log("removing user from lobby: " + userId);
	$("#lobby_" + userId).remove();
};

removeUser = function(userId) {
	removeUserFromLobby(userId);
	$("#signedin_" + userId).remove();
	delete users[userId];
};

createGame = function() {
	var game = new Game();
	game.targetNumUsers = 2;
	sendRequest(new Response("createGame", game));
	$("#game1").addClass("hidden");
	$("#game2").removeClass("hidden");
};

addOpenGame = function(game) {
	$("<span class='button' onclick='joinGame(\"" + game.id + "\")' />")
		.text("Join")
		.appendTo(
	$("<li id='game_" + game.id + "' class='" + game.state + "' />")
		.text("game by " + users[game.owner].nick)
		.appendTo("#game_list"));
};

joinGame = function(gameId) {
	sendRequest(new Response("joinGame", gameId));
	$("#game1").addClass("hidden");
	$("#game2").removeClass("hidden");
	getUsersInGame(gameId);
};

updateAllUsers = function(users) {
	$("#signedin_list").empty();
	for (userId in users) {
		addNewUser(users[userId]);
	}
};

updateUsersInLobby = function(users) {
	$("#inlobby_list").empty();
	for (userId in users) {
		addUserToLobby(users[userId]);
	}
};

getUsersInGame = function(gameId) {
	sendRequest(new Response("getUsersInGame", gameId));
};

updateUsersInGame = function(userIds) {
	$("#usersInGameList").empty();
	for (i in userIds) {
		addUserToGame(userIds[i]);
	}
};

addUserToGame = function(userId) {
	$("<li />", 
		{text: users[userId].nick, id:"userInGame_" + userId})
		.appendTo("#usersInGameList");
};

removeUserFromGame = function(userId) {
	$("#userInGame_" + userId).remove(); 
};

switchGameToActive = function(gameId) {
	$("#game_" + gameId).removeClass("open");
	$("#game_" + gameId).addClass("active");
};

unjoinGame = function() {
	sendRequest(new Response("unjoinGame", {}));
	$("#game1").removeClass("hidden");
	$("#game2").addClass("hidden");
	getUsersInLobby();
};

receiveError = function(data) {
	console.log("ERROR: " + data);
};

getAllUsers = function() {
	sendRequest(new Response("getAllUsers", {}));
};

getUsersInLobby = function() {
	sendRequest(new Response("getUsersInLobby", {}));
};

getAllGames = function() {
	sendRequest(new Response("getAllGames", {}));
};

prepareToStart = function(waitTime) {
	var timerInterval = setInterval(function() {
		$("#timer").text("game starts in " + waitTime + " seconds");
		waitTime = waitTime - 1;	
	}, 1000);
	setTimeout(function() {
		$("#timer").text("game starts in moments...");
		clearInterval(timerInterval);
	}, (waitTime-1) * 1000);
};

startGame = function(gameOpts) {
	$("#timer").text("Start!");
};

removeGame = function(gameId) {
	$("#game_" + gameId).remove();
};

initializeGame = function() {
	$("#messages").val("");
	getAllUsers();
	getUsersInLobby();
	getAllGames();
};

initializeSocket = function(callback) {
	try {
		socket = new WebSocket("ws://zebfross.com:9090/");
	} catch (exc) {
		console.log("error creating socket: " + exc);
	}
	if (socket == null)
		return;
	
	socket.onopen = callback;

	socket.onmessage = function(msg) {
		var call = JSON.parse(msg.data);
		console.log("received message: " + call.method);
		if (call.method == "addUserToLobby") {
			addUserToLobby(call.data);
		} else if (call.method == "getAllGames") {
			updateAllGames(call.data);
		} else if (call.method == "getActiveGames") {
			updateActiveGames(call.data);
		} else if (call.method == "getOpenGames") {
			updateOpenGames(call.data);
		} else if (call.method == "getMessage") {
			receiveMessage(call.data);
		} else if (call.method == "removeUser") {
			removeUser(call.data);
		} else if (call.method == "removeUserFromLobby") {
			removeUserFromLobby(call.data);
		} else if (call.method == "addOpenGame") {
			addOpenGame(call.data);
		} else if (call.method == "getAllUsers") {
			updateAllUsers(call.data);
		} else if (call.method == "getUsersInLobby") {
			updateUsersInLobby(call.data);
		} else if (call.method == "getUsersInGame") {
			updateUsersInGame(call.data);
		} else if (call.method == "addUserToGame") {
			addUserToGame(call.data);
		} else if (call.method == "removeUserFromGame") {
			removeUserFromGame(call.data);
		} else if (call.method == "switchGameToActive") {
			switchGameToActive(call.data);
		} else if (call.method == "addNewUser") {
			addNewUser(call.data);
		} else if (call.method == "prepareToStart") {
			prepareToStart(call.data);
		} else if (call.method == "startGame") {
			startGame(call.data);
		} else if (call.method == "removeGame") {
			removeGame(call.data);
		} else if (call.method == "error") {
			receiveError(call.data);
		} else {
			console.log("unknown message error: " + call.method);
		}
	};

	socket.onclose = function() {
		console.log("socket closed");
		socket = null;
	};

	socket.onerror = function() {
		console.log("socket error");
	};
};

sendRequest = function(data) {
	try {
		socket.send(JSON.stringify(data));
	} catch (exc) {
		console.log("send error: " + exc);
	}
};

registerUser = function() {
	if (socket == null) {
		initializeSocket(registerUser);
		return;
	}
	user = new User();
	user.nick = $("#nick").val();
	sendRequest(new Response("registerUser", user));
	initializeGame();
};

