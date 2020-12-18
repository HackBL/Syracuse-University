/*
	1. Write a SELECT statement that returns two columns: Artist and their individual TotalEarnings, 
	where TotalEarnings is the sum of the UnitPrice column. 
	Return 5 artists who’ve earned the least in ascending order of their earnings. 
	Use ProductOrders database.
*/
SELECT TOP 5 Artist, SUM(UnitPrice) AS TotalEarnings
FROM ProductOrders.dbo.items
GROUP BY Artist
ORDER BY TotalEarnings;


/*
	2. Write a SELECT statement that returns three columns: VendorName, InvoiceCount and InvoiceAverage. 
	InvoiceCount is the count of the number of invoices, and InvoiceAverage is the average of the InvoiceTotal of each vendor. 
	Group the result set by VendorName and sort the result in descending order of number of invoices. 
	Use AP database.
*/
USE [AP]
SELECT VendorName, 
		COUNT(*) AS InvoiceCount,
		AVG(InvoiceTotal) AS InvoiceAverage
From Vendors JOIN Invoices
	ON Vendors.VendorID = Invoices.VendorID
GROUP BY VendorName
ORDER BY InvoiceCount DESC;


/*
	3. Write a SELECT statement that returns: AccountDescription, LineItemCount, and LineItemSum. 
	LineItemCount is the number of entries in the InvoiceLineItems table that have that AccountNo. 
	LineItemSum is the sum of the InvoiceLineItemAmount column for that AccountNo. 
	Filter the result set to include only those rows with LineItemCount more than 2. Group the result set by account description, 
	and sort it in descending order of LineItemSum. Use AP database.
*/
USE [AP]
SELECT AccountDescription,
		COUNT(*) AS LineItemCount,
		SUM(InvoiceLineItemAmount) AS LineItemSum
FROM InvoiceLineItems JOIN GLAccounts
	ON InvoiceLineItems.AccountNo = GLAccounts.AccountNo
GROUP BY AccountDescription
HAVING COUNT(*) > 2
ORDER BY LineItemSum DESC;


/*
	4. Write a SELECT statement that answers the following question: What is the total amount invoiced for each AccountNo? 
	Use the WITH ROLLUP operator to include a row that gives the grand total.
*/
USE [AP]
SELECT AccountNo, SUM(InvoiceLineItemAmount) AS TotalAmount
FROM InvoiceLineItems
GROUP BY AccountNo WITH ROLLUP;


/*
	5. Write a SELECT statement that return the vendor name and the total number of accounts that apply to that vendor’s invoices. 
	Filter the result set to include only the vendor who is being paid more than twice. 
	(HINT: use Vendors table, Invoices table and InvoiceLineItems table).
*/
USE [AP]
SELECT VendorName, COUNT(DISTINCT AccountNo) AS NumberOfAccount
FROM Vendors JOIN Invoices
	ON Vendors.VendorID = Invoice.VendorID
JOIN InvoiceLineItems
	ON Invoice.InvoiceID = InvoiceLineItems.InvoiceID
GROUP BY VendorName
HAVING COUNT(DISTINCT AccountNo) > 2;


/*
	6. Write a SELECT statement that returns the distinct AccountNo for invoicelineitems (AccountNo should not be repeated in the result). 
	Filter the result set to include only accounts having an InvoiceLineItemAmount that is greater than the average InvoiceLineItemAmount for all invoicelineitems. 
	Use GLAccounts and InvoiceLineItems tables from AP database.
*/
USE [AP]
SELECT DISTINCT GLAccounts.AccountNo
FROM InvoiceLineItems JOIN GLAccounts
	ON InvoiceLineItems.AccountNo = GLAccounts.AccountNo
WHERE InvoiceLineItemAmount > 
		(SELECT AVG(InvoiceLineItemAmount)
		 FROM InvoiceLineItems);


/*
	7. Write a SELECT statement that returns the sum of the smallest unpaid invoices submitted by each vendor. 
	Use a derived table that returns MIN(InvoiceTotal) grouped by VendorID, filtering for invoices with a balance due. 
	(HINT: Balance = InvoiceTotal – CreditTotal - PaymentTotal)
*/
USE [AP]
SELECT SUM(MinInvoice.UnpaidInvoices) AS SumOfSmallest
FROM (SELECT VendorID, MIN(InvoiceTotal) AS UnpaidInvoices
		FROM Invoices
		WHERE InvoiceTotal - CreditTotal - PaymentTotal > 0
		GROUP BY VendorID) AS MinInvoice


/*
	8. Write a SELECT statement that returns the id, city, state, and zip-code of each vendor that’s located in a unique city with a unique zip-code (combination is unique). 
	In other words, don’t include vendors that have a city and zip-code in common with another vendor. 
	Sort the result set by city in descending order, and state in ascending order.
*/
USE [AP]
SELECT VendorID, VendorCity, VendorState, VendorZipCode
FROM Vendors 
WHERE VendorCity + VendorZipCode  IN
		(SELECT VendorCity + VendorZipCode
		FROM Vendors
		GROUP BY VendorCity, VendorZipCode
		HAVING COUNT(*) = 1)
ORDER BY VendorCity DESC, VendorState ASC;





















