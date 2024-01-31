#pragma once
#include "includes.h"

template<typename T>
class Relation
{
public:
	Relation() {};
	Relation(std::set<T> relation)
	{
		this->relation = relation;
	}

	inline void SetRelation(std::set<T> relation) { this->relation = relation; }
	inline set<T> GetRelation() { return this->relation; }
	inline int GetMagnitude() { return relation.size(); }

	void Union(std::set<T> B)
	{
		//Faster to insert B one by one
		if (B.size() <= relation.size())
		{
			//Just insert them; if its a duplicate, nothing happens
			for (T b : B)
			{
				relation.insert(b);
			}
		}
		else
		{
			//Make a temp
			std::set<T> temp = relation;
			//Set relation equal to the larger set
			//This assumes cpp can move set references faster than we can insert B into relation
			relation = B;
			//Now insert the smaller set one-by-one into relation
			for (T item : temp)
			{
				relation.insert(item);
			}
		}
	}


	void Intersect(std::set<T> B)
	{
		std::set<T> temp;
		//For each item in relation
		for (T item : relation)
		{
			//If B does contain item
			if (B.count(item))
			{
				//Insert it in temp
				temp.insert(item);
			}
		}

		//Now temp has all items contained in both A and B
		relation.clear();
		//Set relation to temp
		relation = temp;
	}

private:
	std::set<T> relation;
};

