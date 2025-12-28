#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std ;

const int MAX_VALUE = 100 ; 

struct book{

    string title, category, author, publisher, bookId  ;
    int publishYear, productCost, price ; 

} ; 


void printFunction1Instruc(){
    cout << "CHUONG TRINH QUAN LI CUA HANG BAN SACH" << endl ; 
    cout << "--------------------------------------" << endl ;
    cout << "[1] - Them sach " << endl ; 
    cout << "[2] - Sua thong tin cua sach" << endl ; 
    cout << "[3] - Tim kiem ten cua sach " << endl ;
    cout << "[4] - Xem toan bo sach hien co trong kho " << endl ; 
    cout << "----------------------------------------" << endl ;
    

}

int getInt(string promt){
    cout << promt ; 

    string buffer ;
    getline(cin, buffer) ;
    int result = stoi(buffer) ;
    return result ;
}

string getString(string promt){
    cout << promt ; 
    string buffer ;
    getline(cin, buffer) ;

    return buffer ; 
}

book getBook(string promt){
    cout << promt << endl ; 

    book result ;


    result.bookId = getString("Nhap ma sach : ") ;
    result.title = getString("Nhap tieu de cua cuon sach : " ) ; 
    result.category = getString("Nhap ten the loai cua cuon sach : ") ; 
    result.author = getString("Nhap ten tac gia cua cuon sach : ") ; 
    result.publisher = getString("Nhap ten cua nha xuat ban : ") ; 
    result.publishYear = getInt("Nhap nam xuat ban cua cuon sach : ") ; 
    result.productCost = getInt("Nhap gia nhap cua cuon sach : ") ; 
    result.price = getInt("Nhap gia cua cuon sach khi ban ra : ") ; 

    return result ;
}

void writeBook(ofstream& writer, string output, const book& book){

    writer << book.bookId << '|'<< book.title << '|' << book.author
    << '|' << book.category << '|' << book.publisher << '|' << book.publishYear
    << '|' << book.productCost << '|' << book.price << endl ; 

}

void reBuildTheFile(string output, const int& n, book books[]){
    ofstream file(output, ios :: trunc) ;
    file.close() ;      //xoa file ban dau de ghi lai moi 

    ofstream writer ;
    
    writer.open(output, ios :: out) ;
    writer << n << endl ; 

    for(int i = 0 ; i < n ; i++){
        writeBook(writer, output, books[i]) ; 
    }
    writer.close() ;
}

void addBooks(string output, book books[], int& booksCount){

    cout << "Chuong trinh them thong tin sach vao kho" << endl ; 
    int numWantToAdd = getInt("Nhap so loai sach ma ban muon them vao kho : " ) ; 


    cout << books[0].title << " " << books[1].title << endl;
    for(int i = 0 ; i < numWantToAdd ; i++){
        string promt = "Nhap thong tin sach [" ;
        promt += to_string(i + 1) ; 
        promt += ']' ; 
        books[i + booksCount] = getBook(promt) ;
        
        cout << books[i+booksCount].title << endl ; 

    }
    booksCount += numWantToAdd ; 

    reBuildTheFile(output, booksCount, books) ; 


}

book readBookInfo(string buffer){
    stringstream ss(buffer) ; 

    book result ; 

    string attribute ;
   
    getline(ss, attribute, '|') ;
    result.bookId = attribute ; 
    getline(ss, attribute, '|') ; 
    result.title = attribute ; 
    getline(ss, attribute, '|') ;
    result.author = attribute ; 
    getline(ss, buffer, '|') ;
    result.category = attribute ; 
    getline(ss, attribute, '|') ;
    result.publisher = attribute ;  
    getline(ss, attribute, '|') ;
    cout << result.publisher << endl  ; 
    result.publishYear = stoi(attribute) ; 
    getline(ss, attribute, '|') ; 
    result.productCost = stoi(attribute) ; 
    getline(ss, attribute) ;
    result.price = stoi(attribute) ; 

    return result ;
}

