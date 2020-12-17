/*
	1. Write a SELECT statement that returns four columns from the Invoices table: 
	InvoiceNumber, InvoiceDate, InvoiceDueDate, and InvoiceTotal. Use AP database.
*/
SELECT InvoiceNumber, InvoiceDate, InvoiceDueDate, InvoiceTotal
FROM AP.dbo.Invoices;


/*
	2. Write a SELECT statement that returns three columns from the Invoices table, named Number, Total,
	and Credits: 
		Number 		Column alias for the InvoiceNumber column
		Total 		Column alias for the InvoiceTotal column
		Credits 	Column alias for the sum of the PaymentTotal and CreditTotal columns
	And filter for invoices with an InvoiceTotal that’s less or equal to $300. Use AP database.			
*/
SELECT InvoiceNumber AS Number, InvoiceTotal AS Total,
	PaymentTotal + CreditTotal AS Credits
FROM AP.dbo.Invoices
WHERE InvoiceTotal <= 300;


/*
	3. Write a SELECT statement that returns one column from the Vendors table named “Full Name”. 
	Create this column from the VendorContactFName and VendorContactLName columns. 
	Format it as follows: last name, comma, first name. 
	Sort the result set by last name from “Z-A”. Use AP database.
*/
SELECT VendorContactLName + ',' + VendorContactFName AS "Full Name"
FROM Examples.dbo.Vendors
ORDER BY VendorContactLName DESC;


/*
	4. Write a SELECT statement that determines whether the PaymentDate column of the Invoices table has any valid values. 
	To be valid, PaymentDate must be a null value if there is a balance due and a non-null value of there is no balance due. 
	Code a compound condition in the WHERE clause that tests for these conditions. (Balance: InvoiceTotal minus the sum of PaymentTotal and CreditTotal). 
	Use AP database.
*/
SELECT PaymentDate, InvoiceTotal - PaymentTotal - CreditTotal AS Balance
FROM AP.dbo.Invoices
WHERE (InvoiceTotal - PaymentTotal - CreditTotal = 0 AND PaymentDate IS NOT NULL) OR
		(InvoiceTotal - PaymentTotal - CreditTotal > 0 AND PaymentDate IS NULL);


/*
	5. Write a SELECT statement that returns five columns: VendorName, VendorCity, VendorZipCode, DefaultAccountNo 
	and AccountDescription from the Vendors table and GLAccounts table. The result set should have one row for each vendor, 
	with the city, zipcode, account number and account description for that vendor’s default account number. 
	And filter for Vendors whose AccountDescription is ‘Other Equipment’ and sort the result set by VendorCity from Z to A. Use AP database.
*/
SELECT VendorName, VendorCity, VendorZipCode, DefaultAccountNo, AccountDescription
FROM AP.dbo.Vendors JOIN AP.dbo.GLAccounts
	ON Vendors.DefaultAccountNo = GLAccounts.AccountNO
WHERE AccountDescription = 'Other Equipment'
ORDER BY VendorCity DESC;


/*
	6. Write a SELECT statement that returns two columns from ContactUpdates table: FirstName and Full Name (A concatenation of FirstName and LastName, with a comma in between). 
	The result set should have one row for each vendor whose contact has the same last name as another vendor’s contact. 
	Sort the final result set by FirstName from A to Z. Are there such vendors? Use AP database.
*/
SELECT DISTINCT x.FirstName, x.LastName+','+X.FirstName AS 'Full Name'
FROM AP.dbo.ContactUpdates AS x JOIN AP.dbo.ContactUpdates AS y
	ON x.VendorID <> y.VendorID AND x.LastName = y.LastName
ORDRE BY x.FirstName;


/*
	7. Use the UNION operator to generate a result set consisting of two columns from the Vendors table: VendorName and VendorState. 
	If the vendor is in California, the VendorState value should be “CA”; otherwise, the vendorState value should be “Not in CA”. 
	Sort the final result set by VendorName from A to Z. Use AP database.
*/
	SELECT VendorName, VendorState
	FROM AP.dbo.VendorState
	WHERE VendotState = 'CA'
UNION
	SELECT VendorName, 'Not in CA'
	FROM AP.dbo.VendorState
	WHERE VendotState <> 'CA'
ORDER BY VendorName;


/*
	8. Write a SELECT statement that returns a column from the OrderDetails table: ItemID. 
	'The result set should have one row for each item whose order was placed but not yet shipped (i.e. ShippedDate in Orders table has null value). 
	Use ProductOrders database.
*/
SELECT ItemID
FROM ProductOrders.dbo.Orders LEFT JOIN ProductOrders.dbo.OrderDetails
	ON Orders.OrderID = OrderDetails.OrderID
WHERE ShippedDate IS NULL;
























