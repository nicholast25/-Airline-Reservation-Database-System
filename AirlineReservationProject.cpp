#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <fstream> //ofstream, ifstream, fstream
#include <ctime>
#include <cmath>
#include <stdlib.h>


using namespace std;
ofstream myFile;
ifstream readFile;

void bar(){
	cout<<"----------------------------------------------------------"<<endl; //function untuk keluarin gap atau batas berupa bar tipis
}
void bar2(){
	cout<<"=========================================================="<<endl; //function untuk keluarin gap atau batas berupa bar tebal
}
void back_to_menu();			   

	int date,month,year; 		//variabel (tanggal, bulan, dan tahun departure/ pergi) yang akan di-input oleh user 
	int date2,month2,year2; 	//variabel (tanggal, bulan, dan tahun return/ pulang) yang akan di-input oleh user
	time_t now = time(0); 		//untuk record & input tanggal atau waktu sekarang ke program
	tm*ltm=localtime(&now); 	//untuk convert ke waktu lokal (di Indonesia)

    int menu,from,to,flight1,n, flight_time_departure, flight_time_return, passenger_range, seat_class;//variable yang hanya akan di-input oleh user
	long long phone_number; 							//variabel untuk nomor telepon yang di-input oleh user + valuennya disimpen ke File
	char gender; 										//variabel (untuk gender) yang akan di-input oleh user 
	string airport, destination_string, name, flight2, time_departure_string, 
	time_return_string, passenger_range_string, gender_string, seat_class_string, email, password; //variabel yang valuenya akan disimpan ke File
	int price, price_roundtrip;																	  //variabel yang valuenya akan disimpan ke File
	
	//ARRAY yang berisi bulan", dimana akan disimpan ke File melalui monthNames[month-1] or monthNames[month2-1];
	string monthNames[]={"January","February","March","April","May","June","July","August","September","October","November","December"};
	
	
	//VARIABEL UNTUK MEMANGGIL DATA-DATA DARI CSV
   	 string line,test,test2; 
	 string airport_file, destination_file, flight2_file;  														//DATA VARIABEL LOKASI DARI CSV
	 string date1_file, date2_file, month1_file, month2_file, year1_file, year2_file, time1_file, time2_file;  //DATA VARIABEL WAKTU DARI CSV
	 string passenger_range_file, seat_class_file, seat_position_row_file_1st, seat_position_column_file_1st,  //DATA VARIABEL SEAT BOOKING DARI CSV
	 		seat_position_row_file_2nd, seat_position_column_file_2nd;
	 string name_file,gender_file, phone_number_file, email_file, password_file,price_file; 				 //DATA VARIABEL IDENTITAS DARI CSV
	 
	 //VARIABEL SEAT BOOKING
	 int seat_booking[10+1][5+1], 			//MAKSIMAL ARRAY [kolom][baris] UNTUK PERGI
	    seat_booking_2nd[10+1][5+1];	   //Maksimal ARRAY[kolom][baris] UNTUK PULANG
 	char seat_booking_row_char[10]={'A','B','C','D','E','F','G','H','I','J'};
    int seat_position_row_1st, seat_position_column_1st,seat_position_row_2nd, seat_position_column_2nd;
	char row_alphabet;                                         //Input column saat pergi (1st)/pulang (2nd)
	int column, row, column2, row2;                            //Input row saat pergi (1st)/pulang (2nd), dan convert row dari int ke char
	int date1,year1,date2_int,year2_int;  									       //Convert date1_file, year1_file dari string (getline) ke  int
	int economy_1st, business_1st, economy_2nd, business_2nd;  //Jumlah orang memilih kelas economy/business saat pergi (1st)/pulang (2nd)
	

	
	
//FUNCTION UNTUK ISI DAN VALIDASI TANGGAL BERANGKAT (DEPARTURE)
void ddmmyyyy(){
	
	cout<<"Enter the date (DD): "; //input tanggal
	cin>>date;
	while(cin.fail()){ //Selama date bukan integer
		cin.clear(); //menghapus pernyataan error dari cin, sehingga bisa proses input lebih lanjut. Jadi tidak muncul infinite loop error message. 
    	cin.ignore(numeric_limits<streamsize>::max(),'\n'); //mengabaikan atau skip sisa line setelah line error pertama muncul sampai limitnya maksimal (tak hingga) 
    	cout<<"\nPlease enter the date in numbers: ";
		cin>>date;
	    }
				
	cout<<"Enter the month (MM): "; //input bulan (ke berapa)
	cin>>month; 
    while(cin.fail()||month<1||month>12){ //untuk menjalankan program selama nilai month <1 atau >12, atay non-integer agar user isi ulang nilai month.
    			cin.clear(); //menghapus pernyataan error dari cin, sehingga bisa proses input lebih lanjut. Jadi tidak muncul infinite loop error message. 
    			cin.ignore(numeric_limits<streamsize>::max(),'\n'); //mengabaikan atau skip sisa line setelah line error pertama muncul sampai limitnya maksimal (tak hingga) 
				cout<<"\nPlease enter the valid month: "; //perintah untuk isi ulang month
				cin>>month;			
	}
	
	cout<<"Enter the year (YYYY): "; //input tahun
	cin>>year;
	   while(cin.fail()||year<2021||year>2100){ //Menjalankan program selama tahunnya <2021 atau >2100, atau non-integer agar user isi ulang nilai year
    			cin.clear(); //menghapus pernyataan error dari cin, sehingga bisa proses input lebih lanjut. Jadi tidak muncul infinite loop error message. 
    			cin.ignore(numeric_limits<streamsize>::max(),'\n');//mengabaikan atau skip sisa line setelah line error pertama muncul 
				cout<<"\nPlease enter the year correctly: ";
				cin>>year;
			 }	
			
	switch(month){  //kondisi month supaya menyesuaikan tanggal (sesuai kalender)
    	case 1: case 3: case 5: case 7: case 8: case 10: case 12:  //Jika month (31 hari) adalah Januari, Maret, Mei, Juli, Oktober, Desember
				while(date<1||date>31){ //menjalankan program selama date masih <1 atau >31 sampai nilainya sudah diganti oleh user.
				if(cin.fail()){
    				cin.clear(); //menghapus pernyataan error dari cin, sehingga bisa proses input lebih lanjut. Jadi tidak muncul infinite loop error message. 
    				cin.ignore(numeric_limits<streamsize>::max(),'\n');//mengabaikan atau skip sisa line setelah line error pertama muncul 
					cout<<"\nYou have entered wrong input, please enter the correct date (1-31): ";
					cin>>date;
					}	
				else{
					cout<<"\nPlease enter the correct date: ";
					cin>>date;
				 	}
				 }
		       break;		 
		case 2: case 4: case 6: case 9: case 11: //Jika month (kurang dari 31 hari) adalah Februari, April, Juni, September, November
				 if(month==2&& year%4==0){ //Jika monthnya Februari di tahun Kabisat
					while(date<1||date>29){ //Menjalankan program selama tanggal<1 atau >29 agar user isi ulang nilai date
					if(cin.fail()){
    					cin.clear(); //menghapus pernyataan error dari cin, sehingga bisa proses input lebih lanjut. Jadi tidak muncul infinite loop error message. 
    					cin.ignore(numeric_limits<streamsize>::max(),'\n');//mengabaikan atau skip sisa line setelah line error pertama muncul 
						cout<<"\nYou have entered wrong input, please enter the correct date (1-29): ";
						cin>>date;}	
					else{cout<<"\nPlease enter the correct date: ";
						cin>>date;}
					}
					}
			    	else if(month==2&& year%4!=0){ //Jika monthnya Februari di tahun non-Kabisat
					while(date<1||date>28){ //Menjalankan program selama tanggal<1 atau >28 agar user isi ulang nilai date
					if(cin.fail()){
    					cin.clear(); //menghapus pernyataan error dari cin, sehingga bisa proses input lebih lanjut. Jadi tidak muncul infinite loop error message. 
    					cin.ignore(numeric_limits<streamsize>::max(),'\n');//mengabaikan atau skip sisa line setelah line error pertama muncul 
						cout<<"\nYou have entered wrong input, please enter the correct date (1-28): ";
						cin>>date;
						}	
					else{cout<<"\nPlease enter the correct date: ";
		         		cin>>date;}		
					}
				}
				else if(month%2==0){ //Jika monthnya April, Juni, September, November
				while(date<1||date>30){ //Menjalankan program selama tanggal<1 atau > 30 user isi ulang nilai date
					if(cin.fail()){
    				cin.clear(); //menghapus pernyataan error dari cin, sehingga bisa proses input lebih lanjut. Jadi tidak muncul infinite loop error message. 
    				cin.ignore(numeric_limits<streamsize>::max(),'\n');//mengabaikan atau skip sisa line setelah line error pertama muncul 
					cout<<"\nYou have entered wrong input, please enter the correct date (1-30): ";
					cin>>date;
					}	
					else{
					cout<<"\nPlease enter the correct date: ";
					cin>>date;}
					}	
				}
				break;
	  }
					
}

