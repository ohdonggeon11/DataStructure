#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    int data;
    struct Node* next;
} Node;


// 1. 맨 앞에 노드 삽입
Node* insertFirst(Node* head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = head;

    return newNode;
}


// 2. 맨 뒤에 노드 삽입
Node* insertLast(Node* head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    }

    Node* current = head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;

    return head;
}


// 3. 특정 값을 가진 노드 뒤에 삽입
void insertAfterValue(Node* head, int targetValue, int newData) {
    Node* current = head;

    while (current != NULL) {
        if (current->data == targetValue) {
            Node* newNode = (Node*)malloc(sizeof(Node));

            newNode->data = newData;
            newNode->next = current->next;
            current->next = newNode;

            return;
        }

        current = current->next;
    }

    printf("값 %d를 가진 노드를 찾을 수 없습니다. 삽입하지 않습니다.\n", targetValue);
}


// 헤드 노드 삭제
Node* deleteHead(Node* head) {
    if (head == NULL) {
        printf("리스트가 비어 있습니다. 삭제할 노드가 없습니다.\n");
        return NULL;
    }

    Node* temp = head;
    head = head->next;
    free(temp);

    return head;
}


// 마지막 노드 삭제
Node* deleteLast(Node* head) {
    if (head == NULL) {
        printf("리스트가 비어 있습니다. 삭제할 노드가 없습니다.\n");
        return NULL;
    }

    if (head->next == NULL) {
        free(head);
        return NULL;
    }

    Node* current = head;

    while (current->next->next != NULL) {
        current = current->next;
    }

    free(current->next);
    current->next = NULL;

    return head;
}


// 특정 값을 가진 노드 삭제
Node* deleteNode(Node* head, int targetValue) {
    if (head == NULL) {
        printf("리스트가 비어 있습니다. 삭제할 노드가 없습니다.\n");
        return NULL;
    }

    if (head->data == targetValue) {
        Node* temp = head;
        head = head->next;
        free(temp);

        return head;
    }

    Node* current = head;

    while (current->next != NULL && current->next->data != targetValue) {
        current = current->next;
    }

    if (current->next == NULL) {
        printf("값 %d를 가진 노드를 찾을 수 없습니다.\n", targetValue);
        return head;
    }

    Node* temp = current->next;
    current->next = current->next->next;
    free(temp);

    return head;
}


// 실습 1-4. 리스트 출력 함수
void printList(Node* head) {
    Node* current = head;

    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }

    printf("NULL\n");
}


// 실습 1-5. 함수 1: 특정 값의 위치 찾기
int searchValue1(Node* head, int targetValue) {
    Node* current = head;
    int position = 1;

    while (current != NULL) {
        if (current->data == targetValue) {
            return position;
        }

        current = current->next;
        position++;
    }

    return -1;
}


// 실습 1-5. 함수 2: 특정 값의 앞뒤 노드 출력
void searchValue2(Node* head, int targetValue) {
    Node* prev = NULL;
    Node* current = head;

    while (current != NULL) {
        if (current->data == targetValue) {
            printf("%d를 찾았습니다.\n", targetValue);

            if (prev == NULL) {
                printf("앞 노드: 없습니다.\n");
            } else {
                printf("앞 노드: %d\n", prev->data);
            }

            if (current->next == NULL) {
                printf("뒤 노드: 없습니다.\n");
            } else {
                printf("뒤 노드: %d\n", current->next->data);
            }

            return;
        }

        prev = current;
        current = current->next;
    }

    printf("%d를 찾을 수 없습니다.\n", targetValue);
}


// 실습 1-5. 함수 3: 리스트 메모리 해제
void freeList(Node* head) {
    Node* current = head;
    Node* temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
}


int main() {
    Node* head = NULL;

    // 노드 삽입
    head = insertFirst(head, 30);
    head = insertFirst(head, 20);
    head = insertFirst(head, 10);

    head = insertLast(head, 70);
    head = insertLast(head, 80);
    head = insertLast(head, 90);

    insertAfterValue(head, 30, 40);
    insertAfterValue(head, 40, 50);
    insertAfterValue(head, 50, 60);

    // 실습 1-4: 리스트 출력
    printf("현재 리스트: ");
    printList(head);

    // 실습 1-5: searchValue1 테스트
    int val = 30;
    int pos = searchValue1(head, val);

    if (pos == -1) {
        printf("%d를 찾을 수 없습니다.\n", val);
    } else {
        printf("%d의 위치는 %d번째입니다.\n", val, pos);
    }

    // 실습 1-5: searchValue2 테스트
    searchValue2(head, val);

    // 실습 1-5: 메모리 해제
    freeList(head);

    return 0;
}
