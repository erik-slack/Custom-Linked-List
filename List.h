#pragma once;
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
using namespace std;

template <typename ItemType>
class List
{
private:
	class Node 
	{
	// DATA
	public:
		ItemType item;
		Node* next;
		Node* prev;

		//~Node;
	};

	int count;
	Node* head;
	Node* tail;

public:
	// CONSTRUCTORS
	List()
	{
		count = 0;
		head = NULL;
		tail = NULL;
	}

	~List()
	{
		clear();
	}

	// ANALYZERS
	int find(string query)
	{
		int index_out = -1;
		int current_index = 0;
		bool item_found = false;

		Node* item_search = NULL;
		item_search = head;

		while (item_search != NULL && item_found == false)
		{
			if (item_search->item == query)
			{
				item_found = true;
				index_out = current_index;
				break;
			}
			item_search = item_search->next;
			current_index++;
		}

		return index_out;
	}

	Node* get_byIndex(string index_query)
	{
		Node* node_search;
		int query_converted = atoi(index_query.c_str());

		if (query_converted < (count / 2))
		{
			int current_index = 0;
			node_search = head;
			while (current_index != query_converted)
			{
				node_search = node_search->next;
				if (current_index == query_converted)
				{
					break;
				}
				current_index++;
			}
		}
		else
		{
			int current_index = count - 1;
			node_search = tail;
			while (current_index != query_converted)
			{
				if (current_index == query_converted)
				{
					break;
				}
				node_search = node_search->prev;
				current_index--;
			}
		}
		
		return node_search;
	}

	// IMPORTERS
	void loadCommands(string cmd_choice, string save_choice)
	{
		stringstream ss;
		ifstream in_file;
		ofstream out_file;

		in_file.open(cmd_choice);
		out_file.open(save_choice);

		string new_word, index, item;

		while (in_file >> new_word)
		{
			if (new_word == "insert")
			{
				in_file >> index;
				in_file >> item;

				insert(item, index);
				out_file << "insert " << index << " " << item << endl;
			}
			else if (new_word == "remove")
			{
				in_file >> index;

				item = remove(index);  // this function is causing "Unhandled Exception"
				out_file << "remove " << index << " " << item << endl;
			}
			else if (new_word == "find")
			{
				in_file >> item;

				int index = find(item);
				out_file << "find " << item << " " << index << endl;
			}
			else if (new_word == "clear")
			{
				clear();
				out_file << "clear" << endl;
			}
			else if (new_word == "print")
			{
				out_file << "print" << endl;
				out_file << print();
			}
			else
			{
				out_file << "Command failed." << endl;
			}
			//out_file << endl;
		}
	}

	// MUTATORS
	void clear()
	{
		while (head != NULL)
		{
			Node* temp_node = head;
			head = head->next;
			delete temp_node;
		}
		tail = NULL;
		count = 0;
	}

	void insert(const ItemType& item_in, string index_in)
	{
		int index_converted = atoi(index_in.c_str());
		Node* n = new Node();
		n->item = item_in;

		if (count == 0) // add premeire item of list
		{
			head = n;
			tail = n;
			n->next = NULL;
			n->prev = NULL;
		}
		else if (index_converted == 0) // add at beginning of list
		{
			n->next = head;
			n->prev = NULL;
			head->prev = n;
			head = n;
		}
		else if (index_converted == count) // append to list
		{
			n->next = NULL;
			n->prev = tail;
			tail->next = n;
			tail = n;
		}
		else if (index_converted > count) // index is greater than size of list
		{
			// nothing happens
		}
		else // add to middle of list
		{
			Node* node_search = get_byIndex(index_in);
			n->next = node_search;
			n->prev = node_search->prev;
			node_search->prev->next = n;
			node_search->prev = n;
		}
		count++;
	}
	
	void removeSubSection()
	{
		if (count > 1) // this should only happen if there is more than one item in the list
		{
			head = head->next; // sets head to point at second item in list
			head->prev = NULL; // sets the new head's prev to NULL
		}
		else if (count == 1) // remove only item left in list
		{
			head = NULL;
			tail = NULL;
		}
	}

	ItemType remove(string index_in)
	{
		ItemType item_out;
		int index_converted = atoi(index_in.c_str());

		if (count <= 0 || index_converted > count - 1)
		{
			// nothing happens
		}
		else if (index_converted == 0 && head != NULL) // remove first item of list
		{
			Node* temp = head; // makes a second pointer to item already pointed to by head
			
			removeSubSection();
			
			item_out = temp->item; // extracts the item so later we can Return what item was removed
			delete temp; // deletes what used to be the head item from memory
			count--;
		}
		else if (index_converted == count - 1 && count > 1) // remove last item of list
		{
			Node* temp = tail; // makes a second pointer to item already pointed to by list
			tail = temp->prev; // sets tail to point at second to last item in list
			tail->next = NULL; // sets the new tail's next to NULL
			item_out = temp->item; // extracts the item so later we can Return what item was removed
			delete temp; // deletes what used to be the tail item from memory
			count--;
		}
		else // removed from middle of list
		{
			Node* node_search = get_byIndex(index_in);
			node_search->prev->next = node_search->next;
			node_search->next->prev = node_search->prev;
			node_search->next = NULL;
			node_search->prev = NULL;
			item_out = node_search->item; // extracts the item so later we can Return what item was removed
			delete node_search;
			count--;
		}
		return item_out;
	}

	// PRINTERS
	string print()
	{
		stringstream ss;
		Node* current_node = head;
		int current_index = 0;

		while (current_node != NULL)
		{
			ss << "node " << current_index << ": " << current_node->item << endl;
			current_index++;
			current_node = current_node->next;
		}

		return ss.str();
	}
};