//FUNCTION UNTUK ISI DAN VALIDASI TANGGAL PULANG (RETURN)
void ddmmyyyy2(){ 
	cout<<"Enter the date (DD): "; //input tanggal pulang
	cin>>date2;
	while(cin.fail()){   //Selama date bukan angka
		    cin.clear(); //menghapus pernyataan error dari cin, sehingga bisa proses input lebih lanjut. Jadi tidak muncul infinite loop error message. 
  	    	cin.ignore(numeric_limits<streamsize>::max(),'\n'); //mengabaikan atau skip sisa line setelah line error pertama muncul 
			cout<<"\nPlease enter the date in numbers: ";
			cin>>date2;
			}
	   
	cout<<"Enter the month (MM): ";						 //input bulan pulang (bulan ke berap1a)
    cin>>month2;	    
	    while(cin.fail()||month2<1||month2>12){ 		//Menjalankan program selama month<1 atau month>12 agar user isi ulang nilai month2 dengan benar.
                cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');    	//Jika inputnnya int (tapi bulannya masih salah) 
				cout<<"\nPlease enter the valid month: "; 
				cin>>month2; 											//input ulang month2
			}
				
	cout<<"Enter the year (YYYY): "; //input tahun pulang
	cin>>year2;	
		while(cin.fail()||year2<2021||year2>2100){ //Menjalankan program selama tahunnya <2021 atau >2100 agar user isi ulang nilai year
    			cin.clear(); //menghapus pernyataan error dari cin, sehingga bisa proses input lebih lanjut. Jadi tidak muncul infinite loop error message. 
    			cin.ignore(numeric_limits<streamsize>::max(),'\n');//mengabaikan atau skip sisa line setelah line error pertama muncul 
				cout<<"\nPlease enter the year correctly: ";
				cin>>year2;
				}

    	switch(month2){
    	case 1: case 3: case 5: case 7: case 8: case 10: case 12: 
				while(date2<1||date2>31){
				if(cin.fail()){
    				cin.clear(); //menghapus pernyataan error dari cin, sehingga bisa proses input lebih lanjut. Jadi tidak muncul infinite loop error message. 
    				cin.ignore(numeric_limits<streamsize>::max(),'\n'); //mengabaikan atau skip sisa line setelah line error pertama muncul 
					cout<<"\nYou have entered wrong input, please enter the correct date (1-31): "; //perintah untuk input tanggal pulang yang benar
					cin>>date2; //input tanggal pulang
					}	
				else{ 									//Jika inputnya int (tapi tanggalnya masih belum sesuai dengan kalender)
					cout<<"\nPlease enter the correct date: "; 
					cin>>date2; 						//input tanggal pulang
				 	}
				 }
		break;	 
		case 2: case 4: case 6: case 9: case 11: 		//Jika month (kurang dari 31 hari) adalah Februari, April, Juni, September, November 
				 if(month2==2&& year2%4==0){ 			//Menjalankan program kalau bulan Februari di tahun Kabisat
					while(date2<1||date2>29){ 			//Menjalankan program selama tanggal pulang <1 atau >29 supaya user input ulang/ perbaikin tanggalnya.
					if(cin.fail()){ 					//Jika inputnya bukan int
    					cin.clear(); 					//menghapus pernyataan error dari cin, sehingga bisa proses input lebih lanjut. Jadi tidak muncul infinite loop error message. 
    					cin.ignore(numeric_limits<streamsize>::max(),'\n');//mengabaikan atau skip sisa line setelah line error pertama muncul 
						cout<<"\nYou have entered wrong input, please enter the correct date (1-29): ";  
						cin>>date2;}	
					else{cout<<"\nPlease enter the correct date: "; //Jika inputnya int tapi tanggalnya masih belum sesuai
						cin>>date2;}
					}
					}
			    	else if(month2==2&& year2%4!=0){ //Menjalankan program kalau bulan Februari di tahun non-Kabisat 
					while(date2<1||date2>28){ //Menjalankan program selama tanggal pulang <1 atau >28 supaya user input ulang/ perbaikin tanggalnya.
					if(cin.fail()){
    					cin.clear(); //menghapus pernyataan error dari cin, sehingga bisa proses input lebih lanjut. Jadi tidak muncul infinite loop error message. 
    					cin.ignore(numeric_limits<streamsize>::max(),'\n');//mengabaikan atau skip sisa line setelah line error pertama muncul 
						cout<<"\nYou have entered wrong input, please enter the correct date (1-28): ";
						cin>>date2;
						}	
					else{cout<<"\nPlease enter the correct date: ";
		         		cin>>date2;}		
					}
				}
				else if(month2%2==0){ //Menjalankan program kalau bulannya April, Juni, September, November
					while(date2<1||date2>30){ //Menjalankan program selama tanggal pulangnya <1 atau >30 supaya user input ulang/perbaikin tanggalnya.
						if(cin.fail()){
    					cin.clear(); //menghapus pernyataan error dari cin, sehingga bisa proses input lebih lanjut. Jadi tidak muncul infinite loop error message. 
    					cin.ignore(numeric_limits<streamsize>::max(),'\n');//mengabaikan atau skip sisa line setelah line error pertama muncul 
						cout<<"\nYou have entered wrong input, please enter the correct date (1-30): ";
						cin>>date2;
						}	
						else{
						cout<<"\nPlease enter the correct date: ";
						cin>>date2;	}
				  	}				
				}
			break;	
		}
		
}

void departure_condition(); //Prototype Function untuk menjalankan kondisi kalau departure date lebih telah 1 hari dari tanggal hari ini atau tidak (karena booking maksimal h-1 penerbangan)

int digit_number(long long phone){ //Function untuk menghitung digit pada nomor telepon (terlepas dari angka pertama (0 atau +62))
	return log10(phone)+1;} //mengembalikkan digit nomor telepon tersebut
	
bool email_validity(string); //Protoype Function untuk menjalankan email validitas (apakah valid/ invalid)
bool password_validity(string); //Protoype Function untuk menjalankan password validitas (apakah valid/ invalid)


void menu_main(); //Protype Function untuk mengeluarkan Main Menu;


//FUNCTIONS DENAH SEAT BOOKING (1ST PERGI, 2ND PULANG)	 
void seat_reservation_1st(int a, int b){    //a = maksimal baris dan b= maksimal kolom
    for(int i=1; i<=a;i++){                   //baris
		   	for(int j=1;j<=b;j++){            // kolom
			if(seat_booking[i][j]==1){        //jika baris dan kolom sudah dalam file maka program akan jalan
			cout<<setw(9)<<"[ X ]";}          // akan keluar [X]
  			else{cout<<setw(5)<<"["<<seat_booking_row_char[i-1]<<","<<j<<"]";}   //jika baris dan kolom belum ada dalam file maka akan keluar baris dan kolom 
				}
		       cout<<endl;
		   }
		   	bool check = true;       //define variable check sebagai nilai yang true 
		   	
		   	
		 while(check){        // selama ini true maka program berjalan
		   	cout << "\nEnter the row of seat you would like to book for [ROW : A,B,C...]: ";  // akan keluar line ini
		   	    cin>>row_alphabet;                                                            // input baris (alphabet)
		   		while(cin.fail()||row_alphabet<65||row_alphabet>65+a-1){  //row alphabet< 65 atau > 65+jumlah maks row-1 (65 itu dari ASCII)  
		   		cout<<"re-enter correctly: ";                
				cin.clear();            // clear error
		   		cin.ignore();           // clear buffer atau \n
				cin>>row_alphabet;}     //isi alphabet 

	     	
	     	cout<<"\nEnter the column of seat you would like to book for [COLUMN: 1,2,3,4,5]: ";
	     	    cin>>column;               //input kolom (angka)
	        	while(cin.fail()||column<1||column>b){  //selama yang diinput bukan suatu angka atau kurang dari 1 atau lebih besar dari kolom maka program akan berjalan
		   		cout<<"re-enter correctly: ";        
				cin.clear();             //clear error 
		   		cin.ignore();            //clear buffer atau /n
				 cin>>column;}           // input kolom (angka)
			   
		   	  switch(row_alphabet){          //bentuk kondisi percabangan, jika suatu kondisi benar maka blok yang bernilai benar atau sesuai maka akan dijalankan
		   	 	case 'A': row=1; break;      // jika row_alphabet adalah A maka row = 1, dan akan langsung keluar dari loop
		   	 	case 'B': row=2; break;      // jika row_alphabet adalah B maka row = 2, dan akan langsung keluar dari loop  
		   	 	case 'C': row=3; break;      // jika row_alphabet adalah C maka row = 3, dan akan langsung keluar dari loop
		   	 	case 'D': row=4; break;      // jika row_alphabet adalah D maka row = 4, dan akan langsung keluar dari loop
		   	 	case 'E': row=5; break;      // jika row_alphabet adalah E maka row = 5, dan akan langsung keluar dari loop
		   	 	case 'F': row=6; break;      // jika row_alphabet adalah F maka row = 6, dan akan langsung keluar dari loop
		   	 	case 'G': row=7; break;		 // jika row_alphabet adalah G maka row = 7, dan akan langsung keluar dari loop
		   	 	case 'H': row=8; break;      // jika row_alphabet adalah H maka row = 8, dan akan langsung keluar dari loop
		   	 	case 'I': row=9; break;      // jika row_alphabet adalah I maka row = 9, dan akan langsung keluar dari loop
		   	 	case 'J': row=10; break;     // jika row_alphabet adalah J maka row = 10, dan akan langsung keluar dari loop
				}
		    
				if (seat_booking[row][column]==1) {           //jika baris dan kolom sudah dalam file maka program akan berjalan
					cout<<"\n\nThe seat has been taken, please re-enter the seat: "<<endl;
					}
				else{
					check=false;   // jika baris dan kolom belum ada dalam file maka program akan berhenti
				break;             //keluar dari loop 
					}
		
	}
}

