#include "stdafx.h"
#include "HDR.h"
#include "HDR_sql.h"
#include <iostream>
#include <experimental/filesystem>
#include <string>

namespace fs = std::experimental::filesystem;


#define CORSERVER_MAX_STRLEN		30
#define SQLPrepare          SQLPrepareW
#define SQLDriverConnect    SQLDriverConnectW

SQLHANDLE SQLEnvHandle;
SQLHANDLE SQLConnectionHandle = NULL;
SQLHANDLE SQLStatementHandle = NULL;
SQLWCHAR retConString[1024];
SQLRETURN retCode;

// Constructor
HDRsql::HDRsql() {

	// Initialize resources if needed
}

 //Destructor
HDRsql::~HDRsql() {
	//disconnect(); // Cleanup on destruction
}

// Connect to the database
void HDRsql::connectdatabase() 
{
	//std::cout << "Entering inside data" << std::endl;

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle)) {
		disconnect();
		return;
	}

	if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) {
		disconnect();
		return;
	}

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle)) {
		disconnect();
		return;
	}

	//std::cout << "Attempting connection to SQL Server...\n";

	switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=HDR_Service;UID=sa;PWD=panacea;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT))
	{
	case SQL_SUCCESS:
		std::cout << "Successfully connected to SQL Server.\n";
		break;
	case SQL_SUCCESS_WITH_INFO:
		std::cout << "Successfully connected with info.\n";
		break;
	default:
		std::cout << "Failed to connect.\n";
		disconnect();
		return;
	}

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle)) {
		//std::cout << "Failed to allocate statement handle.\n";
		disconnect();
	}


}

void HDRsql::readData() 
{
	// Check if the connection handle and statement handle are valid
	if (!SQLConnectionHandle || !SQLStatementHandle) {
		//std::cout << "Database connection is not established.\n";
		return;
	}

	// The query to fetch the columns
	std::wstring query = L"SELECT Radius, Reference1, Reference2, TopRedPixel_X, TopRedPixel_Y, ButtomRedPixel_X, ButtomRedPixel_Y,Epsilon_Fraction FROM CameraCalibrationDatas"; // Replace "YourTableName" with your actual table name

																		  // Prepare the SQL query
	if (SQLPrepare(SQLStatementHandle, (SQLWCHAR*)query.c_str(), SQL_NTS) != SQL_SUCCESS) {
		//std::cout << "Failed to prepare SQL query.\n";
		disconnect();
		return;
	}

	// Execute the SQL query
	if (SQLExecute(SQLStatementHandle) != SQL_SUCCESS) {
		//std::cout << "Failed to execute SQL query.\n";
		disconnect();
		return;
	}

	// Variables to hold the column values
	

	// Fetch the result row
	if (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		// Retrieve the values of each column
		SQLGetData(SQLStatementHandle, 1, SQL_C_DOUBLE, &radius, sizeof(radius), NULL);
		SQLGetData(SQLStatementHandle, 2, SQL_C_DOUBLE, &refer1, sizeof(refer1), NULL);
		SQLGetData(SQLStatementHandle, 3, SQL_C_DOUBLE, &refer2, sizeof(refer2), NULL);
		SQLGetData(SQLStatementHandle, 4, SQL_C_DOUBLE, &topPixel_x, sizeof(topPixel_x), NULL);
		SQLGetData(SQLStatementHandle, 5, SQL_C_DOUBLE, &topPixel_y, sizeof(topPixel_y), NULL);
		SQLGetData(SQLStatementHandle, 6, SQL_C_DOUBLE, &bottomPixel_x, sizeof(bottomPixel_x), NULL);
		SQLGetData(SQLStatementHandle, 7, SQL_C_DOUBLE, &bottomPixel_y, sizeof(bottomPixel_y), NULL);
		SQLGetData(SQLStatementHandle, 8, SQL_C_DOUBLE, &epsilonfraction, sizeof(epsilonfraction), NULL);


		//std::cout << "radius: " << radius << "ref1: " << refer1 << "ref2" << refer2 << std::endl;
		//return;
	}
	else {
		std::cout << "No data found.\n";
	}

	// Free the statement handle after execution
	SQLFreeStmt(SQLStatementHandle, SQL_CLOSE);
	
	disconnect();
}


void HDRsql::readData1()
{
	// Check if the connection handle and statement handle are valid
	if (!SQLConnectionHandle || !SQLStatementHandle) {
		//std::cout << "Database connection is not established.\n";
		return;
	}

	// The query to fetch the columns
	std::wstring query = L"SELECT SourceCenterPositionRange FROM ConfigurationModels"; // Replace "YourTableName" with your actual table name

																																												  // Prepare the SQL query
	if (SQLPrepare(SQLStatementHandle, (SQLWCHAR*)query.c_str(), SQL_NTS) != SQL_SUCCESS) {
		//std::cout << "Failed to prepare SQL query.\n";
		disconnect();
		return;
	}

	// Execute the SQL query
	if (SQLExecute(SQLStatementHandle) != SQL_SUCCESS) {
		//std::cout << "Failed to execute SQL query.\n";
		disconnect();
		return;
	}

	// Variables to hold the column values
	// Fetch the result row
	if (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		// Retrieve the values of each column
		SQLGetData(SQLStatementHandle, 1, SQL_C_DOUBLE, &SCenter, sizeof(SCenter), NULL);

		//std::cout<< SCenter << std::endl;
		//return;
	}
	else {
		std::cout << "No data found.\n";
	}

	// Free the statement handle after execution
	SQLFreeStmt(SQLStatementHandle, SQL_CLOSE);

	disconnect();
}




// Function to insert 4 values into the database
bool HDRsql::insertData(double value1, double value2, double value3, double value4) {

	// Prepare the SQL query
	std::wstring query = L"UPDATE CameraCalibrationDatas SET TopRedPixel_X = ?, TopRedPixel_Y = ?, ButtomRedPixel_X = ?, ButtomRedPixel_Y = ? ";

	if (SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle) != SQL_SUCCESS) {
		std::cerr << "Error allocating SQL statement handle.\n";
		return false;
	}

	if (SQLPrepare(SQLStatementHandle, (SQLWCHAR*)query.c_str(), SQL_NTS) != SQL_SUCCESS) {
		std::cerr << "Failed to prepare SQL query.\n";
		SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
		return false;
	}

	// Bind parameters
	SQLBindParameter(SQLStatementHandle, 1, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0, &value1, 0, nullptr);
	SQLBindParameter(SQLStatementHandle, 2, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0, &value2, 0, nullptr);
	SQLBindParameter(SQLStatementHandle, 3, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0, &value3, 0, nullptr);
	SQLBindParameter(SQLStatementHandle, 4, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0, &value4, 0, nullptr);

	// Execute the SQL query
	if (SQLExecute(SQLStatementHandle) != SQL_SUCCESS) {
		std::cerr << "Failed to execute SQL query.\n";
		SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
		return false;
	}

	std::cout << "Data inserted successfully.\n";
	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	disconnect();
	return true;

	
}





// Disconnect from the database
void HDRsql::disconnect() {
	if (SQLStatementHandle) SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	if (SQLConnectionHandle) SQLDisconnect(SQLConnectionHandle);
	if (SQLConnectionHandle) SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	if (SQLEnvHandle) SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);

}
