/*
	1. Create VendorCopy table and InvoiceCopy table.
*/
USE [AP]
SELECT * 
INTO VendorCopy
FROM Vendors;

SELECT * 
INTO InvoiceCopy
FROM Invoices;


/*
	2. Write an INSERT statement that adds a row to the InvoiceCopy table with the following values 
	(USE SELECT statement to verify data changes in the table before and after the modification):
	
		VendorID:		2			InvoiceTotal:		$401.40
		TermsID:		3			InvoiceNumber:		CM-007-700
		PaymentTotal:	$2.99 		InvoiceDueDate:		09/01/15
		InvoiceDate:	08/24/15 	CreditTotal:		$5.99

	Do we explicitly need to insert InvoiceID?
*/
USE [AP]
INSERT INTO InvoiceCopy
		(VendorID, TermsID, PaymentTotal, 
		InvoiceDate, InvoiceTotal, InvoiceNumber, 
		InvoiceDueDate, CreditTotal)
VALUES
	(2, 3, 2.99, '08/24/15', 401.40, 'CM-007-700', '09/01/15', 5.99);

-- We don’t need to insert InvoiceID explicitly, because the InvoiceID will be increment by 1 automatically after insert.


/*
	3. Write an UPDATE statement that modifies the VendorCopy table. 
	Change the default account number to 542 for each vendor that has a default account number of 572. 
	(USE SELECT statement to verify data changes in the table before and after the modification).
*/
USE [AP]
UPDATE VendorCopy
SET DefaultAccountNo = 542
WHERE DefaultAccountNo = 572;


/*
	4. Write an UPDATE statement that modifies the InvoiceCopy table. 
	Change the TermsID to 5 for each invoice that’s from a vendor with a defaultTermsID of 2. 
	Use a subquery. 
	(USE SELECT statement to verify data changes in the table before and after the modification).
*/
USE [AP]
UPDATE InvoiceCopy
SET TermsID = 5
FROM (SELECT VendorID
		FROM Vendors
		WHERE DefaultTermsID = 2)
	AS VendorItems
WHERE InvoiceCopy.VendorID = VendorItems.VendorID;


/*
	5. Write a DELETE statement that deletes all vendors in the state of ‘New York’ from the VendorCopy table. 
	(USE SELECT statement to verify data changes in the table before and after the modification).
*/
USE [AP]
DELETE VendorCopy
WHERE VendorState = 'NY';


/*
	6. Write a DELETE statement for the VendorCopy table. 
	Delete the vendors that are located in cities from which no vendor has ever sent an invoice. 
	(USE SELECT statement to verify data changes in the table before and after the modification).
*/
USE [AP]
DELETE VendorCopy
WHERE VendorCity NOT IN 
			(SELECT DISTINCT VendorCity
			FROM VendorCopy JOIN InvoiceCopy
			ON VendorCopy.VendorID = InvoiceCopy.VendorID);


/*
	7. Write a SELECT statement that returns four columns based on the InvoiceTotal column of the Invoices table:
		- Use CAST function to return the first column as data type decimal with 4 digits to the right of the decimal point.
		- Use CAST to return the second column as a VARCHAR.
		- Use CONVERT function to return third column as the same type as the first column.
		- Use CONVERT to return the fourth column as a VARCHAR, using style 10.
*/

USE [AP]
SELECT 
	CAST (InvoiceTotal AS decimal(20, 4)) AS InvoiceTotalCast,
	CAST (InvoiceTotal AS varchar) AS CastToVarchar,
	CONVERT (decimal(20, 4), InvoiceTotal) AS InvoiceTotalConvert,
	CONVERT (varchar, InvoiceTotal, 10) AS Style_10_Convert
FROM Invoices;


/*
	Write a SELECT statement that returns four columns based on the InvoiceDate column of the Invoices table:
		- Use the CAST function to return the first column as data type VARCHAR.
		- Use the CONVERT function to return the second and third columns as a VARCHAR, using style 5 and style 9, respectively.
		- Use the CAST function to return the fourth column as a data type real.
*/
USE [AP]
SELECT 
	CAST (InvoiceDate AS varchar) AS VarcharDate,
	CONVERT (varchar, InvoiceDate, 5) AS Style_5_Convert,
	CONVERT (varchar, InvoiceDate, 9) AS Style_9_Convert,
	CAST (InvoiceDate AS real) AS CastToReal
FROM Invoices;