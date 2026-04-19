#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 10
#define NAME_LEN 50
#define MAX_PAGES 50

// 프린터 작업 구조체
typedef struct {
    char documentName[NAME_LEN];
    int numPages;
} PrintJob;

// 순차 큐 구조체
typedef struct {
    PrintJob jobs[SIZE];
    int count;
} PrintQueue;

// 입력 버퍼 비우기
void clearInputBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// 문자열 한 줄 입력
void readLine(char str[], int size) {
    if (fgets(str, size, stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
    }
}

// 큐 초기화
void initQueue(PrintQueue *q) {
    q->count = 0;
}

// 큐가 비었는지 확인
bool isEmpty(const PrintQueue *q) {
    return q->count == 0;
}

// 큐가 가득 찼는지 확인
bool isFull(const PrintQueue *q) {
    return q->count == SIZE;
}

// 작업 추가
bool enqueue(PrintQueue *q, const char *documentName, int numPages) {
    if (numPages > MAX_PAGES) {
        printf("50장을 초과하는 문서는 추가할 수 없습니다.\n");
        return false;
    }

    if (numPages <= 0) {
        printf("페이지 수는 1 이상이어야 합니다.\n");
        return false;
    }

    if (isFull(q)) {
        printf("대기열이 가득 찼습니다. 작업을 추가할 수 없습니다.\n");
        return false;
    }

    strncpy(q->jobs[q->count].documentName, documentName, NAME_LEN - 1);
    q->jobs[q->count].documentName[NAME_LEN - 1] = '\0';
    q->jobs[q->count].numPages = numPages;
    q->count++;

    printf("작업 '%s' (%d 페이지)가 대기열에 추가되었습니다.\n", documentName, numPages);
    return true;
}

// 작업 처리(맨 앞 작업 제거)
bool dequeue(PrintQueue *q, PrintJob *job) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다. 작업이 없습니다.\n");
        return false;
    }

    *job = q->jobs[0];

    for (int i = 0; i < q->count - 1; i++) {
        q->jobs[i] = q->jobs[i + 1];
    }

    q->count--;
    return true;
}

// 특정 문서 취소
bool cancelJob(PrintQueue *q, const char *documentName) {
    int foundIndex = -1;

    for (int i = 0; i < q->count; i++) {
        if (strcmp(q->jobs[i].documentName, documentName) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("해당 문서가 없습니다.\n");
        return false;
    }

    for (int i = foundIndex; i < q->count - 1; i++) {
        q->jobs[i] = q->jobs[i + 1];
    }

    q->count--;
    printf("작업 '%s'가 취소되었습니다.\n", documentName);
    return true;
}

// 대기열 전체 비우기
void clearQueue(PrintQueue *q) {
    initQueue(q);
    printf("대기열 초기화\n");
}

// 대기열 출력
void printQueue(const PrintQueue *q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return;
    }

    printf("현재 대기 중인 작업:\n");
    for (int i = 0; i < q->count; i++) {
        printf("%d. %s (%d 페이지)\n",
               i + 1,
               q->jobs[i].documentName,
               q->jobs[i].numPages);
    }
}

int main(void) {
    PrintQueue q;
    int choice;
    int numPages;
    char documentName[NAME_LEN];
    PrintJob job;

    initQueue(&q);

    while (true) {
        printf("\n[프린터 작업 관리]\n");
        printf("1. 작업 추가\n");
        printf("2. 작업 처리\n");
        printf("3. 대기열 출력\n");
        printf("4. 인쇄 취소\n");
        printf("5. 대기열 전체 비우기\n");
        printf("6. 종료\n");
        printf("선택: ");

        if (scanf("%d", &choice) != 1) {
            printf("숫자를 입력해 주세요.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                printf("문서 이름: ");
                readLine(documentName, NAME_LEN);

                printf("페이지 수: ");
                if (scanf("%d", &numPages) != 1) {
                    printf("페이지 수는 숫자로 입력해 주세요.\n");
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();

                enqueue(&q, documentName, numPages);
                break;

            case 2:
                if (dequeue(&q, &job)) {
                    printf("작업 '%s' (%d 페이지)를 처리 중입니다...\n",
                           job.documentName, job.numPages);
                }
                break;

            case 3:
                printQueue(&q);
                break;

            case 4:
                printf("취소할 문서 이름: ");
                readLine(documentName, NAME_LEN);
                cancelJob(&q, documentName);
                break;

            case 5:
                clearQueue(&q);
                break;

            case 6:
                printf("프로그램을 종료합니다.\n");
                return 0;

            default:
                printf("잘못된 입력입니다. 다시 선택해 주세요.\n");
        }
    }
}
