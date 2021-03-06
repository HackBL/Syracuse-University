/*
	1. Write a view named InvoiceBasic that returns three columns: VendorName, InvoiceNumber, InvoiceTotal. 
	Then, write a SELECT statement that returns all the columns in the view, 
	sorted by InvoiceTotal from smallest to largest, 
	where the first letter of the vendor name is A, B, or C.
*/
CREATE VIEW InvoiceBasic 
AS
SELECT VendorName, InvoiceNumber, InvoiceTotal
FROM Vendors JOIN Invoices
	ON Vendors.VendorID = Invoices.VendorID;


SELECT * 
FROM InvoiceBasic 
WHERE VendorName IN ('A', 'B', 'C')
ORDER BY InvoiceTotal ASC;


/*
	2. Create a view named Top10PaidInvoices that returns three columns for each vendor: VendorName, LastInvoiceDate (the most recent invoice date), 
	and SumOfInvoices (the sum of the InvoiceTotal column). 
	Return only the 10 vendors with the largest SumOfInvoices and include only paid invoices (i.e. InvoiceTotal - CredeitTotal - PaymentTotal = 0). 
	Then write a SELECT statement to show results of the view.
*/
CREATE VIEW Top10PaidInvoices
AS
SELECT TOP 10 VendorName, MAX(InvoiceDate) AS LastInvoiceDate, SUM(InvoiceTotal) AS SumOfInvoices
FROM Vendors JOIN Invoices
	ON Vendors.VendorID = Invoices.VendorID
WHERE InvoiceTotal - CreditTotal - PaymentTotal = 0
GROUP BY VendorName
ORDER BY SumOfInvoices DESC;
GO

SELECT * FROM Top10PaidInvoices;

/*
	3. Create an updatable views named VendorAddress that returns the VendorID, Address (i.e. VendorAddress1 + ‘ ’ + VendorAddress2), and the city, 
	state, and zipcode columns for each vendor. Whenever VendorAddress2 is NULL, substitute the NULL with a blank space. 
	Then write a SELECT query to examine the result set where VendorID=7. Write a SELECT statement to verify the result.
*/
CREATE VIEW VendorAddress
AS
SELECT VendorID, VendorAddress1 + ' ' + IsNull(VendorAddress2, '') AS Address, VendorCity, VendorState, VendorZipCode
FROM Vendors;
GO

SELECT *
FROM VendorAddress
WHERE VendorID = 7;


/*
	4. Write a SELECT statement that selects all the columns for the catalog view that returns information about foreign keys in the AP database. 
	How many foreign key(s) is/are defined in the AP database and what is/are they?

*/
USE [AP]
SELECT *
FROM sys.foreign_keys;


/*
	5. Write a script that declares and sets a variable named @TotalBalanceDue, which is equal to the total outstanding balance due. What is the datatype of the variable @TotalBalanceDue? If that balance due is less than $45,000.00, 
	the script should return a result set consisting of VendorName, InvoiceNumber, InvoiceDueDate, and Balance for each invoice with a balance due, 
	sorted with the newest due date last. Then also return the value of @TotalBalanceDue in the format of “Balance due is ...”. If the total outstanding balance due is more than $45,000.00, the script should return the message “Balance due is more than $45,000.00”.
*/
USE[AP];
-- Declare a variable named TotalBalanceDue with type of money
DECLARE @TotalBalanceDue money;

-- Set variable @TotalBalanceDue to sum of balance due
SET @TotalBalanceDue = 
	(SELECT SUM(InvoiceTotal - CreditTotal - PaymentTotal)
	 FROM Invoices
	 WHERE (InvoiceTotal - CreditTotal - PaymentTotal) > 0);

-- If @TotalBalanceDue less than 45,000.00, return the following results
IF @TotalBalanceDue < 45000
	BEGIN
SELECT VendorName, InvoiceNumber, InvoiceDueDate, InvoiceTotal - CreditTotal - PaymentTotal AS Balance
		FROM Vendors JOIN Invoices
			ON Vendors.VendorID = Invoices.VendorID
		WHERE (InvoiceTotal - CreditTotal - PaymentTotal) > 0
		ORDER BY InvoiceDueDate;

		PRINT 'Balance due is $' + CONVERT(varchar, @TotalBalanceDue, 1);
	END;
