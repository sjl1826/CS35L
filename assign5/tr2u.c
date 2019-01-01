#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

void checkArgs(int numArgs) {
  if(numArgs != 3) {
    fprintf(stderr, "Only 2 arguments allowed!");
    exit(1);
  }
}

void checkSameLength(int fromLen, int toLen) {
  if(fromLen != toLen) {
    fprintf(stderr, "Arguments must be of same length!");
    exit(1);
  }
}

void checkFromDuplicateBytes(char* from) {
  int i; int j;
  for(i = 0; i < strlen(from); i++) {
    for(j = i+1; j < strlen(from); j++) {
      if(from[i] == from[j]) {
	fprintf(stderr, "From must not have any duplicate bytes");
	exit(1);
      }
    }
  }
}

void translateString(char* from, char* to) {
  char currentChar[1];
  int charVal = read(0, currentChar, 1);
  char checkNoneFound = 'n';
  while(charVal > 0) {
    checkNoneFound = 'n';
    int i;
    for(i = 0; i < strlen(from); i++) {
      if(currentChar[0] == from[i]) {
	checkNoneFound = 'y';
	currentChar[0] = to[i];
	write(1, currentChar, 1);
	break;
      }
    }
    if(checkNoneFound == 'n')
      write(1, currentChar, 1);
    charVal = read(0, currentChar, 1);
  }
}

int main(int argc, char*argv[]) {
  checkArgs(argc);
  char* from = argv[1];
  char* to = argv[2];
  checkSameLength(strlen(from), strlen(to));
  checkFromDuplicateBytes(from);
  translateString(from, to);
  exit(0);
}
