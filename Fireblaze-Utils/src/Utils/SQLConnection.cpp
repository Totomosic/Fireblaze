#include "SQLConnection.h"

namespace Fireblaze
{

	static const char QUERY_PREFIX[] = "Query: ";
	static const char COMMIT_PREFIX[] = "Commit";
	static const char ROLLBACK_PREFIX[] = "Rollback";
	static const char RESPONSE_PREFIX[] = "Response: ";
	
	static const char SUCCESS_PREFIX[] = "Success";
	static const char ERROR_PREFIX[] = "Error";

	SQLConnection::SQLConnection(const SocketAddress& address)
		: m_Socket()
	{
		Connect(address);
	}

	SQLConnection::SQLConnection()
		: m_Socket()
	{
		
	}

	int SQLConnection::Connect(const SocketAddress& address)
	{
		return m_Socket.Connect(address);
	}

	void SQLConnection::Disconnect()
	{
		m_Socket.Close();
	}

	SQLQueryResult SQLConnection::Execute(const blt::string& sqlQuery, bool logResponse)
	{
		blt::string request = QUERY_PREFIX + sqlQuery;
		blt::string response = GetStringResponse(request);
		return ConvertStringToQueryResult(response, logResponse);
	}

	bool SQLConnection::CommitChanges()
	{
		blt::string response = GetStringResponse(COMMIT_PREFIX);
		return response.begins_with(SUCCESS_PREFIX);
	}

	bool SQLConnection::RollbackChanges()
	{
		blt::string response = GetStringResponse(ROLLBACK_PREFIX);
		return response.begins_with(SUCCESS_PREFIX);
	}

	blt::string SQLConnection::GetStringResponse(const blt::string& sendData)
	{
		m_Socket.Send(sendData.data(), sendData.length() + 1);
		char buffer[2048];
		int received = m_Socket.Recv(buffer, sizeof(buffer));
		if (received > 0)
		{
			return blt::string(buffer);
		}
		return "";
	}

	SQLQueryResult SQLConnection::ConvertStringToQueryResult(const blt::string& str, bool logResponse)
	{
		SQLQueryResult result;
		result.Status = SQLQueryStatus::Error;
		result.Error = "Invalid Query";
		if (str.begins_with(ERROR_PREFIX))
		{
			result.Status = SQLQueryStatus::Error;
			result.Error = str.substr((ERROR_PREFIX + blt::string(": ")).length());
			if (logResponse)
			{
				BLT_CORE_ERROR(result.Error);
			}
			return result;
		}
		else if (str.begins_with(RESPONSE_PREFIX))
		{
			result.Status = SQLQueryStatus::Ok;
			result.Error = "";
			blt::string response = str.substr(blt::string(RESPONSE_PREFIX).length());

			if (logResponse)
			{
				BLT_CORE_INFO(response);
			}

			response.pop_front();
			response.pop_back();
			
			std::vector<SQLRow> rows;
			std::vector<blt::string> rowStrings = response.split(']');
			for (blt::string& row : rowStrings)
			{				
				if (row.begins_with(','))
				{
					row.pop_front();
				}
				if (row.begins_with('['))
				{
					row.pop_front();
				}
				std::vector<blt::string> rowValues;
				uint32_t start = 0;
				uint32_t end = row.find_first_of(',');
				while (end != blt::string::npos)
				{
					rowValues.push_back(row.substr(start, end - start));
					start = end + 1;
					end = row.find_first_of(',', start);
				}
				rowValues.push_back(row.substr(start));
				rows.push_back(SQLRow(rowValues));
			}
			SQLTable table(rows);
			result.Table = std::move(table);
		}
		return result;
	}

}