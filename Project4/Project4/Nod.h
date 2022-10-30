#include <iostream>
#include <fstream>
using namespace std;
using uchar = unsigned char;


class Node {
public:
	using pointer = shared_ptr<Node>;


	pointer left{ nullptr };
	pointer right{ nullptr };
	pointer parent{ nullptr };

	Node() = default;
	Node(uchar uch, int f) :ch(uch), freq(f) {};
	Node(const  string & n, int f) :name(n), freq(f) {};

	bool operator<(const Node& oth) const {
		return freq < oth.freq;
	}
	friend ostream& operator<<(ostream& os, const Node& node);
	
	int get_freq()const {
		return freq;
	}

	void set_freq(int f) {
		freq = f;
	}
	string code() const {
		return code_string;
	}

	void code(const string& c) {
		code_string = c;
	}
	string get_name()const  {
		if (ch == 0) {
			return name;
		}
		else {
			if (ch == 10) {
				return "\\n";
			}
			return string(1, static_cast<char>(ch));
		}
	}

	uchar  get_byte() {
		return ch;
	}
private:
	string code_string{ "" };
	uchar ch{ 0 };
	int freq{ 0 };
	string name{ "" };
};


ostream& operator <<(ostream& os, const Node& node) {
	return os << "[" << node.get_name() << "] = " << node.freq;
}

class LowestPriority {
public:
	bool operator()(const Node::pointer& left, const Node::pointer& right) const {
		return left->get_freq() > right->get_freq();
	}
};