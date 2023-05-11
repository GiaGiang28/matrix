#include <iostream>
#include <fstream>
#include <cmath>
#include<ctime>
#include <iomanip>
#include<conio.h>
using namespace std;
#define CHOICE 11
#define N 100
#define epsi 1e-8
#define max_loop 1000
#define input "input.txt"
#define input1 "input1.txt"
#define input2 "input2.txt"
#define input3 "input3.txt"
#define output "output.txt"
#define ESC 27
#define ENTER 13
#define UP 72
#define DOWN 80

#include "BTL.h"

void menu();

string s[CHOICE] = {"0. Thoat", "1. Random ma tran","2. Cong 2 ma tran",
                    "3. Tru 2 ma tran", "4. Nhan 2 ma tran", "5. Nhan vo huong",
                    "6. Dinh thuc cua ma tran", "7. Hang cua ma tran", "8. Ma tran nghich dao bang phu dai so",
                    "9. Ma tran nghich dao bang Gauss Jordan", "10. Tri rieng, vector rieng cua ma tran",
};

int main(){
    
    menu();
    
    return 0;
}
void menu()
{
    MT A, B;
    double value;
    int k = 0, temp = 0;
    char p;
    fstream out;

    while(true){
        system("cls");
        out.open(output, ios::out | ios::app);
        cout << "\n----------------MENU---------------\n";
        cout << "\nPress ESC to exit !\n";

        out << "\n----------------MENU---------------\n";
        out << "\nPress ESC to exit !\n";
        for (int i=0; i<CHOICE; i++){
            if (i == k){
                out << "-->> "<<s[i]<<'\n';
                cout << "-->> "<<s[i]<<'\n';
            }
            else {
                out << "    " << s[i] << '\n';
                cout << "    " << s[i] << '\n';
            }
        }
        out.close();

        p = getch();
        if (p == UP){
            k = (k + CHOICE - 1) % CHOICE;
        }
        else if (p == DOWN) {
            k = (k + CHOICE + 1) % CHOICE;
        }
        else if (p == ENTER){
            switch(k){
                case 0:
                    exit(0);
                case 1:
                    cout << "1. Random ma tran";
                    random_matrix(input);
                    input_matrix(input, A);
                    cout <<"\nMa tran vua random: \n";
                    cout <<A.row <<" "<<A.col;
                    output_screen(A);

                    out.open(output, ios::out | ios::app);
                    out << "\n1. Random ma tran";
                    out <<"\nMa tran vua random: \n";
                    out <<A.row <<" "<<A.col;
                    out.close();
                    output_file(output, A);
                    getch();
                    break;
                case 2:
                    input_matrix(input1, A);
                    input_matrix(input2, B);
                    cout <<"\n2. Cong 2 ma tran";
                    cout <<"\nInput ma tran A: \n";
                    cout <<A.row <<" "<<A.col;
                    output_screen(A);
                    cout <<"\nInput ma tran B: \n";
                    cout <<B.row <<" "<<B.col;
                    output_screen(B);

                    out.open(output, ios::out | ios::app);
                    out <<"\n2. Cong 2 ma tran";
                    out <<"\nInput ma tran A: \n";
                    out <<A.row <<" "<<A.col;
                    out.close();
                    output_file(output, A);

                    out.open(output, ios::out | ios::app);
                    out <<"\nInput ma tran B: \n";
                    out <<B.row <<" "<<B.col;
                    out.close();
                    output_file(output, B);

                    if (A.row == B.row && A.col == B.col){
                        cout <<"\nMa tran tong: ";
                        output_screen(addition_matrix(A, B));

                        out.open(output, ios::out | ios::app);
                        out <<"\nMa tran tong: ";
                        out.close();
                        output_file(output, addition_matrix(A, B));
                    }
                    else{
                        cout << "2 ma tran khong cung kich thuoc ! ";

                        out.open(output, ios::out | ios::app);
                        out << "\n2 ma tran khong cung kich thuoc ! ";
                        out.close();
                    }
                    getch();
                    break;
                case 3:
                    input_matrix(input1, A);
                    input_matrix(input2, B);
                    cout <<"\n3. Tru 2 ma tran";
                    cout <<"\nInput ma tran A: \n";
                    cout <<A.row <<" "<<A.col;
                    output_screen(A);
                    cout <<"\nInput ma tran B: \n";
                    cout <<B.row <<" "<<B.col;
                    output_screen(B);

                    out.open(output, ios::out | ios::app);
                    out <<"\n3. Tru 2 ma tran";
                    out <<"\nInput ma tran A: \n";
                    out <<A.row <<" "<<A.col;
                    out.close();
                    output_file(output, A);

                    out.open(output, ios::out | ios::app);
                    out <<"\nInput ma tran B: \n";
                    out <<B.row <<" "<<B.col;
                    out.close();
                    output_file(output, B);

                    if (A.row == B.row && A.col == B.col){
                        cout <<"\nMa tran hieu: ";
                        output_screen(subtraction_matrix(A, B));

                        out.open(output, ios::out | ios::app);
                        out <<"\nMa tran hieu: ";
                        out.close();
                        output_file(output, subtraction_matrix(A, B));
                    }
                    else{
                        cout << "\n2 ma tran khong cung kich thuoc !";

                        out.open(output, ios::out | ios::app);
                        out << "\n2 ma tran khong cung kich thuoc !";
                        out.close();
                    }
                    getch();
                    break;
                case 4:
                    input_matrix(input1, A);
                    input_matrix(input2, B);
                    cout <<"\n4. Nhan 2 ma tran";
                    cout <<"\nInput ma tran A: \n";
                    cout <<A.row <<" "<<A.col;
                    output_screen(A);
                    cout <<"\nInput ma tran B: \n";
                    cout <<B.row <<" "<<B.col;
                    output_screen(B);

                    out.open(output, ios::out | ios::app);
                    out <<"\n4. Nhan 2 ma tran";
                    out <<"\nInput ma tran A: \n";
                    out <<A.row <<" "<<A.col;
                    out.close();
                    output_file(output, A);

                    out.open(output, ios::out | ios::app);
                    out <<"\nInput ma tran B: \n";
                    out <<B.row <<" "<<B.col;
                    out.close();
                    output_file(output, B);

                    if (A.col == B.row){
                        cout <<"\nTich hai ma tran: ";
                        output_screen(multiplication_matrix(A, B));

                        out.open(output, ios::out | ios::app);
                        out <<"\nTich hai ma tran: ";
                        out.close();
                        output_file(output, A); ///Vì hàm multiplication truyền vào địa chỉ ma trận A và trả về ma trận A
                    }
                    else{
                        cout << "\n2 ma tran khong hop le !";

                        out.open(output, ios::out | ios::app);
                        out << "\n2 ma tran khong hop le !";
                        out.close();
                    }
                    getch();
                    break;
                case 5:
                    input_matrix(input1, A);
                    cout <<"\n5. Nhan vo huong ma tran voi 1 so thuc";
                    cout <<"\nInput ma tran A: ";
                    cout <<A.row <<" "<<A.col;
                    output_screen(A);
                    cout << "\nNhap coeff = ";
                    cin >> value;

                    out.open(output, ios::out | ios::app);
                    out <<"\n5. Nhan vo huong ma tran voi 1 so thuc";
                    out <<"\nInput ma tran A: ";
                    out <<A.row <<" "<<A.col;
                    out.close();
                    output_file(output, A);

                    cout <<"\nMa tran ket qua: ";
                    output_screen(scalar_matrix(A, value));

                    out.open(output, ios::out | ios::app);
                    out << "\nNhap coeff = ";
                    out << value;
                    out <<"\nMa tran ket qua: ";
                    out.close();
                    output_file(output, A);
                    getch();
                    break;
                case 6:
                    input_matrix(input1, A);
                    cout <<"\n6. Tinh dinh thuc cua ma tran";
                    cout <<"\nInput ma tran A: \n";
                    cout <<A.row <<" "<<A.col;
                    output_screen(A);

                    out.open(output, ios::out | ios::app);
                    out <<"6. Tinh dinh thuc cua ma tran";
                    out <<"\nInput ma tran A: \n";
                    out <<A.row <<" "<<A.col;
                    out.close();
                    output_file(output, A);

                    out.open(output, ios::out | ios::app);
                    if (A.col == A.row){
                        cout <<"\nDinh thuc cua ma tran la: ";
                        cout << determinant_matrix(A);

                        out <<"\nDinh thuc cua ma tran la: ";
                        out << determinant_matrix(A);
                    }
                    else{
                        cout << "\nMa tran khong vuong !";
                        out << "\nMa tran khong vuong !";
                    }
                    out.close();
                    getch();
                    break;
                case 7:
                    input_matrix(input1, A);
                    cout <<"\n7. Tinh hang cua ma tran";
                    cout <<"\nInput ma tran A: \n";
                    cout <<A.row <<" "<<A.col;
                    output_screen(A);

                    out.open(output, ios::out | ios::app);
                    out <<"\n7. Tinh hang cua ma tran";
                    out <<"\nInput ma tran A: \n";
                    out <<A.row <<" "<<A.col;
                    out.close();
                    output_file(output, A);

                    cout <<"\nHang cua ma tran la: " << rank_matrix(A);

                    out.open(output, ios::out | ios::app);
                    out <<"\nHang cua ma tran la: " << rank_matrix(A);
                    out.close();
                    getch();
                    break;
                case 8:
                    input_matrix(input1, A);
                    cout <<"\n8. Tinh ma tran nghich dao bang phan bu dai so";
                    cout <<"\nInput ma tran A: \n";
                    cout <<A.row <<" "<<A.col;
                    output_screen(A);

                    out.open(output, ios::out | ios::app);
                    out <<"\n8. Tinh ma tran nghich dao bang phan bu dai so";
                    out <<"\nInput ma tran A: \n";
                    out <<A.row <<" "<<A.col;
                    out.close();
                    output_file(output, A);

                    if (A.row == A.col){
                        if (determinant_matrix(A) != 0) {
                            cout <<"\nMa tran nghich dao la: ";
                            output_screen(inverse_matrix_algebraic(A));

                            out.open(output, ios::out | ios::app);
                            out <<"\nMa tran nghich dao la: ";
                            out.close();
                            output_file(output, inverse_matrix_algebraic(A));
                        }
                        else {
                            cout <<"\nDinh thuc cua ma tran bang 0 => Khong ton tai ma tran nghich dao !";

                            out.open(output, ios::out | ios::app);
                            out <<"\nDinh thuc cua ma tran bang 0 => Khong ton tai ma tran nghich dao !";
                            out.close();
                        }
                    }
                    else{
                        cout << "\nMa tran khong vuong => Khong ton tai ma tran nghich dao !";

                        out.open(output, ios::out | ios::app);
                        out << "\nMa tran khong vuong => Khong ton tai ma tran nghich dao !";
                        out.close();
                    }
                    getch();
                    break;
                case 9:
                    input_matrix(input1, A);
                    cout <<"\n9. Tinh ma tran nghich dao bang phuong phap Gauss Jordan";
                    cout <<"\nInput ma tran A: \n";
                    cout <<A.row <<" "<<A.col;
                    output_screen(A);

                    out.open(output, ios::out | ios::app);
                    out <<"\n9. Tinh ma tran nghich dao bang phuong phap Gauss Jordan";
                    out <<"\nInput ma tran A: \n";
                    out <<A.row <<" "<<A.col;
                    out.close();
                    output_file(output, A);

                    if (A.row == A.col){
                        if (determinant_matrix(A) != 0) {
                            cout <<"\nMa tran nghich dao la: ";
                            output_screen(inverse_matrix_GJ(A));

                            out.open(output, ios::out | ios::app);
                            out <<"\nMa tran nghich dao la: ";
                            out.close();
                            output_file(output, inverse_matrix_GJ(A));
                        }
                        else {
                            cout <<"\nDinh thuc cua ma tran bang 0 => Khong ton tai ma tran nghich dao !";

                            out.open(output, ios::out | ios::app);
                            out <<"\nDinh thuc cua ma tran bang 0 => Khong ton tai ma tran nghich dao !";
                            out.close();
                        }
                    }
                    else{
                        cout << "\nMa tran khong vuong => Khong ton tai ma tran nghich dao !";

                        out.open(output, ios::out | ios::app);
                        out << "\nMa tran khong vuong => Khong ton tai ma tran nghich dao !";
                        out.close();
                    }
                    getch();
                    break;
                case 10:
                    input_matrix(input3, A);
                    cout <<"\n10. Tinh tri rieng, vector rieng cua ma tran";
                    cout <<"\nInput ma tran A: \n";
                    cout <<A.row <<" "<<A.col;
                    output_screen(A);

                    out.open(output, ios::out | ios::app);
                    out <<"\n10. Tinh tri rieng, vector rieng cua ma tran";
                    out <<"\nInput ma tran A: \n";
                    out <<A.row <<" "<<A.col;
                    out.close();
                    output_file(output, A);

                    if (A.row == A.col){
                        find_eigenvalues_eigenvectors(A);
                    }
                    else{
                        cout << "\nMa tran khong vuong => Khong tinh duoc tri rieng, vector rieng !";

                        out.open(output, ios::out | ios::app);
                        out << "\nMa tran khong vuong => Khong tinh duoc tri rieng, vector rieng !";
                        out.close();
                    }
                    getch();
                    break;
            }
        }
        else if (p == ESC)
            exit(0);
    }
}
