#pragma once
#include "bltpch.h"
#include "FBLDefines.h"

namespace Fireblaze
{

	FBL_API enum class SQLQueryStatus
	{
		Error,
		Ok
	};

	class FBL_API SQLRow
	{
	private:
		std::vector<blt::string> m_Values;

	public:
		SQLRow();
		SQLRow(const std::vector<blt::string>& values);

		int GetValueCount() const;
		const blt::string& GetValue(int index) const;
		blt::string& GetValue(int index);

		std::vector<blt::string>::const_iterator begin() const;
		std::vector<blt::string>::const_iterator end() const;
		std::vector<blt::string>::iterator begin();
		std::vector<blt::string>::iterator end();
	};

	class FBL_API SQLTable
	{
	private:
		std::vector<SQLRow> m_Rows;
		int m_ColumnCount;

	public:
		SQLTable();
		SQLTable(const std::vector<SQLRow>& rows);

		int GetRowCount() const;
		int GetColumnCount() const;
		const SQLRow& GetRow(int index) const;
		SQLRow& GetRow(int index);

		std::vector<SQLRow>::const_iterator begin() const;
		std::vector<SQLRow>::const_iterator end() const;
		std::vector<SQLRow>::iterator begin();
		std::vector<SQLRow>::iterator end();
	};

	struct FBL_API SQLQueryResult
	{
	public:
		SQLQueryStatus Status;
		SQLTable Table;
		blt::string Error;
	};

}