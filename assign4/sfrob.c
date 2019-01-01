#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const* a, char const* b) {
  int aI = 0;
  int bI = 0;
  while(a[aI] != ' ' && b[bI] != ' ') {
    if(((a[aI])^42) > (((b[bI])^42))) { return 1; }
    else if (((a[aI])^42) < ((b[bI])^42)) { return -1; }
    aI++; bI++;
  }
  if(a[aI] == ' ' && b[bI] == ' ') { return -1; }
  if(b[bI] == ' ') { return 1; }
  return 0;
}

int compare(const void* a, const void* b) {
  const char* aC = *(const char **) a;
  const char* bC = *(const char **) b;
  return frobcmp(aC, bC);
}

void checkReadError() {
  if(ferror(stdin)) {
    fprintf(stderr, "Error reading file!");
    exit(1);
  }
}

void checkIfNull(char* character) {
  if(character == NULL) {
    free(character);
    fprintf(stderr, "Error reallocating memory!");
    exit(1);
  }
}

void checkIfNull2(char** words) {
    if(words == NULL) {
      free(words);
      fprintf(stderr, "Error reallocating memory!");
      exit(1);
    }
}

void checkEOF(char character) {
  if(putchar(character) == EOF) {
    fprintf(stderr, "Output error!");
    exit(1);
  }
}

int main() {
  char* word = (char*)malloc(0);
  int letterCount = 0;
  char** words = (char**)malloc(0);
  int wordCount = 0;
  char currentLetter = ' ';

  while(currentLetter != EOF && !ferror(stdin) && !feof(stdin)) {
    currentLetter = getchar();
    if(currentLetter == EOF) { break; }
    checkReadError();
    if(currentLetter == ' ' && letterCount == 0) { continue; }
    word = realloc(word, (letterCount + 1) * sizeof(char));
    word[letterCount] = currentLetter;
    letterCount++;
    checkIfNull(word);
    if(currentLetter == ' ' && letterCount > 1) {
      words = realloc(words, (wordCount + 1) * sizeof(char*));
      words[wordCount] = word;
      wordCount++;
      checkIfNull2(words);
      word = (char*)malloc(0);
      letterCount = 0;
    }
  }

  //clean up any words that weren't accounted for
  if(letterCount != 0) {
    word = realloc(word, (letterCount + 1) * sizeof(char));
    word[letterCount] = ' ';
    letterCount++;
    checkIfNull(word);

    words = realloc(words, (wordCount + 1) * sizeof(char*));
    words[wordCount] = word;
    wordCount++;
    checkIfNull2(words);
    word = (char*)malloc(0);
    letterCount = 0;
  }
  qsort(words, wordCount, sizeof(char*), compare);

  size_t i; size_t j;
  for(i = 0; i < wordCount; i++) {
    for(j = 0;; j++) {
      checkEOF(words[i][j]);
      if(words[i][j] == ' ')
	break;
    }
  }

  for(i = 0; i < wordCount; i++) { free(words[i]); }
  free(words);
  exit(0);
}
