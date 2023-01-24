#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct token {
  char token[100], tokenname[100];
  int row, col;
};

char specialsym[] = {
  ';',
  '?',
  ',',
  ':'
};
const char * dtype[] = {
  "int",
  "float",
  "char"
};
const char * predef[] = {
  "printf",
  "scanf"
};

static int row = 1, col = 0;
char c = ' ';
char * keyword[] = {
  "int",
  "float",
  "char",
  "const",
  "return",
  "if",
  "else",
  "else if",
  "while",
  "break",
  "continue",
  "case",
  "for",
  "switch",
  "boolean"
};
int retsize(char * str) {
  if (strcmp(str, "int") == 0)
    return 4;
  if (strcmp(str, "float") == 0)
    return 8;
  if (strcmp(str, "char") == 0)
    return 1;
  else
    return 0;
}
int ispredef(char * str) {
  for (int i = 0; i < 2; i++)
    if (strcmp(str, predef[i]) == 0)
      return 1;
  return 0;
}
int isdtype(char * str) {
  for (int i = 0; i < 3; i++)
    if (strcmp(str, dtype[i]) == 0)
      return 1;
  return 0;
}
int isspecialchar(char ch) {
  int flag = 0;
  for (int i = 0; i < 4; i++) {
    if (ch == specialsym[i]) {
      flag = 1;
      break;
    }
  }
  return flag;
}
int temp;
void filltoken(struct token * tok, char * tokenname, char * token) {
  strcpy(tok -> token, token);
  strcpy(tok -> tokenname, tokenname);
  tok -> row = row;
  tok -> col = temp;
}
struct token getnexttoken(FILE * fd) {
  char buf[100], d;
  int i = 1;
  struct token tok;
  while ((c = fgetc(fd)) != EOF) {
    col++;
    temp = col;
    if (isalpha(c) || c == '_') {
      buf[0] = c;
      c = fgetc(fd);
      col++;
      while (isalpha(c) || c == '_') {
        buf[i] = c;
        c = fgetc(fd);
        col++;
        i++;
      }
      buf[i] = '\0';
      fseek(fd, -1, SEEK_CUR);
      col--;
      for (i = 0; i < 14; i++) {
        if (strcmp(buf, keyword[i]) == 0) {
          filltoken( & tok, "keyword", buf);
          return tok;
        }
      }
      filltoken( & tok, "id", buf);
      return tok;
    } else if (isspecialchar(c)) {
      buf[0] = c;
      buf[1] = '\0';
      filltoken( & tok, "special symbol", buf);
      return tok;
    } else if (c == '+') {
      d = fgetc(fd);

      if (d == '+') {
        col++;
        filltoken( & tok, "incriment operator", "++");
        return tok;
      }
      filltoken( & tok, "Arithmatic operator", "+");
      fseek(fd, -1, SEEK_CUR);
      return tok;
    } else if (c == '-') {
      d = fgetc(fd);

      if (d == '-') {
        col++;
        filltoken( & tok, "incriment operator", "--");
        return tok;
      }
      filltoken( & tok, "Arithmatic operator", "-");
      fseek(fd, -1, SEEK_CUR);
      return tok;
    } else if (c == '*') {
      filltoken( & tok, "Arithmatic operator", "*");
      return tok;
    } else if (c == '<') {
      d = fgetc(fd);

      if (d == '=') {
        col++;
        filltoken( & tok, "le", "<=");
        return tok;
      }
      filltoken( & tok, "l", "<");
      fseek(fd, -1, SEEK_CUR);
      return tok;
    } else if (c == '>') {
      d = fgetc(fd);
      col++;
      if (d == '=') {
        filltoken( & tok, "ge", ">=");
        return tok;
      }
      filltoken( & tok, "g", ">");
      fseek(fd, -1, SEEK_CUR);
      col--;
      return tok;
    } else if (c == '!') {
      d = fgetc(fd);
      if (d == '=') {
        col++;
        filltoken( & tok, "ne", "!=");
        return tok;
      }
      filltoken( & tok, "complement", "!");
      fseek(fd, -1, SEEK_CUR);
      return tok;
    } else if (c == '=') {
      d = fgetc(fd);

      if (d == '=') {
        col++;
        filltoken( & tok, "equal to", "==");
        return tok;
      }
      filltoken( & tok, "assignment operator", "=");
      fseek(fd, -1, SEEK_CUR);
      return tok;
    } 
    else if (c == '%') {
      filltoken( & tok, "mulop", "%");
      return tok;
    }
    else if (c == '{') {
      filltoken( & tok, "lfb", "{");
      return tok;
    } else if (c == '}') {
      filltoken( & tok, "rfb", "}");
      return tok;
    } else if (c == '[') {
      filltoken( & tok, "lsb", "[");
      return tok;
    } else if (c == ']') {
      filltoken( & tok, "rsb", "]");
      return tok;
    } else if (c == '(') {
      filltoken( & tok, "lb", "(");
      return tok;
    } else if (c == ')') {
      filltoken( & tok, "rb", ")");
      return tok;
    } else if (isdigit(c)) {
      buf[0] = c;
      c = fgetc(fd);
      col++;
      while (isdigit(c)) {
        buf[i] = c;
        c = fgetc(fd);
        col++;
        i++;
      }
      buf[i] = '\0';
      fseek(fd, -1, SEEK_CUR);
      filltoken( & tok, "num", buf);
      return tok;
    } else if (c == '"') {
      buf[0] = c;
      while ((c = fgetc(fd)) != '"') {
        col++;
        buf[i] = c;
        i++;
      }
      col++;
      buf[i++] = c;
      buf[i] = '\0';
      filltoken( & tok, "string literal", buf);
      return tok;
    } else if (c == 39) {
      buf[0] = c;
      while ((c = fgetc(fd)) != 39) {
        col++;
        buf[i] = c;
        i++;
      }
      buf[i++] = c;
      buf[i] = '\0';
      col++;
      filltoken( & tok, "char const", buf);
      return tok;
    } else if (c == '&') {
      d = fgetc(fd);
      if (d == '&') {
        col++;
        filltoken( & tok, "logical And operator", "&&");
        return tok;
      }
      filltoken( & tok, "binary and operator", "+");
      fseek(fd, -1, SEEK_CUR);
      return tok;
    } else if (c == '|') {
      d = fgetc(fd);
      if (d == '|') {
        col++;
        filltoken( & tok, "logical or operator", "||");
        return tok;
      }
      filltoken( & tok, "binary or operator", "|");
      fseek(fd, -1, SEEK_CUR);
      return tok;
    } else if (c == '/') {
      d = fgetc(fd);
      if (d == '/') {
        col++;
        while ((c = fgetc(fd)) != '\n') {
          col++;
          continue;
        }
        row++;
        col = 0;
      } else if (d == '*') {
        col++;
        do {
          while ((d = fgetc(fd)) != '*') {
            if (d == '\n') {
              col = 0;
              row++;
            }
            col++;
            continue;
          }
          col++;
          c = fgetc(fd);
          col++;
        } while (c != '/');
      } else {
      fseek(fd, -1, SEEK_CUR);
        col++;
        filltoken( & tok, "arithmatic oprator", "/");
        return tok;
      }
    }
    else if (c == '#') {
      while ((c = fgetc(fd)) != '\n') {
        col++;
        continue;
      }
      row++;
      col = 0;
    } else if (c == ' ') {
      c = fgetc(fd);
      while (c == ' ') {
        col++;
        c = fgetc(fd);
        continue;
      }
      fseek(fd, -1, SEEK_CUR);
      continue;
    } else if (c == '\n') {
      row++;
      col = 0;
      continue;
    }
  }
  return tok;
}

