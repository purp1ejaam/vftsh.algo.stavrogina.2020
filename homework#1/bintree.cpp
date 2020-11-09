
//it's set 
#include <iostream>
#include<list>
#include<string>
struct TBinTreeEl {
	int data;
	TBinTreeEl* left;//указатель на левого потомка
	TBinTreeEl* right;//указатель на правого потомка
	TBinTreeEl* parent;//указатель на родителя
};
class TBinTree {
	TBinTreeEl* root;//корень дерева
	unsigned int len = 0;//размер
	TBinTreeEl* shiftDown(int x, TBinTreeEl* parent) {
		if (x >= parent->data) {
			if (parent->right == nullptr) return parent;
			return shiftDown(x, parent->right);
		}
		else {
			if (parent->left == nullptr) return parent;
			return shiftDown(x, parent->left);
		}
	}
	void shiftForShow(TBinTreeEl* element) {
		if (element != nullptr) {
			std::cout << "element: " << element->data << '\n';
			if (element->right != nullptr) {
				std::cout << "element right: " << element->data << " " << element->right->data << '\n';
				shiftForShow(element->right);
			}
			if (element->left != nullptr) {
				std::cout << "element left : " << element->data << " " << element->left->data << '\n';
				shiftForShow(element->left);
			}
		}
	}
	TBinTreeEl* search(int x, TBinTreeEl* element) {
		if (x == element->data) return element;
		else if (x > element->data) {
			if (element->right == nullptr) return element;
			return search(x, element->right);
		}
		else if (x < element->data) {
			if (element->left == nullptr)return element;
			return search(x, element->left);
		}
	}
public:
	void Push(int x) {//okay
		if (len == 0) {
			TBinTreeEl* newEl = new TBinTreeEl;
			newEl->data = x;
			newEl->parent = nullptr;
			newEl->right = nullptr;
			newEl->left = nullptr;
			root = newEl;
		}
		else {
			if (!Find(x)) {
				TBinTreeEl* newEl = new TBinTreeEl;
				TBinTreeEl* ancestor = shiftDown(x, root);
				newEl->parent = ancestor;
				newEl->data = x;
				newEl->left = nullptr;
				newEl->right = nullptr;
				if (ancestor->data >= x) {
					ancestor->left = newEl;
				}
				if (ancestor->data < x) {
					ancestor->right = newEl;
				}
			}
		}
		++len;
	}
	bool Find(int x){//okay
		if (search(x, root)->data != x) return false;
		else return true;
	}
	void Delete(int x) {//okay
		auto element = search(x, root);
		if (element->right == nullptr && element->left == nullptr) {
			if (len > 1) {
				if (element->parent->data > element->data) delete element->parent->left;
				delete element->parent->right;
			}
			else delete element;
		}
		else if (element->right != nullptr && element->left != nullptr) {
			auto minimum = search(x + 1, element);
			element->data = minimum->data;
			if (minimum->parent->data > minimum->data) minimum->parent->left = nullptr;
			else minimum->parent->right = nullptr;
			delete minimum;
		}
		else {
			TBinTreeEl* key;
			if (element->right != nullptr) {
				key = element->right;
			}
			else {
				key = element->left;
			}
			if (element->parent->data > element->data) {
				element->parent->left = key;
				key->parent = element->parent;
			}
			else {
				element->parent->right = key;
				key->parent = element->parent;
			}
			delete element;
		}
		--len;
	}
	void Show() {
		shiftForShow(root);
	}
	int Size() {//okay
		return len;
	}
};
int main() {
	TBinTree h;
	std::cout << "Hello! It is set. ";
	std::string type;
	while (type != "Nothing") {
		std::cout << "Choose what you want to do: " << '\n' << "Push" << '\n' << "Show" << '\n' << "Size" << '\n' << "Find" << '\n' << "Delete" << '\n' << "Nothing" << '\n';
		std::cin >> type;
		if (type == "Push") {
			std::cout << "how many elements do you want to push? " << '\n';
			int count;
			std::cin >> count;
			for (int i = 0; i < count; ++i) {
				int el;
				std::cin >> el;
				h.Push(el);
			}
		}
		else if (type == "Delete") {
			if (h.Size() == 0)
				std::cout << "Oops! There is nothing here!" << '\n';
			else {
				std::cout << "Which elemenet? " << '\n';
				int el;
				std::cin >> el;
				h.Delete(el);
			}
		}
		else if (type == "Find") {
			if (h.Size() == 0)
				std::cout << "Oops! There is nothing here!" << '\n';
			else {
				std::cout << "Which elemenet? " << '\n';
				int el;
				std::cin >> el;
				h.Find(el);
			}
		}
		else if (type == "Size")
			std::cout << "size of set is " << h.Size() << '\n';
		else if (type == "Show")
			h.Show();
		else if (type == "Nothing")
			break;
	}
	return 0;
}
