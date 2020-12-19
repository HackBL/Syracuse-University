/*
	1. Write a SELECT statement that returns two columns based on the Vendors table. 

	The first column, Contact, is the vendor contact name in this format: 
	Vendor Last name followed by first two letters of Vendor First name 
	(for example, the format must look like, “Alberto Fr.”) 

	The second column, Phone, is the VendorPhone column without the area code. 

	Only return rows for those vendors in the 209 area code. 
	Sort the results set by first name, then last name. Use Examples database.
*/
USE [Examples]

SELECT VendorContactLName + ' ' + LEFT(VendorContactFName, 2) + '.' AS Contact,
	RIGHT(VendorPhone, 8) AS Phone
FROM Vendors
WHERE SUBSTRING(VendorPhone, 2, 3) = 209
ORDER BY VendorContactFName, VendorContactLName;


/*
	2. Write a SELECT statement that returns the InvoiceNumber and balance due for every invoice with 
	a non-zero balance and an InvoiceDueDate that’s less than 12 days from today 
	(i.e. InvoiceDueDate < today’s date + 12).
*/
USE[AP]

SELECT InvoiceNumber,
	InvoiceTotal - PaymentTotal - CreditTotal AS BalanceDue
FROM Invoices
WHERE InvoiceTotal - PaymentTotal - CreditTotal > 0 AND
InvoiceDueDate < GETDATE() + 12;


/*
	3. Modify the search expression for InvoiceDueDate from the solution for question 2. 
	Rather than 12 days from today, return invoices due before the last day of the current month.
*/
USE[AP]

SELECT InvoiceNumber,
	InvoiceTotal - PaymentTotal - CreditTotal AS BalanceDue
FROM Invoices
WHERE InvoiceTotal - PaymentTotal - CreditTotal > 0 AND
	InvoiceDueDate < EOMONTH(GETDATE());


/*
	4. Add a column to the query described in question 2 that uses the RANK() function 
	to return a column named BalanceRank that ranks the balance due in ascending order.
*/
USE[AP]

SELECT InvoiceNumber,
	InvoiceTotal - PaymentTotal - CreditTotal AS BalanceDue,
	RANK() OVER (ORDER BY InvoiceTotal - PaymentTotal - CreditTotal) AS BalanceRank 
FROM Invoices
WHERE InvoiceTotal - PaymentTotal - CreditTotal > 0 AND 
InvoiceDueDate < GETDATE() + 12;

