#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   

int main() {
    int scores[10];      // 10명의 성적을 저장할 배열
    int sum = 0;         // 합계를 저장할 변수
    double average;      // 평균을 저장할 변수

    srand(time(NULL));

    printf("--- 학생 10명의 성적 생성 ---\n");

   
    for (int i = 0; i < 10; i++) {
        scores[i] = rand() % 101; 
        sum += scores[i];         

        printf("%d번 학생 점수: %d점\n", i + 1, scores[i]);
    }

    // 2. 평균 점수 계산 (소수점까지 구하기 위해 형변환 사용)
    average = (double)sum / 10;

    // 3. 결과 출력
    printf("----------------------------\n");
    printf("전체 합계: %d점\n", sum);
    printf("전체 평균: %.2f점\n", average);

    return 0;
}
