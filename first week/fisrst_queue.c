/*
    큐(queue)는 컴퓨터의 기본적인 자료구조의 한가지로, 먼저 집어 넣은 데이터가 먼저 나오는
    FIFO(First In First Out) 구조로 저장하는 형식을 말한다.
    나중에 집어 넣은 데이터가 먼저 나오는 스택과는 반대되는 개념이다.
    큐는 front 에서 Dequeue(데이터를 꺼냄) 연산이 진행되고, back 부분에서 Enqueue(데이터를 넣음) 연산이 진행된다.
*/

#include <stdio.h>
#include <string.h>
int queue[10000];  //10000의 배열크기를 가지는 정수형 배열 선언
int queue_size = 0; //큐 사이즈를 0으로 초기화

//함수 선언 및 정의

void push(int push_data) {   //큐의 마지막 요소에 정수를 추가하는 함수 
    queue[queue_size] = push_data;
    queue_size += 1;                //큐 사이즈 1 증가
}

int empty() {    //전달값이 없고 조건에 따라 0 또는 1을 반환하는 함수
    if (queue_size == 0) {
        return 1;   //큐가 비어있으면 1을 반환하고 채워져 있으면 0을 반환
    }
    else {
        return 0;
    }
}

void pop() {      //큐의 가장 앞에있는 정수를 빼고 출력, 큐에 정수가 없으면 -1 출력
    if (queue_size == 0) {
        printf("%d\n", -1);
    }
    else {
        queue_size -= 1;
        printf("%d\n", queue[0]);
        
        for (int i = 0; i < queue_size; i++){  //pop명령어를 실행하면 첫번째 요소가 제거되는 특성 
        queue[i] = queue[i+1];
    }
    }
}

void size() {
    printf("%d\n", queue_size);
}

void front() {
    if (queue_size == 0) {
        printf("%d\n", -1);
    }
    else {
        printf("%d\n", queue[0]);
    }
}

void back() {
    if (queue_size == 0) {
        printf("%d\n", -1);
    }
    else {
        printf("%d\n", queue[queue_size - 1]);
    }
}



int main() {
    int N = 0, push_data = 0;
    char command[5]; // 명령어 크기에 따른 배열 생성
    scanf("%d", &N);  //명령 횟수 N주소에 저장
    for (int i = 0; i < N; i++) {
        scanf("%s", command);
        if (strcmp("push", command) == 0) {  //입력한 명령어가 push와 같으면 if문 실행
            scanf("%d", &push_data);
            push(push_data);
        }
        else if (strcmp("pop", command) == 0) {
            pop();
        }

        else if (strcmp("empty", command) == 0) {
            printf("%d\n",empty());
        }
        else if (strcmp("size", command) == 0) {
            size();
        }
        else if (strcmp("front", command) == 0) {
            front();
        }
        else if (strcmp("back", command) == 0) {
            back();
        }
    }

    return 0;
}
