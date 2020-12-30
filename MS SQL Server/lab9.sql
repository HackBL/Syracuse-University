/*
	1. Create a stored procedure named spBalanceRange that accepts three optional parameters. 
	The procedure should return a result set consisting of VendorName, InvoiceNumber, 
	and Balance for each invoice with a balance due, sorted with smallest balance due first. 
	The parameter @VendorVar is a mask that’s used with a LIKE operator to filter by vendor name. 
	@BalanceMin and @BalanceMax are parameters used to specify the requested range of balances due. 
	If called with no parameters or with a maximum value of 0, the procedure should return all invoices with a balance due.
*/
USE [AP];
GO

CREATE PROC spBalanceRange
	@VendorVar	varchar(40) = '%',
	@BalanceMin money = 0,
	@BalanceMax money = 0
AS
IF @BalanceMax = 0
	SELECT @BALANCEMAX = MAX(InvoiceTotal - CreditTotal - PaymentTotal) FROM Invocies;

SELECT VendorName, InvoiceNumber, InvoiceTotal-CreditTotal-PaymentTotal AS Balance
FROM Vendors JOIN Invoices
	ON Vendors.VendorID = Invoices.VendorID
WHERE VendorName LIKE @VendorVar AND 
	(InvoiceTotal-CreditTotal-PaymentTotal) > 0 AND
	(InvoiceTotal-CreditTotal-PaymentTotal) BETWEEN @BalanceMin AND @BalanceMax
ORDER BY Balance ASC;


/*
	2. Code three calls to the procedure created in question 1:
*/
-- a. passed by position with @VendorVar = ‘C%’ and no balance range
EXEC spBalanceRange 'C%';

-- b. passed by name with @VendorVar omitted and a balance range from $300 to $600
EXEC spBalanceRange @BalanceMin = 300, @BalanceMax = 600; 

-- c. passed by position with a balance due from $50 to $250, filtering for vendors whose names begin with A or B
EXEC spBalanceRange '[A,B]%', 50, 250;  


/*
	3. Create a stored procedure named spDateRange that accepts two parameters, @DateMin and @DateMax, with data type varchar and default value null. 
	If called with no parameters or with null values, raise an error that describes the problem. If called with non-null values, validate the parameters. 
	Test that the literal strings are valid dates and test that @DateMin is earlier than @DateMax. If the parameters are valid, 
	return a result set that includes the InvoiceNumber, InvoiceDate, InvoiceTotal, and Balance for each invoice for which the InvoiceDate is within the date range, 
	sorted with earliest invoice first.
*/
CREATE PROC spDateRange
	@DateMin varchar(50) = NULL,
	@DateMax varchar(50) = NULL
AS
IF @DateMin IS NULL OR @DateMax IS NULL
	THROW 50001, 'Error due to @DateMin and @DateMax require non-null values!', 1;
IF NOT(ISDATE(@DateMin) = 1 AND ISDATE(@DateMax)= 1) 
	THROW 50001, 'Error due to the format is invalid!', 1;
IF CAST(@DateMin AS datetime) > CAST(@DateMax AS datetime)
	THROW 50001, 'Error due to @DateMin is later than @DateMax!', 1;
-- ELSE everything is valid
SELECT InvoiceNumber, InvoiceDate, InvoiceTotal, 
		(InvoiceTotal-CreditTotal-PaymentTotal) AS Balance
FROM Invoices
WHERE InvoiceDate BETWEEN @DateMin AND @DateMax
ORDER BY InvoiceDate ASC;


/*
	4. Code 
	These calls should also catch any errors that are raised by the procedure and print the error number and description.
*/
-- (1) A call to the stored procedure created in question 3 that returns invoices with an InvoiceDate between December 10 and December 31, 2015, 
BEGIN TRY
	EXEC spDateRange @DateMin = '12/10/2015', @DateMax = '12/31/2015';
END TRY
BEGIN CATCH
	PRINT 'An Error Occurred!'
	PRINT 'Error number: ' + CONVERT(varchar, ERROR_NUMBER());
	PRINT 'Error message: ' + CONVERT(varchar, ERROR_MESSAGE());
END CATCH;


-- (2) A call to the stored procedure again that returns invoices with an @DateMin is December 10. 
BEGIN TRY
	EXEC spDateRange '12/10/2015', '';
END TRY
BEGIN CATCH
	PRINT 'An Error Occurred!'
	PRINT 'Error number: ' + CONVERT(varchar, ERROR_NUMBER());
	PRINT 'Error message: ' + CONVERT(varchar, ERROR_MESSAGE());
END CATCH;


/*
	5. Create a scalar-valued function named fnUnpaidInvoiceID that returns the InvoiceID of the latest invoice with an unpaid balance. 
	Test the function in the following SELECT statement:

	SELECT VendorName, InvoiceNumber, InvoiceDueDate, InvoiceTotal - CreditTotal - PaymentTotal AS Balance
	FROM Vendors JOIN Invoices
	ON Vendors.VendorID = Invoices.VendorID 
	WHERE InvoiceID = dbo.fnUnpaidInvoiceID();
*/
USE [AP];
GO

CREATE FUNCTION fnUnpaidInvoiceID()
	RETURNS int
BEGIN 
	RETURN (SELECT InvoiceID FROM Invoices
			WHERE InvoiceTotal-CreditTotal-PaymentTotal > 0 AND
				InvoiceDate = (SELECT MAX(InvoiceDate) FROM Invoices
								WHERE InvoiceTotal-CreditTotal-PaymentTotal > 0))
END;


/*	
	6. Create a table-valued function named fnDateRange, similar to the stored procedure of question 3. 
	The function requires two parameters of data type smalldatetime. Don’t validate the parameters. 
	Return a result set that includes the InvoiceNumber, InvoiceDate, InvoiceTotal, 
	and Balance for each invoice for which the InvoiceDate is within the date range. 
	Invoke the function from within a SELECT statement to return those invoices with InvoiceDate between January 10 and January 15, 2016.
*/
USE [AP];
GO

CREATE FUNCTION fnDateRange
	(@DateMin smalldatetime,
	 @DateMax smalldatetime)
	 RETURNS TABLE
RETURN
(SELECT InvoiceNumber, InvoiceDate, InvoiceTotal, 
		InvoiceTotal-CreditTotal-PaymentTotal AS Balance
FROM Invoices
WHERE InvoiceDate BETWEEN @DateMin AND @DateMax);


SELECT * 
FROM dbo,fnDateRange('1/10/2016', '1/15/2016');


/*
	7. Use the function you created in question 6 in a SELECT statement that returns five columns: 
	VendorCity and the four columns returned by the function.
*/
SELECT VendorCity, RangeTable.*
FROM Vendors JOIN Invoices
	On Vendors.VendorID = Invoices.VendorID
JOIN dbo.fnDateRange('1/10/2016', '1/15/2016') AS RangeTable
	ON Invoices.InvoiceNumber = RangeTable.InvoiceNumber;