void seat_reservation_2nd(int a, int b){  //void adalah fungsi yang tidak mengembalikan nilai keluaran dari program . a = maksimal baris dan b= maksimal kolom
    for(int i=1; i<=a;i++){               //for loop untuk baris
		   	for(int j=1;j<=b;j++){        //for loop untuk kolom
			if(seat_booking_2nd[i][j]==1){  //jika baris dan kolom sudah ada dalam file maka program akan berjalan 
			cout<<setw(9)<<"[ X ]";}           //akan keluar [X]
  			else{cout<<setw(5)<<"["<<seat_booking_row_char[i-1]<<","<<j<<"]";}  //jika baris dan kolom tidak ada dalam file maka akan keluar baris dan kolom
				}
		       cout<<endl;
		   }
		   
		   	bool check = true;    //define variabel check sebagai nilai yang true 
		   	
		   	
		while(check){      //selama ini true maka program akan berjalan
		   	cout << "\nEnter the row of seat you would like to book for [ROW : A,B,C...]: ";  
		   	    cin>>row_alphabet;            //input baris (alphabet)
		   		while(cin.fail()||row_alphabet<65||row_alphabet>65+a-1){   //selama yang kita input bukan alphabet atau row alphabet< 65 atau > 65+jumlah maks row-1 (65 itu dari ASCII) maka program akan berjalan
		   		cout<<"re-enter correctly: ";
				cin.clear();           //clear error
		   		cin.ignore();          //clear buffer atau \n
				cin>>row_alphabet;}    //input baris (alphabet)

	     	
	     	cout<<"\nEnter the column of seat you would like to book for [COLUMN: 1,2,3,4,5]: ";
	     	    cin>>column2;                  //input kolom (integer)
	        	while(cin.fail()||column2<1||column2>b){   //selama yang kita input bukan suatu integer atau < 1 atau > dari maks kolom maka program akan berjalan
		   		cout<<"re-enter correctly: ";
				cin.clear();           //clear error
		   		cin.ignore();          //clear buffer atau /n
				 cin>>column2;}        //input kolom (integer)
			   
			   
		   	  switch(row_alphabet){       //bentuk kondisi percabangan, jika suatu kondisi benar maka blok yang bernilai benar atau sesuai maka akan dijalankan
		   	 	case 'A': row2=1; break;  //jika row_alphabet = A maka blok ini akan berjalan dan program akan langsung berhenti
		   	 	case 'B': row2=2; break;  //jika row_alphabet = B maka blok ini akan berjalan dan program akan langsung berhenti
		   	 	case 'C': row2=3; break;  //jika row_alphabet = C maka blok ini akan berjalan dan program akan langsung berhenti
		   	 	case 'D': row2=4; break;  //jika row_alphabet = D maka blok ini akan berjalan dan program akan langsung berhenti
		   	 	case 'E': row2=5; break;  //jika row_alphabet = E maka blok ini akan berjalan dan program akan langsung berhenti
		   	 	case 'F': row2=6; break;  //jika row_alphabet = F maka blok ini akan berjalan dan program akan langsung berhenti
		   	 	case 'G': row2=7; break;  //jika row_alphabet = G maka blok ini akan berjalan dan program akan langsung berhenti
		   	 	case 'H': row2=8; break;  //jika row_alphabet = H maka blok ini akan berjalan dan program akan langsung berhenti
		   	 	case 'I': row2=9; break;  //jika row_alphabet = I maka blok ini akan berjalan dan program akan langsung berhenti
		   	 	case 'J': row2=10; break; //jika row_alphabet = J maka blok ini akan berjalan dan program akan langsung berhenti
				}
		    
				if (seat_booking_2nd[row2][column2]==1) {          //baris dan kolom sudah ada dalam file maka program akan berjalan
					cout<<"\n\nThe seat has been taken, please re-enter the seat: "<<endl;    //akan keluar line ini 
					}
				else{                        
					check=false;          // jika baris dan kolom tidak ada dalam file maka program akan berhenti 
				break;
					}
	
	}
}

//FUNCTIONS SISTEM SEAT BOOKING
void seat_booking_map(){                 //function untuk seat booking
	readFile.open("dataPassengers.csv");     //membuka dan membaca file dalam file dataPassengers
	  
   while(getline(readFile, line)){           //selama filenya masih baca 1 line, yang dimana 1 line itu adalah 1 data penumpang 
   	   	stringstream ss(line);               //stringstream berfungsi untuk memecah 1 line atau  1 data passenger jadi beberapa bagian 
		getline(ss,airport_file,',');        //getline untuk baca airport_file dalam file untuk di define menjadi airport_file
		getline(ss,destination_file,',');    //getline untuk baca destination_file dalam file untuk di define menjadi destination_file
		getline(ss,flight2_file,',');        //getline untuk baca flight2_file dalam file untuk di define menjadi flight2_file
		getline(ss,date1_file,',');          //getline untuk baca date1_file dalam file untuk di define menjadi date1_file
		   istringstream(date1_file)>>date1;  //convert date1_file dari string ke int
		getline(ss,month1_file,',');          //getline untuk baca airport_file dalam file untuk di define menjadi airport_file               
		getline(ss,year1_file,',');           //getline untuk baca year1_file dalam file untuk di define menjadi year1_file
			istringstream(year1_file)>>year1;  //convert year1_file dari string ke int
	    getline(ss,time1_file,',');            //getline baca time1_file dalam file untuk di define menjadi time1_file
        if(flight2_file=="One way"){		   //jika flight2_file = one way maka program akan berjalan              
       		 if(airport==airport_file && destination_string==destination_file && date1==date && month1_file==monthNames[month-1] && year1==year && time1_file==time_departure_string){	//jika data yang kita input sama dengan yang ada dalam file maka program akan berjalan
			              getline(ss,passenger_range_file,',');                                    //getline untuk baca passenger_range_file dalam file untuk di define menjadi passenger_range_file
			              getline(ss,seat_class_file,',');                                         //getline untuk baca seat_class_file dalam file untuk di define menjadi seat_class_file
			              getline(ss,seat_position_row_file_1st,'.');                              //getline untuk baca seat_position_row_file_1st dalam file untuk di define menjadi seat_position_row_file_1st
			              		istringstream(seat_position_row_file_1st)>>seat_position_row_1st;  //convert seat_position_row_file_1st dari string ke int
						  getline(ss,seat_position_column_file_1st,',');                           //getline untuk baca seat_position_column_file_1st dalam file untuk di define menjadi seat_position_column_file_1st
			             		 istringstream(seat_position_column_file_1st)>>seat_position_column_1st; //convert seat_position_column_file_1st dalam file untuk di define menjadi seat_position_column_file_1st
			             		 
			              if(seat_class_file==seat_class_string){                               //jika seat class dalam file = dengan seat class yang kita input maka program akan berjalan
			              		seat_booking[seat_position_row_1st][seat_position_column_1st]=1;     //array seatbooking untuk seat position baris dan kolom = 1 berarti baris dan kolom yang diinput sudah ada dalam file
			              		if(seat_class_file=="Economy"){economy_1st++;}	                     //jika seat class dalam file = economy maka seat class economy akan bertambah 
								else if(seat_class_file=="Business Class"){business_1st++;}	         //jika seat class dalam file = business class maka seat bussines class akan bertambah
							}			              
			 }
	   } 
       else if(flight2_file=="Round trip"){ 			                              //jika flight dalam file = round trip maka program akan berjalan
			              getline(ss,date2_file,',');                                 //getline untuk baca date2_file dalam file untuk di define menjadi date2_file
       					  		istringstream(date2_file)>>date2_int;                 //convert date2_file dari string ke int
      				      getline(ss,month2_file,',');                                //getline untuk baca month2_file dalam file untuk di define menjadi month2_file
       					  getline(ss,year2_file,',');								  //getline untuk baca year2_file dalam file untuk di define menjadi year2_file
       					        istringstream(year2_file)>>year2_int;                 //convert year2_file dari string ke int
       					  getline(ss,time2_file,',');                                 //getline untuk baca time2_file dalam file untuk di define menjadi time2_file
       					  getline(ss,passenger_range_file,',');                       //getline untuk baca passenger_range_file dalam file untuk di define menjadi passenger_range_file
			              getline(ss,seat_class_file,',');                            //getline untuk baca seat_class_file dalam file untuk di define menjadi seat_class_file
			              
			              getline(ss,seat_position_row_file_1st,'.');                 //getline untuk baca seat_position_row_file_1st dalam file untuk di define menjadi seat_position_row_file_1st
			              		istringstream(seat_position_row_file_1st)>>seat_position_row_1st;        //convert seat_postion_row_file_1st dari string ke int
						  getline(ss,seat_position_column_file_1st,',');                                 //getline untuk baca seat_position_row_file_1st dalam file untuk di define menjadi seat_position_row_file_1st
			              		istringstream(seat_position_column_file_1st)>>seat_position_column_1st;  //convert seat_position_column_file_1st dari string ke int
			              getline(ss,seat_position_row_file_2nd,'.');                                    //getline untuk baca seat_position_column_file_1st dalam file untuk di define menjadi seat_position_column_file_1st
			              		istringstream(seat_position_row_file_2nd)>>seat_position_row_2nd;        //convert seat_position_row_2nd dari string ke int
						  getline(ss,seat_position_column_file_2nd,',');                                 //getline untuk baca seat_position_column_file_2nd dalam file untuk di define menjadi seat_position_column_file_2nd
			              		istringstream(seat_position_column_file_2nd)>>seat_position_column_2nd;  //convert seat_position_column_file_2nd dari string ke int
			              		
       	    if(airport==airport_file && destination_string==destination_file && date1==date && month1_file==monthNames[month-1] && year1==year && time1_file==time_departure_string){	//jika data yang kita input sama dengan yang ada dalam file maka program akan berjalan
			               if(seat_class_file==seat_class_string){                                        //jika seat class dalam file = seat class yang kita input maka program akan berjalan
			              		 seat_booking[seat_position_row_1st][seat_position_column_1st]=1;         //array seat booking untuk seat position row dan column = 1, berarti row dan column yang diinput sudah ada dalam file
						   		 if(seat_class_file=="Economy"){economy_1st++;}	                          //jika seat class dalam file = economy maka seat untuk economy akan bertambah, supaya bisa menghitung banyak yang booking di economy class
							 	 else if(seat_class_file=="Business Class"){business_1st++;}              //jika seat class dalam file = business class maka seat untuk business akan bertambah, supaya bisa menghitung banyak yang booking di business	  
							  }
				}
       	
       	   if(airport==airport_file && destination_string==destination_file && date2==date2_int && month2_file==monthNames[month2-1] && year2==year2_int && time2_file==time_return_string){	//jika data yang kita input sama dengan yang ada dalam file maka program akan berjalan
						  if(seat_class_file==seat_class_string){                                     //jika seat class dalam file  = seat class yang kita input  maka program akan berjalan
			             		 seat_booking_2nd[seat_position_row_2nd][seat_position_column_2nd]=1; // =1 ini berarti seat booking sudah diambil
			              		 if(seat_class_file=="Economy"){economy_2nd++;}	                      // ++ artinya nambah, biar bisa hitung passenger dalam class tersebut
							 	 else if(seat_class_file=="Business Class"){business_2nd++;}           //jika seat class dalam file = business class maka seat untuk business class akan bertambah, supaya bisa menghitung banyak yang booking di economy class
						   }
	 	   }
		}
}
 //Menutup file yang datanya akan dibaca oleh program
 readFile.close();

 //Jika Kursi Penuh 
  if(economy_1st==50||business_1st==16){   			 //Jika Kursi Berangkat Penuh, maa program ini berjalan
  	cout<<"Sorry, no seats remaining for departure date. Please rebook your reservation"<<endl;
  	return;   										//keluar dari function 
  }
  else if(economy_2nd==50||business_2nd==16){     	//Jika Kursi Pulang Penuh, maa program ini berjalan
  	cout<<"Sorry, no seats remaining for returning date. Please rebook your reservation"<<endl;
  	return; 										// keluar dari function
  }
 
  system("CLS"); //Clearing the Screen, hapus bekas output   
  
   //Jika hanya pergi (One way)
   cout<<"\n==============  AIRLINE BOOKING DEPARTURE- "<<airport<<" to "<<destination_string<<" "<<date<<" "<<monthNames[month-1]<<" "<<year<<" "<<time_departure_string<<"  =============="<<endl<<endl;
   if(seat_class_string=="Economy"){
   seat_reservation_1st(10,5);}      //Kalau Economy
   else{seat_reservation_1st(4,4);} //Kalau Business class
   
   
   //Jika juga Pulang, maka program minta jalani kursi dua kali
if(flight2=="Round trip"){
	cout<<"\n\n==============  AIRLINE BOOKING RETURNING- "<<destination_string<<" to "<<airport<<" "<<date2<<" "<<monthNames[month2-1]<<" "<<year2<<" "<<time_return_string<<"  =============="<<endl<<endl; 

   if(seat_class_string=="Economy"){    //
   seat_reservation_2nd(10,5);} 	//Kalau Economy    ,10 baris 5 kolom
   else{seat_reservation_2nd(4,4);} //Kalau Business Class  
} 
   
}


