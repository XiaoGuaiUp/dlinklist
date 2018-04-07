#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "dlinklist.h"

//创建节点
DLinkNode* CreateDLinkNode(DLinkType value)
{
    DLinkNode* new_node=(DLinkNode*)malloc(sizeof(DLinkNode));
    new_node->data=value;
    new_node->prev=new_node;
    new_node->next=new_node;
    return new_node;
}
//初始化
void DLinkListInit(DLinkNode** phead)
{
    if(phead == NULL)
        return; //非法输入
    //创建节点
    *phead=CreateDLinkNode(2);
}

//尾插
void DLinkListPushBack(DLinkNode* head,DLinkType value)
{
    if(head==NULL)
    {//非法输入
        return;
    }
    DLinkNode* tail=head->prev;
    DLinkNode* new_node=CreateDLinkNode(value);
    //以下要修改4个指针
    //head VS new_node
    head->prev=new_node;
    new_node->next=head;
    //new_node VS tail
    tail->next=new_node;
    new_node->prev=tail;
    return;
}

//尾删
void DLinkListPopBack(DLinkNode* head)
{
    if(head==NULL)
    {//非法输入
        return;
    }
    if(head->prev==head)
    {//空链表
        return;
    }
    //修改两个指针
    DLinkNode* to_delete=head->prev;
    DLinkNode* prev=to_delete->prev;
    head->prev=prev;
    prev->next=head;
    free(to_delete);
    return;
}


//头插
void DLinkListPushFront(DLinkNode* head,DLinkType value)
{
    if(head==NULL)
    {
        return;
    }
    //找到head的下一个节点
    DLinkNode* next=head->next;
    DLinkNode*new_node=CreateDLinkNode(value);
    head->next=new_node;
    new_node->prev=head;
    new_node->next=next;
    next->prev=new_node;
    return;
}
//头删
void DLinkListPopFront(DLinkNode* head)
{
    if (head==NULL)
    {
        return;
    }
    if(head->prev==NULL)
    {//空链表
        return;
    }
    //找到要删除节点
    DLinkNode* to_delete=head->next;
    //找到要删除节点的下一个节点
    DLinkNode* next=to_delete->next;
    //修改两个指针
    head->next=next;
    next->prev=head;
    free(to_delete);
    return;
}


//插入pos之后
void DLinkListBackInsert(DLinkNode* head,DLinkNode* pos,DLinkType value)
{
    if(head==NULL && pos==NULL)
    {
        return;
    }
    DLinkNode* new_node=CreateDLinkNode(value);
    DLinkNode* next=pos->next;
    //修改4个指针
    pos->next=new_node;
    new_node->prev=pos;
    new_node->next=next;
    next->prev=new_node;
    return;
}
//插入pos之前
void DLinkListBeforeInsert(DLinkNode* head,DLinkNode* pos,DLinkType value)
{
    if(head==NULL && pos==NULL)
    {
        return;
    }
    DLinkNode* prev=pos->prev;
    DLinkNode* new_node=CreateDLinkNode(value);
    //修改4个指针
    prev->next=new_node;
    new_node->prev=prev;
    new_node->next=pos;
    pos->prev=new_node;
    return;
}

//查找给定值的节点，找到返回该节点，否则返回NULL
DLinkNode* DLinkListFind(DLinkNode* head,DLinkType to_find)
{
    if(head==NULL)
    {//非法输入
        return NULL;
    }
    if(head->prev==head)
    {//空链表
        return NULL;
    }
    DLinkNode* cur=head->next;
    for(;cur!=head;cur=cur->next)
    {
        if(cur->data==to_find)
        {
            return cur;
        }
    }
    return NULL;
}
//删除pos位置指向的值
void DLinkListErase(DLinkNode* head,DLinkNode* pos)
{
    if(head==NULL && pos==NULL)
    {//非法输入
        return;
    }
    if(head->prev==head)
    {//空链表
        return;
    }
    if(head == pos)
    {//头结点不能删
        return;
    }
    //找到pos之前的值
    DLinkNode* prev=pos->prev;
    DLinkNode* next=pos->next;
    //修改4个指针
    prev->next=next;
    next->prev=prev;
    free(pos);
    return;
}

//删除给定值的节点
void DLinkListRemove(DLinkNode* head,DLinkType to_remove_value)
{
    if(head==NULL)
    {
        return;
    }
    DLinkNode* to_remove_pos=DLinkListFind(head,to_remove_value);
    if(to_remove_pos==NULL)
    {//没找到
        return;
    }    
    DLinkListErase(head,to_remove_pos);
    return;
}

