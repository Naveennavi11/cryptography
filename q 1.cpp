#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void encrypt(char *text, int k){
	int length=strlen(text);
	for(int i=0;i<length;i++){
		if(isalpha(text[i])){
			char offset=isupper(text[i])?'A':'a';
			text[i]=(text[i]-offset+k)%26+offset;
		}
	}
}

int main(){
	char text[100];
	int k;
	
	printf("enter the text to be encrypted: ");
	fgets(text,sizeof(text),stdin);
	text[strcspn(text, "\n")]='\0';
	
	printf("enter the shift value (k): ");
	scanf("%d", &k);
	
	if(k<1 || k>25){
		printf("shift value must be in the range 1 through 25.\n");
		return 1;
	}
	
	encrypt(text,k);
	printf("encrypted text: %s\n",text);
	
	return 0;
}