//Function Void Program Menu-1 (Booking Flight)
void booking_flight(){
	    ofstream myFile; //mendefinsikan variabel file (untuk input atau edit file) 
		myFile.open("dataPassengers.csv", ios::app);  //membuka file dataPassengers.csv supaya mengisi+tambahin baris terakhir (ios::app)
     	    bar(); //memanggil fungsi bar
     	 	cout<<"\nFrom:"<<endl; //berangkat dari..
     	 	cout<<"\n1.Soekarno-Hatta International Airport (Banten)"<<"\n2.Sam Ratulangi International Airport (Manado)"
     	 	    <<"\n3.Ngurah Rai International Airport (Denpasar)"<<"\n4.Sentani Airport (Jayapura)"
     	 	    <<"\n5.Kualanamu Airport (Medan)"<<endl;
     	    cout<<"\nPlease enter your choice: ";
     	    cin>>from; //input variabel untuk titik berangkat (dalam int)
     	    
     	    while(from<1||from>5){ //selama user input angka selain 1-5, program minta isi variabel from sampai benar
			 cout<<"Please enter the right option: ";
			 cin>>from;}
			 
     	      switch(from){ //Kondisi nilai from supaya memasukkan string pada variabel airport
     	      	  case 1:
     	      			airport="Soekarno-Hatta International Airport (Banten)";
     	      	  		break;
     	      	  case 2:	
     	      	  		airport="Sam Ratulangi International Airport (Manado)";
     	      	  		break;
     	      	   case 3:	
     	      	  		airport="Ngurah Rai International Airport (Denpasar)";
     	      	  		break;
     	           case 4:
     	            	airport="Sentani Airport (Jayapura)";
     	      	  		break;
     	           case 5:
     	           		airport="Kualanamu Airport (Medan)";
 	                    break;
			  }       
              cout<<endl;  
              
     	    //Tujuan
     	    bar();
     	 	cout<<"\nTo:"<<endl; 
     	 	cout<<"\n1.Singapore Changi Airport (Singapore)"<<"\n2.Suvarnabhumi Airport (Bangkok| Thailand)"
			    <<"\n3.Sydney Kingsford Smith Airport (Sydney| Australia)"<<"\n4.Kuala Lumpur International Airport (Kuala Lumpur| Malaysia)"
				<<"\n5.Beijing Capital International Airport (Beijing| China)"<<endl;
     	 	cout<<"\nPlease enter your destination: ";
     	 	cin>>to; //Input variabel untuk titik tujuan (dalam int)
     	 	
     	    while(to<1||to>5){ //selama user input angka selain 1-5, program minta isi variabel from sampai benar
			cout<<"Please enter the right choice: ";
			 cin>>to;}
     	 	
     	 	switch(to){  //Kondisi nilai to supaya memasukkan string pada variabel desination_string
     	 		case 1: destination_string="Singapore Changi Airport (Singapore)";
     	 			break;
     	 		case 2: destination_string="Suvarnabhumi Airport (Bangkok| Thailand)";
     	 			break;
     	 		case 3: destination_string="Sydney Kingsford Smith Airport (Sydney| Australia)";
     	 			break;
     	 		case 4: destination_string="Kuala Lumpur International Airport (Kuala Lumpur| Malaysia)";
     	 			break;
     	 		case 5: destination_string="Beijing Capital International Airport (Beijing| China)";
     	 			break;
					}
     	 	cout<<endl;
     	 	
     	 	
     	 	//One way= pergi, Round trip= pulang pergi.
     	 	bar(); 												//memanggil fungsi untuk mengeluarkan bar
     	 	cout<<"1.One way"<<"\n2.Round trip"<<endl; 
			do{ 												//menjalankan program di dalam do dan menjalankannya lagi (selama kondisi dalam while terpenuhi)
     	 	cout<<"\nPlease enter your choice (above): ";
     	 	cin>>flight1; 										//input variabel untuk tipe penerbangan (dalam int)
     	 	    switch(flight1){ 
     	 	       case 1:                                      //Kondisi nilai flight1 untuk memasukkan string (one way/ round trip) pada flight2
     	 	       	     flight2="One way";                     
     					 break;
				   case 2:
				   	     flight2="Round trip";
     					 break;
				  }
				  } while(flight1!=1 && flight1!=2);          //Selama opsi penerbangan (flight1) tidak sesuai (bukan 1 atau 2), program dalam do akan dijalankan ulang 
				  cout<<endl;
				  
     	 	//tanggal penerbangan (atau dan kembali)    	
     	 	bar(); 
			  if(flight1==1){								//Menjalankan program jika opsi penerbangannya 1(One way)
     			cout<<"Departure Date (due one day before the flight): "<<endl; 
     			ddmmyyyy();  								//Menjalankan fungsi ddmmyyyy untuk input dan validasi tanggal berangkat
			    departure_condition();  					//Membandingkan tanggal berangkat dengan tanggal sekarang (apakah lebih awal (salah) atau lebih telat 1 hari (benar))
						 	
			 	//jam berangkat penerbangan	    	 
			    cout<<"Time: "<<endl;
			    cout<<"1) 08:00  2) 12:00  3) 18:00 "<<endl;  //Mengeluarkan opsi jam penerbangan
				cin>>flight_time_departure; 																    //Input jam penerbangan (dalam int, sesuai opsi)
				  while(flight_time_departure<1 || flight_time_departure> 3){									//Selama opsi bukan 1-8, user diminta mengisi opsi sampai benar
				  	cout<<"Please choose your option correctly for the flight time: ";
				  	cin>>flight_time_departure; 															   //Input opsi jam penerbangan
			     	  }
		     	
		     	   switch(flight_time_departure){							//Kondisi nilai flight_time_departure supaya memasukkan string pada variabel time_departure_string
		     	   	   case 1: time_departure_string="08:00";               
		     	   	     break;
		     	   	   case 2: time_departure_string="12:00";
		     	   	   	 break;
		     	   	   case 3: time_departure_string="18:00";
						break;
					}
         }
					 
     		  else if(flight1==2){                                    //Menjalankan program jika opsi penerbangannya Round Trip
     		  	cout<<"Departure Date (due one day before the flight): "<<endl;      		
     			ddmmyyyy();                                           //Menjalankan funsgi ddmmyyyy untuk input dan validasi tanggal berangkat
                departure_condition();                               
					    
				//jam berangkat penerbangan	    
                cout<<"Time: "<<endl;  
			    cout<<"1) 08:00  2) 12:00  3) 18:00 "<<endl;
				cin>>flight_time_departure;
				  while(flight_time_departure<1 || flight_time_departure> 3){  	//Selama opsi bukan 1-3, user diminta mengisi opsi ulang dengan benar
				  	cout<<"Please choose your option correctly for the flight time: ";
				  	cin>>flight_time_departure;
				  }
			 	   switch(flight_time_departure){ 					//Kondisi nilai flight_time_departure supaya memasukkan string pada variabel time_departure_string
		     	   	   case 1: time_departure_string="08:00";
		     	   	     break;
		     	   	   case 2: time_departure_string="12:00";
		     	   	   	 break;
		     	   	   case 3: time_departure_string="18:00";
                          break;
					}
				    	
     			cout<<"\nReturn Date: "<<endl;
     	        ddmmyyyy2();									  			//Mejalankan fungsi input dan validasi tanggal pulang
     	        //MEMBANDINGKAN TANGGAL PULANG DENGAN TANGGAL BERANGKAT
     	        while(year2<=year){ 										 //Tanggal pulang yang benar: year2>=year, month2>=month, date2>=date jika monthnya sama.
     	        	if(year2<year){
     	        		cout<<"\nReenter the returning date: "<<endl;
     	        		ddmmyyyy2(); 										//Menjalankan function untuk input tanggal pulang ulang 
					 }
					 else if(month2<month){
					 	cout<<"\nReenter the returning date: "<<endl;
     	        		ddmmyyyy2();
					 }
					 else if(date2<=date && month2==month){
					 	cout<<"\nReenter the returning date: "<<endl;
     	        		ddmmyyyy2();
					 }
					 else{break;}					 //Jika kondisi diatas tidak terpenuhi, loop while diatsa akan berhenti (break)
					 }

				
		 	        cout<<"Time: "<<endl;  
			        cout<<"1) 11:00  2) 16:00  3) 20:00 "<<endl;
			    	cin>>flight_time_return;                      				//Input jam pulang ke flight_time_return (dala int, sesuai opsi)
				    while(flight_time_return<1 || flight_time_return> 3){  		//Selama opsi bukan 1-8, user diminta isi opsi jam pulang sampai benar
				  	cout<<"Please choose your option correctly for the flight time: ";  
				  	cin>>flight_time_return;									//Input opsi jam pulang
				          }
		    	   switch(flight_time_return){									//Kondisi nilai flight_time_return supaya memasukkan string pada variabel time_return_string
		     	   	   case 1: time_return_string ="11:00";
		     	   	     break;
		     	   	   case 2: time_return_string ="16:00";
		     	   	   	 break;
		     	   	   case 3: time_return_string ="20:00";
		     	   	   	 break;
					}     
				 }
			   
			
			bar2();										
			cout<<"\nPassengers: "<<endl;					//Opsi usia Passengers
		    cout<<"1.Adult (above 12 years)"<<endl;
			cout<<"2.Child (4-12 years)"<<endl;
			cout<<"Enter your age range: ";
			cin>>passenger_range;							//Input opsi passengers
					
			while(passenger_range!=1&&passenger_range!=2){  //Menjalankan program dalam while jika passsenger_range bukan 1-2
				  cout<<"Please enter your choice (correctly) for age range : "; 
				  cin>>passenger_range;}					//Isi kembali nilai passenger_range sampai benar (1 atau 2)
			switch(passenger_range){						//Kondisi nilai passenger_range supaya memasukkan string ke variabel passenger_range_string
				case 1: passenger_range_string="Adult";     
					break;
				case 2: passenger_range_string="Child";
					break;
			}	  
							  
            bar(); 
            cout<<"\nSeat Class: "<<endl;
            cout<<"1.Economy "<<endl;
            cout<<"2.Business Class "<<endl;
            cout<<"Choose your class: ";
			cin>>seat_class;
            while(seat_class!=1 && seat_class!=2){
            	  cout<<"Please enter the right option: ";
				  cin>>seat_class;}
			if(seat_class==1){seat_class_string="Economy";}
			else if(seat_class=2){seat_class_string="Business Class";}
					 
			 //DENAH SEAT BOOKING
			 bar2();
			 cout<<endl;
			 seat_booking_map();
			 if(economy_1st==50||business_1st==16){return;}   		 //Jika Kursi Berangkat Penuh, maa program ini berjalan
 			 else if(economy_2nd==50||business_2nd==16){return;}     //Jika Kursi Pulang Penuh, maa program ini berjalan
 			 
  			//SAVE DATA KE FILE dataPassengers.csv
  			if(flight2=="One way"){
			 myFile<<airport<<","<<destination_string<<","<<flight2<<","<<date<<","<<monthNames[month-1]<<","<<year<<","
				   <<time_departure_string<<","<<passenger_range_string<<","<<seat_class_string<<",";
			}
			else if(flight2=="Round trip"){
			  myFile<<airport<<","<<destination_string<<","<<flight2<<","<<date<<","<<monthNames[month-1]<<","<<year<<","
				   <<time_departure_string<<","<<date2<<","<<monthNames[month2-1]<<","<<year2<<","<<time_return_string<<","
				   <<passenger_range_string<<","<<seat_class_string<<",";
			}
			  	
			 if(flight2=="One way"){myFile<<row<<"."<<column<<",";}
			 else if (flight2=="Round trip"){
			 myFile<<row<<"."<<column<<",";
			 myFile<<row2<<"."<<column2<<",";}   
			 
			//BOOKING DETAILS   
			bar2();
			system("CLS");            //Clearing the Screen, remove bekas output
			cout<<"\nBOOKING DETAILS"<<endl;                  
			
			  cout<<"\nPlease enter your name: ";   //Nama
			  cin.ignore();   		  //untuk merefresh buffer, jadi cin tidak langsung masukkin value ke variabel (tapi cin-->buffer-->variable). 
			  getline(cin,name);     //Input nama lebih dari 1 kata
			  myFile<<name<<",";     //Simpan nama ke File
			  
			  cout<<"\nGender (M/F): "; //Gender
			  while(cin>>gender){       //Menjalankan program selama kita input char gender
				  if(gender=='M'|| gender=='F'||gender=='m'||gender=='f'){
			  	   break;               //Jika kondisi terpenuhi, maka loop while berhenti (break) dan next to bagian selanjutnya
				   }     
			     else{                  //Jika (selama) kondisi tidak terpenuhi, maka akan mengeluarkan perintah untuk input char gender ulang
				  cout<<"Please re-enter the gender correctly: ";
				   }
				}
				  if(gender=='M'||gender=='m')  //Kondisi untuk memasukkan string ke gender_string sesuai abjad
					{gender_string="Male";
					}
				  else if(gender=='F'||gender=='f')
				    {gender_string="Female";
					}
				 myFile<<gender_string<<",";    //Simpan string gender_string (Male atau Female) ke file
				
			  cout<<"\nPhone Number (+62 _______): ";   //Nomor Telepon
			  cin>>phone_number;
		      while(digit_number(phone_number)<10||digit_number(phone_number)>12){ //Menjalani program bawah selama digit nomor telepon (tidak termasuk angka depan 0 atau +62) <10 atau >12
					cout<<"Please enter the right digit (after +62): ";    //Perintah untuk input ulang nomor telepon
					cin>>phone_number;	
			        }
			    myFile<<phone_number<<",";	 							  //Simpan long long phone_number ke file
			  
			  cout<<"\nCreate Email Address: ";                                 //Alamat Email
			  while(cin>>email){										//Menjalani program dalam bracket selama input email
			  bool e_validity=email_validity(email);   					//memasukkan hasil function email_validity() ke e_validity				
			  	 if(e_validity){                                        
				     break;											  //Jika email valid (e_validity==true), maka loop akan berhenti
				      }
				 else{
				 	cout<<"Invalid! Please create your email correctly: "; //Jika email invalid, maka program terus minta input email sampai valid.
				   }  
			  }
			   myFile<<email<<",";										//simpan email ke file
			  
			  cout<<"\nCreate Password [min.8 characters (including one Capital Letter, one number, & one special character)]: ";  //Perintah Input Password
   			      cin>>password;   //Input password 
  			      bool pass_validity= password_validity(password);  //define bool pass_validity sebagai nilai apakah password valid (true) atau tidak (false)
     
     			  while (pass_validity==false){                      //selama password tidak valid, maka akan diminta untuk input password kembali
     			 cout<<"Invalid! Please create your password correctly: ";
     			 cin>>password;
     			 pass_validity= password_validity(password);         //apakah password yang terakhir diinput valid atau tidak
       					}
			   myFile<<password<<",";                          //simpan password ke file. Password yang ini sudah discreening valid
			  
			  //HARGA PENERBANGAN
			  if(airport=="Soekarno-Hatta International Airport (Banten)"){ 
				   if(destination_string=="Singapore Changi Airport (Singapore)"){price=1775010;}
				   else if(destination_string=="Suvarnabhumi Airport (Bangkok| Thailand)"){price=2991220;}
				   else if(destination_string=="Sydney Kingsford Smith Airport (Sydney| Australia)"){price=5078510;}
				   else if(destination_string=="Kuala Lumpur International Airport (Kuala Lumpur| Malaysia)"){price=1758570;}
				   else if(destination_string=="Beijing Capital International Airport (Beijing| China)"){price=30775100;}
				   }		   
			  else if(airport=="Sam Ratulangi International Airport (Manado)"){
			       if(destination_string=="Singapore Changi Airport (Singapore)"){price=3674100;}
				   else if(destination_string=="Suvarnabhumi Airport (Bangkok| Thailand)"){price=7840000;}
				   else if(destination_string=="Sydney Kingsford Smith Airport (Sydney| Australia)"){price=21711000;}
				   else if(destination_string=="Kuala Lumpur International Airport (Kuala Lumpur| Malaysia)"){price=4108000;}
				   else if(destination_string=="Beijing Capital International Airport (Beijing| China)"){price=31500000;}
				   }
			  else if(airport=="Ngurah Rai International Airport (Denpasar)"){
			       if(destination_string=="Singapore Changi Airport (Singapore)"){price=1469000;}
				   else if(destination_string=="Suvarnabhumi Airport (Bangkok| Thailand)"){price=2909050;}
				   else if(destination_string=="Sydney Kingsford Smith Airport (Sydney| Australia)"){price=2880000;}
				   else if(destination_string=="Kuala Lumpur International Airport (Kuala Lumpur| Malaysia)"){price=1610000;}
				   else if(destination_string=="Beijing Capital International Airport (Beijing| China)"){price=27269000;}
				   }
			  else if(airport=="Sentani Airport (Jayapura)"){
				if(destination_string=="Singapore Changi Airport (Singapore)"){price==8529900;}
				   else if(destination_string=="Suvarnabhumi Airport (Bangkok| Thailand)"){price==10100000;}
				   else if(destination_string=="Sydney Kingsford Smith Airport (Sydney| Australia)"){price=13300000;}
				   else if(destination_string=="Kuala Lumpur International Airport (Kuala Lumpur| Malaysia)"){price=7600000;}
				   else if(destination_string=="Beijing Capital International Airport (Beijing| China)"){price=56300000;}
				   }
			  else if(airport=="Kualanamu Airport (Medan)"){
			  	   if(destination_string=="Singapore Changi Airport (Singapore)"){price=1810300;}
				   else if(destination_string=="Suvarnabhumi Airport (Bangkok| Thailand)"){price=1659000;}
				   else if(destination_string=="Sydney Kingsford Smith Airport (Sydney| Australia)"){price=5400100;}
				   else if(destination_string=="Kuala Lumpur International Airport (Kuala Lumpur| Malaysia)"){price=1012000;}
				   else if(destination_string=="Beijing Capital International Airport (Beijing| China)"){price=42080000;}
				   }
			  
			  bar();
			   if(flight2=="One way"){											  //Harga sekali penerbangan
			        if(passenger_range==2){price=price*0.99;}                     //Jika jangkauan umurnya anak-anak (opsi ke 2)
			        if(seat_class_string=="Business Class"){price=price*3.5;}     //Jika kelasnya Business Class
			        cout<<"The price for One Way will be Rp "<<price<<endl;
					myFile<<price<<"."<<endl;} 
			        
			   else if(flight2=="Round trip"){										//Harga seupama, bukan harga asli 
			        if(seat_class_string=="Business Class"){                         //Jika kelas penerbanganya Business Class
					     if(passenger_range==2){price_roundtrip=price*0.99*3*2.5;}   //Jika anak-anak, maka harga menjadi lebih rendah
					     else{price_roundtrip=price*3*2.5;}                          //Jika dewasa, maka harga menjadi lebih tinggi
					}
			 		else{														   //Jika kelas penerbangan Economy
					   if(passenger_range==2){price_roundtrip=price*0.99*2.5;}           //Jika anak-anak, maka harga menjadi lebih rendah
					   else{price_roundtrip=price*2.5;}
					   }                                //Jika dewasa, maka harga menjadi lebih tinggi
			   		cout<<"The price for Round Trip will be Rp "<<price_roundtrip<<endl;  
			 		myFile<<price_roundtrip<<"."<<endl; 
			 	}
			 
			   cout<<"\nThank You for Booking on Nusantara Airline Flight, Enjoy the Flight\n"<<endl;  
			  
			 //Close the file and return to main menu 
			  	myFile.close();     //menutup file dataPassengers.csv setelah dibuka sebelumnya
				back_to_menu();     //function yang memberi perintah tekan key apapun untuk lanjut ke main menu, serta clear screen (hasil bekas" output). 
}

