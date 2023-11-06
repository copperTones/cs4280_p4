void nont_start() {
	nont_vars();
	require(mainToken);
	nont_stats();
	require(endToken);
}

void nont_vars() {
	if (next.type == letToken) {
		require(letToken);
		require(idToken);
		require(equalsToken);
		require(intToken);
		nont_varList();
	}
}

void nont_varList() {
	if (next.type == idToken) {
		require(idToken);
		require(equalsToken);
		require(intToken);
		nont_varList();
	}
}

void nont_exp() {
	nont_exp2();
	if (next.type == opToken && next.instance == "+") {
		require(opToken);
		nont_exp();
	} else if (next.type == opToken && next.instance == "-") {
		require(opToken);
		nont_exp();
	}
}

void nont_exp2() {
	nont_exp3();
	if (next.type == opToken && next.instance == "*") {
		require(opToken);
		nont_exp2();
	}
}

void nont_exp3() {
	if (next.type == opToken && next.instance == "-") {
		require(opToken);
		nont_exp3();
	} else {
		nont_exp4();
		if (next.type == opToken && next.instance == "/") {
			require(opToken);
			nont_exp3();
		}
	}
}

void nont_exp4() {
	if (next.type == opToken && next.instance == "[") {
		require(opToken);
		nont_exp();
		require(opToken, "]");
	} else if (next.type == intToken) {
		require(intToken);
	} else {
		require(idToken);
	}
}

void nont_stats() {
	nont_stat();
	nont_stat2();
}

void nont_stats2() {
	if (statPred(next.type)) {
		nont_stat();
		nont_stats2();
	}
}

void nont_stat() {
	switch (next.type) {
		case startToken:
			nont_block();
			break;
		case scanToken:
			nont_in();
			break;
		case printToken:
			nont_out();
			break;
		case condToken:
			nont_if();
			break;
		case loopToken:
			nont_loop();
			break;
		case idToken:
			nont_assign();
			break;
		default:
			errMsg();
			break;
	}
}

void nont_block() {
	require(startToken);
	nont_vars();
	nont_stats();
	require(stopToken);
}

void nont_in() {
	require(scanToken);
	require(idToken);
	require(opToken, ".");
}

void nont_out() {
	require(scanToken);
	nont_exp();
	require(opToken, ".");
}

void nont_if() {
	require(condToken);
	require(opToken, "(");
	nont_exp();
	nont_relOp();
	nont_exp();
	require(opToken, ")");
	nont_stat();
}

void nont_loop() {
	require(loopToken);
	require(opToken, "(");
	nont_exp();
	nont_relOp();
	nont_exp();
	require(opToken, ")");
	nont_stat();
}

void nont_assign() {
	require(idToken);
	require(opToken, "~");
	nont_exp();
	require(opToken, ".");
}

void nont_relOp() {
	switch (next.instance) {
		case "<=":
		case ">=":
		case "<":
		case ">":
		case "=":
		case "~":
			require(opToken);
			break;
		default:
			errMsg();
			break;
	}
}
