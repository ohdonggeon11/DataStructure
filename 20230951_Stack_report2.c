#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100  // 스택의 최대 크기 정의

typedef struct {
    int data[MAX];
    int top;  // 스택의 최상단 요소를 가리키는 인덱스
} Stack;

// --- 기존 스택 함수들 시작 ---
void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack overflow! Cannot push %d\n", value);
        return;
    }
    s->data[++(s->top)] = value;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        return -1;  // 에러 값
    }
    return s->data[(s->top)--];
}
// --- 기존 스택 함수들 끝 ---


// 💡 교수님이 추가하신 괄호 짝 검사 함수
int isMatching(char open, char close){
    if(open == '(' && close == ')') return 1;
    if(open == '[' && close == ']') return 1;
    if(open == '{' && close == '}') return 1;
    return 0;
}

int main() {
    Stack s;
    char str[MAX];
    initStack(&s);
    int isValid = 1;
    
    printf("문자열 입력 : ");
    fgets(str, MAX, stdin);
    str[strcspn(str, "\n")] = '\0';
    
    // 교수님 코드와 동일한 로직
    for(int i=0; str[i] != '\0'; i++){
        char ch = str[i];
        
        // 여는 괄호면 push
        if(ch == '(' || ch == '[' || ch == '{'){
            push(&s, ch);
        } 
        // 닫는 괄호면 스택에서 꺼내서 짝이 맞는지 확인
        else if(ch == ')' || ch == ']' || ch == '}'){
            // 스택이 비어있거나, 꺼낸 괄호와 짝이 안 맞으면 무효!
            if(isEmpty(&s) || !isMatching(pop(&s), ch)){
                isValid = 0;
                break;
            }
        }
    }
    
    // 💡 문자열을 다 돌았는데 스택에 여는 괄호가 남아있다면 무효! (예: "(()" 같은 경우)
    if(!isEmpty(&s)){
        isValid = 0;
    }
    
    // 최종 결과 출력 (교수님 화면 밑에 잘린 부분)
    if(isValid){
        printf("유효한 괄호\n");
    } else {
        printf("유효하지 않은 괄호\n");
    }
    
    return 0;
}
