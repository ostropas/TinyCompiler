#pragma once
#include <string>

namespace std {
	/// <summary>
	/// All possible parser kinds
	/// </summary>
	enum class ParserKind {
		VAR,
		CONST,
		ADD,
		SUB,
		LT,
		SET,
		IF1,
		IF2,
		WHILE,
		DO,
		EMPTY,
		SEQ,
		EXPR,
		PROG
	};

	/// <summary>
	/// Parser struct in tree, Node is realisation of tree
	/// </summary>
	struct Node {
	public:
		ParserKind kind;
		int value;
		// Next tree leafs
		shared_ptr<Node> op1;
		shared_ptr<Node> op2;
		shared_ptr<Node> op3;

		Node(){};
		Node(ParserKind kind, int value = NULL, shared_ptr<Node> op1 = nullptr, shared_ptr<Node> op2 = nullptr, shared_ptr<Node> op3 = nullptr)
		{

			this->kind = kind;
			this->value = value;
			this->op1 = move(op1);
			this->op2 = move(op2);
			this->op3 = move(op3);
		}
	};
}
