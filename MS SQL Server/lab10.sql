/*
	1. Write a set of action queries coded as a transaction to reflect the following change: 
	“The Drawing Board” has been purchased by “Computer Library” and the new company is named ‘ComputerBoard’. 
	Rename one of the vendors and delete the other after updating the VendorID column in the Invoices table. 
	Use SELECT statement to verify the results.
*/
USE [AP]

BEGIN TRAN
	UPDATE Invoices
	SET VendorID = 68
	WHERE VendorID = 65;
	
	DELETE Vendors
	WHERE VendorID = 65;

	UPDATE Vendors
	SET VendorName = 'ComputerBoard'
	WHERE VendorID = 68;

COMMIT TRAN;


/*
	2. Write a set of action queries coded as a transaction to move rows from the Invoices table to the InvoiceArchive table. 
	Insert all paid invoices from Invoices into InvoiceArchive, but only if the invoice doesn’t already exist in the InvoiceArchive table. 
	Then, delete all paid invoices from the Invoices table, but only if the invoice exists in the InvoiceArchive table. 
	Use SELECT statement to verify the results.
*/

USE [AP]

BEGIN TRAN

	INSERT InvoiceArchive
	SELECT Invoices.* 
	FROM Invoices LEFT JOIN InvoiceArchive
		ON Invoices.InvoiceID = InvoiceArchive.InvoiceID
	WHERE Invoices.InvoiceTotal - Invoices.CreditTotal - Invoices.PaymentTotal = 0 
			AND InvoiceArchive.InvoiceID IS NULL;

	DELETE Invoices
	WHERE InvoiceID IN (SELECT InvoiceID
				FROM InvoiceArchive);

COMMIT TRAN;
