#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   

// 함수 선언
double calculateAverage(int scores[], int size);
int getStudentScore(int scores[], int size, int studentNumber);
void printScore(int scores[],int size,double average, int option);
int main() {
    int scores[30];
    int studentNumber; // 1. 누락된 변수 선언 추가
    double average;
    
    srand(time(0));
    
    for (int i = 0; i < 30; i++) {
        scores[i] = rand() % 101; 
    }
    
    average = calculateAverage(scores, 30);
    printf("학급 평균 점수: %.2f\n", average); // %2f -> %.2f (소수점 정리)
    
    printf("학생 번호를 입력하세요 (1~30): ");
    scanf("%d", &studentNumber);
    
    
    int score = getStudentScore(scores, 30, studentNumber);
   
    if (score != -1) {
        printf("%d번 학생의 점수: %d\n", studentNumber, score);
    } else {
        printf("유효하지 않은 학생 번호입니다.\n");
    }
    
    // 함수 printScore 0, 1, 2 값입력 0은 모든학생 1은 평균이상 학생 2는 평균 미만 학생
    
    
    int numscore;
     printf("0,1,2 중에 값을 입력하세요");
    scanf("%d", &numscore);
    
    printScore(scores,30,average,numscore);
    
    
    
    printScore(scores,30,average,0);
    printScore(scores,30,average,1);
    printScore(scores,30,average,2);
    return 0;
}

double calculateAverage(int scores[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += scores[i];
    }
    return (double)sum / size; 
}

int getStudentScore(int scores[], int size, int studentNumber) {
    
    if (studentNumber >= 1 && studentNumber <= size) {
        return scores[studentNumber - 1];
    } else {
        return -1; 
    }
}

void printScore(int scores[],int size,double average, int option){
    switch(option){
        case 0:
            printf("모든학생 점수 \n");
            for (int i=0; i<size;i++){
                printf("학생번호 : %d 점수 %d \n",i+1,scores[i]);
            }
            break;
        
        case 1:
             printf("평균 이상 학생\n");
             for (int i=0; i<size;i++){
                 if(scores[i] >= average)printf("학생번호 : %d 점수 %d \n",i+1,scores[i]);
            }
            break;
        
        case 2:
            printf("평균 미만 학생\n");
            for (int i=0; i<size;i++){
                 if(scores[i] <= average)printf("학생번호 : %d 점수 %d \n",i+1,scores[i]);
            }
            break;
        default:
            printf("유효하지않은 옵션입니다.\n");
            break;
    }
}
