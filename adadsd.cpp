#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std ;

const int MAX_VALUE = 100 ; 

struct book{

    string title, category, author, publisher, bookId  ;
    int publishYear, productCost, price, quantity ; 

} ; 

void printFunction1Instruc(){
    cout << "CHƯƠNG TRÌNH QUẢN LÍ CỬA HÀNG BÁN SÁCH" << endl ; 
    cout << "--------------------------------------" << endl ;
    cout << "[1] - --------------------------" << endl ; 
    cout << "[2] - Sửa lại thông tin của sách" << endl ; 
    cout << "[3] - Xem thông tin/ tìm kiếm sách" << endl ;
    cout << "[4] - Thêm số lượng sách cũ sẵn có" << endl;
    cout << "[5] - Thêm loại sách mới vào kho " << endl ; 
    cout << "----------------------------------------" << endl ;
    

}

void printFindBookInfoFuncInstruc(){

    cout << "Xem thong tin sach...." << endl ; 
    cout << "[1] - Xem sach theo the loai" << endl ; 
    cout << "[2] - Tim kiem sach " << endl ; 
    cout << "[3] - Xem tat ca sach hien co trong kho " << endl ; 

}

void printFind1BookInstruc(){
    
    cout << "Tim kiem sach " << endl ; 
    cout << "[1] - Tim sach theo ma sach" << endl ; 
    cout << "[2] - Tim sach theo ten " << endl ; 
}

void printBookInfo(book books[], int index){

    cout << books[index].bookId << "|" << books[index].title << '|' << books[index].author
    << '|' << books[index].category << '|' << books[index].publisher << '|' << books[index].publishYear
    << '|' << books[index].productCost << '|' << books[index].price << '|' << books[index].quantity << endl ; 
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

    result.bookId = getString("Nhập mã sách: ") ;
    result.title = getString("Nhập tiêu đề của cuốn sách: " ) ; 
    result.category = getString("Nhập tên thể loại của cuốn sách: ") ; 
    result.author = getString("Nhập tên tác giả của cuốn sách: ") ; 
    result.publisher = getString("Nhập tên của nhà xuất bản : ") ; 
    result.publishYear = getInt("Nhập năm xuất bản của cuốn sách: ") ; 
    result.productCost = getInt("Nhập giá nhập hàng của cuốn sách: ") ; 
    result.price = getInt("Nhập giá của cuốn sách khi bán ra : ") ; 
    result.quantity = getInt("Nhập số lượng sách được nhập vào: ");

    return result ;
}

