#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct token{
  char token[100], tokenname[100];
  int row, col;
}token;

char specialsym[] = {
  ';',
  '?',
  ',',
  ':'
};
const char* dtype[] = {
  "int",
  "float",
  "char"
};
const char* predef[] = {
  "printf",
  "scanf"
};

static int row = 1, col = 0;
char c = ' ';

char *keyword[] = {
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

// Return size of datatype
int retsize(char* str) {
  if (strcmp(str, "int") == 0)
    return 4;
  if (strcmp(str, "float") == 0)
    return 8;
  if (strcmp(str, "char") == 0)
    return 1;
  else
    return 0;
}

// Check if it is printf, scanf
int ispredef(char* str) {
  for (int i = 0; i < 2; i++)
    if (strcmp(str, predef[i]) == 0)
      return 1;
  return 0;
}

// Check if it is a datatype
int isdtype(char* str) {
  for (int i = 0; i < 3; i++)
    if (strcmp(str, dtype[i]) == 0)
      return 1;
  return 0;
}

// Check if it is a special symbol
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


// Create a token
void filltoken(token* tok, char* tokenname, char* token) {
  strcpy(tok -> token, token);
  strcpy(tok -> tokenname, tokenname);
  tok -> row = row;
  tok -> col = temp;
  // Print token
  printf("< %s , %s >", tok->token, tok->tokenname);
  printf("\n");
}


// Generate Token
token getnexttoken(FILE * fd) {
  char buf[100], d;
  int i = 1;
  token tok;

  // While loop till EOF
  while ((c = fgetc(fd)) != EOF) {
    col++;
    temp = col;
    
    // Check if it is a alphabet
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

      // Move fd back to i-1 pos
      fseek(fd, -1, SEEK_CUR);
      col--;

      // Check if it is a keyword
      for (i = 0; i < 14; i++) {
        if (strcmp(buf, keyword[i]) == 0) {
          filltoken(&tok, "keyword", buf);
          return tok;
        }
      }
      filltoken(&tok, "id", buf);
      return tok;
    }

    // Check if it is a special symbol
    else if (isspecialchar(c)) {
      buf[0] = c;
      buf[1] = '\0';
      filltoken(&tok, "special symbol", buf);
      return tok;
    }
    
    // Check between unary & binary '+' operator
    else if (c == '+'){
      d = fgetc(fd);    // IMP
      if (d == '+') {
        col++;
        filltoken( & tok, "incriment operator", "++");
        return tok;
      }
      // Binary
      filltoken( & tok, "Arithmatic operator", "+");
      fseek(fd, -1, SEEK_CUR);
      return tok;
    }
    
    // Check between unary & binary '-' operator
    else if (c == '-'){
      d = fgetc(fd);    // IMP
      if (d == '-') {
        col++;
        filltoken( & tok, "incriment operator", "--");
        return tok;
      }
      // Binary
      filltoken( & tok, "Arithmatic operator", "-");
      fseek(fd, -1, SEEK_CUR);
      return tok;
    }
    
    // Check if it is a '*' operator
    else if (c == '*') {
      filltoken( & tok, "Arithmatic operator", "*");
      return tok;
    }
    
    // Check if it is a '<' or '<=' operator
    else if (c == '<') {
      d = fgetc(fd);

      if (d == '=') {
        col++;
        filltoken( & tok, "le", "<=");
        return tok;
      }
      filltoken( & tok, "l", "<");
      fseek(fd, -1, SEEK_CUR);
      return tok;
    }
    
    // Check if it is a '>' or '>=' operator
    else if (c == '>') {
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
    }
    
    // Check if it is a '!' operator
    else if (c == '!') {
      d = fgetc(fd);
      if (d == '=') {
        col++;
        filltoken( & tok, "ne", "!=");
        return tok;
      }
      filltoken( & tok, "complement", "!");
      fseek(fd, -1, SEEK_CUR);
      return tok;
    }
    
    // Check if it is a '=' or '==' operator
    else if (c == '=') {
      d = fgetc(fd);
      // Comparision
      if (d == '=') {
        col++;
        filltoken( & tok, "equal to", "==");
        return tok;
      }
      // Assignment
      filltoken(&tok, "assignment operator", "=");
      fseek(fd, -1, SEEK_CUR);
      return tok;
    }

    // Check if it is a '%' operator
    else if (c == '%') {
      filltoken( & tok, "mulop", "%");
      return tok;
    }

    // Check if it is a left flower bracket
    else if (c == '{') {
      filltoken( & tok, "lfb", "{");
      return tok;
    }
    
    // Check if it is a right flower bracket
    else if (c == '}') {
      filltoken( & tok, "rfb", "}");
      return tok;
    }

    // Check if it is a left square bracket
    else if (c == '[') {
      filltoken( & tok, "lsb", "[");
      return tok;
    }
    
    // Check if it is a right square bracket
    else if (c == ']') {
      filltoken( & tok, "rsb", "]");
      return tok;
    }
    
    // Check if it is a left circle bracket
    else if (c == '(') {
      filltoken( & tok, "lb", "(");
      return tok;
    }
    
    // Check if it is a right circle bracket
    else if (c == ')') {
      filltoken( & tok, "rb", ")");
      return tok;
    }
    
    // Check if it is a Number
    else if (isdigit(c)) {
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
    }
    
    // Check if it is a string literal
    else if (c == '"') {
      buf[0] = c;
      while ((c = fgetc(fd)) != '"') {
        col++;
        buf[i] = c;
        i++;
      }
      col++;
      buf[i++] = c;
      buf[i] = '\0';
      filltoken(&tok, "string literal", buf);
      return tok;
    }
    
    // Check if it is a number
    else if (c == 39) {
      buf[0] = c;
      while ((c = fgetc(fd)) != 39) {
        col++;
        buf[i] = c;
        i++;
      }
      buf[i++] = c;
      buf[i] = '\0';
      col++;
      filltoken(&tok, "char const", buf);
      return tok;
    }
    
    // Binary and Unary '&'
    else if (c == '&') {
      d = fgetc(fd);
      if (d == '&') {
        col++;
        filltoken( & tok, "logical And operator", "&&");
        return tok;
      }
      filltoken( & tok, "binary and operator", "+");
      fseek(fd, -1, SEEK_CUR);
      return tok;
    }
    
    // Binary & Unary '|'
    else if (c == '|') {
      d = fgetc(fd);
      if (d == '|') {
        col++;
        filltoken( & tok, "logical or operator", "||");
        return tok;
      }
      filltoken( & tok, "binary or operator", "|");
      fseek(fd, -1, SEEK_CUR);
      return tok;
    }
    
    // Comments
    else if (c == '/') {
      d = fgetc(fd);

      // Single line comments
      if (d == '/') {
        col++;
        while ((c = fgetc(fd)) != '\n') {
          col++;
          continue;
        }
        row++;
        col = 0;
      }
      
      // Mutli-line comments
      else if (d == '*') {
        col++;
        do{
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
        }while (c != '/');
      }
      
      // Check if it is a division operator { single '/' }
      else{
        // One step back, to the '/'.
        fseek(fd, -1, SEEK_CUR);
        col++;
        filltoken(&tok, "arithmatic oprator", "/");
        return tok;
      }
    }

    // Header files
    else if (c == '#') {
      while ((c = fgetc(fd)) != '\n') {
        col++;
        continue;
      }
      row++;
      col = 0;
    }
    
    // Empty Spaces
    else if (c == ' '){
      c = fgetc(fd);
      while(c == ' '){
        col++;
        c = fgetc(fd);
        continue;
      }
      // One step back, to the start of the next token
      fseek(fd, -1, SEEK_CUR);
      continue;
    }
    
    // Next line
    else if (c == '\n') {
      row++;
      col = 0;
      continue;
    }
  }
  return tok;
}