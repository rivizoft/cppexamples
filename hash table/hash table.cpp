#include <iostream>
#include <string>

class HashTable {
public:
	HashTable() {
		_size = 13;
		_primeNumber = 524287;
		*items = new Item[_size];

		for (int i = 0; i < _size; i++) {
			items[i] = new Item;
			items[i]->key = "";
			items[i]->value = "";
			items[i]->next = nullptr;
		}
	}

	~HashTable() {
		for (int i = 0; i < _size; i++) {
			delete items[i];
		}
		delete[] items;
	}

	void add(const std::string key, const std::string value) {
		int cell = getHashCode(key);

		if (items[cell]->key == "") {
			items[cell]->key = key;
			items[cell]->value = value;
		}
		else {
			Item* ptr = items[cell];
			Item* newItem = new Item;
			newItem->key = key;
			newItem->value = value;
			newItem->next = nullptr;

			while (ptr->next != nullptr)
				ptr = ptr->next;

			ptr->next = newItem;
		}
	}

	std::string get(const std::string key) {
		int cell = getHashCode(key);
		std::string result;

		Item* ptr = items[cell];
		while (ptr != nullptr) {
			if (ptr->key == key) {
				result = ptr->value;	
			}
			ptr = ptr->next;
		}

		return result;
	}

private:
	struct Item
	{
		std::string key;
		std::string value;
		Item* next;
	};

	int getHashCode(const std::string& key) {
		unsigned __int64 hash = 0;

		for (int i = 0; i < key.length(); i++) {
			hash += _primeNumber * hash + (int)key[i];
		}

		return hash % _size;
	}

private:
	unsigned int _size;
	unsigned __int64 _primeNumber;
	Item* items[];
};

int main(int argc, char* argv[])
{
	HashTable* ht = new HashTable();

	// Neo?ae n iaieeiaui ee???i
	ht->add("Beer", "$2");
	ht->add("Beer",  "$3");

	//Neo?ae n eieeeceyie
	ht->add("Bread", "$2");
	ht->add("Berad", "$4");
	ht->add("Berda", "$6");

	std::cout << ht->get("Beer")  << std::endl;
	std::cout << ht->get("Bread") << std::endl;
	std::cout << ht->get("Berad") << std::endl;
	std::cout << ht->get("Berda") << std::endl;

	return 0;
}