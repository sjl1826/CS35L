#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int frobcmp(char const* a, char const* b) {
  int aI = 0;
  int bI = 0;
  while(a[aI] != ' ' && b[bI] != ' ') {
    if(((a[aI])^42) > (((b[bI])^42))) { return 1; }
    else if (((a[aI])^42) < ((b[bI])^42)) { return -1; }
    aI++; bI++;
  }
  if(a[aI] == ' ' && b[bI] == ' ') { return 0; }
  if(a[aI] == ' ') { return -1; }
  if(b[bI] == ' ') { return 1; }
  return 0;
}

int compare(const void* a, const void* b) {
  const char* aC = *(const char **) a;
  const char* bC = *(const char **) b;
  return frobcmp(aC, bC);
}

int frobcmp2(char const* a, char const* b) {
  int aI = 0;
  int bI = 0;
  while(a[aI] != ' ' && b[bI] != ' ') {
    char aUpper = (a[aI])^42;
    char bUpper = (b[bI])^42;
    if(isalpha(aUpper))
      aUpper = toupper((unsigned char) aUpper);
    if(isalpha(bUpper))
      bUpper = toupper((unsigned char) bUpper);
    if(a[aI] == ' ' && b[bI] == ' ') return 0;
    if(a[aI] == ' ' || aUpper < bUpper) return -1;
    if(b[bI] == ' ' || aUpper > bUpper) return 1;
    aI++; bI++;
  }
  return 0;
}

int comparef(const void* a, const void* b) {
  const char* aC = *(const char **) a;
  const char* bC = *(const char **) b;
  return frobcmp2(aC, bC);
}

int setSize() {
  struct stat fileStat;
  if(fstat(0, &fileStat) < 0) {
    fprintf(stderr, "File stat error");
    exit(1);
  }
  int size = 0;
  if(S_ISREG(fileStat.st_mode)) {
    size = fileStat.st_size;
  }
  return size;
}

int main(int argc, char* const argv[]) {
  int size = setSize();
  
  char* word = (char*)malloc(size*sizeof(char));
  int letterCount = 0;
  char** words = (char**)malloc(0);
  int wordCount = 0;
  char currentLetter = ' ';

  while(read(0, &currentLetter, sizeof(char)) > 0) {
    if(letterCount >= size) {
      size++;
      word = realloc(word, size*sizeof(char));
    }

    if((letterCount == 0) && (currentLetter == ' ')) { continue; }
    if((letterCount > 0) && (currentLetter == ' ') && (word[letterCount-1] == ' ')) { continue; }
    word[letterCount] = currentLetter;
    letterCount++;
  }
  if(word[letterCount-1]!= ' ') {
    size++;
    word = realloc(word, size*sizeof(char));
    word[letterCount] = ' ';
    letterCount++;
  }
  int a = 0;
  int next = 0;
  while(a < letterCount) {
    if(word[a] == ' ') {
      wordCount++;
      words = realloc(words, wordCount * sizeof(char*));
      words[wordCount-1] = word + next;
      next = a + 1;
    }
    a++;
  }

  if(argc == 2) {
    if(argv[1][1] == 'f') {
      qsort(words, wordCount, sizeof(char*), comparef);
    }
  } else {
      qsort(words, wordCount, sizeof(char*), compare);
  }

  char space = ' ';
  char holder;
  size_t i; size_t j;
  for(i = 0; i < wordCount; i++) {
    for(j = 0; words[i][j] != ' '; j++) {
      holder = words[i][j];
      write(1, &holder, 1);
    }
    write(1, &space, 1);
  }

  free(word);
  free(words);
  exit(0);
}
