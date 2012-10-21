
User = function(args) {
	this.messages = [];
	this.nick = null;
	if (args) {
		if (args.nick !== undefined) {
			this.nick = args.nick;
		}
		if (args.messages !== undefined) {
			this.messages = args.messages;
		}
	}
};

Error = function(args) {
	this.prototype = args;
	this.method = "error";
};
