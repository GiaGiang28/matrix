///============================== file header chứa các hàm để thực hiện yêu cầu ==============================
struct matrix{
    double a[N][N];
    int row;
    int col;
};
typedef struct matrix MT;

///--------------------- Khai báo nguyên mẫu hàm ------------------------

void input_matrix(string file_name, MT &A);
void output_file(string file_name, MT A);
void output_screen(MT A);
void random_matrix(string file_name);

MT addition_matrix(MT A, MT B);
MT subtraction_matrix(MT A, MT B);
MT multiplication_matrix(MT A, MT B);
MT scalar_matrix(MT A, double value);

MT swap_row(MT &A, int x, int y);
MT swap_col(MT &A, int x, int y);
MT create_unit_matrix(MT &A);
int rank_matrix(MT A);
double determinant_matrix(MT A);

///===========================================================================================
MT matrix_transposition(MT A);
MT inverse_matrix_algebraic(MT A);

///===========================================================================================
bool index_element_solution(MT A, int index[N], int &row_solution, int &col_solution);
MT inverse_matrix_GJ(MT A);

///====== Gói giải phương trình đa thức với nghiệm là các trị riêng của ma trận A ============
double derivative(double x, double coeff_poly[N], int n);
double function_value(double x, double coeff_poly[N], int n);
void domain_solution(double &lower_bround, double &upper_bround, double coeff_poly[N], int n);
double halving_method(double x0, double x1, double coeff_poly[N], int n);
void solve_polynomial(double coeff_poly[N], int n, double eigenvalues[N], int &pos);

///===========================================================================================
MT multiply_square_matrix(MT A, MT &B, MT C);
void find_eigenvalues_eigenvectors(MT A);

///Chi tiết các hàm trên
///===========================================================================================

void input_matrix(string file_name, MT &A) {
    fstream inp;
    double c;
    inp.open(file_name, ios::in);
    if (!inp.is_open()) {
        cout << "\nERROR !! Khong ton tai file !!\n";
        exit(0);
    }
    inp >> c;
    A.row = c;
    inp >> c;
    A.col = c;
    for (int i = 0; i < A.row; i++)
        for (int j = 0; j < A.col; j++) {
            inp >> c;
            A.a[i][j] = c;
        }
    inp.close();
}
void output_file(string file_name, MT A){
    fstream out;
    out.open(file_name, ios::out | ios::app);
    for (int i=0; i<A.row; i++){
        out <<"\n";
        for (int j=0; j<A.col; j++){
            out << fixed << setw(12) << setprecision(6)<< A.a[i][j] <<"  ";
        }
    }
    out <<"\n****************************************************************************************************\n";
    out.close();
}
void output_screen(MT A){
    for (int i=0; i<A.row; i++){
        cout <<"\n";
        for (int j=0; j<A.col; j++){
            cout << fixed << setw(12) << setprecision(6)<< A.a[i][j] <<"  ";
        }
    }
    cout <<"\n***************************************************************************************************\n";
}
void random_matrix(string file_name){
    fstream out;
    double temp;
    out.open(file_name, ios::out);
    srand(time(0));
    temp = 2 + rand()%19;   // 2 + [0, 18] = [2, 20]
    out << temp <<" "<< temp;
    for (int i=0; i<temp; i++) {
        out <<"\n";
        for (int j=0; j<temp; j++) {
            out << fixed << setw(12) << setprecision(6)<< -50.0 + static_cast <double> (rand()) /(static_cast <double> (RAND_MAX/(100))) <<"  ";
        }
    }
    out.close();
}

MT addition_matrix(MT A, MT B){
    MT C;
    C.row = A.row;
    C.col = A.col;
    for (int i=0; i<A.row; i++){
        for (int j=0; j<A.col; j++)
        {
            C.a[i][j] = A.a[i][j] + B.a[i][j];
        }
    }
    return C;
}
MT subtraction_matrix(MT A, MT B){
    MT C;
    C.row = A.row;
    C.col = A.col;
    for (int i=0; i<A.row; i++){
        for (int j=0; j<A.col; j++)
        {
            C.a[i][j] = A.a[i][j] - B.a[i][j];
        }
    }
    return C;
}
MT multiplication_matrix(MT A, MT B){
    MT C;
    C.row = A.row;
    C.col = B.col;
    for (int i=0; i<A.row; i++) {
        for (int j = 0; j < B.col; j++) {
            C.a[i][j] = 0;
            for (int k = 0; k < A.col; k++) {
                C.a[i][j] += A.a[i][k] * B.a[k][j];
            }
        }
    }
    return C;
}
MT scalar_matrix(MT A, double value) {
    MT B;
    B.row = A.row;
    B.col = A.col;
    for (int i = 0; i < A.row; i++)
        for (int j = 0; j < A.col; j++) {
            B.a[i][j] = A.a[i][j] * value;
        }
    return B;
}

