#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Book {
private:
	string title, author, isbn, genre;
	int publicationYear;
	bool isAvailable;
public:
	Book(string title, string author,string isbn,string genre,int publicationYear):title(title),author(author),isbn(isbn), genre(genre), publicationYear(publicationYear), isAvailable(true) {
	
	}
	string getTitle() const{
		return title;
	}
	string getAuthor() const {
		return author;
	}
	string getISBN() const {
		return isbn;
	}
	int getPublicationYear() const {
		return publicationYear;
	}
	string getGenre() const {
		return genre;
	}
	bool getAvailability() const {
		return isAvailable;
	}
	void setTitle( const string& newTitle) {
		title = newTitle;

	}
	void setAuthor(const string& newAuthor){
		author = newAuthor;
	}
	void setAvailability(const bool& status) {
		isAvailable = status;
	}
	virtual void displayInfo() const {
		cout << "Title: " << title << endl;
		cout << "Author: " << author << endl;
		cout << "ISBN: " << isbn << endl;
		cout << "Publication Year: " << publicationYear << endl;
		cout << "genre: " << genre << endl;
		cout << "Status: " << (isAvailable?"Available":"Borrowed" ) << endl;

	}
};
class FictionBook :public Book {
private:
	string fictionType;
public:
	FictionBook(string title, string author, string isbn, string genre, int publicationYear,string fictionType)
		:Book(title, author, isbn, genre, publicationYear),fictionType((fictionType)){}

	string getFictionType() const {
		return fictionType;
	}
	void setFictionType(const string& type) {
		fictionType = type;
	}
	void displayInfo() const override {
		Book::displayInfo();
		cout << "Fiction Type: " << fictionType << endl;
	}
};
class NonFictionBook :public Book {
private:
	string subject;
public:
	NonFictionBook(string title, string author, string isbn, string genre, int publicationYear,string subject):
		Book(title,author,isbn,genre,publicationYear),subject(subject){ }
	void setSubject(const string & newSubject) {
		subject = newSubject;
	}
	string getSubject() const {

		return subject;
	}
	void displayInfo()const override{
		Book::displayInfo();
		cout << "The subject: " << subject << "\n";
	}
};
class ReferenceBook :public Book {
private:
	bool canBeBorrowed;
public:
	ReferenceBook(string title, string author, string isbn, string genre, int publicationYear) :
		Book(title, author, isbn, genre, publicationYear) ,canBeBorrowed(false){
		
	}
	bool getCanBeBorrowed()const {
		return canBeBorrowed;
	}
	void displayInfo()const override {
		Book::displayInfo();
		cout << "Type:Reference Book \n";
		cout << "canBeBorrowed : " << (canBeBorrowed ? "Yes": "No") << "\n";
	}
};
class Date {
private:
	int day, month, year;
	bool validateDate(int d,int m,int y) const{
		if (y <= 0 || m <= 0||m>12 || d <1) return false;
		const int dayINMonths[] = { 0,31,28,31,30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int maxDays = dayINMonths[m];
		if (m == 2 && (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)))
			maxDays = 29;

		return d <= maxDays;
	}
public:
	Date():day(1),month(1),year(2000){}
	Date(int d, int m, int y) {
		if (validateDate(d, m, y)) {
			day = d;
			month = m;
			year = y;

		}
		else {
			cout << "Inavlid date setting to defult...\n";
			day = 1;
			month = 1;
			year = 2000;
		}
	}
	int getDay() const {
		return day;
	}
	int getMonth() const {
		return month;
	}
	int getYear() const {
		return year;
	}
	void setDate(int d, int m, int y) {
		if (validateDate(d, m, y)) {
			day = d;
			month = m;
			year = y;
		}
		else {
			cout << "Invalid date....\n";
		}
	}
	string toString() const{
		return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
	}
	Date operator+(int days)const {
		Date result = *this;
		result.day += days;// result.day = result.day+days
		return result;
	}
	int operator-(const Date& other)const {
		int thisDays = year * 365 + month * 30 + day;
		int otherDays = other.year * 365 + other.month * 30 + other.day;
		return thisDays - otherDays;
	
	}	
	bool operator==(const Date& other)const {
		return(day == other.day && month == other.month && year == other.year);
	}
	bool operator>(const Date& other)const {
		if (year != other.year) return year > other.year;
		if (month != other.month)return month > other.month;
		return  day > other.day;
	}
	bool operator<(const Date& other) const {
		return !(*this > other || *this == other);
	}

};
class Member {
private:
	int id;
	string name, contactInfo;
	vector<Book*> borrwedBooks;
	double fineAmount;
public:
	Member(int id, string name,string contactInfo):id(id),name(name),contactInfo(contactInfo),fineAmount(0.0){}
	int getId() const{
		return id;
	}
	string getName() const{
		return name;

	}
	string getContactInfo() const {
		return contactInfo;
	}

