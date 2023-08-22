#include <iostream>

using namespace std;

struct st_List
{
    st_List()
    {
        next = nullptr;
        prev = nullptr;
    }
    struct st_List *next;
    struct st_List *prev;
    char data;
};

void Add(st_List **cur, char ch)
{
    st_List *new_list = new st_List;

    printf("In Add[%p] l%p r%p\n", (*cur), (*cur)->prev, (*cur)->next);
    new_list->data = ch;
    new_list->prev = (*cur);
    
    new_list->next = (*cur)->next;
    new_list->next->prev = new_list;
    new_list->prev->next = new_list;

}
void MoveLeft(st_List **cur)
{
    if ((*cur)->prev != nullptr)
        *cur = (*cur)->prev;
}

void MoveRight(st_List **cur)
{
    if ((*cur)->next != nullptr)
        *cur = (*cur)->next;
}

void Delete(st_List **cur)
{
    st_List *tmp;
    if ((*cur)->prev == nullptr)
        return;
    tmp = (*cur)->prev;
    (*cur)->prev = tmp->prev;
    tmp->prev->next = (*cur);
    free(tmp);
}


int main()
{
    st_List *head = new st_List;
    st_List *tail = new st_List;
    head->next = tail;
    tail->prev = head;

    st_List *cur = tail;

    string str;
    cin >> str;
    for (int i = 0 ; i < str. size() ; ++i)
    {
        Add(&cur, str[i]);
        MoveRight(&cur);
    }
    // cout << cur->data << ' ' << cur->prev << ' ' << cur->next;
    // while (tail->prev)
    // {
    //     cout << tail->data << '\n';
    //     tail = tail->prev;
    // }

    
    while (head)
    {
        printf("now:%p prev:%p next:%p\n", head, head->prev, head->next);
        head = head->next;
    }


    printf("%p %p %p\n", cur, cur->prev, cur->next);
    MoveLeft(&cur);
    printf("%p %p %p\n", cur,cur->prev, cur->next);
    MoveLeft(&cur);
    printf("%p %p %p\n", cur,cur->prev, cur->next);
    Add(&cur, 'B');
    printf("%p %p %p\n", cur,cur->prev, cur->next);
}