#include<stdio.h>
#include "getnexttoken.h"
struct token tok;
FILE * f;
void declarations();
void data_types();
void identifier_list();
void assign_stat();
void A();
void B();
void program(){
if(strcmp(tok.token,"main")==0){
tok=getnexttoken(f);

if(strcmp(tok.token,"(")==0){
tok=getnexttoken(f);
if(strcmp(tok.token,")")==0){
tok=getnexttoken(f);
if(strcmp(tok.token,"{")==0){
tok=getnexttoken(f);
declarations();
assign_stat();
if(strcmp(tok.token,"}")==0)
return;
else
{
printf("Expected } at row: %d col: %d",tok.row,tok.col);
exit(1);
}
}
else {
printf("Expected \"{\" at row: %d col:%d",tok.row,tok.col);
exit(0);
}
}
else {
printf("Expected \")\" at row: %d col:%d",tok.row,tok.col);
exit(0);
}
}
else {
printf("Expected \"(\" at row: %d col:%d",tok.row,tok.col);
exit(0);
}}
else {
printf("Expected \"main\" at row: %d col:%d",tok.row,tok.col);
exit(1);
}
}
void declarations(){
if((strcmp(tok.tokenname,"id")==0)){
return;
}
else if((strcmp(tok.token,"int")==0)||(strcmp(tok.token,"char")==0)){
data_types();
identifier_list();
if(strcmp(tok.token,";")==0){
tok=getnexttoken(f);
declarations();
}
else {
printf("Expected ; at row: %d col:%d",tok.row,tok.col);
exit(0);
}
}
else{
printf("expected datatype or identifier at row: %d col: %d",tok.row,tok.col);
exit(1);}
}
void data_types(){
if(strcmp(tok.token,"int")==0){
tok=getnexttoken(f);
return;
}
else if(strcmp(tok.token,"char")==0){
tok=getnexttoken(f);
return;
}
else {
printf("Expected int or char at row:%d col:%d",tok.row,tok.col);
exit(0);
}
}
void identifier_list(){
if(strcmp(tok.tokenname,"id")==0){
tok=getnexttoken(f);
A();
}
else
{
printf("Expected id at position row:%d col:%d",tok.row,tok.col);
exit(1);
}
}
void A(){
if(strcmp(tok.token,",")==0){
tok=getnexttoken(f);
identifier_list();
}
else if(strcmp(tok.token,";")==0){
return;
}
else{
printf("Expected , or ; at position row:%d col:%d",tok.row,tok.col);
exit(1);
}

}
void assign_stat(){
if(strcmp(tok.tokenname,"id")==0){
tok=getnexttoken(f);
if(strcmp(tok.token,"=")==0){
tok=getnexttoken(f);
B();
}
else
{
printf("Expected = at position row:%d col:%d",tok.row,tok.col);
exit(1);
}
}
else
{
printf("Expected id at position row:%d col:%d",tok.row,tok.col);
exit(1);
}
}
void B(){
if(strcmp(tok.tokenname,"id")==0){
tok=getnexttoken(f);
if(strcmp(tok.token,";")==0){
tok=getnexttoken(f);
return;
}
else
{
printf("Expected ; at position row:%d col:%d",tok.row,tok.col);
exit(1);
}
}
else if(strcmp(tok.tokenname,"num")==0)
{
tok=getnexttoken(f);
if(strcmp(tok.token,";")==0){
tok=getnexttoken(f);
return;
}
else
{
printf("Expected ; at position row:%d col:%d",tok.row,tok.col);
exit(1);
}
}
else
{
printf("Expected id or num at position row:%d col:%d",tok.row,tok.col);
exit(1);
}
}
int main(){
f=fopen("input.c","r");
tok=getnexttoken(f);
program();
printf("compiled successfully");
return 0;
}
