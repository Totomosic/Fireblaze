#include "sql.h"

namespace Fireblaze
{

	SQLRow::SQLRow()
		: m_Values()
	{
	
	}

	SQLRow::SQLRow(const std::vector<blt::string>& values)
		: m_Values(values)
	{
	
	}

	int SQLRow::GetValueCount() const
	{
		return m_Values.size();
	}

	const blt::string& SQLRow::GetValue(int index) const
	{
		return m_Values.at(index);
	}

	blt::string& SQLRow::GetValue(int index)
	{
		return m_Values.at(index);
	}

	std::vector<blt::string>::const_iterator SQLRow::begin() const
	{
		return m_Values.begin();
	}

	std::vector<blt::string>::const_iterator SQLRow::end() const
	{
		return m_Values.end();
	}

	std::vector<blt::string>::iterator SQLRow::begin()
	{
		return m_Values.begin();
	}

	std::vector<blt::string>::iterator SQLRow::end()
	{
		return m_Values.end();
	}


	SQLTable::SQLTable()
		: m_Rows(), m_ColumnCount(0)
	{
	
	}

	SQLTable::SQLTable(const std::vector<SQLRow>& rows)
		: m_Rows(rows), m_ColumnCount(0)
	{
		if (m_Rows.size() > 0)
		{
			m_ColumnCount = m_Rows.at(0).GetValueCount();
		}
	}

	int SQLTable::GetRowCount() const
	{
		return m_Rows.size();
	}

	int SQLTable::GetColumnCount() const
	{
		return m_ColumnCount;
	}

	const SQLRow& SQLTable::GetRow(int index) const
	{
		return m_Rows.at(index);
	}

	SQLRow& SQLTable::GetRow(int index)
	{
		return m_Rows.at(index);
	}

	std::vector<SQLRow>::const_iterator SQLTable::begin() const
	{
		return m_Rows.begin();
	}

	std::vector<SQLRow>::const_iterator SQLTable::end() const
	{
		return m_Rows.end();
	}

	std::vector<SQLRow>::iterator SQLTable::begin()
	{
		return m_Rows.begin();
	}

	std::vector<SQLRow>::iterator SQLTable::end()
	{
		return m_Rows.end();
	}

}