void search_flight(){
		 ifstream readFile;    					 //Tipe data input yang memungkinkan kita melakukan pembacaan informasi dari file
		 int c(0);                                      //Untuk menghitung berapa banyak data yang bersesuaian dengan input nama
		 
		 readFile.open("dataPassengers.csv");    //Membuka file dataPassengers.csv

		 cout<<"Please enter your full name: ";		//Input nama lengkap yang akan disearch
		 cin.ignore();							   //Digunakan untuk clear buffer input sebelumnya, supaya line code cin ini tidak diskip oleh program. 
		 getline(cin,test);
		 cout<<endl;
		 
		while(getline(readFile, line)){
		 				stringstream ss(line);                //Mengaitkan objek string dengan stream yang memungkinkan membaca string dari data pecah-pecah yang di extract
		 				getline(ss,airport_file,',');		 //Membaca string airport_file dari input
		    			getline(ss,destination_file,',');   //Membaca string destination_file dari input
		    			getline(ss,flight2_file,',');      	//Membaca string flight2_file dari input
		    			getline(ss,date1_file,',');		    //Membaca string date1_file dari input
		   				getline(ss,month1_file,',');     	//Membaca string date1_file dari input
		   				getline(ss,year1_file,',');			//Membaca string year1_file dari input
		   				getline(ss,time1_file,',');			//Membaca string time1_file dari input
		   				
		 	if(flight2_file=="One way"){     //Kalau kategori flight2 nya one way (sekali penerbangan) maka program ini yang akan berjalan		   			
		   				getline(ss,passenger_range_file,',');   		//Membaca string passenger_range_file (jangakauan umur penumpang) dari input
		   				getline(ss,seat_class_file,',');				//Membaca string seat_class_file dari input
		   				getline(ss,seat_position_row_file_1st,'.'); 	//Membaca string row_file dari input
		   				    istringstream(seat_position_row_file_1st)>>seat_position_row_1st;   	//istringstream = convert dari string ke int
		   				getline(ss,seat_position_column_file_1st,',');								//Membaca string column_file dari input
		   					istringstream(seat_position_column_file_1st)>>seat_position_column_1st;  
		   				getline(ss,name_file,',');				//Membaca string name_file dari input
		   				getline(ss,gender_file, ',');			//Membaca string gender_file dari input
		   				getline(ss,phone_number_file, ',');		//Membaca string phone_number_file dari input
		   				getline(ss,email_file, ',');			//Membaca string email_file dari input
		   				getline(ss,password_file, ',');			//Membaca string password_file  dari input
		   				getline(ss,price_file,'.');			//Membaca string price_file dari input
		   				
		   				if(test==name_file){
		   				bar();
					   	cout<<"Name: "<<name_file<<endl;								//Mengeluarkan output name dari string name_file
		   				cout<<"Gender: "<<gender_file<<endl;							//Mengeluarkan output gender dari string gender_file
		   				cout<<"Phone Number: "<<"+62"<<phone_number_file<<endl;				//Mengeluarkan output phone number dari string phone_number_file
					   	cout<<"Airport: "<<airport_file<<endl;						//Mengeluarkan output airport dari string airport_file
					   	cout<<"Destination: "<<destination_file<<endl;				//Mengeluarkan output destination dari string destination_file
					   	cout<<"Flight: "<<flight2_file<<endl;							//Mengeluarkan output flight dari string flight2_file
						cout<<"Month: "<<month1_file<<endl;							//Mengeluarkan output month dari string month1_file
						cout<<"Department Date: "<<date1_file<<" "<<month1_file<<" "<<year1_file<<endl;			//Mengeluarkan output department date dari string date1_file, month1_file, year1_file
						cout<<"Time: "<<time1_file<<endl;															//Mengeluarkan output time dari string time1_file
						cout<<"Seat Position: "<<seat_booking_row_char[seat_position_row_1st-1]<<"."<<seat_position_column_1st<<endl;	//Mengeluarkan output seat position dari string row_file dan column_file
						cout<<"Passenger Age: "<<passenger_range_file<<endl;									//Mengeluarkan output passenger range dari string passenger_range_file
						cout<<"Seat Class: "<<seat_class_file<<endl;               								//Mengeluarkan output seat class dari string seat_class_file
						cout<<"Price: "<<"Rp."<<price_file<<endl;						  								//Mengeluarkan output price
						c++;
						} 
			 	}
		 
		  		else if(flight2_file=="Round trip"){
		   			    getline(ss,date2_file,',');				 //Membaca string date2_file dari input
		   				getline(ss,month2_file,',');             //Membaca string month2_file dari input
		   				getline(ss,year2_file,',');				 //Membaca string year2_file dari input
						getline(ss,time2_file,',');             //Membaca string time2_file dari input
		   				getline(ss,passenger_range_file,',');   
		   				getline(ss,seat_class_file,',');		
		   				getline(ss,seat_position_row_file_1st,'.'); 	 			//Membaca string row_file dari input
		   				    istringstream(seat_position_row_file_1st)>>seat_position_row_1st;   
		   				getline(ss,seat_position_column_file_1st,',');			    //Membaca string column_file dari input
		   					istringstream(seat_position_column_file_1st)>>seat_position_column_1st; 
		   				getline(ss,seat_position_row_file_2nd,'.'); 	 			//Membaca string row2_file (posisi baris duduk pulang) dari input
		   				    istringstream(seat_position_row_file_2nd)>>seat_position_row_2nd;   
		   				getline(ss,seat_position_column_file_2nd,',');			    //Membaca string column2_file (posisi baris duduk pulang) dari input
		   					istringstream(seat_position_column_file_2nd)>>seat_position_column_2nd;			
		   				getline(ss,name_file,',');				
		   				getline(ss,gender_file, ',');			
		   				getline(ss,phone_number_file, ',');		
		   				getline(ss,email_file, ',');			
		   				getline(ss,password_file, ',');			
		   				getline(ss,price_file,'.');			
		   			
		   				if(test==name_file){//Kalau kita masukkan nama file yang akan di search yang kategori nya round trip maka output nya adalah sbb
		   				bar();	
		   				cout<<"Name: "<<name_file<<endl;
		   				cout<<"Gender: "<<gender_file<<endl;
		   				cout<<"Phone Number: "<<"+62"<<phone_number_file<<endl;
					   	cout<<"Airport: "<<airport_file<<endl;
					   	cout<<"Destination: "<<destination_file<<endl;
					   	cout<<"Flight: "<<flight2_file<<endl;
						cout<<"Month: "<<month1_file<<endl;
						cout<<"Department Date: "<<date1_file<<" "<<month1_file<<" "<<year1_file<<endl;
						cout<<"Time: "<<time1_file<<endl;
						cout<<"Seat Position Departure: "<<seat_booking_row_char[seat_position_row_1st-1]<<"."<<seat_position_column_1st<<endl;
						cout<<"Returning Date: "<<date2_file<<" "<<month2_file<<" "<<year2_file<<endl;	//Mengeluarkan output returning date dari string date2_file, month2_file, year2_file
						cout<<"Time: "<<time2_file<<endl;													//Mengeluarkan output time dari string time2_file
						cout<<"Seat Position Returning: "<<seat_booking_row_char[seat_position_row_2nd-1]<<"."<<seat_position_column_2nd<<endl;
						cout<<"Passenger Age: "<<passenger_range_file<<endl;
						cout<<"Seat Class: "<<seat_class_file<<endl;
						cout<<"Price: "<<"Rp."<<price_file<<endl;
						++c;
						}
		   		}
		   		
	 }
	 
	 	 if(c==0){
				 	cout<<"No data has been found."<<endl;
				     }
	   
		 readFile.close();
		 cout<<endl;
} 