	double getFineAmount() const {
		return fineAmount;
	}
	bool borrwBook(Book *book){
		if (book && book->getAvailability()) {
			borrwedBooks.push_back(book);
			book->setAvailability(false);
			return true;
		}
		return false;
	}
	bool returnBook(Book* book) {
		auto it = find(borrwedBooks.begin(), borrwedBooks.end(), book);
		if (it != borrwedBooks.end()) {
			borrwedBooks.erase(it);
			book->setAvailability(true);
			return true;
		}
		return false;
	
	}
	bool hasBorrowedBook(Book* book) {
		return find(borrwedBooks.begin(), borrwedBooks.end(), book) != borrwedBooks.end();
	}
	void payFine(double amount) {
		if (amount > 0 && amount < fineAmount) {
			fineAmount -= amount;//fineAmount = fineAmount - fine
		}

	}
	void addFine(double amount) {
		fineAmount += amount;
	}
	void displayInfo() const {
		cout << "Member ID: " << id << endl;
		cout << "Name: " << name << endl;
		cout << "Contact: " << contactInfo << endl;
		cout << "Fine Amount: $" << fineAmount << endl;
		cout << "Number of books borrowed: " << borrwedBooks.size() << endl;
	}
	void displayBorrowedBooks() const {
		if (borrwedBooks.empty()) {
			cout << "No borrwed books....\n";
			return;
		}
		else {
			cout << "Borrwed Books: \n";
			for (auto& book : borrwedBooks) {
				cout << "- " << book->getTitle() << "by" << book->getAuthor() << endl;
			}
		}
	}
};
class Transaction {
private:
	Book* book;
	Member* member;
	Date borrowDate, dueDate, returnDate;
	bool isReturned;
	const double FINE_PER_DAY = 1.0;
public:
	Transaction(Book *book,Member*member,const Date& borrowDate,const Date& dueDate):
		book(book),member(member),borrowDate(borrowDate),dueDate(dueDate),isReturned(false){ }
	Book* getBook() const{
		return book;
	}
	Member* getMember()const {
		return member;
	}
	Date getBorrowDate() const { return borrowDate; }
	Date getDueDate() const { return dueDate; }
	Date getReturnDate() const { return returnDate; }
	bool isBookReturned() const { return isReturned; }
	void returnBook(const Date& date) {
		returnDate = date;
		isReturned = true;
		if (book) {
			book->setAvailability(true);
		}
		double fine = calculateFine();
		if (fine > 0 && member) {
			member->addFine(fine);
		}

	}
	double calculateFine() const{
		if (!isReturned)return 0.0;
		if (returnDate > dueDate) {
			int daysLate = returnDate - dueDate;
			return daysLate * FINE_PER_DAY;
		}
		return 0.0;
	}
	void extendDueDate(const Date& newDueDate) {
		if (!isReturned && newDueDate > dueDate) {
			dueDate = newDueDate;
		}
	}
	bool isOverDue(const Date &currentDate)const {
		
		return !isReturned && currentDate > dueDate;
	}
	void displayInfo() const {
		cout << "Transaction Details: \n";
		cout << "Book: " << book->getTitle() << " \nISBN: " << book->getISBN() << "\n";
		cout << "Member: " << member->getName() << " \nID: " << member->getId() << "\n";
		cout << "Borrow Date: " << borrowDate.toString() << "\n";
		cout << "Due Date: " << dueDate.toString() << "\n";
		if (isReturned) {
			cout << "Return Date: " << returnDate.toString() << endl;
			cout << "Fine: " << calculateFine() << "$\n";
		}
		else {
			 cout << "Status: Not returned yet" << endl;
		}

		cout << "-------------------------\n";
	}
};
class Library {
private:
	vector <Book*>books;
	vector <Member*>members;
	vector <Transaction*>transactions;
public:
	Library() {}
	void addBook(Book *book){
		if (book) {
			books.push_back(book);
		}
	}
	bool RemoveBook(string& isbn) {
		
		auto it = std::find_if(books.begin(), books.end(),
			[&isbn](Book* book) {return book->getISBN() == isbn;});
		//lambda function syntax--> [](){}
		if (it != books.end()) {
			delete* it;
			books.erase(it);
			return true;
		}
		return false;
	}
	void registerMember(Member* member) {
		if (member) {
			members.push_back(member);
		}
	}
	bool removeMember(int id) {
		auto it = find_if(members.begin(), members.end(), [id](Member* member) {return member->getId() == id; });
		if (it != members.end()) {
			delete *it;
			members.erase(it);
			return true;
		}
		return false;
	}
	bool borrowBook(const std::string& isbn, int memberId) {
		auto bookIt = find_if(books.begin(), books.end(), [&isbn](Book* book) {return book->getISBN() == isbn; });
		auto memberIt = find_if(members.begin(), members.end(), [memberId](Member* member) {return member->getId() == memberId; });
		if (bookIt == books.end() || memberIt == members.end()) {
			return false;
		}
		Book* book = *bookIt;
		Member* member = *memberIt;
		if (!book->getAvailability()) {
			return false;
		}
		Date borrowDate;
		Date dueDate = borrowDate + 14;
		
		Transaction *t=new Transaction(book, member, borrowDate, dueDate);
		member->borrwBook(book);
		book->setAvailability(false);
		transactions.push_back(t);
		return true;
	}
	bool returnBook(const std::string& isbn, int memberId){
		auto bookIt = find_if(books.begin(), books.end(), [&isbn](Book* book) {return book->getISBN() == isbn; });
		auto memberIt = find_if(members.begin(), members.end(), [memberId](Member* member) {return member->getId() == memberId; });
		if (bookIt == books.end() || memberIt == members.end()) {
			return false;
		}
		Book* book = *bookIt;
		Member* member = *memberIt;
		auto transactionIt = find_if(transactions.begin(), transactions.end(), [&](Transaction* t) {
			return t->getBook() == book && t->getMember() == member && t->isBookReturned();
				});
		if (transactionIt == transactions.end()) {
			return false;
		}
		Date returnDate;
		(*transactionIt)->returnBook(returnDate);
		return true;
	}

};
int main() {
	Library library;

	// Create some books
	FictionBook* novel1 = new FictionBook("To Kill a Mockingbird", "Harper Lee", "9780446310789", "Fiction", 1960, "Classic Literature");

	NonFictionBook* scienceBook = new NonFictionBook(
		"A Brief History of Time",
		"Stephen Hawking",
		"9780553380163",
		"Science",
		1988,
		"Cosmology"
	);

	ReferenceBook* encyclopediaBook = new ReferenceBook(
		"Encyclopedia Britannica",
		"Various Authors",
		"9781593392930",
		"Reference",
		2019);
	library.addBook(novel1);
	library.addBook(encyclopediaBook);
	library.addBook(scienceBook);
	Member* member1 = new Member(1, "John Doe", "john.doe@email.com");
	Member* member2 = new Member(2, "Jane Smith", "jane.smith@email.com");
	library.registerMember(member1);
	library.registerMember(member2);
	cout << "\n=== Borrowing a Book ===" << std::endl;
	library.borrowBook(novel1->getISBN(), member1->getId());
	member1->displayInfo();

	return 0;
}