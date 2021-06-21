#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 22

typedef struct list
{
  char field[22]; // поле данных
  struct list *next; // указатель на следующий элемент
  struct list *prev; // указатель на предыдущий элемент
} list;


struct list* head;

struct list * init(char* a)  // а- значение первого узла
{
  struct list *lst;
  // выделение памяти под корень списка
  lst = (struct list*)malloc(sizeof(struct list));
  strcpy(lst->field, a);
  lst->next = lst; // указатель на следующий узел
  lst->prev = lst; // указатель на предыдущий узел
  return(lst);
}

struct list * addelem(struct list *lst, char* number)
{
  struct list *temp, *p;
  temp = (struct list*)malloc(sizeof(list));
  p = lst->next; // сохранение указателя на следующий узел
  lst->next = temp; // предыдущий узел указывает на создаваемый
  strcpy(temp->field, number); // сохранение поля данных добавляемого узла
  temp->next = p; // созданный узел указывает на следующий узел
  temp->prev = lst; // созданный узел указывает на предыдущий узел
  p->prev = temp;
  return(temp);
}

struct list * deletelem(list *lst)
{
  struct list *prev, *next;
  prev = lst->prev; // узел, предшествующий lst
  next = lst->next; // узел, следующий за lst
  prev->next = lst->next; // переставляем указатель
  next->prev = lst->prev; // переставляем указатель
  free(lst); // освобождаем память удаляемого элемента
  return(prev);
}

void listprint(list *lst)
{
  struct list *p;
  p = lst;
  do {
    puts(p->field); // вывод значения элемента p
    p = p->next; // переход к следующему узлу
  } while (p != lst); // условие окончания обхода
}

int main(void) {
  int n_people;
  char line;
  scanf("%d", &n_people);
  fgets(line, SIZE, stdin);
  head = init(line);

}