void writeBook(ofstream& writer, string output, const book& book){

    writer << book.bookId << '|'<< book.title << '|' << book.author
    << '|' << book.category << '|' << book.publisher << '|' << book.publishYear
    << '|' << book.productCost << '|' << book.price << '|' << book.quantity << endl ; 

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

    cout << "Chương trình thêm thông tin sách vào kho" << endl ; 
    int numWantToAdd = getInt("Nhập số loại sách mà bạn muốn thêm vào kho: " ) ; 


    cout << books[0].title << " " << books[1].title << endl;
    for(int i = 0 ; i < numWantToAdd ; i++){
        string promt = "Nhập thông tin sách [" ;
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
    getline(ss, attribute, '|') ;
    result.category = attribute ; 
    getline(ss, attribute, '|') ;
    result.publisher = attribute ;  
    getline(ss, attribute, '|') ;
    result.publishYear = stoi(attribute) ; 
    getline(ss, attribute, '|') ; 
    result.productCost = stoi(attribute) ; 
    getline(ss, attribute, '|') ;
    result.price = stoi(attribute) ; 
    getline(ss, attribute) ;
    result.quantity = stoi(attribute) ;

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

void addAvailableBook(string output, const int& bookCount, book books[]){
    cout << "Chương trình tăng số lượng sách sẵn có " << endl;
    bool found = false;
    do{
        string id = getString("Nhập ID cuốn sách bạn muốn tăng số lượng: ");
        for(int i = 0; i < bookCount; ++i){
            if(id == books[i].bookId){
                cout << "Đây là tên cuốn sách của bạn: " << books[i].title << endl;
                int quantity1 = getInt("Nhập số lượng sách bạn muốn tăng: ");
                books[i].quantity += quantity1;
                found = true;
                cout << "Đã cập nhật số lượng sách. Số lượng sách " << books[i].title << " hiện có trong kho là: " << books[i].quantity << " cuốn." << endl;
                break;
            }
        }
        if(!found){
            cout << "Không tìm thấy ID của sách. Mời nhập lại: " << endl;
        }
    }while(!found);
    reBuildTheFile(output, bookCount, books); 
}

void changeBooksInfo(book books[], int booksCount, string ouput){

    bool isFound = false ;
    string buffer ; 
    string targetId = getString("Nhap ma sach ma ban muon sua : ") ; 
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
            targetId = getString("") ;
        }
    }

    if(isFound){

        printBookInfo(books, index) ; 
        cout << endl; 
        printChangeBookInstruction() ; 

        buffer = getString("Nhap lua chon cua ban : ") ; 
        int userChoice = stoi(buffer) ;
            
        while(
            (userChoice < 1)
            || (userChoice > 8)
        ){
            buffer = getString("Nhap lieu khong hop le, vui long nhap so khac : ") ; 
        }

        if(
            (1 == userChoice)
        ){
            buffer = getString("Nhap ma sach ma ban muon thay doi : ") ; 
            books[index].bookId = buffer ; 
        }
        else if(
            (2 == userChoice)
        ){
            buffer = getString("Nhap tieu de sach ma ban muon thay doi : ") ; 
            books[index].title = buffer ;
        }
        else if(
            (3 == userChoice)
        ){
            buffer = getString("Nhap ten tac gia ma ban muon thay doi : ") ; 
            books[index].author = buffer ; 
        }
        else if(
            (4 == userChoice)
        ){
            buffer = getString("Nhap the loai ma ban muon thay doi : ") ;
            books[index].category = buffer ; 
        }
        else if(
            (5 == userChoice)
        ){
            buffer = getString("Nhap ten nha san xuat ma ban muon thay doi : ") ; 
            books[index].publisher = buffer ; 
        }
        else if(
            (6 == userChoice)
        ){
            int newPublishYear = getInt("Nhap nam xuat ban ma ban muon thay doi ") ; 
            books[index].publishYear = newPublishYear ; 
        }
        else if(
            (7 == userChoice)
        ){
            int newProductCost = getInt("Nhap gia nhap hang cua sach ma ban muon thay doi :") ;
            books[index].productCost = newProductCost ; 
        }
        else if(
            (8 == userChoice)
        ){
            int newPrice = getInt("Nhap gia ban ma ban muon thay doi : ") ; 
            books[index].price = newPrice ; 
        }


    }

    reBuildTheFile(ouput, booksCount, books) ; 
    printBookInfo(books, index) ; 


}

void findBookByCateGory(book books[], int booksCount){

    string categoryInput = getString("Nhap the loai sach ma ban muon xem : ") ;
    int resultCount = 0 ;
    bool isFound = false ;  

        
    while(
        (!isFound)
    ){
            
        for(int i = 0 ; i < booksCount ; i++){
            // cout << books[i].category << endl ; 
            if(
                (books[i].category == categoryInput)
            ){
                isFound = true ; 
                resultCount++ ; 
            }
        }
            
        if(
            (!isFound)
                
        ){
           categoryInput = getString("Khong co the loai sach tuong ung, vui long nhap the loai khac : ") ;
        }
        else{
            break;
        }
            
    }
        
    book* result = new book[resultCount] ; 
    int count = 0 ; 
        
    for(int i = 0 ; i < booksCount ; i++){
        if(
            (books[i].category == categoryInput)
        ){
            result[count] = books[i] ; 
            count++ ; 
        }
    }

    for(int i = 0 ; i < resultCount ; i++){
        printBookInfo(result, i) ; 
    }

    cout << "Chuong trinh dang ket thuc, bam enter de tiep tuc...." << endl ; 
    cin.get() ; 

}

