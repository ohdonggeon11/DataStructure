int main() {
    Stack s;
    initStack(&s); 
    
    
    char *str = (char*)malloc(MAX * sizeof(char));
    if (str == NULL) {
        printf("메모리 할당 실패\n");
        return -1;
    }
    
    printf("문자열 입력: ");
    fgets(str, MAX, stdin);
    str[strcspn(str, "\n")] = '\0';  
    
    
    for(int i = 0; str[i] != '\0'; i++) {
        push(&s, str[i]);
    }
    
    printf("거꾸로 된 문자열: ");
    
    
    while(!isEmpty(&s)){
        printf("%c", pop(&s));
    }
    printf("\n");
    
    
    free(str);
    
    return 0;
}
