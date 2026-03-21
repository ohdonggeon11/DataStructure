#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 함수 선언
double calculateAverage(int scores[], int size);
int getStudentScore(int scores[], int size, int studentNumber);
void printScore(int scores[], int size, double average, int option);
void deleteStudent(int scores[], int* size, int studentNumber); // size를 포인터로 전달

int main() {
    int* scores;
    int size = 30;
    int capacity = 30;
    int choice, studentNumber;

    scores = (int*)malloc(capacity * sizeof(int));
    if (scores == NULL) {
        printf("메모리 할당 오류\n");
        return 1;
    }

    srand(time(0));
    for (int i = 0; i < size; i++) {
        scores[i] = rand() % 101;
    }
    printf("초기 데이터 30개 생성 완료.\n");

    while (1) {
        printf("\n--- 학생 성적 관리 프로그램 ---\n");
        printf("1. 학생 정보 추가 | 2. 학생 정보 삭제 | 3. 학생 정보 검색 | 4. 학생 정보 출력 | 5. 프로그램 종료\n");
        printf("선택: ");
        if (scanf("%d", &choice) != 1) break;

        if (choice == 5) {
            free(scores);
            printf("프로그램을 종료합니다.\n");
            break;
        }

        switch (choice) {
            
        case 1: // 학생 추가
            if (size >= capacity) {
                capacity += 10;
                int* newScores = (int*)realloc(scores, capacity * sizeof(int));
                if (!newScores) { printf("재할당 오류\n"); break; }
                scores = newScores;
            }
            scores[size] = rand() % 101;
            printf("%d번 학생 추가 완료 (점수: %d)\n", size + 1, scores[size]);
            size++;
            break;

        case 2: // 학생 삭제
            printf("삭제할 번호(1~%d): ", size);
            scanf("%d", &studentNumber);
            deleteStudent(scores, &size, studentNumber);
            break;

        case 3: // 검색
            printf("검색할 번호(1~%d): ", size);
            scanf("%d", &studentNumber);
            int s = getStudentScore(scores, size, studentNumber);
            if (s != -1) printf("%d번 학생 점수: %d\n", studentNumber, s);
            else printf("존재하지 않는 번호입니다.\n");
            break;

        case 4: // 출력
            printf("옵션(0:전체, 1:평균이상, 2:평균미만): ");
            int opt;
            scanf("%d", &opt);
            printScore(scores, size, calculateAverage(scores, size), opt);
            break;

        default:
            printf("잘못된 선택입니다.\n");
        }
    }
    return 0;
}


void deleteStudent(int scores[], int* size, int studentNumber) {
    if (studentNumber < 1 || studentNumber > *size) {
        printf("범위를 벗어난 번호입니다.\n");
        return;
    }
    for (int i = studentNumber - 1; i < *size - 1; i++) {
        scores[i] = scores[i + 1];
    }
    (*size)--;
    printf("%d번 학생 정보가 삭제되었습니다.\n", studentNumber);
}

double calculateAverage(int scores[], int size) {
    if (size == 0) return 0;
    int sum = 0;
    for (int i = 0; i < size; i++) sum += scores[i];
    return (double)sum / size;
}

int getStudentScore(int scores[], int size, int studentNumber) {
    if (studentNumber >= 1 && studentNumber <= size) {
        return scores[studentNumber - 1];
    }
    return -1;
}

void printScore(int scores[], int size, double average, int option) {
    switch (option) {
    case 0:
        for (int i = 0; i < size; i++) printf("[%d번]: %d\n", i + 1, scores[i]);
        break;
    case 1:
        for (int i = 0; i < size; i++) if (scores[i] >= average) printf("[%d번]: %d\n", i + 1, scores[i]);
        break;
    case 2:
        for (int i = 0; i < size; i++) if (scores[i] < average) printf("[%d번]: %d\n", i + 1, scores[i]);
        break;
    default:
        printf("잘못된 옵션입니다.\n");
    }
}
