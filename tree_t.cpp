#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

class tree_t
{
private:
	struct node_t {
		node_t * left;
		node_t * right;
		int key;

		node_t() : left(nullptr), right(nullptr), key(0)
		{

		}

		~node_t()
		{
			delete right;
			delete left;
		}

		void printrec(std::ostream & stream, int set) const {
			if (this == nullptr)
			{
				throw "Binary tree is empty";
			}
			else
			{
				if (this->right != nullptr) {
					this->right->printrec(stream, set + 5);
				}

				std::cout << std::setw(set + 5) << std::setfill('-') << key;

				if (this->left != nullptr) {
					this->left->printrec(stream, set + 5);
				}
			}

		}
	};


private:
	node_t * root_;
public:
	tree_t();
	~tree_t();

	void insert(int key);
	bool find(int key) const;
	void print(std::ostream & stream) const;
};



tree_t::tree_t() : root_(nullptr)
{

}

tree_t::~tree_t()
{
	delete root_;
}

bool tree_t::find(int key, node_t * temp) const
{
	if (temp == 0 || key == temp->key)
	{
		return key;
	}

	if (key > temp->key)
	{
		return find(key, temp->right);
	}
	else
	{
		return find(key, temp->left);
	}
}

void tree_t::print(std::ostream & stream) const
{
	root_->printrec(stream, 0);
}

void tree_t::insert(int key)
{
	node_t * tree = new node_t;
	tree->key = key;
	tree->left = tree->right = 0;

	node_t * buff = root_;
	node_t * temp = root_;

	while (temp)
	{
		buff = temp;
		if (key < temp->key)
			temp = temp->left;
		else
			temp = temp->right;
	}

	if (!buff)
	{
		root_ = tree;
	}

	else
	{
		if (key < buff->key)
			buff->left = tree;
		else
			buff->right = tree;
	}
}

int main()
{
	tree_t tree;

	char bin_char;
	while (std::cin >> bin_char && bin_char != 'e') {

		int number_tree = 0;
		bool bool_ = false;

		switch (bin_char) {
		case '=':
			tree.print(std::cout);
			break;
		case '+':

			if (std::cin >> number_tree) {
				tree.insert(number_tree);
				tree.print(std::cout);
			}
			else {
				std::cout << "Error";
				exit(0);
			}
			break;
		case '?':

			if (std::cin >> number_tree) {
				tree.find(number_tree);
				if (bool_) {
					std::cout << "true" << '\n';
				}
				else {
					std::cout << "false" << '\n';
				}
			}
			else {
				std::cout << "Error";
				exit(0);
			}
			break;
		}

	}


	std::cin.get();
	return 0;
}