void readBooksInfo(string input, int& bookCount, book books[]){

    string buffer ;
    ifstream reader ;
    reader.open(input) ;
    reader.ignore(MAX_VALUE, '\n') ; 
    for(int i = 0 ; i  < bookCount ; i++){

        getline(reader, buffer) ; 
        books[i] = readBookInfo(buffer) ;

    }

    reader.close() ; 
}

void updateBookStock(string output, int bookCount){

    ofstream writer ;
    writer.open(output, ios:: out | ios::trunc) ; 

    writer.close() ;
}

int getBookInStocks(string input){

    ifstream reader ; 
    reader.open(input) ;
    string buffer ;
    getline(reader, buffer) ;
    int result = stoi(buffer) ;

    reader.close() ; 
    return result ;

}

void printChangeBookInstruction(){

    cout << "Nhap thong tin ma ban muon chinh sua : " << endl ; 
    cout << "[1] - Ma sach " << endl ; 
    cout << "[2] - Ten sach " << endl; 
    cout << "[3] - Tac gia " << endl ; 
    cout << "[4] - The loai" << endl ; 
    cout << "[5] - Nha san xuat" << endl ; 
    cout << "[6] - Nam xuat ban" << endl ; 
    cout << "[7] - Gia nhap " << endl ; 
    cout << "[8] - Gia ban" << endl ; 

}

void printBookInfo(book books[], int index){

    cout << books[index].bookId << "|" << books[index].title << '|' << books[index].author
    << '|' << books[index].category << '|' << books[index].publisher << '|' << books[index].publishYear
    << '|' << books[index].productCost << '|' << books[index].price << endl ; 
}



void changeBooksInfo(string targetId, book books[],int booksCount, string ouput){

    bool isFound = false ;
    string buffer ; 
    targetId = getString("Nhap ma sach ma ban muon sua : ") ; 
    int index = -1 ; 

    while(!isFound){

        for(int i = 0 ; i < booksCount ; i++){
            if(
                (books[i].bookId == targetId)
            ){
                isFound = true ; 
                index = i ; 
          
            }
        }

            if(!isFound){
                cout << "Ma sach khong ton tai trong kho, vui long nhap ma sach khac :" << endl ; 
                buffer = getString("") ; 
            }
    }

    if(isFound){

        printBookInfo(books, index) ; 
        printChangeBookInstruction() ; 
        buffer = getString("Nhap lua chon cua ban") ; 
        int userChoice = stoi(buffer) ;
            
        while(
            (userChoice < 1)
            || (userChoice > 8)
        ){
            buffer = getString("Nhap lieu khong hop le, vui long nhap so khac :") ; 
        }

        if(
            (1 == userChoice)
        ){
            buffer = getString("Nhap ma sach ma ban muon thay doi :") ; 
        
        }

    }

       
    


}

int main(){

    string input = "books.txt" ; 
    int bookCount = getBookInStocks(input) ;
    // int bookCount = 0 ;  
    book books[MAX_VALUE] ;
    readBooksInfo(input,  bookCount, books) ; 
    cout << bookCount << endl ; 
    cout << books[3].title << " " << books[3].author << " " 
    << books[3].publishYear << endl ; 


    
    
    printFunction1Instruc() ; 
    int userChoice = getInt("Nhap chuc nang ma ban muon su dung : ") ;

    while( (userChoice < 1)
        || (userChoice > 4)

    ){
        cout << "Nhap lieu khong hop le, vui long nhap lai" << endl ; 
        userChoice = getInt("") ; 
    }

    if (1 == userChoice){

        string output = input ; 
        addBooks(output, books, bookCount) ; 
        cout << "Them sach thanh cong !!" << endl ; 
        
         

    }
    else if(2 == userChoice){



    }
    else if(3 == userChoice){

    }
    else if(4 == userChoice){

    }
   
  



    return 0 ; 
}