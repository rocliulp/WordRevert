#include "stdio.h"
#include "stdlib.h"

int revert_sentence (char * sentence, int len) {
  int ret = 0;

  int tagS = 0;
  int tagE = 0;

  int startS = 0;
  int lenS = 0;

  int startE = 0;
  int lenE = 0;

  char * buffer = NULL;

  int i = 0;

  int gap = 0;

  tagS = 0;
  while (tagS < len && sentence[tagS] != ' ') {
    ++tagS;
  }

  if (tagS == len) return 0;

  tagE = len - 1;
  while (tagE > -1 && sentence[tagE] != ' ') {
    --tagE;
  }

  if (tagE == 0) return 1;
  if (tagE < tagS) return 1;

  startS = 0;
  lenS = tagS;

  startE = tagE + 1;
  lenE = len - 1 - tagE;


  if (lenS > lenE) {
    buffer = malloc (lenS);
    
    i = 0;
    while (i < lenS) {
      buffer[i] = sentence[i];
      ++i;
    }

    i = 0;
    while (i < lenE) {
      sentence[i] = sentence[startE + i];
      ++i;
    }

    gap = lenS - lenE;
    i = tagS;
    while (i < startE) {
      sentence[i - gap] = sentence[i];
      ++i;
    }

    i = 0;
    while (i < lenS) {
      sentence[len - 1 - i] = buffer[lenS - 1 - i];
      ++i;
    }

    free (buffer);
  } else {
    buffer = malloc (lenE);
    
    i = 0;
    while (i < lenE) {
      buffer[i] = sentence[startE + i];
      ++i;
    }

    i = 0;
    while (i < lenS) {
      sentence[len - 1 - i] = sentence[lenS - 1 - i];
      ++i;
    }

    gap = lenE - lenS;
    i = tagE;
    while (i > tagS - 1) {
      sentence[i + gap] = sentence[i];
	  --i;
    }

    i = 0;
    while (i < lenE) {
      sentence[i] = buffer[i];
      ++i;
    }

    free (buffer);
  }

  if (tagS == tagE) {
    return 0;
  } else {
    len = len - lenS - lenE - 2;
    buffer = sentence + lenE + 1;
    return revert_sentence (buffer, len);
  }
}

int main (int argc, char * argv []) {
  int ret = 0;

  char sentence [1024] = {'\0'};
  char * pChar = 0;

  int i = -1;
  int j = -1;

  while (++i < argc - 1) {
    pChar = argv[i];
    while (*pChar != '\0') {
      sentence[++j] = *pChar;
      ++pChar;
    }
    sentence[++j] = ' ';
  }
  pChar = argv[argc - 1];
  while (*pChar != '\0') {
    sentence[++j] = *pChar;
    ++pChar;
  }

  printf ("\n\r");
  printf ("%s\n\r", sentence);

  ret = revert_sentence (sentence, j + 1);
  printf ("ret: %d\n\r", ret);
  printf ("%s\n\r", sentence);

  return 0;
}
