#pragma once  // "保证只编译一次"

typedef char DLinkType;

typedef struct DLinkNode{
    DLinkType data;
    struct DLinkNode* prev;
    struct DLinkNode* next;
} DLinkNode;

//初始化
void DLinkListInit(DLinkNode** phead);
//创建节点
DLinkNode* CreateDLinkNode(DLinkType value);
//尾插
void DLinkListPushBack(DLinkNode* head,DLinkType value);
//尾删
void DLinkListPopBack(DLinkNode* head);
//头插
void DLinkListPushFront(DLinkNode* head,DLinkType value);
//头删
void DLinkListPopFront(DLinkNode* head);
//插入pos之后
void DLinkListBackInsert(DLinkNode* head,DLinkNode* pos,DLinkType value);
//插入pos之前
void DLinkListBeforeInsert(DLinkNode* head,DLinkNode* pos,DLinkType value);
//查找给定值的节点，找到返回该节点，否则返回NULL
DLinkNode* DLinkListFind(DLinkNode* head,DLinkType to_find);
//删除pos位置指向的值
void DLinkListErase(DLinkNode* head,DLinkNode* pos);
//删除给定值的节点
void DLinkListRemove(DLinkNode* head,DLinkType to_remove_value);
//删除给定值的所有节点
void DLinkListRemoveAll(DLinkNode* head,DLinkType to_remove_value);
//销毁链表
void DLinkListDestroy(DLinkNode** phead);//要修改头指针，要用**；如果不修改头指针就成野指针了。