MT swap_row(MT &A, int x, int y){
    double temp;
    for (int j=0; j<A.col; j++){
        temp = A.a[x][j];
        A.a[x][j] = A.a[y][j];
        A.a[y][j] = temp;
    }
    return A;
}
MT swap_col(MT &A, int x, int y){
    double temp;
    for (int i=0; i<A.row; i++){
        temp = A.a[i][x];
        A.a[i][x] = A.a[i][y];
        A.a[i][y] = temp;
    }
    return A;
}
MT create_unit_matrix(MT &A){
    for (int i=0; i<A.row; i++){
        for (int j=0; j<A.col; j++){
            if (i == j) A.a[i][j] = 1;
            else A.a[i][j] = 0;
        }
    }
    return A;
}

int rank_matrix(MT A) {
    int rank = 0, k = 0;
    double coeff;
    for (int i = 0; i < A.row - 1; i++) {
        if (k < A.col) {
            if (A.a[i][k] != 0) {
                rank++;
                for (int h = i + 1; h < A.row; h++) {
                    coeff = A.a[h][k] / A.a[i][k];
                    for (int j = k; j < A.col; j++) {
                        A.a[h][j] = A.a[h][j] - coeff * A.a[i][j];
                    }
                }
                output_screen(A);
                output_file(output, A);
            }
            else {
                for (int j = i + 1; j < A.row; j++) {
                    if (A.a[j][k] != 0) {
                        swap_row(A, i, j);
                        k--;
                        output_screen(A);
                        output_file(output, A);
                        break;
                    }
                }
                i--;
            }
            k++;
        }
        else break;
    }
    for (int j = A.col - 1; j >= 0; j--) {
        if (A.a[A.row - 1][j] != 0) {
            rank++;
            break;
        }
    }
    return rank;
}
double determinant_matrix(MT A) {
    double det = 1, sign = 1, coeff;
    int k = 0, temp;
    for (int i = 0; i < A.row - 1; i++) {
        if (A.a[i][k] != 0) {
            det = det * A.a[i][k];
            for (int h = i + 1; h < A.row; h++) {
                coeff = A.a[h][k] / A.a[i][k];
                for (int j = k; j < A.col; j++) {
                    A.a[h][j] = A.a[h][j] - coeff * A.a[i][j];
                }
            }
        }
        else {
            temp = 0;
            for (int j = i + 1; j < A.row; j++) {
                if (A.a[j][k] != 0) {
                    swap_row(A, i, j);
                    sign = sign * -1;
                    temp = 1;
                    break;
                }
            }
            if (temp == 0) return 0;
            else {
                i--;
                k--;
            }
        }
        k++;
    }
    det = det * A.a[A.row - 1][A.col - 1] * sign;
    return det;
}

MT matrix_transposition(MT A){
    MT B;
    B.row = A.row;
    B.col = A.col;
    for (int i=0; i<A.row; i++){
        for (int j=0; j<A.col; j++){
            B.a[i][j] = A.a[j][i];
        }
    }
    return B;
}
MT inverse_matrix_algebraic(MT A) {
    MT B, TEMP;
    double det = determinant_matrix(A);
    int h, k;
    B.row = A.row;
    B.col = A.col;
    TEMP.row = A.row - 1;
    TEMP.col = A.col - 1;
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {
            h = -1;
            for (int m = 0; m < A.row; m++) {
                if (m == i) continue;
                h++;
                k = -1;
                for (int n = 0; n < A.col; n++) {
                    if (n == j) continue;
                    k++;
                    TEMP.a[h][k] = A.a[m][n];
                }
            }
            if ((i + j) % 2 == 1) B.a[i][j] = -determinant_matrix(TEMP);
            else B.a[i][j] = determinant_matrix(TEMP);
        }
    }
    return scalar_matrix(matrix_transposition(B), 1 / det);
}

