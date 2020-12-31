/*
	1. Write a script that creates a user-defined database role named PaymentEntry in the AP database. 
	Give UPDATE permission to the new role for the Vendors and Invoices table, 
	UPDATE and INSERT permission for the InvoiceLineItems table, and SELECT permission for all user tables. 
*/
USE AP;

CREATE ROLE PaymentEntry;

GRANT UPDATE ON Vendors TO PaymentEntry;

GRANT UPDATE ON Invoices TO PaymentEntry;

GRANT UPDATE, INSERT ON InvoiceLineItems TO PaymentEntry;

ALTER ROLE db_datareader ADD MEMBER PaymentEntry;


/*
	2.	Write a script that 
	(1) creates a login ID named “Fall2020” with the password “123456”; 
	(2) sets the default database for the login to the AP database; 
	(3) creates a user named “Robert” for the login; and 
	(4) assigns the user to the PaymentEntry role you created in question 1
*/
USE AP;

CREATE LOGIN Fall2020 WITH PASSWORD = '123456',
DEFAULT_DATABASE = AP;

CREATE USER Robert FOR LOGIN Fall2020;

ALTER ROLE PaymentEntry ADD MEMBER Robert;
