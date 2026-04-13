#include <iostream>
#include <string>
#include "Reader.h"

using namespace std;

class Category
{
private:
	int category_id;
	string category_name;
	Category(int id, string name) : category_id(id), category_name(name)
	{
	}
public:
	int getCategoryId() const
	{
		return category_id;
	}

	string getCategoryName() const
	{
		return category_name;
	}
};


