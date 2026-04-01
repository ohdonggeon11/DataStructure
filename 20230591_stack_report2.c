int main() {
    Stack s;
    initStack(&s);  // 스택 초기화
    
    // 문자열을 저장할 메모리 동적 할당
    char *str = (char*)malloc(MAX * sizeof(char));
    if (str == NULL) {
        printf("메모리 할당 실패\n");
        return -1;
    }
    
    printf("문자열을 입력하세요: ");
    fgets(str, MAX, stdin);
    str[strcspn(str, "\n")] = '\0';  // 엔터 키('\n') 제거
    
    int isValid = 1; // 괄호의 유효성을 체크하는 플래그 (1: 유효함, 0: 유효하지 않음)
    
    for(int i = 0; str[i] != '\0'; i++) {
        char ch = str[i];
        
        // 1. 여는 괄호일 경우 스택에 삽입 (Push)
        if (ch == '(' || ch == '{' || ch == '[') {
            push(&s, ch);
        } 
        // 2. 닫는 괄호일 경우 확인 로직
        else if (ch == ')' || ch == '}' || ch == ']') {
            // 스택이 비어있는데 닫는 괄호가 나온 경우 (짝이 부족함)
            if (isEmpty(&s)) {
                isValid = 0;
                break;
            }
            
            char topCh = pop(&s); // 스택의 맨 위 괄호를 꺼냄
            
            // 꺼낸 여는 괄호와 현재 닫는 괄호의 짝이 맞는지 검사
            if ((ch == ')' && topCh != '(') ||
                (ch == '}' && topCh != '{') ||
                (ch == ']' && topCh != '[')) {
                isValid = 0; // 짝이 맞지 않으면 무효 처리
                break;
            }
        }
    }
    
    // 3. 문자열을 끝까지 검사했는데 스택에 여는 괄호가 남아있는 경우 (닫는 괄호가 부족함)
    if (!isEmpty(&s)) {
        isValid = 0;
    }
    
    // 최종 결과 출력
    if (isValid) {
        printf("유효한 괄호\n");
    } else {
        printf("유효하지 않은 괄호\n");
    }
    
    free(str); // 프로그램 종료 시 메모리 해제
    
    return 0;
}
