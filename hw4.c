#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);
//들어가게 될 모든 함수 선언
int main()
{

    char command;
    printf("[----- [박성준]  [2021040026] -----]\n");//학번,이름

    int row, col;
    srand(time(NULL));//난수생성을 위한 함수 

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);//scanf를 통해서 행과열의 크기값을 받기 
    int** matrix_a = create_matrix(row, col);//matrix_a 만들기
    int** matrix_b = create_matrix(row, col);//matrix_b 만들기
    int** matrix_a_t = create_matrix(col, row);//matrix_a_t 만들기

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;} //비어있으면 오류

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);//입력 받음 

        switch(command) {
        case 'z': case 'Z': //z 선택시
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);//matrix_a의 fill_data 함수 실행
            fill_data(matrix_b, row, col);//matrix_b의 fill_data 함수 실행
            break;
        case 'p': case 'P'://p 선택시
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);//matrix_a의 print_matrix함수 실행
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);//matrix_b의 print_matrix함수 실행
            break;
        case 'a': case 'A'://a 선택시
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);//matrix_a와 matrix_b,addtion_matrix함수 실행
            break;
        case 's': case 'S'://s 선택시
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);//matrix_a와 matrix_b,subtraction_matrix함수 실행
            break;
        case 't': case 'T'://t 선택시
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);//matrix_a와 matrix_a_t,transpose_matrix함수 실행
            print_matrix(matrix_a_t, col, row);//출력
            break;
        case 'm': case 'M'://m 선택시
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);//matrix_a와 matrix_a_t,transpose_matrix함수 실행
            multiply_matrix(matrix_a, matrix_a_t, row, col);//matrix_a와 matrix_a_t,multiply_matrix함수 실행
            break;
        case 'q': case 'Q'://q 선택시
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);//matrix_a_t,free_matrix
            free_matrix(matrix_a, row, col);//matrix_a,free_matrix
            free_matrix(matrix_b, row, col);//matrix_b,free_matrix
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //항상 출력
            break;
        }

    }while(command != 'q' && command != 'Q');//q전까지 반복

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return NULL;
	}//행열 값 0이면 오류값

    int **x, i;  //메트릭스가 될 x와 i선언
    x = (int**)malloc(sizeof(int*) * row);//x의 행에 해당하는 부분을 동적할당
    for (i=0; i<row; i++)
        x[i] = (int*)malloc(sizeof(int)*col); //반복문을 이용해서 x의 열에 해당하는 부분 할당

    if (x == NULL) {
		printf("Memory Allocation Failed.\n");
		return NULL;
	}// 비어있을 경우 오류값 

    
    return x; 
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    int i,j;

    if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return;
	}//행열 값 0이면 오류값

    for(i=0; i<row; i++)
        for(j=0; j<col; j++)
           printf("%d",matrix[i][j]); //두 개의 반복문을 통해서 모든 메트릭스값을 출력
        printf("\n");

     if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
	}// 비어있을 경우 오류값 
	return;

}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{

    int i;
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}//행열 값 0이면 오류값

	for (i = 0; i < row; i++) {
		free(matrix[i]);//free를 통해서 메모리 해제 해준다.
	}

	free(matrix);//free를 통해서 matrix 메모리 해제 해준다.
	return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}//행열 값 0이면 오류값

    int i,j;
    for(i=0; i<row; i++)
        for(j=0; j<col; j++)
            matrix[i][j] = rand()%20; //랜덤함수를 이용하고,20으로 나눔으로써 0-19사이의 수를 대입할 수 있도록 한다.  
    
    if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}// 비어있을 경우 오류값 

	return 1;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col); //matrix_sum라는 새로운 매트릭스를 만든다. 

    if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}//행열 값 0이면 오류값

    int i,j;
    
    for(i=0; i<row; i++)
        for(j=0; j<col; j++)
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
             //모든 행열을 반복문을 통해 하나씩 비교하며 더해준다.
    
    if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}// 비어있을 경우 오류값 

    print_matrix(matrix_sum, row, col);
	free_matrix(matrix_sum, row, col); //matrix_sum에 대해, free_matrix
    return 1;

}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
 int i,j;

    int** matrix_sub = create_matrix(row, col);

    if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}//행열 값 0이면 오류값
    
    for(i=0; i<row; i++)
        for(j=0; j<col; j++)
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
            //모든 행열을 반복문을 통해 하나씩 비교하며 빼준다.

    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}// 비어있을 경우 오류값 

    print_matrix(matrix_sub, row, col);
	free_matrix(matrix_sub, row, col);//matrix_sub에 대해,free_matrix
    return 1;

}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
  int i,j;
 
  if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}//행열 값 0이면 오류값

  for(i=0; i<row; i++)
        for(j=0; j<col; j++)
            matrix_t[i][j] = matrix[j][i]; 
            // matrix_t는 matrix에서 반복문을 통해 i->j,j->i로 전치한 것.

  if (matrix == NULL || matrix_t ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}// 비어있을 경우 오류값 

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
 int i,j,temp;
    
    
    int** matrix_axt = create_matrix(row, row); //행열의 곱에서는 row*row크기의 행열이 생성 
    
     if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}//행열 값 0이면 오류값

    for (int k= 0; k < row;k++) { // matrix_a의 행은 크게 row번 바뀌어야 한다. 
        for(i=0; i<row; i++){//matrix_t의 행은 각각의 값을 곱하기 위해서 row*row번 바뀌어야 한다.
            temp = 0; //i가 바뀔때마다 temp 초기화
            for(j=0; j<col; j++)
                temp += matrix_a[k][j] * matrix_t[j][i]; //j가 0부터 col-1까지의 곱값을 모두 더해준다. 
            matrix_axt[k][i] = temp; //그 값을 matrix_axt[k][i]로 지정해준다.
        }
    }

     if (matrix_a == NULL || matrix_t == NULL || matrix_axt == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}// 비어있을 경우 오류값 

    print_matrix(matrix_axt, row, row);//출력
	free_matrix(matrix_axt, row, col);//free_matrix로 해제
    return 1;
}

