#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

void encrypt(char *plaintext, char *ciphertext_alphabet){
	char ciphertext[100];
	for(int i=0;plaintext[i]!='\0';i++){
		if(isalpha(plaintext[i])){
			char offset=isupper(plaintext[i])?'A':'a';
			int index=plaintext[i]-offset;
			ciphertext[i]=isupper(plaintext[i])?toupper(ciphertext_alphabet[index]):tolower(ciphertext_alphabet[index]);
		}
		else{
			ciphertext[i]=plaintext[i];
		}
	}
	ciphertext[strlen(plaintext)]='\0';
	printf("encrypted text: %s\n",ciphertext);	
}

int main(){
	char plaintext[100];
	char ciphertext_alphabet[27];
	
	printf("enter the text to be encrypted: ");
	fgets(plaintext,sizeof(plaintext),stdin);
	plaintext[strcspn(plaintext, "\n")] = '\0';
	
	printf("enter the ciphertext alphabet: ");
	fgets(ciphertext_alphabet,sizeof(ciphertext_alphabet),stdin);
	ciphertext_alphabet[strcspn(ciphertext_alphabet,"\n")]='\0';
	
	if(strlen(ciphertext_alphabet)!=26){
		printf("error: the ciphertext must contain 26 alphabets");
		return 1;
	}
	encrypt(plaintext,ciphertext_alphabet);
	return 0;
}
