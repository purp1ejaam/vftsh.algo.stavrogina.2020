﻿#include <iostream>
#include<vector>
#include<string>

class THashTable {
private:
	std::vector<std::pair<bool, double>> table; //сначала надо заполнить вектор!
	void FirstFilling() {
		resize(128);
		
	}
	void resize(int size) {
		for (int i = 0; i < size; ++i)
			table.push_back(std::make_pair(0, 0));
		
	}
	int hash1(int key) {
		return key % table.size(); // первая хэш-функция
	}
	int hash2(int key) {
		return key % (table.size() - 1) + 1; //вторая хэш функция
	}
	int HashPush(int key) { //возвращаем позицию для вставки элемента
		for (int i = 0; i < table.size(); ++i) {
			if (!table[int((hash1(key) + i * hash2(key)) % table.size())].first)
				return int((hash1(key) + i * hash2(key)) % table.size()); //возвращаем позицию если тут пусто
		}
		resize(table.size()); //увеличиваем вдвое размер таблицы если нет свободных позиций
		HashPush(key); //снова пытаемся найти позицию для элемента
	}
	int HashFind(int key, int el) {
		for (int i = 0; i < table.size(); ++i) {
			if (table[int((hash1(key) + i * hash2(key)) % table.size())].first &&
				table[int((hash1(key) + i * hash2(key)) % table.size())].second == el)
								 //делаем такой же поиск по ключу
									 //и проверяем совбадают ли значения
			return int(hash1(key) + i * hash2(key) % table.size()); //возвращаем позицию если совпадают
		}
		return NULL;
	}
public:
	void Push(int key, int element) {
		if (table.empty())
		    FirstFilling();
		int position = HashPush(key);
		table[position].first = true;
		table[position].second = element;
	}
	bool Find(int key, int element) {
		if (table.empty())
		     return false;
		if (HashFind(key, element) == NULL)
			return false;
		else
			return true;
	}
	void Delete(int key, int element) {
		if (table.empty())
			std::cout << "there's no elements";
		else {
			int position = HashFind(key, element);
			if (position != NULL) {
				table[position].first = false;
				table[position].second = 0; // этот шаг можно пропустить
			}
		}
	}
};
int main() {
	THashTable t;
	std::cout << "how many items? " << '\n';
	int count;
	std::cin >> count;
	for (int i = 0; i < count; ++i) { //этот мейн похож на какой-то костыль , можно так не заморчаиваться или покрасивше сделать
		std::cout << "enter key & element : " << '\n';
		int key, el;
		std::cin >> key >> el;
		std::cout << "what you want to do? : " << std::endl << "Push" << std::endl << "Find" << std::endl << "Delete" << std::endl;
		std::string type;
		std::cin >> type;
		if (type == "Push")
			t.Push(key, el);
		else if (type == "Delete")
			t.Delete(key, el);
		else
			t.Find(key, el);
	}
	 return 0;
}