bool index_element_solution(MT A, int index[N], int &row_solution, int &col_solution) {
    ///Mảng index[N] lưu vị trí của các phần tử giải A[i]: vị trí hàng của phần tử giải thuộc cột i
    double max = 0;
    int temp = 0, check;
    for (int i = 0; i < A.row; i++) {
        check = 0;
        for (int m = 0; m < A.col; m++) {
            if (i == index[m]) {
                check = 1;
                break;
            }
        }
        if (check == 1) continue;
        else {
            for (int j = 0; j < A.col; j++) {
                if (index[j] != -1)
                    continue;
                if (abs(A.a[i][j]) >= 1) {
                    row_solution = i;
                    col_solution = j;
                    temp = 1;
                    break;
                }
                else {
                    if (abs(A.a[i][j]) > max) {
                        max = abs(A.a[i][j]);
                        row_solution = i;
                        col_solution = j;
                    }
                }
            }
        }
        if (temp == 1) break;
    }
    if (temp == 1) {
        index[col_solution] = row_solution;
        return true;
    }
    else {
        if (max != 0) {
            index[col_solution] = row_solution;
            return true;
        }
        else return false;
    }
}
MT inverse_matrix_GJ(MT A){
    int index[N], row_solution, col_solution;
    double coeff;
    MT unit_matrix;
    unit_matrix.row = A.row;
    unit_matrix.col = A.col;
    create_unit_matrix(unit_matrix);
    for (int i=0; i<A.col; i++) {
        index[i] = -1;
    }
    for (int m=0; m<A.row; m++){
        if (index_element_solution(A, index, row_solution, col_solution)){
            for (int i=0; i<A.row; i++){
                if (i != row_solution) {///Hàng đang xét thì giữ nguyên
                    coeff = A.a[i][col_solution] / A.a[row_solution][col_solution];
                    for (int j = 0; j < A.col; j++) {
                        A.a[i][j] = A.a[i][j] - coeff * A.a[row_solution][j];
                        unit_matrix.a[i][j] = unit_matrix.a[i][j] - coeff * unit_matrix.a[row_solution][j];
                    }
                }
            }
        }
        else break;
    }
    ///Chuẩn hóa ma trận unit_matrix về đúng yêu cầu
    for (int i=0; i<A.row; i++){
        if (A.a[i][i] == 0){
            for (int h=i+1; h<A.row; h++){
                if (A.a[h][i] != 0){
                    swap_row(A, h, i);
                    swap_row(unit_matrix, h, i);
                    break;
                }
            }
        }
    }
    for (int i=0; i<unit_matrix.row; i++){
        for (int j=0; j<unit_matrix.col; j++){
            unit_matrix.a[i][j] = unit_matrix.a[i][j] / A.a[i][i];
        }
    }
    return unit_matrix;
}