void findBookByNameOrBookId(book books[], int booksCount){

    printFind1BookInstruc() ; 
    string buffer ; 
    int userChoice = getInt("Nhap lua chon cua ban : ") ; 
    
    while(
        (1 > userChoice)
        ||(2 < userChoice)
    ){
        userChoice = getInt("Nhap so khong hop le, vui long nhap so khac :") ;
    }

    bool isFound = false ; 

    if(
        (1 == userChoice)
    ){
        string bookIdInput = getString("Nhap ma sach ma ban muon tim :") ; 

        while(!isFound){

            for(int i = 0 ; i < booksCount ; i++){
                // printBookInfo(books,i) ; 

                if(
                    (books[i].bookId == bookIdInput)
                ){
                    isFound = true ;
                    printBookInfo(books, i) ; 
                    break ; 
                }
            }
            if(!isFound){
                bookIdInput = getString("Khong tim thay ma sach tuong ung trong kho, vui long nhap ma khac : ") ; 

            }
        }


        
    }   
    else if(
        (2 == userChoice)
    ){
        string bookNameInput = getString("Nhap ten sach ma ban muon tim : ") ;

        while(!isFound){

            for(int i = 0 ; i < booksCount ; i++){

                if(
                    (books[i].title == bookNameInput)
                ){
                    isFound = true ;
                    printBookInfo(books, i) ; 
                    break ; 
                }
            }

            if(!isFound){
                bookNameInput = getString("Khong tim thay ten sach tuong ung trong kho, vui long nhap ten khac : ") ; 
                
            }
        }
         
    }
}

void findBooks(book books[], int booksCount, int userChoice){
    
    if(
        (1 == userChoice)
    ){
        findBookByCateGory(books, booksCount) ; 
    }
    else if(
        (2 == userChoice)
    ){
        findBookByNameOrBookId(books, booksCount) ; 
    }
    else if (
        (3 == userChoice)
    ){
        for(int i = 0 ; i < booksCount ; i++){
            printBookInfo(books, i) ; 
        }
    }
    

}


int main(){

    string input = "books.txt" ; 
    int booksCount = getBookInStocks(input) ;
    // int bookCount = 0 ;  
    book books[MAX_VALUE] ;
    readBooksInfo(input, booksCount, books) ; 
    cout << booksCount << endl ; 
    cout << books[3].title << " " << books[3].author << " " 
    << books[3].publishYear << endl ; 

    printFunction1Instruc() ; 
    int userChoice = getInt("Chọn chức năng bạn muốn sử dụng: ") ;
    
    while( (userChoice < 1)
        || (userChoice > 5)

    ){
        cout << "Nhập liệu không hợp lệ, vui lòng nhập lại" << endl ; 
        userChoice = getInt("") ; 
    }

    if (1 == userChoice){

    }
    else if(2 == userChoice){
        
        string output = input ; 
        changeBooksInfo(books, booksCount, output) ;
        cout << "Chinh sua thong tin sach thanh cong !!!" << endl;

        while(userChoice != 0){

            cout << "Ban co muon chinh sua them cuon sach khac khong " << endl ; 
            cout << "[1] - Co " << endl ; 
            cout << "[0] - Khong" << endl ; 
            userChoice = getInt("Nhap lua chon cua ban : ") ; 

            if(userChoice == 0 ){
                break;
            } 
            else{
                changeBooksInfo(books, booksCount, output) ;

            }

        }
        cout << "Chuong trinh dang ket thuc, bam phim Enter de tiep tuc....." ; 
        cin.get() ;

    }
    else if(3 == userChoice){

        printFindBookInfoFuncInstruc() ; 

        userChoice = getInt("Nhap lua chon cua ban : ") ; 
        while(
            (userChoice > 5)
            || (userChoice < 1)
        ){
            userChoice = getInt("Nhap so khong hop le, vui long nhap so khac : ") ; 
        }
        cout << books[0].category << endl ;  
        findBooks(books, booksCount, userChoice) ; 

    }
    else if(4 == userChoice){

        addAvailableBook("books.txt", booksCount, books);

    }else if(5 == userChoice){
        string output = input ; 
        
        addBooks(output, books, booksCount) ; 
        cout << "Thêm sách thành công!" << endl ; 
        
    }
   
  



    return 0 ; 
}