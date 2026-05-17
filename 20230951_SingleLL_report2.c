#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 연락처 노드 구조체
typedef struct Contact {
    char name[50];
    char phone[30];
    struct Contact* next;
} Contact;


// 연락처 추가 함수
Contact* addContact(Contact* head, char name[], char phone[]) {
    Contact* newNode = (Contact*)malloc(sizeof(Contact));

    if (newNode == NULL) {
        printf("메모리 할당 실패\n");
        return head;
    }

    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->next = NULL;

    // 전화번호부가 비어 있는 경우
    if (head == NULL) {
        return newNode;
    }

    // 마지막 노드까지 이동
    Contact* current = head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;

    return head;
}


// 연락처 검색 함수
void searchContact(Contact* head, char name[]) {
    Contact* current = head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("검색 성공!\n");
            printf("이름: %s\n", current->name);
            printf("전화번호: %s\n", current->phone);
            return;
        }

        current = current->next;
    }

    printf("%s 이름의 연락처를 찾을 수 없습니다.\n", name);
}


// 연락처 삭제 함수
Contact* deleteContact(Contact* head, char name[]) {
    if (head == NULL) {
        printf("전화번호부가 비어 있습니다.\n");
        return NULL;
    }

    // 삭제할 연락처가 첫 번째 노드인 경우
    if (strcmp(head->name, name) == 0) {
        Contact* temp = head;
        head = head->next;
        free(temp);

        printf("%s 연락처가 삭제되었습니다.\n", name);
        return head;
    }

    Contact* current = head;

    while (current->next != NULL && strcmp(current->next->name, name) != 0) {
        current = current->next;
    }

    // 삭제할 연락처를 찾지 못한 경우
    if (current->next == NULL) {
        printf("%s 이름의 연락처를 찾을 수 없습니다.\n", name);
        return head;
    }

    Contact* temp = current->next;
    current->next = current->next->next;
    free(temp);

    printf("%s 연락처가 삭제되었습니다.\n", name);

    return head;
}


// 전체 연락처 출력 함수
void printContacts(Contact* head) {
    if (head == NULL) {
        printf("전화번호부가 비어 있습니다.\n");
        return;
    }

    Contact* current = head;

    printf("\n===== 현재 전화번호부 =====\n");

    while (current != NULL) {
        printf("이름: %s, 전화번호: %s\n", current->name, current->phone);
        current = current->next;
    }

    printf("==========================\n");
}


// 메모리 해제 함수
void freeContacts(Contact* head) {
    Contact* current = head;
    Contact* temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
}


int main() {
    Contact* head = NULL;

    int menu;
    char name[50];
    char phone[30];

    while (1) {
        printf("\n===== 전화번호부 관리 시스템 =====\n");
        printf("1. 연락처 추가\n");
        printf("2. 연락처 검색\n");
        printf("3. 연락처 삭제\n");
        printf("4. 전체 연락처 출력\n");
        printf("0. 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &menu);

        if (menu == 1) {
            printf("이름 입력: ");
            scanf("%s", name);

            printf("전화번호 입력: ");
            scanf("%s", phone);

            head = addContact(head, name, phone);
            printf("연락처가 추가되었습니다.\n");
        }
        else if (menu == 2) {
            printf("검색할 이름 입력: ");
            scanf("%s", name);

            searchContact(head, name);
        }
        else if (menu == 3) {
            printf("삭제할 이름 입력: ");
            scanf("%s", name);

            head = deleteContact(head, name);
        }
        else if (menu == 4) {
            printContacts(head);
        }
        else if (menu == 0) {
            printf("프로그램을 종료합니다.\n");
            break;
        }
        else {
            printf("잘못된 메뉴입니다. 다시 선택하세요.\n");
        }
    }

    freeContacts(head);

    return 0;
}
