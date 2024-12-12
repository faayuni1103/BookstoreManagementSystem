/******************************************************************************************/
/* Mini Project (Implementation of Stack and Queue)                                       */
/* Topic: Bookstore Management System                                                     */
/*                                                                                        */
/* Members:                                                                               */
/*                                                                                        */
/* [Section 10]                                                                           */
/* Fatin Aimi Ayuni Binti Affindy (A20EC0190)                                             */
/* Bilkis Musa (A20EC0233)                                                                */
/*                                                                                        */
/* [Section 11]                                                                           */
/* Amirah Binti Zulkifli (A20EC0012)                                                      */
/* Nurin Sofiya Binti Rosle (A20EC0124)                                                   */
/* Nur Dinie Sajeeda Binti Azman (A20EC0112)                                              */
/*                                                                                        */
/* NOTES:                                                                                 */
/* - THIS SYSTEM REQUIRES THE USER TO RUN IN A FULL SCREEN                                */
/* - CUSTOMER WILL RECEIVE AN INVOICE IN TXT FORMAT AFTER SUCCESSFULLY PURCHASE THE BOOKS */
/* - TO ENTER AS A MEMBER, PLEASE REFER TO THE MAIN FUNCTION FOR THE MEMBERS DECLARED     */
/* - STAFF MAY PRINT SALES REPORT IN TXT FORMAT                                           */
/* - TO ENTER AS A STAFF, PLEASE REFER TO THE MAIN FUNCTION FOR THE STAFF DECLARED        */
/******************************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <cstring>

using namespace std;

class PaymentSystem 
{
	private:
		double pay;
		double amount;
		
	public:
		void setValue(double a, double p) // to set the values inside the variables
		{
			amount = a;
			pay = p;
		}
		
		// to return the values in the variables
		double getAmount() { return amount; }
		double getPay() { return pay; }
};

class Order
{
	private:
		PaymentSystem *paymentsystem;
		string orderId;
		string status;
		
	public:
		Order()
		{
			orderId = "A200012";
			status = "Paid";
			paymentsystem = NULL;
		}
		
		void checkout(PaymentSystem *donePay, double a) // to proceed with checkout and calculate payment
		{
			double p;
			paymentsystem = donePay;
			
		
			cout << "\n\t\t\t Please enter payment amount: RM";
			cin >> p;
			cout << "\n\t\t\t Calculating..... Please wait";
			Sleep(3000);
			
			paymentsystem->setValue(a, p);
			
			if(p>a)
			{
				cout << "\n\n\t\t\t Your balance: RM" << paymentsystem->getPay() - paymentsystem->getAmount();
				cout << "\n\t\t\t Your balance will be credited to your account!\n\n\t\t\t " ;
			}
			else if (p==a)
				cout << "\n\n\t\t\t Your order is successful!\n\n\t\t\t " ;
			else
			{
				cout << "\n\n\t\t\t You enter the wrong amount! You will be terminated from this program\n\t\t\t Thank you! ";
				exit(0);
			}
				
			system("pause");
		}
				
		// to return the values in the variables		
		string getId() { return orderId; }
		string getStatus() { return status; }
};

class Book
{
	private: 
		int bookId;
		string bookTitle;
		string bookAuthor;
		double bookPrice;
		int bookQuantity;
		int buyQuantity;
	
	public:
		Book* next;
		Book(int id, string title, string author, double price, int quantity)
		{
			bookId = id;
			bookTitle = title;
			bookAuthor = author;
			bookPrice = price;
			bookQuantity = quantity;
		}
		// to return the values in the variables	
		int getId() { return bookId; }
		string getTitle() { return bookTitle; }
		string getAuthor () { return bookAuthor;}
		double getPrice() { return bookPrice; }
		int getQuantity() {	return bookQuantity; }
		int getBuyQuantity() { return buyQuantity; }
		
		// to set the values inside the variables
		void setId(int id) { bookId = id; }
		void setTitle(string title) { bookTitle = title; }
		void setAuthor(string author) { bookAuthor = author; }
		void setPrice(double price) { bookPrice = price; }
		void setQuantity(int qty) { bookQuantity = qty; }
		void setBuyQuantity(int q) { buyQuantity = q; }
		
		// to update the variables
		void updateQuantity() { bookQuantity -= buyQuantity; }		
		void updateStock(int s) { bookQuantity += s; }
		void updatePrice(int p) { bookPrice -= (p*bookPrice/100); }

		void displayBook() // to display book's details
		{
			cout << "\t\t\t" << left << setw(14) << bookId << setw(34) << bookTitle << setw(21) 
				 << bookAuthor << setw(24) << fixed << setprecision(2) << bookPrice << setw(17) << bookQuantity << endl;
		}
		
};

class BookList // Implementation of Stack using Linked List that contain
{			   // the list of books in the store.
	private:
		Book *topBook;
		
	public:
		BookList() { topBook = NULL; }
		
		void getdata(ifstream& infile) // to read book data from input file
		{ 	
			int tempid, tempquantity;
			string temptitle, tempauthor;
			float tempprice;
			
			infile >> tempid;
			infile.ignore();
			getline(infile, temptitle);
			getline(infile, tempauthor);
			infile >> tempprice >> tempquantity;
			
			Book *currBook = new Book(tempid, temptitle, tempauthor, tempprice, tempquantity);
			
			if(topBook == NULL)
				topBook = currBook;
			else
			{
				currBook->next = topBook;
				topBook = currBook;
			}
			
		}
		
		int searchId(int i) // to perform searching using the book ID
		{
			Book *currBook = topBook;
			int index = 1;
			while(currBook != NULL && currBook->getId() != i)
			{
				currBook = currBook->next;
				index++;
			}
			
			if (currBook)
				return index;
			else
				return 0;
		}
		
		int searchTitle(string t) // to perform searching using the book title
		{
			Book *currBook = topBook;
			int index = 1;
			while(currBook != NULL && currBook->getTitle() != t)
			{
				currBook = currBook->next;
				index++;
			}
			
			if (currBook)
				return index;
			else
				return 0;
		}
		
		int searchAuthor(string a) // to perform searching using the book author
		{
			Book *currBook = topBook;
			int index = 1;
			while(currBook != NULL && currBook->getAuthor() != a)
			{
				currBook = currBook->next;
				index++;
			}
			
			if (currBook)
				return index;
			else
				return 0;
		}
		
		void displayList() // to display the list of the book
		{
			Book *currBook = topBook;
			
			cout << "\n\t\t\tHere are the available books: " << endl << endl 
		 		 << "\t\t\t--------------------------------------------------------------------------------------------------------" << endl;
			cout << "\t\t\t" << left << setw(14) << "Book ID" << setw(34) << "Title" << setw(19) << "Author"
				 << setw(20) << "Price(RM)" << setw(17) << "Quantity In Stock" << endl;
			cout << "\t\t\t--------------------------------------------------------------------------------------------------------" << endl;
						
			while (currBook != NULL)
			{
				currBook->displayBook();
				currBook = currBook->next;
			}
				
			cout << "\t\t\t--------------------------------------------------------------------------------------------------------" << endl << endl << "\t\t\t";

		}
		
		void update(string t, int q) // to update the quantity in stock after the customer
		{							 // add a specific book into cart
			Book *currBook = topBook;
			while(currBook && currBook->getTitle() != t)
				currBook = currBook->next;
			currBook->setBuyQuantity(q);
			currBook->updateQuantity();
		}
		
		Book *compareId(int id) // to compare the book ID and return
		{						// the node pointer containing similar book ID
			Book *currBook = topBook;
			while(currBook && currBook->getId() != id)
				currBook = currBook->next;
			return currBook;
		}

		Book *compareTitle(string t) // to compare the book title and return 
		{							 // the node pointer containing similar book title
			Book *currBook = topBook;
			while(currBook && currBook->getTitle() != t)
				currBook = currBook->next;
			return currBook;
		}
		
		Book *compareAuthor(string a) // to compare the book author and return
		{							  // the node pointer containing similar book author
			Book *currBook = topBook;
			while(currBook && currBook->getAuthor() != a)
				currBook = currBook->next;
			return currBook;
		}
		
		void addNewBook(int id, string title, string author, float price, int qty) // to add new book into system
		{																		   // using the values entered by staff
			Book *currBook = new Book(id, title, author, price, qty);
			
			if(topBook == NULL)
				topBook = currBook;
			else
			{
				currBook->next = topBook;
				topBook = currBook;
			}
		}

		void addStock(int id) // to add stocks into particular book
		{
			int x;
			Book *currBook = topBook;
			while(currBook && currBook->getId() != id)
				currBook = currBook->next;
			
			cout << "\t\t\t Book ID: " << currBook->getId() << endl;
			cout << "\t\t\t Book Title: " << currBook->getTitle() << endl;
			cout << "\t\t\t Book Author: " << currBook->getAuthor() << endl;
			cout << "\t\t\t Book Price: " << currBook->getPrice() << endl;
			cout << "\t\t\t Quantity: " << currBook->getQuantity() << endl;
			cout << "\n\t\t\t Enter the stock you want to add: ";
			cin >> x;
			
			currBook->updateStock(x);
		}
		
		void getDiscount(int id) // to update price of any particular book
		{
			int dis;
			Book *currBook = topBook;
			while(currBook && currBook->getId() != id)
				currBook = currBook->next;
			
			cout << "\t\t\t Book ID: " << currBook->getId() << endl;
			cout << "\t\t\t Book Title: " << currBook->getTitle() << endl;
			cout << "\t\t\t Book Author: " << currBook->getAuthor() << endl;
			cout << "\t\t\t Book Price: " << currBook->getPrice() << endl;
			cout << "\t\t\t Quantity: " << currBook->getQuantity() << endl;
			cout << "\n\t\t\t Enter the discount you want to give (in %): ";
			cin >> dis;
			
			currBook->updatePrice(dis);
		}
		
		void bookSort() // to sort the book according to the book ID 
		{				// in ascending order using Selection Sort
			Book *outerBook, *innerBook, *tempBook;
			int tempid, tempqty;
			string temptitle, tempauthor;
			double tempprice;
			
			for(outerBook = topBook; outerBook->next != NULL; outerBook = outerBook->next)
			{
				for(innerBook = outerBook->next; innerBook != NULL; innerBook = innerBook->next)
				{
					if(outerBook->getId() > innerBook->getId())
					{
						tempid = innerBook->getId();							//-----------------
						innerBook->setId(outerBook->getId());					//
						outerBook->setId(tempid);								//
																				//
						temptitle = innerBook->getTitle();						//
						innerBook->setTitle(outerBook->getTitle());				//
						outerBook->setTitle(temptitle);							// 
																				// This section of coding
						tempauthor = innerBook->getAuthor();					// will be used
						innerBook->setAuthor(outerBook->getAuthor());			// to swap the data
						outerBook->setAuthor(tempauthor);						//
																				//
						tempprice = innerBook->getPrice();						//
						innerBook->setPrice(outerBook->getPrice());				//
						outerBook->setPrice(tempprice);							//
																				//
						tempqty = innerBook->getQuantity();						//
						innerBook->setQuantity(outerBook->getQuantity());		//
						outerBook->setQuantity(tempqty);						//-----------------
					}
				}
			}
			displayList();
		}
		
		void readBook(Book *b, int q) // to read the data of the book that has been sold
		{
			Book *currBook = new Book(b->getId(), b->getTitle(), b->getAuthor(), b->getPrice(), b->getQuantity());
			Book *tempBook;
			currBook->setBuyQuantity(q);
			if(topBook == NULL)
				topBook = currBook;
			else
			{
				currBook->next = topBook;
				topBook = currBook;
			}
		}
		
		void printReport(ofstream& out) // to print sales report
		{
			double earned=0.0;
			Book *currBook = topBook;
			out << "\t\t\t -------------------------------\n" << "\t\t\t  Bright Bookstore Sales Report \n" << "\t\t\t -------------------------------\n\n";
			out << left << setw(15) << "\t\t\t Book ID" << setw(28) << "Title" << setw(19) << "Author"
				<< setw(15) << "Price(RM)" << setw(18) << "Quantity Sold" << setw(12) << "Sales(RM)" << "Total Earned(RM)\n";
			
			while (currBook != NULL)
			{
				out << "\t\t\t " << left << setw(11) << currBook->getId() << setw(28) << currBook->getTitle() << setw(21) << currBook->getAuthor()
				<< fixed << setprecision(2) << setw(18) << currBook->getPrice() << setw(14) << currBook->getBuyQuantity() << setw(15) 
				<< (currBook->getPrice()*currBook->getBuyQuantity()) << (30*(currBook->getPrice()*currBook->getBuyQuantity())/100) << endl;
				
				earned += (30*(currBook->getPrice()*currBook->getBuyQuantity())/100);
				currBook = currBook->next;
			}
			out << "\n\t\t\t Total earned: RM" << earned;
			out << "\n\n\t\t\t Notes: \n" << "\t\t\t - Total earned is 30% of sales generated by the books" 
				<< "\n\t\t\t - Sales are total amount of sold books times the price\n";
		}
};

class ShoppingCart // Implementation of Queue using Linked List that contain
{				   // the list of books in the shopping cart.
	private:
		int numBook;
		double amount;
		Book *frontBook;
		Book *backBook;
				
	public:
		ShoppingCart() 
		{ 
			numBook = 0; 
			amount = 0.0;
			frontBook = NULL;
			backBook = NULL;
		}
		
		void addCartBook(Book *b, int q) // to add book to the cart
		{
			Book *currBook = new Book(b->getId(), b->getTitle(), b->getAuthor(), b->getPrice(), b->getQuantity());
			
			if(frontBook == NULL && backBook == NULL)
			{
				frontBook = currBook;
				backBook = currBook;
			}
			else
			{
				backBook->next = currBook;
				backBook = currBook;
			}
			currBook->setBuyQuantity(q);
			currBook->updateQuantity();
		}
		
		void viewCartBook() // to display the shopping cart
		{
			Book *currBook = frontBook;
			amount = 0.0;
			
			cout << "\n\t\t\tThese are your books in the cart: " << endl << endl 
			 	 << "\t\t\t--------------------------------------------------------------------------------------------------------" << endl;
			cout << "\t\t\t" << left << setw(14) << "Book ID" << setw(27) << "Title" << setw(19) << "Author"
				 << setw(15) << "Price(RM)" << setw(15) << "Quantity" << setw(15) << "Amount(RM)" << endl;
			cout << "\t\t\t--------------------------------------------------------------------------------------------------------" << endl;
	
			while (currBook != NULL)
			{				
				cout << "\t\t\t" << left << setw(14) << currBook->getId() << setw(27) << currBook->getTitle() << setw(21) << currBook->getAuthor() 
					 << setw(16) << fixed << setprecision(2) << currBook->getPrice() << setw(14) << currBook->getBuyQuantity() 
					 << setw(10) << currBook->getPrice()*currBook->getBuyQuantity() << endl;
			    
			    amount += currBook->getPrice()*currBook->getBuyQuantity();
			    currBook = currBook->next;
			}
			
			cout << "\t\t\t--------------------------------------------------------------------------------------------------------" << endl << endl;
		}
		
		void printInvoice(ofstream &outfile) // to print list of books bought by the customer
		{									 // into the invoice txt file
			Book *currBook = frontBook;
			
			outfile << "\n\t\t\t\tThese are the books you bought: " << endl << endl 
			 	    << "\t\t\t\t--------------------------------------------------------------------------------------------------------" << endl;
			outfile << "\t\t\t\t" << left << setw(14) << "Book ID" << setw(27) << "Title" << setw(19) << "Author"
				 	<< setw(15) << "Price(RM)" << setw(15) << "Quantity" << setw(15) << "Amount(RM)" << endl;
			outfile << "\t\t\t\t--------------------------------------------------------------------------------------------------------" << endl;
			
			while (currBook != NULL)
			{
				outfile << "\t\t\t\t" << left << setw(14) << currBook->getId() << setw(27) << currBook->getTitle() << setw(21) << currBook->getAuthor() 
					    << setw(16) << fixed << setprecision(2) << currBook->getPrice() << setw(14) << currBook->getBuyQuantity() 
					    << setw(10) << currBook->getPrice()*currBook->getBuyQuantity() << endl;
				currBook = currBook->next;
			}
			outfile << "\t\t\t\t--------------------------------------------------------------------------------------------------------" << endl << endl << "\t\t\t\t";
		}
		
		// to return the values in the variables
		double getAmount() { return amount; }
};

class Customer
{
	protected:
		string name;
		string address;
		string email;
		string phone;
		double discount;
		Order order;
		ShoppingCart shopcart;
	
	public:
		Customer(){}
		Customer(string n, string a, string e, string p)
		{
			name = n;
			address = a;
			email = e;
			phone = p;
			discount = 0.0;
		}
		void invoice() // to print customer's invoice in txt file
		{
			ofstream outfile;
			outfile.open("CustomerInvoice.txt");
			
			outfile << "\n\n\t\t\t\t--------------------------------------------------------------------------------------------------------";
			outfile << "\n\t\t\t\t\t\t\t\t WELCOME TO BRIGHT BOOKSTORE\t\t\t" << endl;
			outfile << "\t\t\t\t--------------------------------------------------------------------------------------------------------";
			outfile << "\n\t\t\t\t <<< CUSTOMER INVOICE >>>";
			outfile << "\n\n\t\t\t\t Order Id: " << order.getId() << endl;
			outfile << "\t\t\t\t Name: " << name << endl;
			outfile << "\t\t\t\t Address: " << address << endl;
			outfile << "\t\t\t\t Email: " << email << endl;
			outfile << "\t\t\t\t Phone: " << phone << endl;
			outfile << "\t\t\t\t Status: " << order.getStatus() << endl;
			
			shopcart.printInvoice(outfile);
			
			outfile << "\n\t\t\t\t Book Subtotal: RM" << shopcart.getAmount() << endl;
			outfile << "\t\t\t\t Discount: RM" << discount << endl;
			outfile << "\t\t\t\t Total: RM" << shopcart.getAmount() - discount << endl << endl;
		}
		
		// to proceed with checkout and payment of the book(s) in the cart
		void checkOut(double a, PaymentSystem *newPay) { order.checkout(newPay, a); }
		
		// to add book into the cart
		void addBook(Book *book, int qty) { shopcart.addCartBook(book, qty); }
		
		// to review the cart
		void viewCart() { shopcart.viewCartBook(); }
		
		// to return the values in the variables
		double shopAmount() { return shopcart.getAmount(); }
		
		virtual double getDiscount()=0;
};

class Staff
{
	protected:
		string StaffID;
		string StaffPassword;
		string sname;
		string sAddress;
		string sEmail;
		string sPhone;
		
	public:
		Staff(string ID, string pass, string SN, string SA, string SE, string SP)
		{
			StaffID = ID;
			StaffPassword = pass;
			sname=SN;
			sAddress=SA;
			sEmail=SE;
			sPhone=SP;
		}
		
		void verifyLogin() // verify staff's login
		{
			cout << "\n\t\t\t Your login is successful\n"; 
			cout << "\t\t\t Welcome " << StaffID << "!\n" << endl << "\t\t\t ";
			system("pause");
		}
		
		// to return the values in the variables
		string getStaffID() { return StaffID; }
		string getPassword() { return StaffPassword; }
		
};

class Member : public Customer
{
	private:
		string username;
		string password;		
	public:
		Member(string Um, string Pm, string N, string A, string E, string P) : Customer(N, A, E, P)
		{
			username=Um;
			password=Pm;
			name=N;
			address=A;
			email=E;
			phone=P;
		}
		
		void verifyLogin() // to verify the member login
		{
			cout << "\n\n\t\t\t Login verified!\n";
			cout << "\t\t\t Welcome " << username << "!\n";
			cout << "\t\t\t CONGRATULATION! You received RM10 capped off during check out!" << endl << endl << "\t\t\t ";
			system("pause");
		}
		
		double getDiscount() // return default discount for member
		{ 
			discount = 10.00; 
			return discount;
		}
		
		// to return the values in the variables
		string getUsername() { return username; }
		string getPassword() { return password; }
};

class Guest : public Customer
{		
	public:
		double getDiscount() // return default discount for guest
		{ 
			discount = 2.00; 
			return discount;
		}
		
		void registerProfile() // register guest's information
		{
			cin.ignore();
			cout << "\t\t\t Please enter the following detail:" << endl;
			cout << "\t\t\t Name: ";
			getline(cin,name);			
			cout << "\t\t\t Address: ";
			getline(cin, address);
			cout << "\t\t\t Email: ";
			getline(cin, email);
			cout << "\t\t\t Phone: ";
			getline(cin, phone);
			cout << endl << "\t\t\t CONGRATULATION! You received RM2 capped off during check out!" << endl << endl << "\t\t\t ";
			system("pause");
		}
};

void thankMessage();
void welcome();
void chooseBook(Customer*, BookList);
void manageBook(Staff*, BookList);
void printReport(BookList);
int chooseUser();
int customerMenu();
int staffMenu();
Staff* loginStaff(Staff[]);
Customer* chooseCustomer(Member[], Guest*);

int main()
{
	BookList bookList;
	Guest *G = new Guest;
	Customer *c;
	Staff *s;
	int user;
	
	// Bookstore member declaration
	Member member[5] = { Member("laskarpelangi", "laskar123pp", "Ahmad Ali Bin Abu", "Tawau, Sabah", "ahmali@gmail.com", "0102345678"), 
						 Member("winmetawin", "wincharlott55", "Win Metawin O.", "Bintulu, Sarawak", "metawin@gmail.com", "0187236956"), 
						 Member("donutcoklat", "donutsedap123", "Tan Jia Chua", "Muar, Johor", "jiachua@gmail.com", "0133344456"), 
						 Member("bookwormy", "ulatbuku123", "Mark Johnsonn", "Seremban, Negeri Sembilan", "markj@gmail.com", "0145557654"),
						 Member("yogaemily", "yoga123emi", "Emily Clarke", "Sabak Bernam, Selangor", "emilyclarke@gmail.com", "0198769765")};
	
	// Bookstore staff declaration					 
	Staff staff[5] = { Staff("amrhzulkfl", "mirah18A", "Amirah binti Zulkifli","Jitra, Kedah", "amirahzulkifli27@gmail.com", "0136878707"),
	                   Staff("Aqifzul", "aqiful123", "Muhammad Aqif bin Zulhilmi","Skudai, Johor", "aqiful@gmail.com", "0132456789"),
					   Staff("chronic1d98", "tetikus98", "Nur Dinie Sajeeda binti Azman", "Pasir Puteh, Kelantan", "nurdinie@gmail.com", "01110862706"),
					   Staff("anaslee", "lee0580", "Anas Lee","Arau, Perlis", "anaslee@gmail.com", "01110562796"),
					   Staff("arfanazz", "arfa123", "Arfa nazeeha binti Amin","Jitra, Kedah", "arfanaz@gmail.com", "012567893")};
	
	ifstream infile("BookData.txt");
	
	// to read the data file and put into the linked list of books
	while(!(infile.eof()))
		bookList.getdata(infile);
	
	user = chooseUser();
	if (user == 1)
	{
		c = chooseCustomer(member, G);
		chooseBook(c, bookList);
	}
	else if (user == 2)
	{
		s = loginStaff(staff);
		manageBook(s, bookList);
	}
	
	infile.close();
	return 0;
}

void thankMessage() // to display thank you message
{
	cout << "\n\n\t\t\t\t\t\t\t ____________________________________\n";
	cout << "\t\t\t\t\t\t\t|                                    |\n";
	cout << "\t\t\t\t\t\t\t| Thank you for choosing our system! |\n";
	cout << "\t\t\t\t\t\t\t|____________________________________|\n";
}

int chooseUser() // function to choose user
{
	int user;
	
	welcome();
	cout << "\n\t\t\t Please choose the following option:" << endl;
	cout << "\t\t\t [1] Enter as Customer" << endl;
	cout << "\t\t\t [2] Enter as Staff" << endl << endl;
	cout << "\t\t\t Enter your choice: ";
	cin >> user;
	cout << endl;
	
	if(user == 1)
		return 1;
	else if(user == 2)
		return 2;
	else
	{
		cout << "\t\t\t\t\t\t Invalid option! Please try again next time!" << endl;
				 cout << "\t\t\t\t\t\t Thank you for choosing our system";
				 exit(0);
	}
}

Staff* loginStaff(Staff staff[]) // function for staff login
{
	string id;
	string pass;
	Staff *s;
	
	cout << "\t\t\t Please enter the following detail:"<<endl;
	cout << "\t\t\t Staff ID: ";
	cin >> id;
	cout << "\t\t\t Password: ";
	cin >> pass;
	
	for(int j=4; j!=0; j--)
	{
		for(int i=0; i<5; i++)
		{
			if((id==staff[i].getStaffID()) && (pass==staff[i].getPassword()))
			{
				staff[i].verifyLogin();
				s = &staff[i];
				return s;
				break;
			}
		}
		
		if(j==1)
		{
			cout << endl << "\t\t\t You have no trial left. Please try again next time. Thank you for choosing our system!" << endl;
			exit(0);
		}
		else
		{
			cout << endl << "\t\t\t You have entered the wrong username or password!" << endl;
			cout << "\t\t\t You have " << (j-1) << " trials!" << endl << endl;
			cout << "\t\t\t Please enter the following detail:" << endl;
			cout << "\t\t\t Staff ID: ";
			cin >> id;
			cout << "\t\t\t Password: ";
			cin >> pass;
		}
		
	}
}

Customer* chooseCustomer(Member member[], Guest *G) // function to choose customer
{
	string user;
	string pass;
	int choice;
	Customer *c;
	
	cout << "\n\t\t\t Please choose the following option:" << endl;
	cout << "\t\t\t [1] Login as Member" << endl;
	cout << "\t\t\t [2] Register as Guest" << endl << endl;
	cout << "\t\t\t Enter your choice: ";
	cin >> choice;
	cout << endl;
	
	switch(choice)
	{
		case 1	:	cout<<"\t\t\t Please enter the following detail:"<<endl;
					cout<<"\t\t\t Username: ";
					cin>>user;
					cout<<"\t\t\t Password: ";
					cin>>pass;
					
					for(int j=4; j!=0; j--)
					{
						for(int i=0; i<5; i++)
						{
							if((user==member[i].getUsername()) && (pass==member[i].getPassword()))
							{
								member[i].verifyLogin();
								c = &member[i];
								return c;
								break;
							}
						}
							
						if(j==1)
						{
							cout << endl << "\t\t\t You have no trial left. Please try again next time. Thank you for choosing our system!" << endl;
							exit(0);
						}
						else
						{
							cout << endl << "\t\t\t You have entered the wrong username or password!" << endl;
							cout << "\t\t\t You have " << (j-1) << " trials!" << endl << endl;
							cout << "\t\t\t Please enter the following detail:" << endl;
							cout << "\t\t\t Username: ";
							cin >> user;
							cout << "\t\t\t Password: ";
							cin >> pass;
						}
							
												
					}
					break;
					
		case 2	:	G->registerProfile();
					c = G;
					return c;
				 	break;
				 	
		default	: 	cout << "\t\t\t Invalid option! Please try again next time!" << endl;
					cout << "\t\t\t Thank you for choosing our system";
				 	exit(0);
	}
}

void welcome() // display welcome banner
{
	system("cls");
	cout << "\n\n\t\t\t--------------------------------------------------------------------------------------------------------";
	cout << "\n\t\t\t\t\t\t\t     WELCOME TO BRIGHT BOOKSTORE\t\t\t" << endl;
	cout << "\t\t\t--------------------------------------------------------------------------------------------------------";
}

int customerMenu() // display menu for customer
{
	int choice;
	welcome();
	cout << "\n\t\t\t Please choose the following option: " << endl;
	cout << "\t\t\t [1] View Book List" << endl;
	cout << "\t\t\t [2] Search Book"<< endl;
	cout << "\t\t\t [3] Buy Book"<< endl;
	cout << "\t\t\t [4] View Shopping Cart" << endl;
	cout << "\t\t\t [5] Proceed to Checkout" << endl;
	cout << "\t\t\t [6] Exit"<< endl;
	
	cout << "\n\t\t\t Enter your choice: ";
	if (!(cin >> choice))
	{
		cin.clear();
		cin.ignore();
	}
		
	return choice;
}

void chooseBook(Customer *cust, BookList bookList) // task option for customer
{
	int choice, search, j, result;
	int qty;
	string title, author;
	Book *book;

	PaymentSystem *payDone = new PaymentSystem;

	do
	{
		do
		{
			choice = customerMenu();
			welcome();
			
			switch(choice)
			{
				case 1 : bookList.displayList();
					     system("pause");
					     break;
				
				case 2 : do
						 {
						 	 cout << "\n\t\t\t Search with: "<< endl;
							 cout << "\t\t\t [1] Title" << endl;
							 cout << "\t\t\t [2] Author" << endl;
							 cout << "\t\t\t Enter your choice: ";
							 if (!(cin >> search))
							 {
								cin.clear();
								cin.ignore();
							 }
							
						     if ( search == 1) // search by book title
							 {
								cout << "\n\t\t\t Enter the book title: ";
								cin.ignore();
								getline (cin, title);
								result = bookList.searchTitle(title); // pass the argument to check whether the book title exist in the store or not
								if (result == 0) 
								   cout << "\n\t\t\t ---We are sorry. The book did not exist in this store---"<< endl;
								else
								{
								   book = bookList.compareTitle(title);
								   cout << "\n\t\t\t -------The following are your details of the book-------"<< endl;
								   cout << "\t\t\t ID: " << book->getId() << "\n\t\t\t Title: "<< book->getTitle() << "\n\t\t\t Author: " << book->getAuthor() 
								   		<< "\n\t\t\t Price: " << book->getPrice() << "\n\t\t\t Stock: " << book->getQuantity() << endl;
								}
								cout <<  "\n\t\t\t ";
							    system("pause");
							 }
							 else if ( search == 2) // search by book author
							 {
								cout << "\n\t\t\t Enter the author's name: ";
								cin.ignore();
								getline(cin, author);
								result = bookList.searchAuthor(author); // pass the argument to check whether the book author exist in the store or not
								if (result == 0)
								   cout << "\n\t\t\t ---We are sorry. The book did not exist in this store----"<< endl;
								else
								{
								   book = bookList.compareAuthor(author);
								   cout << "\n\t\t\t -------The following are your details of the book-------"<< endl;
								   cout << "\t\t\t Book ID: " << book->getId() << "\n\t\t\t Title: "<< book->getTitle() << "\n\t\t\t Author:  " << book->getAuthor()
								   		<< "\n\t\t\t Price: " << book->getPrice() << "\n\t\t\t Stock: " << book->getQuantity() << endl;
								}
								cout << "\n\t\t\t";
								system ("pause");  
							 }
							 else
								cout << "\t\t\t Invalid input! Please try again. ";
						 } while ( search !=1 && search != 2 );
						 break;
	
				case 3 : bookList.displayList();
						 cout << "\n\t\t\t Enter the book you want to buy" << endl;
						 cout << "\t\t\t Book title: ";
						 cin.ignore();
						 getline(cin, title);
						 cout << "\t\t\t Quantity to purchase: ";
						 cin >> qty;
						 book = bookList.compareTitle(title); 		// to pass the pointer containing similar title
					     cust->addBook(book, qty); 					// to add the book into cart
					     bookList.update(title, qty); 				// to update the quantity of the book in the linked list
						 cout << "\n\t\t\t Book is succesfully added to your cart!\n\t\t\t ";
						 system("pause");
						 break;
				
				case 4 : cust->viewCart();  // to display the customer's cart
						 cout << "\n\t\t\t ";
						 system ("pause");
						 break;
				
				case 5 : cust->viewCart();  // to display the customer's cart
					
						 cout << "\t\t\t Book Subtotal: RM" << cust->shopAmount() << endl;
						 cout << "\t\t\t Discount: RM" << cust->getDiscount() << endl;
						 cout << "\t\t\t Total: RM" << (cust->shopAmount() - cust->getDiscount() )<< endl << endl << "\t\t\t ";
						 system("pause");
						
						 cust->checkOut(cust->shopAmount() - cust->getDiscount(), payDone);
						 cout << "\n\t\t\t Printing your invoice.....Please wait";
						 Sleep(2000);
						 cust->invoice();
						 cout << "\n\n\t\t\t Printing done! \n\t\t\t ";
						 system("pause");
						 
						 welcome();
						 thankMessage();		
						 exit(0);
						 
				case 6 : thankMessage();
						 exit(0);
				
				default : cout << "\n\t\t\t Invalid input. Please enter your choice again. \n\t\t\t ";
						  system("pause");
						  break;
			}
			
			
		} while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5);
	}while (choice != 5);
}

int staffMenu() // display menu for staff
{
	int choice;
	welcome();
	cout << "\n\t\t\t Please choose the following option" << endl;
	cout << "\t\t\t [1] Add new book" << endl;
	cout << "\t\t\t [2] Update price" << endl;
	cout << "\t\t\t [3] Add stock" << endl;
	cout << "\t\t\t [4] Sort book" << endl;
	cout << "\t\t\t [5] View book list" << endl;
	cout << "\t\t\t [6] Print report" << endl;
	cout << "\t\t\t [7] Exit" << endl;
	cout << "\n\t\t\t Enter your choice: ";
	if (!(cin >> choice))
	{
		cin.clear();
		cin.ignore();
	}

	return choice;
}

void manageBook(Staff *staff, BookList bookList) // task option for staff
{
	int choice, id, quantity, stock, result;
	string title, author;
	float price, discount;
	
	do
	{
		do
		{
			choice = staffMenu();
			welcome();
			switch (choice)
			{
				case 1: cout << "\n\t\t\t Please enter the books detail"<<endl;       //----------
						cout << "\t\t\t Book ID: ";									  //
						cin >> id;													  //
						cout << "\t\t\t Book title: ";								  //
						cin.ignore();												  // This section will allow 
						getline(cin, title);										  // the staff to enter
						cout << "\t\t\t Author name: ";								  // the details of
						getline(cin, author);										  // the new book
						cout << "\t\t\t Price: ";									  //
						cin >> price;												  //
						cout << "\t\t\t In stock quantity: ";						  //
						cin >> quantity;											  //-----------
						cout << "\n\n\t\t\t Adding the books to the system\n";
						cout << "\t\t\t .........Please wait.........\n";
						bookList.addNewBook(id, title, author, price, quantity);      // to add the new book into the linked list
						Sleep(2000);
						cout << "\n\t\t\t BOOK ADDED!\n\t\t\t ";
						system("pause");
						break;
						
				case 2: cout << "\n\t\t\t Please enter the Book ID you want to update price"<<endl;
						cout << "\t\t\t Book ID : ";
						cin >> id;
						result = bookList.searchId(id);  // pass the argument to check whether the book ID exist in the store or not
						if (result == 0) 
						   cout << "\n\t\t\t ---We are sorry. The book did not exist in this store---"<< endl;
						else
						{
							cout << "\n\t\t\t -------The following are the details of the book-------\n";
							bookList.getDiscount(id);
							cout << "\n\n\t\t\t Updating the price in the system";
							cout << "\n\t\t\t .........Please wait.........\n";
							Sleep(2000);
							cout << "\n\t\t\t PRICE UPDATED!\n ";
						}
						cout << "\n\t\t\t ";  								
						system("pause");	
						break;
						
				case 3: cout << "\n\t\t\t Please enter the Book ID you want to add stock"<<endl;
						cout << "\t\t\t Book ID : ";
						cin >> id;
						result = bookList.searchId(id);  // pass the argument to check whether the book ID exist in the store or not
						if (result == 0) 
						   cout << "\n\t\t\t ---We are sorry. The book did not exist in this store---"<< endl;
						else
						{
							cout << "\n\t\t\t -------The following are the details of the book-------\n";
							bookList.addStock(id);
							cout << "\n\n\t\t\t Adding more stock in the system";
							cout << "\n\t\t\t .........Please wait.........\n";
							Sleep(2000);
							cout << "\n\t\t\t STOCK ADDED!\n ";
						}
						cout << "\n\t\t\t "; 
						system("pause");
						break;
						
				case 4: cout << "\n\t\t\t Sorting the stock according to the book ID\n";
						cout << "\t\t\t .........Please wait.........\n";
						Sleep(2000);
						bookList.bookSort();  // to perform the book sorting
						cout << "\n\t\t\t BOOK SORTED!\n\t\t\t ";
						system("pause");
						break;
						
				case 5:	bookList.displayList();  // to display the list of the books in the store
						system("pause");
						break;
				
				case 6:	cout << "\n\t\t\t Printing sales report and inventory\n";
						cout << "\t\t\t .........Please wait.........\n";
						printReport(bookList);  // to print the sales report
						Sleep(2000);
						cout << "\n\t\t\t PRINTING DONE!\n\t\t\t ";
						thankMessage();
						exit(0);
						
				case 7: thankMessage();
						exit(0);
						
				default: cout << "\n\t\t\t Invalid input. Please enter your choice again. \n\t\t\t ";
						 system("pause");
						 break;			
			}
		} while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice !=7);
	} while (choice !=7);
}

void printReport(BookList list) // to print the report by referring
{								// to the input file of books sold
	ifstream in("BooksBought.txt");
	ofstream out("SalesReport.txt");
	int id, qty;
	BookList soldBook;
	Book *book;
	while(!(in.eof()))
	{
		in >> id >> qty;
		book = list.compareId(id);
		soldBook.readBook(book, qty);
	}
	
	soldBook.printReport(out);
	
	in.close();
}
