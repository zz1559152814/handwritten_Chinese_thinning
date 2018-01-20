#ifndef LIST_H__
#define LIST_H__

#include <iostream>
#define list_elem double
typedef struct Node
{
    int data;
    Node *next;
};

class ListOperate
{
    friend int &justatest(ListOperate &listf,int &a);
public:
    operator double();

    ListOperate(void);

    Node *gethead(void) const;

    void setphead(Node *p);

    double getdata(int pos) const;

    void initlist(void);

    void readdatafromfile(void);

    void ListCreat(void);

    void pflist(void) const;

    int  sizelist() const;

    void clearlist() const;

    void returnelem(int pos) const;

    void findelem(list_elem indata) const;

    list_elem returnelem(int pos,double x ) const;

    void change(int pos,double x) const;

    void exchange(int pos1 ,int pos2) const;

    void setnode(int pos,double number) const;

    void inserthead(list_elem indata);

    void deletepos(int pos);

    void inserttail(int indata);

    void deletelem(list_elem ele);

    /*√∞≈›°¢—°‘Ò°¢≤Â»Î°¢øÏ≈≈°¢πÈ≤¢°¢œ£∂˚°¢∂—≈≈–Ú*/
    void bubblesort1() const;

    void bubblesort2() const;


//    Node *sortlist();
//    bool insertandsort(elem data);
private:

    Node *phead;

    Node *ptail;
};

#endif