//删除给定值的所有节点
void DLinkListRemoveAll(DLinkNode* head,DLinkType to_remove_value)
{
    if(head==NULL)
    {
        return;
    }
    while(1)
    {

        DLinkNode* to_remove_pos=DLinkListFind(head,to_remove_value);
        if(to_remove_pos==NULL)
        {//没找到
            return;
        }
        DLinkListErase(head,to_remove_pos);
    }
    return;
}
//销毁链表
void DLinkListDestroy(DLinkNode** phead)//要修改头指针，要用**；如果不修改头指针就成野指针了。
{
    if(phead==NULL)
    {
        return;
    }
    DLinkNode* cur=(*phead)->next;
    while(cur!=*phead)
    {
        //备份next
        DLinkNode* next=cur->next;
        free(cur);
        cur=next;
    }
    //将头节点销毁
    free(*phead);
    *phead=NULL;
}


/////////////////////////////////////////////////////////////////////////////////////
//以下是测试代码
///////////////////////////////////////////////////////////////////////////////////
#define TESTHEADER printf("=================  %s  ===============\n",__FUNCTION__);


void DLinkPrint(DLinkNode* head,const char* msg)
{
    if(head == NULL)
    {
        return;
    }
    printf("[ %s ]\n",msg);
    //正向打一遍，反向打一遍
    DLinkNode* cur=head->next;
    for(;cur!=head;cur=cur->next)
    {
        printf("[ %c | %p ]",cur->data,cur);
    }
    printf("\n");
    for(cur=cur->prev;cur!=head;cur=cur->prev)
    {
        printf("[ %c | %p ]",cur->data,cur);
    }
    printf("\n");
}

void TestInit()
{

    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkPrint(head,"测试初始化");
}

void TestPushBack()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'d');
    DLinkPrint(head,"尾插4个元素");
}

void TestPopBack()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'d');
    DLinkPrint(head,"尾插4个元素");

    DLinkListPopBack(head);
    DLinkListPopBack(head);
    DLinkPrint(head,"尾删2个元素");
    DLinkListPopBack(head);
    DLinkListPopBack(head);
    DLinkPrint(head,"再尾删2个元素");
}

void TestPushFront()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head,'a');
    DLinkListPushFront(head,'b');
    DLinkListPushFront(head,'c');
    DLinkListPushFront(head,'d');
    DLinkPrint(head,"头插4个元素");

}

void TestPopFront()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head,'a');
    DLinkListPushFront(head,'b');
    DLinkListPushFront(head,'c');
    DLinkListPushFront(head,'d');
    DLinkPrint(head,"头插4个元素");

    DLinkListPopFront(head);
    DLinkListPopFront(head);
    DLinkPrint(head,"头删2个元素");
    DLinkListPopFront(head);
    DLinkListPopFront(head);
    DLinkPrint(head,"头删2个元素");
}

void TestBackInsert()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head,'a');
    DLinkListPushFront(head,'b');
    DLinkListPushFront(head,'c');
    DLinkListPushFront(head,'d');
    DLinkPrint(head,"头插4个元素");

    DLinkListBackInsert(head,head->next->next,'e');
    DLinkPrint(head,"在b之后插入e");

}

void TestBeforeInsert()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head,'a');
    DLinkListPushFront(head,'b');
    DLinkListPushFront(head,'c');
    DLinkListPushFront(head,'d');
    DLinkPrint(head,"头插4个元素");

    DLinkListBeforeInsert(head,head->next->next,'e');
    DLinkPrint(head,"在c之前插入e");
}

void TestFind()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head,'a');
    DLinkListPushFront(head,'b');
    DLinkListPushFront(head,'c');
    DLinkListPushFront(head,'d');
    DLinkPrint(head,"头插4个元素");
    
    DLinkNode* find = DLinkListFind(head,'c');
    printf("找到的节点是 [ %c | %p ]\n",find->data,find);
}

void TestErase()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head,'a');
    DLinkListPushFront(head,'b');
    DLinkListPushFront(head,'c');
    DLinkListPushFront(head,'d');
    DLinkPrint(head,"头插4个元素");
    
    DLinkNode* pos_c=DLinkListFind(head,'c');
    DLinkListErase(head,pos_c);
    DLinkPrint(head,"给出c的节点位置，删除c ");
}

void TestRemove()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head,'a');
    DLinkListPushFront(head,'b');
    DLinkListPushFront(head,'c');
    DLinkListPushFront(head,'d');
    DLinkPrint(head,"头插4个元素");

    DLinkListRemove(head,'c');
    DLinkPrint(head,"给出c,删除c");

    DLinkListPushBack(head,'b');
    DLinkListRemoveAll(head,'b');
    DLinkPrint(head,"给出b，删除所有b ");
}

void TestDestroy()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head,'a');
    DLinkListPushFront(head,'b');
    DLinkListPushFront(head,'c');
    DLinkListPushFront(head,'d');
    DLinkPrint(head,"头插4个元素");
    
    DLinkListDestroy(&head);
    DLinkPrint(head,"销毁链表");
}

void main()
{
    TestInit();
    TestPushBack();
    TestPopBack();
    TestPushFront();
    TestPopFront();
    TestBackInsert();
    TestBeforeInsert();
    TestFind();
    TestErase();
    TestRemove();
    TestDestroy();
}
