int main() {
    Stack s;
    char str[MAX];
    initStack(&s);
    int isValid = 1;
    
    printf("문자열 입력 : ");
    fgets(str, MAX, stdin);
    str[strcspn(str, "\n")] = '\0';
    
    
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
    
   
    if(!isEmpty(&s)){
        isValid = 0;
    }
    
   
    if(isValid){
        printf("유효한 괄호\n");
    } else {
        printf("유효하지 않은 괄호\n");
    }
    
    return 0;
}
