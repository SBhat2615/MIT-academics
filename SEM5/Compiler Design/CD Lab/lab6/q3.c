#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr = 0;
char str[100];

void S();
void A();
void Aprime();
void B();

void invalid(){
	printf("Error\n");
	exit(0);
}

void valid(){
	printf("Success\n");
	exit(0);
}

void S(){
	if(str[curr] == 'a'){
		curr++;
		A();
		if(str[curr] == 'c'){
			curr++;
			B();
			if(str[curr] == 'e'){
				curr++;
				return;
			}
			else
				invalid();
		}
		else
			invalid();
	}
	else
		invalid();
}

void A(){
	if(str[curr] == 'b'){
		curr++;
		Aprime();
	}
	else
		invalid();
}

void Aprime(){
	if(str[curr] == 'b'){
		curr++;
		Aprime();
	}
}

void B(){
	if(str[curr] == 'd'){
		curr++;
	}
	else
		invalid();
}

int main(){
	printf("Enter string: ");
	scanf("%s", str);
	S();
	if(str[curr] == '$')
		valid();
	else{
		printf("%c\n", str[curr]);
		invalid();
	}
}