///===========================================================================================
double derivative(double x, double coeff_poly[N], int n) {
    double temp = 0;
    for (int i = n; i >= 1; i--) {
        temp += coeff_poly[n - i] * i * pow(x, i - 1);
    }
    return temp;
}
double function_value(double x, double coeff_poly[N], int n) {
    double temp = 0;
    for (int i = n; i >= 0; i--) {
        temp += coeff_poly[n - i] * pow(x, i);
    }
    return temp;
}
void domain_solution(double &lower_bround, double &upper_bround, double coeff_poly[N], int n) {
    double temp[N], max, k;
    upper_bround = -1;
    lower_bround = 1;
    for (int i = 0; i <= n; i++) {
        temp[i] = coeff_poly[i];
    }
    do {
        max = 0;
        k = 0;
        if (temp[0] < 0) {
            for (int i = 0; i <= n; i++) {
                temp[i] = -temp[i];
            }
        }
        for (int i = 1; i <= n; i++) {
            if (temp[i] < 0) {
                k = i;
                break;
            }
        }
        for (int i = 1; i <= n; i++) {
            if (temp[i] < 0) {
                if (abs(temp[i]) > max) max = abs(temp[i]);
            }

        }
        if (max == 0) {
            if (upper_bround == -1) upper_bround = 0;///Đang đi tìm cận trên
            else lower_bround = 0; ///Đang đi tìm cận dưới
        }
        else {
            if (upper_bround == -1) upper_bround = 1 + pow((max / temp[0]), 1 / k);
            else lower_bround = -(1 + pow((max / temp[0]), 1 / k));
        }
        for (int i = 0; i <= n; i++) {
            if (i % 2 == 1)
                temp[n - i] = -temp[n - i];///Thay x = -x vào f(x) để đi tìm cận dưới
        }
    }
    while (lower_bround > 0);
}
double halving_method(double x0, double x1, double coeff_poly[N], int n) {
    double a1 = x0;
    double b1 = x1;
    double c, value, temp;
    c = (a1 + b1) / 2;
    value = function_value(c, coeff_poly, n);
    do {
        temp = function_value(a1, coeff_poly, n);
        if (value == 0)
            return c;
        else {
            if (temp * value < 0) b1 = c;
            else a1 = c;
        }
        c = (a1 + b1) / 2;
        value = function_value(c, coeff_poly, n);
    }
    while (abs(value) > epsi);
    return c;
}
void solve_polynomial(double coeff_poly[N], int n, double eigenvalues[N], int &pos) {
    double survey_value[N];
    double x0, x1, sign, temp0, temp1, value1, value2, lower_bround, upper_bround;
    double eta = 1e-6;
    int k = 1;
    domain_solution(lower_bround, upper_bround, coeff_poly, n);
    if (lower_bround == upper_bround) {
        if (function_value(lower_bround, coeff_poly, n) == 0) {
            eigenvalues[pos] = lower_bround;
            pos++;
        }
    }
    else {
        x1 = lower_bround;
        while (x1 < upper_bround) {
            x0 = x1;
            temp0 = derivative(x0, coeff_poly, n);
            if (temp0 < 0)
                sign = -1;
            else
                sign = 1;
            x1 = x0 + sign * eta * temp0;
            temp1 = derivative(x1, coeff_poly, n);
            for (int i = 0; i < max_loop; i++) {
                if (temp0 * temp1 > 0) {
                    while (eta < 0.008) {
                        if (abs(temp0) > 1e4) {
                            eta = eta * 4;
                        }
                        else {
                            eta = eta * 2;
                        }
                        x1 = x0 + sign * eta * temp0;
                        if (derivative(x1, coeff_poly, n) * temp0 < 0) {
                            eta = eta / 4;
                            break;
                        }
                    }
                }
                else {
                    while (eta > 0) {
                        eta = eta / 2;
                        x1 = x0 + sign * eta * temp0;
                        if (derivative(x1, coeff_poly, n) * temp0 > 0)
                            break;
                    }
                }
                x1 = x0 + sign * eta * temp0;
                x0 = x1;
                if (abs(derivative(x1, coeff_poly, n)) < 1e-4) {
                    survey_value[k] = x1;
                    k++;
                    break;
                }
                eta = 1e-6;
                temp0 = derivative(x0, coeff_poly, n);
                x1 = x0 + sign * eta * temp0;
                temp1 = derivative(x1, coeff_poly, n);
                if (x1 > upper_bround)
                    break;
            }
            x1 = x1 + 0.001;
        }
        survey_value[0] = lower_bround;
        survey_value[k] = upper_bround;
        for (int i = 0; i < k; i++) {
            value1 = function_value(survey_value[i], coeff_poly, n);
            value2 = function_value(survey_value[i + 1], coeff_poly, n);
            if (value1 == 0) {
                eigenvalues[pos] = survey_value[i];
                pos++;
            }
            else if (value2 == 0) {
                eigenvalues[pos] = survey_value[i + 1];
                i++;
                pos++;
            }
            else if (value1 * value2 < 0) {
                eigenvalues[pos] = halving_method(survey_value[i], survey_value[i + 1], coeff_poly, n);
                pos++;
            }
        }
    }
}

