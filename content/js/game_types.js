Game = function() {
	this.users = [];
	this.id = null;
	this.owner = null;
	this.messages = [];
	this.targetNumUsers = 0;
	this.state = "open";
};

User = function() {
	this.nick = null;
	this.currentGame = null;
	this.id = null;
};

Chat = function() {
	this.message = null;
	this.user = null;
	this.timestamp = new Date();	
};

Response = function(method, data) {
	this.method = method;
	this.data = data;
};

ClientInterface = function() {};
ClientInterface.prototype.initialize = function(gameId) {
	this.gameId = gameId;
};
ClientInterface.prototype.start = function() {
	console.log("starting");
};

ClientA = function() {};
ClientA.prototype = new ClientInterface();

ClientB = function() {};
ClientB.prototype = new ClientInterface();