void delete_flight(){
	 ifstream read;                              
     ofstream write;
         string email_test, password_test;        //Variabel string untuk input email dan password
		 int c(0);                               //Untuk menghitung berapa banyak data yang kedelete
		 
 		  read.open("dataPassengers.csv");        //Read (variabel ifstream) untuk membaca data dan open file dataPassengers.csv 
		  write.open("dataPassengers2.csv");      //Write (variabel ofstream) untuk open file dataPassengers2.csv sebagai file temporary (akan direname dengan dataPassengers.csv) 
		  
		  cout<<"Please enter your email: ";        //Perintah input email
     	  cin.ignore();							    //Digunakan untuk clear buffer input sebelumnya, supaya line code cin ini tidak diskip oleh program. 
		  getline(cin,email_test);
		  cout<<"\nPlease enter your password: ";   //Perintah input password
		  getline(cin,password_test);
		  cout<<endl;
		 
		   while(getline(read,line)){
		 				stringstream ss(line);
		 				getline(ss,airport_file,',');
		 				getline(ss,destination_file,',');
		    			getline(ss,flight2_file,',');
		    			getline(ss,date1_file,',');
		   				getline(ss,month1_file,',');
		   				getline(ss,year1_file,',');
		   				getline(ss,time1_file,',');
		   if(flight2_file=="One way"){
		   				getline(ss,passenger_range_file,',');   		//Membaca string passenger_range_file (jangakauan umur penumpang) dari input
		   				getline(ss,seat_class_file,',');				//Membaca string seat_class_file dari input
		   				getline(ss,seat_position_row_file_1st,'.'); 	//Membaca string row_file dari input
		   				    istringstream(seat_position_row_file_1st)>>seat_position_row_1st;   	//istringstream = convert dari string ke int
		   				getline(ss,seat_position_column_file_1st,',');								//Membaca string column_file dari input
		   					istringstream(seat_position_column_file_1st)>>seat_position_column_1st;  
		   				getline(ss,name_file,',');				//Membaca string name_file dari input
		   				getline(ss,gender_file, ',');			//Membaca string gender_file dari input
		   				getline(ss,phone_number_file, ',');		//Membaca string phone_number_file dari input
		   				getline(ss,email_file, ',');			//Membaca string email_file dari input
		   				getline(ss,password_file, ',');			//Membaca string password_file  dari input
		   				getline(ss,price_file,'.');				//Membaca string price_file dari input
		   				
		  	  			 if(password_test!=password_file || email_test !=email_file){
						  write<<airport_file<<","<<destination_file<<","<<flight2_file<<","<<date1_file<<","<<month1_file<<","<<year1_file<<","
					 	  <<time1_file<<","<<passenger_range_file<<","<<seat_class_file<<","<<seat_position_row_file_1st<<"."<<seat_position_column_file_1st<<","
						  <<name_file<<","<<gender_file<<","<<phone_number_file<<","<<email_file<<","<<password_file<<","<<price_file<<"."<<endl;
					}
						else{cout<<"The data has been removed"<<endl;
				     		++c;}
				 }
				
		  else if(flight2_file=="Round trip"){
						getline(ss,date2_file,',');				 //Membaca string date2_file dari input
		   				getline(ss,month2_file,',');             //Membaca string month2_file dari input
		   				getline(ss,year2_file,',');				 //Membaca string year2_file dari input
						getline(ss,time2_file,',');             //Membaca string time2_file dari input
		   				getline(ss,passenger_range_file,',');   
		   				getline(ss,seat_class_file,',');		
		   				getline(ss,seat_position_row_file_1st,'.'); 	 			//Membaca string row_file dari input
		   				getline(ss,seat_position_column_file_1st,',');			    //Membaca string column_file dari input
		   				getline(ss,seat_position_row_file_2nd,'.'); 	 			//Membaca string row2_file (posisi baris duduk pulang) dari input
		   				getline(ss,seat_position_column_file_2nd,',');			    //Membaca string column2_file (posisi baris duduk pulang) dari input
		   				getline(ss,name_file,',');				
		   				getline(ss,gender_file, ',');			
		   				getline(ss,phone_number_file, ',');		
		   				getline(ss,email_file, ',');			
		   				getline(ss,password_file, ',');			
		   				getline(ss,price_file,'.'); 	
						   	
						if(password_test!=password_file || email_test !=email_file){
					      write<<airport_file<<","<<destination_file<<","<<flight2_file<<","<<date1_file<<","<<month1_file<<","<<year1_file<<","
					 	  <<time1_file<<","<<date2_file<<","<<month2_file<<","<<year2_file<<","<<time2_file<<","<<passenger_range_file<<","<<seat_class_file<<","
						  <<seat_position_row_file_1st<<"."<<seat_position_column_file_1st<<","<<seat_position_row_file_2nd<<"."<<seat_position_column_file_2nd
						  <<","<<name_file<<","<<gender_file<<","<<phone_number_file<<"," <<email_file<<","<<password_file<<","<<price_file<<"."<<endl;
						 }
						else{cout<<"The data has been removed"<<endl;
				        ++c;
				      		}
	      	   	}
		}
		       		 if(c==0){
				 	cout<<"No data has been deleted. Please check your email or password"<<endl;         
				     }
		   
		  			write.close();													//tutup file variabel write
		  			read.close();												    //tutup file variabel read
					  	
					if (remove("dataPassengers.csv") != 0){                          //Supaya ada warning error apabila dataPassengers file yang lama tidak terhapus
					cout << "\nTemporary file is not deleted";}
					if (rename("dataPassengers2.csv", "dataPassengers.csv") != 0) {  //Supaya ada warning error apabila dataPassengers2 file tidak replace/ rename dengan dataPassengers.csv
					cout << "\nFile does not rename";} 
					else {cout << "\n";}	
			cout<<endl;		 
}