MT multiply_square_matrix(MT A, MT &B, MT C) {
    MT D;
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.row; j++) {
            D.a[i][j] = 0;
            for (int k = 0; k < A.row; k++) {
                D.a[i][j] += A.a[i][k] * B.a[k][j];
            }
        }
    }
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.row; j++) {
            B.a[i][j] = 0;
            for (int k = 0; k < A.row; k++) {
                B.a[i][j] += D.a[i][k] * C.a[k][j];
            }
        }
    }
    return B;
}
void find_eigenvalues_eigenvectors(MT A) {
    MT M, M1, C, B;
    double eigenvalues[N];
    double Y[N];
    double coeff_poly[N + 1];
    double eigenvector[N];
    double sum, value;
    int temp, n, h, pos = 0, count;
    fstream out;
    C.row = A.row;
    C.col = A.row;
    create_unit_matrix(C);
    M.row = A.row;
    M.col = A.row;
    M1.row = A.row;
    M1.col = A.row;
    for (int i = A.row - 1; i >= 1; i--) {
        create_unit_matrix(M);
        create_unit_matrix(M1);
        if (A.a[i][i - 1] != 0) {
            for (int j = 0; j < A.row; j++) {
                M.a[i - 1][j] = A.a[i][j];
                M1.a[i - 1][j] = -A.a[i][j] / A.a[i][i - 1];
                M1.a[i - 1][i - 1] = 1 / A.a[i][i - 1];
            }
            multiply_square_matrix(M, A, M1);
        }
        else {
            for (int k = 0; k < i - 1; i++) {
                if (A.a[i][k] != 0) {
                    swap_row(A, i - 1, k);
                    swap_col(A, i - 1, k);

                    swap_row(M1, i - 1, k);
                    swap_col(M1, i - 1, k);
                    i++;
                    break;
                }
            }
        }
        for (int m = 0; m < A.row; m++) {
            for (int l = 0; l < A.row; l++) {
                B.a[m][l] = 0;
                for (int k = 0; k < A.row; k++) {
                    B.a[m][l] += C.a[m][k] * M1.a[k][l];
                }
            }
        }
        for (int m = 0; m < A.row; m++) {
            for (int l = 0; l < A.row; l++) {
                C.a[m][l] = B.a[m][l];
            }
        }
        output_screen(A);
        output_file(output, A);
    }
    ///Bắt đầu quá trình đi tìm trị riêng
    out.open(output, ios ::out | ios::app);
    h = A.row;
    for (int i = A.row - 1; i >= 0; i--) {
        if (A.a[i][i - 1] == 0 || i == 0) {
            temp = 1;
            n = h - i;
            coeff_poly[0] = pow(-1, n);
            for (int j = i; j <= h - 1; j++) {
                coeff_poly[temp] = -A.a[i][j] * coeff_poly[0];
                temp++;
            }
            solve_polynomial(coeff_poly, n, eigenvalues, pos);
            h = i;
        }
    }
    ///Bắt đầu quá trình đi tìm vector riêng ứng với trị riêng
    for (int k = 0; k < pos; k++) {
        h = A.row;
        count = A.row;
        for (int i = 0; i < count; i++)
            Y[i] = 0;
        for (int i = A.row - 1; i >= 0; i--) {
            if (A.a[i][i - 1] == 0 || i == 0) {
                temp = 1;
                n = h - i;
                coeff_poly[0] = pow(-1, n);
                for (int j = i; j <= h - 1; j++) {
                    coeff_poly[temp] = -A.a[i][j] * coeff_poly[0];
                    temp++;
                }
                value = function_value(eigenvalues[k], coeff_poly, n);
                if (value < 1e-8) {
                    for (int m = 0; m < n; m++) {
                        Y[count - 1] = pow(eigenvalues[k], m);
                        count--;
                    }
                }
                else {
                    sum = 0;
                    for (int m = 0; m < A.row; m++) sum += Y[m] * A.a[i][m];
                    for (int m = 0; m < n; m++) {
                        Y[count - 1] = pow(-1, n) * (sum / value) * pow(eigenvalues[k], m);
                        count--;
                    }
                }
                h = i;
            }
        }

        ///Nhân ma trận C với mảng Y
        for (int m = 0; m < A.row; m++) {
            eigenvector[m] = 0;
            for (int l = 0; l < A.col; l++) {
                eigenvector[m] += C.a[m][l] * Y[l];
            }
        }
        cout << "\nVector rieng ung voi tri rieng: " << fixed << setprecision(12) << eigenvalues[k];
        out << "\nVector rieng ung voi tri rieng: " << fixed << setprecision(12) << eigenvalues[k];
        for (int m = 0; m < A.row; m++) {
            cout << "\n" << fixed << setw(18) << setprecision(12) << eigenvector[m];
            out << "\n" << fixed << setw(18) << setprecision(12) << eigenvector[m];
        }
    }
    out.close();
}
