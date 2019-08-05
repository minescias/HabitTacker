#ifndef __DATASET2_H
#define __DATASET2_H

#include <memory>
#include <set>
#include <string>
#include <vector>

#include <Core/Database/DatasetHeader.h>
#include <Core/Database/Row.h>

namespace Db
{

class Dataset2
{
public:
	
	class Iterator
	{
	public:
		Iterator(std::vector<std::unique_ptr<Row>>* data, int position)
			: data(data),position(position) {}

      	Row& operator*() const
		{
			// dereferencja wskaźnika wyciągniętego przez dereferencję 
			// z smart pointera... nice
			return *(*data)[position].get();
		}

		Iterator& operator++() 
		{
			if(++position == data->size())
				position = 0;
			
			return *this;
		}

		bool operator!=(const Iterator& it) const
		{
			return position != it.position;
		}

	private:
		int position;
		std::vector<std::unique_ptr<Row>>* data;	
	};

	Iterator begin() { return Iterator(&data, 0); }
	Iterator end() { return Iterator(&data, data.size() - 1); }

	class ConstIterator
	{
	public:
		ConstIterator(const std::vector<std::unique_ptr<Row>>* data, int position)
			: data(data),position(position) {}

      	const Row& operator*() const 
		{
			// dereferencja wskaźnika wyciągniętego przez dereferencję 
			// z smart pointera... nice
			return *(*data)[position].get();
		}

		ConstIterator& operator++()
		{
			if(++position == data->size())
				position = 0;
			
			return *this;
		}

		bool operator!=(const ConstIterator& it) const
		{
			return position != it.position;
		}

	private:
		int position;
		const std::vector<std::unique_ptr<Row>>* data;	
	};

	ConstIterator begin() const { return ConstIterator(&data, 0); }
	ConstIterator end() const { return ConstIterator(&data, data.size() - 1); }

public:
	Dataset2();

	void addColumn(const std::string& name);
	Row* addRow();

	int getColumnsCount() const;
	int getRowsCount() const;

	bool isInitialized() const;
	bool isEmpty() const;

	Row* getFirstRow() const;

private:
	DatasetHeader header;
	std::vector<std::unique_ptr<Row>> data;
};

} // namespace Db

#endif // __DATASET2_H