-- If @TotalBalanceDue >= 45,000.00, return the following message
ELSE
PRINT 'Balance due is more that 45,000.00';


/*
	6. Explain the execution result generated by the following script. 
	Then Write a script that generates the same result set but uses a temporary table in place of the derived table. 
	Make sure your script tests for the existence of any objects it creates.

	USE AP;
	SELECT VendorName,LastInvoiceDate, InvoiceTotal
	FROM Invoices 
	JOIN (SELECT VendorID, MAX(InvoiceDate) AS LastInvoiceDate
			FROM Invoices
			GROUP BY VendorID) AS LastInvoice
	ON (Invoices.VendorID = LastInvoice.VendorID AND
		Invoices.InvoiceDate = LastInvoice.LastInvoiceDate) 
	JOIN Vendors ON Invoices.VendorID = Vendors.VendorID 
	ORDER BY VendorName, LastInvoiceDate;
*/

-- Explanation: The script returns Vendor Name, LastInvoiceDate and InvoiceTotal using derived table issued by each vendor. 

USE[AP];

IF OBJECT_ID('#LastInvoices') IS NOT NULL
	DROP TABLE #LastInvoices;

-- Temporary Table #LastInvoices stored data from derived table
SELECT VendorID, MAX(InvoiceDate) AS LastInvoiceDate
INTO #LastInvoices
FROM Invoices
GROUP BY VendorID;

-- Using temp table to join by Invoices
SELECT VendorName, LastInvoiceDate, InvoiceTotal
FROM Invoices JOIN #LastInvoices
	ON (Invoices.VendorID = #LastInvoices.VendorID AND
		Invoices.InvoiceDate = #LastInvoices.LastInvoiceDate)
JOIN Vendors
	ON Invoices.VendorID = Vendors.VendorID
ORDER BY VendorName, LastInvoiceDate;  



/*
	7. Write a script that generates the date and invoice total of the earliest invoice issued by each vendor, using a view instead of a derived table. 
	Also write the script that creates the view, then use SELECT statement to show result of the view. Make sure that your script tests for the existence of the view. 
	The view doesn’t need to be redefined each time the script is executed.
*/

USE[AP];
-- Drop View if it exists
IF OBJECT_ID('TempInvoices') IS NOT NULL
	DROP VIEW TempInvoices;
GO

-- Create view as tempory invoices that return vendorID and earliest date
CREATE VIEW TempInvoices
AS
SELECT VendorID, MIN(InvoiceDate) AS Earliest
FROM Invoices
GROUP BY VendorID;
GO

-- Return VendorName, Earliest and InvoiceTotal called by view
SELECT VendorName, Earliest, InvoiceTotal
FROM Invoices JOIN TempInvoices
	ON (Invoices.VendorID = TempInvoices.VendorID AND
		Invoices.InvoiceDate = TempInvoices.Earliest)
JOIN Vendors ON Invoices.VendorID = Vendors.VendorID
ORDER BY VendorName, Earliest;
GO


/*
	8. Write a script that uses dynamic SQL to return a single column that represents the number of rows in the first table in the current database. 
	The script should automatically choose the table that appears first alphabetically, and it should exclude tables named dtproperties and sysdiagrams. 
	Name the column CountOfTable, where Table is the chosen table name. Show results for AP database.
*/

USE[AP];
-- Drop View if it exists
IF OBJECT_ID('TempInvoices') IS NOT NULL
	DROP VIEW TempInvoices;
GO

-- Create view as tempory invoices that return vendorID and earliest date
CREATE VIEW TempInvoices
AS
SELECT VendorID, MIN(InvoiceDate) AS Earliest
FROM Invoices
GROUP BY VendorID;
GO

-- Return VendorName, Earliest and InvoiceTotal called by view
SELECT VendorName, Earliest, InvoiceTotal
FROM Invoices JOIN TempInvoices
	ON (Invoices.VendorID = TempInvoices.VendorID AND
		Invoices.InvoiceDate = TempInvoices.Earliest)
JOIN Vendors ON Invoices.VendorID = Vendors.VendorID
ORDER BY VendorName, Earliest;
GO