int main(){
	
	//ios::out (default) operasi output;
	//ios::app menuliskan pada akhir baris;
	//ios::trunc (default) membuat file jika tidak ada, dan kalau ada akan dhapus
	//ios ::in
	//ios:: mulai dari akhir file
	//ios::binary = untuk membaca file binary

 loop:
         menu_main();
	//Body
	//Create Seat Booking Ticket
     	 if(menu==1){             //Menjalankan program di dalam bracket jika menu=1 (melakukan Booking)
     	  booking_flight();       //Function untuk mengeluarkan program di menu 1 (melakukan Booking)
     	     if(economy_1st==50||business_1st==16){exit(0);}   		 //Jika Kursi Berangkat Penuh, maa program ini selesai
 			 else if(economy_2nd==50||business_2nd==16){exit(0);}     //Jika Kursi Pulang Penuh, maa program ini selesai
     	  goto loop;			 //kembali ke line code menu_main() untuk menampilkan Main Menu kembali;
		  }
		  
	//Search Seat Booking Ticket	  
         else if(menu==2){
	     search_flight();       	  //Menjalankan function untuk menu ke 2 (Search Data Penumpang)
		 back_to_menu();              //Perintah "press any key" untuk return ke main menu
		  goto loop;				  //Lompat ke line code "loop: "
		}
         
    //Delete or Cancel Seat Booking Ticket  
     	 else if(menu==3){
     	 	 delete_flight();		//Menjalankan function untuk menu ke 3 (Cancel Flight)
		     back_to_menu();  	 		
			 goto loop;    
			}
     	 
    //Exit 	  
      	 else if(menu==4){
      	char exit;                                                  
		   cout<<"Are you sure to exit the program (Y/N)?"<<endl;   //Memberikan opsi (Y/N) untuk exit program atau tidak
		   cin>>exit;
		   while(cin.fail()||(exit!='Y' && exit!='N')){             //Selama tidak input dalam bentuk char,
		        cout<<"Invalid, enter the right option (Y/N): " ;   //atau tidak isi antara Y atau N, program minta input opsi kembali
				cin>>exit;
		   		}
		   	if(exit=='N'){                                         
		   		system("CLS");                                   //untuk clear the screen (Hapus bekas output program sebelumnya)
		     	goto loop;                                      //Lompat ke line code "loop: "
			   }
			else{
				cout<<"\nThankyou for using our online booking system"<<endl;
				}
		   } 

	return 0;
}

