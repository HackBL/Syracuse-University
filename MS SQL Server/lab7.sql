/*
	1. Create a new database named Shopping.
*/
CREATE DATABASE Shopping;


/*
	2. (1) Describe the relationship type shown in figure (one-to-one, one-to-many or many-to-many). 
*/
--Customers - products: many-to-many
--CustomerGroups is a linking table

/*
	2. (2) Write the CREATE TABLE statements needed to implement the following design in the Shopping database. 
	   Include foreign key constraints. Define CustomerID and ProductID as identity columns. 
	   Decide which columns should allow null values, if any, and explain your decision. 
	   Define the ProductCost column with a default of zero and a check constraint to allow only positive values.
*/
USE [Shopping]

CREATE TABLE Customers
(CustomerID	int			NOT NULL	IDENTITY	PRIMARY KEY,
FirstName	VARCHAR(50)	NOT NULL,
LastName	varchar(50)	NOT NULL,
Phone		varchar(50)	NULL);


CREATE TABLE Products
(ProductID	int			NOT NULL	IDENTITY	PRIMARY KEY,
ProductName	varchar(50)	NOT NULL,
ProductCost	money		NOT NULL	DEFAULT 0	CHECK(ProductCost>0));


CREATE TABLE CustomerGroups
(CustomerID	int	NOT NULL
				REFERENCES Customers(CustomerID),
ProductID	int	NOT NULL
				REFERENCES Products(ProductID)); 


/* 
	3. Write the CREATE INDEX statements to create a clustered index 
	on the ProductID column and a nonclustered index on the CustomerID column of the CustomerGroups table.
*/
USE [Shopping]

CREATE CLUSTERED INDEX IX_ProductID
					ON CustomerGroups(ProductID);

CREATE NONCLUSTERED INDEX IX_CustomerID
					ON CustomerGroups(CustomerID);


/*
	4. Write an ATER TABLE statement that adds a new column, BillsPaid, to the Customers table. Use the bit data type, 
	disallow null values, and assign a default Boolean value of False.
*/
USE [Shopping]

ALTER TABLE Customers
ADD BillsPaid	bit		NOT NULL	DEFAULT 0;


/*
	5. Write an ALTER TABLE statement that adds two new check constraints to the Invoices table (in AP database) of the AP database. 
	The first should allow 
	(1) PaymentDate to be null only if PaymentTotal is zero and 
	(2) PaymentDate to be not null only if PaymentTotal is greater than zero. 
	The second constraint should prevent the sum of PaymentTotal and CreditTotal from being greater than InvoiceTotal.

*/
USE [AP]

ALTER TABLE Invoices
ADD CHECK((PaymentDate IS NULL AND PaymentTotal = 0) 
	OR (PaymentDate IS NOT NULL AND PaymentTotal > 0)),

	CHECK((PaymentTotal + CreditTotal) <= InvoiceTotal);


/*
	6. Delete the CustomerGroups table from the Shopping database. 
	Then, write a CREATE TABLE statement that recreates the table, 
	this time with a unique constraint that prevents a customer from being a customer-group member buying same product twice.
*/
USE [Shopping]
DROP TABLE CustomerGroups;

CREATE TABLE CustomerGroups
(CustomerID	INT NOT NULL	
				REFERENCES Customers(CustomerID),
ProductID	INT	NOT NULL
				REFERENCES Products(ProductID),
UNIQUE(CustomerID, ProductID));




