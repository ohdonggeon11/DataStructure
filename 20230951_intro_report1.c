#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   

int main() {
    int scores[10];    
    int sum = 0;        
    double average;     

  
    srand(time(NULL));

    printf("--- 학생 10명의 성적 생성 ---\n");

    
    for (int i = 0; i < 10; i++) {
        scores[i] = rand() % 101;
        sum += scores[i];         

        printf("%d번 학생 점수: %d점\n", i + 1, scores[i]);
    }

  
    average = (double)sum / 10;

    // 3. 결과 출력
    printf("----------------------------\n");
    printf("전체 합계: %d점\n", sum);
    printf("전체 평균: %.2f점\n", average);

    return 0;
}