void back_to_menu(){
	string any_key;
	    bar2();
		cout<<"Press any character/key to continue: ";  
		if(cin>>any_key){ //Menjalankan program dalam bracket jika isi key apapun
	    cout<<endl;     
		system("CLS");  //CLS= Cleaning the screen, menghapus bekas output.
		}
	}

void menu_main(){
	//Main Menu
    cout<<"*** Welcome to Nusantara Airline Flight Online Booking System ***\n"<<endl;

        	cout<<"\t"<<"1.Booking Flight"<<endl;
        	cout<<"\t"<<"2.Check Ticket"<<endl;
        	cout<<"\t"<<"3.Cancel Flight"<<endl;
        	cout<<"\t"<<"4.Exit\n"<<endl;
            bar2();     
            cout<<"\nPlease enter the option above: ";
	    	cin>>menu;
	  
    while(menu!=1&&menu!=2&&menu!=3&&menu!=4){
	    	if(cin.fail()){
    		cin.clear(); //menghapus pernyataan error dari cin, sehingga bisa proses input lebih lanjut. Jadi tidak muncul infinite loop error message. 
    		cin.ignore(numeric_limits<streamsize>::max(),'\n');//mengabaikan atau skip sisa line setelah line error pertama muncul 
			cout<<"You have entered wrong option, please enter the option above: ";
			cin>>menu;
				}
			else{
        		cout<<endl;
	    		cout<<"You have entered wrong number, please enter the option above: ";
	    		cin>>menu;
				}
	}
}

void departure_condition(){  //Define Function departure_condition 
	    																		 //Tanggal yang valid: year>= tahun ini, month2>= bulan ini, date> tanggal ini jika monthnya sama.
 		while(year<=(1900+ltm->tm_year)){        								//harus +1900 karena ltm->tm_year = [tahun sekarang - 1900]
    		if(year<(1900+ltm->tm_year)){        								//ltm= local time  
     	       cout<<"\nReenter the departure date (correctly): "<<endl;   		//Perintah untuk input date (tanggal penerbangan) kembali           
         	   ddmmyyyy();  													//Function untuk input date
	   		 }
	    	else if(month<(1+ltm->tm_mon)){  		 						  //harus +1 karena ltm->tm_month dimulai dari 0
		        cout<<"\nReenter the departure date (correctly): "<<endl;
     	     	ddmmyyyy();
			 }
		    else if(date<(ltm->tm_mday)+1 && (1+ltm->tm_mon)==month){
	        	cout<<"\nReenter the departure date (due one day before the flight): "<<endl;
             	ddmmyyyy();
			 }		
			else{break;}					 								//Jika tanggalnya valid, maka loop akan berhenti
		 }	
}	

//Functions to check email validity
bool email_character(char email_contain){    //Untuk check apakah character yang dimasukkan ke function ada alphabet atau tidak
	return ((email_contain>='a'&& email_contain<='z')||(email_contain>='A'&& email_contain<='Z')); //sama aja kayak if((email_contain>=.....)){return true;}
}

bool email_digit(char email_contain){        //Untuk check apakah character yang dimasukkan ke function ada angka atau tidak
	return ((email_contain>=0 || email_contain<=9));
}

bool email_validity(string email){         //Function apakah email valid atau tidak
    if(!email_character(email[0])){       //Jika character pertama di email bukan alphabet, maka return false (invalid)
    	return 0;
    	}	
    	
	int email_at(-1),email_dot(-1);	     
    int email_len=email.length();	  //define email_len sebagai jumlah character di email
    for(int i=0;i<email_len;i++){     //loop untuk check setiap character di email
       if(email[i]=='@'){             //Jika character di email ada @, maka email_at = posisi characternya (posisi array ke-berapa yang ada @)
       	   email_at=i;
	   }
	   else if(email[i]=='.'){       //Jika character di email ada ., maka email_dot = posisi characternya (posisi array ke-berapa yang ada .)
	   	   email_dot=i;
	   }
	}
      if(email_at>email_dot){      //Jika @ berada setelah . , maka email invalid
      	  return 0;
	  }	
	  if(email_at==-1 || email_dot==-1){  //Jika @ dan . tidak ada dalam email, maka email invalid
	  	   return 0;
	  }
      if(email_dot>=email_len-2){      //Jika . ada di 1-2 character dari belakang
      	   return 0;
	  }
}


bool pass_uppercase(char pass_contain){    //Untuk check apakah ada Huruf Kapital di password 
 return (pass_contain>='A' && pass_contain<='Z'); //sama aja kayak if((pass_contain>=.....)){return true;}
}

bool pass_lowercase(char pass_contain){  //Untuk check apakah ada Huruf kecil di password 
  return (pass_contain>='a'&& pass_contain<='z');}

bool pass_digit(char pass_contain){   //Untuk check apakah ada angka di password 
 return ((pass_contain>=48 && pass_contain<=57));  //48-57 itu kode didapet dari char ASCII (bisa lihat dari google)
 }
 
bool pass_special(char pass_contain){  //Untuk check apakah ada special character di password (%,^,*,#,etc.)
 if  ( pass_contain != 44 && ((pass_contain<48 && pass_contain>31)|| (pass_contain>57 && pass_contain<65) ||(pass_contain>90 && pass_contain<97) || pass_contain>122)){
 return 1;}  							//Jika kode char selain uppercase, lowercase, dan number
 else {return 0;}
 }
 
bool password_validity(string password){  
    int pass_up(-1), pass_down(-1),pass_no(-1),pass_spec(-1); 
    int pass_len=password.length();    //define panjang dari password;
    
    if(pass_len<8){                    //Jika jumlah karakter password lebih kecil dari 8, maka return false (invalid);
    	return 0;
	}
    for(int i=0;i<pass_len;i++){     //Periksa setiap character di password;
        if(pass_uppercase(password[i])){   //Jika ada uppercase, pass_up +1
         pass_up++;
  }
   if(pass_lowercase(password[i])){        //Jika ada lowercase, pass_down +1
         pass_down++;
  }
      if(pass_digit(password[i])){        //Jika ada pass_digit, pass_no +1
          pass_no++;
  } 
      if(pass_special(password[i])){      //Jika ada special character, pass_spec +1
   pass_spec++;
  }    
 }
 
    if(pass_up==-1 || pass_down==-1 || pass_no==-1 || pass_spec==-1){  //Jika salah satu dari syarat tidak terpenuhi maka return false (invalid)
     return 0;}
     return 1;  //secara default, function ini mengembalikan true (valid).
 }
