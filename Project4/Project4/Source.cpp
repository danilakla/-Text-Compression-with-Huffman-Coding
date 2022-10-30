#include<iostream>
#include<fstream>
#include<vector>
#include "Nod.h"
#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include <string_view>

using namespace std;



ifstream::pos_type get_size(const string& fn) {
	ifstream ifs(fn, ifstream::ate);
	return ifs.tellg();
}

void read_file(const string& filename, vector<int>& freq) {
	int filesize = get_size(filename);
	if (filesize < 0) {
		cout << "error";
	}
	ifstream ifs(filename, ifstream::binary);
	if (!ifs) {
		cout << "error 2";
	}

	int i = 0;
	while (true)
	{
		char ch;
		ifs.read(&ch, 1);
		if (ifs.eof()) {
			break;
		}
		freq[static_cast<unsigned char>(ch)]++;
		if (i % 20 == 0) {
			int value = (i + filesize % 20) * 100.0 / filesize;
			cout << "\r" << value << "%" << flush;
		}
		i++;
	}
	cout << endl;

	for (int i = 0; i < freq.size(); ++i)
	{
		if (freq[i] != 0)
			cout << "[" << i << "] = " << freq[i] << ", \t" << " \n"[i == freq.size() - 1];
	}
}

void make_code(Node::pointer& node, string str, vector<string>& codes) {
	if (node->left != nullptr) {
		make_code(node->left, str + "0", codes);
	}
	if (node->right != nullptr) {
		make_code(node->right, str + "1", codes);
	}

	if (node->left == nullptr && node->right == nullptr) {
		node->code(str);
		codes[node->get_byte()] = str;
		cout << "node: " << *node << " code: " << node->code() << "\n";
	}
}

string messageDecode(const string filename, const vector<string>& codes) {
	string msg{ "" };
	ifstream ifs(filename, ifstream::binary);
	if (!ifs) {
		cout << "err";
		return msg;
	}
	while (true) {
		char ch;

		ifs.read(&ch, 1);

		if (ifs.eof())
		{
			break;
		}
		msg += codes[static_cast<uchar>(ch)] + "|";
		
	}
	return msg;
}
int main() {
	string filename = "D:\\text.txt";
	vector<int> freq(0x100, 0);
	read_file(filename, freq);

	using queue_t= priority_queue<Node::pointer, vector<Node::pointer>, LowestPriority> ;
	queue_t queue;
	uchar byte = 0;
	for_each(freq.begin(), freq.end(), [&queue, &byte](const auto& value) {
		if (value != 0) {
			Node::pointer node = make_shared<Node>(byte, value);
			queue.push(node);
		}
		++byte;
	});



	while (queue.size()>1) {
		Node::pointer x = queue.top();
		queue.pop();
	
		Node::pointer y = queue.top();
		queue.pop();

		string name = x->get_name() + y->get_name();

		Node::pointer z = make_shared<Node>(name, x->get_freq()+y->get_freq());
			z->left = x;
			z->right = y;
			x->parent = z;
			y->parent = z;

			queue.push(z);

	
	}
	vector<string> codes(0x100, "");
	Node::pointer root = queue.top();
	make_code(root,"", codes);
	cout<<messageDecode(filename, codes);
	 
	//while (!queue.empty()) {
	//	cout << *(queue.top())<< " ";
	//	queue.pop();
	//}
	
}