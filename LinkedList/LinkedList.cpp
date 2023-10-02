#include <iostream>
#include<cassert>
using namespace std;
class node;
class OurSet { // DobleLinkedlist
public:
    typedef double value_type;
    OurSet();
    OurSet(value_type); // constructure
    OurSet(const OurSet&); //  Copy Constructor
    ~OurSet(); // destructor

    //the functions defined for singly linked lists.
    size_t list_length(); //O
    node* list_search(const value_type& target); // O
    node* list_locate(size_t position); //O position > 0
    void list_head_insert(const value_type& entry);
    void list_insert(node* previous_ptr, const value_type& entry);
    void list_head_remove();
    void list_remove(node* previous_ptr);
    void list_clear(node*& head_ptr);
    void list_copy(const node* source_ptr);

    //the functions, constructors, and operators
    void insert(const value_type& entry);
    bool erase_one(const value_type& target);
    int count(const value_type& target) const;
    void operator+(const OurSet& addend);
    void operator+=(const OurSet& other);
    void operator=(const OurSet& addend);
    bool operator==(const OurSet& addend);
    bool operator!=(const OurSet& addend);
    //show_contents
    void show_contents();
    void sort();
private:
    node* head;
    node* tail;
    int size;
    //복사용 포인터
    node* cphead = NULL;
    node* cptail = NULL;
    int cpsize =0;

};
class node
{
    friend OurSet;
public:
    typedef double value_type; // 
    node(node* n, node* p, value_type val) {
        next = n;
        prev = p;
        this->value = val;
    }
    node(value_type val) {
        next = NULL;
        prev = NULL;
        this->value = val;
    }

private:
    value_type value; // value_type == double == 1
    node* next; // next node
    node* prev; // previous node

};

int main()
{
    OurSet* list = new OurSet();
    for (int i = 0; i < 15; i += 3) {
        list->insert(i + 7);
    }
    list->show_contents();
    cout << (list != NULL) << endl;
    cout << "This is my" << endl;
    OurSet list2; // constructure, copy
    for (int i = 0; i < 15; i += 3) {
        list2.insert(i);
    }


    cout << endl;
    cout << endl;
    cout << endl;
    cout << "thisS@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

    list.show_contents();

    /*list->sort();
    list->show_contents();*/

    cout << "this" << endl;
    cout << endl;
    //list += list2;
    cout << endl;

    cout << endl;

}

OurSet::OurSet() {
    head = tail = NULL;
    size = 0;
}
OurSet::OurSet(value_type value) {
    head = tail = new node(value);
    size = 1;
}
OurSet::OurSet(const OurSet& copy) {
    node* cur = copy.tail;
    while (cur != NULL) {
        list_head_insert(cur->value);
        cur = cur->prev;
    }
}
OurSet::~OurSet() {
    node* cur = head;
    while (cur != NULL) {
        list_head_remove();

    }
}

size_t OurSet::list_length() {
    cout << "Befor: ";
    show_contents();
    cout << endl;

    size_t answer = 0;
    node* cursor = head;
    while (cursor != NULL)
    {
        answer++;
        cursor = cursor->next;
    }
    cout << "After: ";
    show_contents();
    cout << endl;
    return answer;

}
node* OurSet::list_search(const node::value_type& target) {
    cout << "Befor: ";
    show_contents();
    cout << endl;
    if (head == NULL) return NULL;
    node* cursor = head;
    while (cursor != NULL)
    {
        if (target == cursor->value)
        {
            cout << "After: ";
            show_contents();
            cout << endl;

            return cursor;
        }
        cursor = cursor->next;
    }
    cout << "The Target you've selected is not exit in the OurSet" << endl;
    return NULL;
}
node* OurSet::list_locate(size_t position) {
    if (0 > position || head == NULL || position > size)
    {
        assert(0 > position || position > size || head == NULL);
        return NULL;
    }
    cout << "Befor: ";
    show_contents();
    cout << endl;

    node* cursor = head;
    int i = 1;
    
    while (cursor != NULL) {

        if (position == i)
        {
            cout << "After: ";
            show_contents();
            cout << endl;
            return cursor;
        }
        i++;
        cursor = cursor->next;
    }
}

void OurSet::list_head_insert(const value_type& entry) {
    cout << "Befor: ";
    show_contents();
    cout << endl;

    //  15 -> 13 - > 7   ->  10 -> 15 -> 13 - > 7
    // head_ptr : 15
    node* newnode = new node(entry); // node: prev = next = NULL;
    if (head == NULL) {
        head = newnode;
    }
    else {
        newnode->next = head;
        head->prev = newnode;
    }
    head = newnode;
    ++size;

    cout << "After: ";
    show_contents();
    cout << endl;
}
void OurSet::list_insert(node* previous_ptr, const value_type& entry) { //13, 10 15 - o - 7 -? 10 15 13 7
    if (previous_ptr == NULL || entry == NULL) return;

    node* insert_ptr = new node(entry);
    node* pre = list_search(previous_ptr->value);
    if (pre == NULL) { // pre don't exit
        cout << "previous_ptr don'y exit" << endl;
        return;
    }
    else { // end or mid
        insert_ptr->next = pre->next;
        insert_ptr->prev = pre;
        if (pre->next != nullptr) {
            pre->next->prev = insert_ptr;
        }
        pre->next = insert_ptr;
        ++size;
    }
    cout << "After: ";
    show_contents();
    cout << endl;
}
void OurSet::list_head_remove() {
    if (head == NULL) { // 10 -> 15 -> 13 - > 7   ->    15 -> 13 - > 7
        cout << "This OurSet is Null" << endl;
        return;
    }
    else
    { // 10 -> 15 -> 13 - > 7   ->    15 -> 13 - > 7
        cout << "Befor: ";
        show_contents();
        cout << endl;

        node* del = head; // 10
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        delete del;
        size--;

        cout << "After: ";
        show_contents();
        cout << endl;
    }


}
void OurSet::list_remove(node* previous_ptr) { // prev 다음 번째를 지우는 코드
    if (head == NULL)
    {
        cout << "This OurSet is empty" << endl;
        return;
    }
    node* cur = list_search(previous_ptr->value);

    if (cur == NULL) { // pre don't exit
        cout << "previous_ptr don't exit" << endl;
    }
    else if (cur == tail) { // prev(CUR)이 꼬리일 떄
        cout << "Befor: ";
        show_contents();
        cout << endl;

        cout << "Prev(CUR) node is tail node" << endl;

        cout << "After: ";
        show_contents();
        cout << endl;
    }
    else if (cur->next->next == NULL) { // 1 - 2 - 3(c) - 4(d)
        // target이 꼬리 노드일 때
        cout << "Befor: ";
        show_contents();
        cout << endl;

        node* del = cur->next; 
        cur->next = NULL;
        --size;
        delete del;
        cout << "After: ";
        show_contents();
        cout << endl;
    }
    else {
        //target(CUR)가 중간일 때
        cout << "Befor: ";
        show_contents();
        cout << endl;

        node* del = cur->next; // 1 - 2(c) - 3(d) - 4
        cur->next = del->next;
        del->next->prev = cur;
        --size;
        delete del;

        cout << "After: ";
        show_contents();
        cout << endl;
    }

}
void OurSet::list_clear(node*& head_ptr) {
    cout << "Befor: ";
    show_contents();
    cout << endl;

    node* cursor = head_ptr;
    while (cursor != NULL) {
        list_head_remove();
        cursor = cursor->next;
    }

    cout << "After: ";
    show_contents();
    cout << endl;
}
void OurSet::list_copy(const node* source_ptr) { // Basic i is 1
    if (source_ptr == NULL) return;

    cout << "Befor: ";
    show_contents();
    cout << endl;
    cphead = NULL; cptail = NULL;
    cpsize = 0;
    cptail = cphead;
    while (source_ptr->next != NULL)
    {
        source_ptr = source_ptr->next;
    }
    source_ptr = source_ptr->next;
    while (source_ptr != NULL) {    // 10 -> 15 -> 13 - > 7
        node* newnode = new node(source_ptr->value); // node: prev = next = NULL;
        if (cphead == NULL) {
            cphead = newnode;
        }
        else {
            newnode->next = cphead;
            cphead->prev = newnode;
        }
        cphead = newnode;
        ++size;
        source_ptr = source_ptr->prev;
    }
    cout << "After: ";
    show_contents();
    cout << endl;
}

void OurSet::insert(const value_type& entry) {
    cout << "Befor: ";
    show_contents();
    cout << endl;
    list_head_insert(entry);
    cout << "After: ";
    show_contents();
    cout << endl;
};
bool OurSet::erase_one(const value_type& target) {
    node* target_ptr = list_search(target);;
    if (target_ptr == NULL || head == NULL) {
        return false;
    }
    if (target_ptr == head) { // head이니 그냥 냅둠
        cout << "Befor: ";
        show_contents();
        cout << endl;
        list_head_remove();
        cout << "After: ";
        show_contents();
        cout << endl;
    }
    else if (tail == target_ptr) { // 꼬리이니 그냥 냅둠
        cout << "Befor: ";
        show_contents();
        cout << endl;
        list_remove(target_ptr->prev); //list_remove(prev)
        cout << "After: ";
        show_contents();
        cout << endl;
    }
    else { // 중간이면 head부분을 빠질 부분으로 넣고 head을 재설정 해준다 1 - 5 - 6 - 2
        cout << "Befor: ";
        show_contents();
        cout << endl;

        node* cur = head;
        while (cur != NULL) {    // 10 -> 15 -> 13 - > 7
            if (cur == target_ptr) {
                cur->value = head->value;
                list_head_remove();
            }
            cur = cur->next;
        }

        cout << "After: ";
        show_contents();
        cout << endl;
    }
    return true;
};
int OurSet::count(const value_type& target) const {
    int count = 1;
    node* cursor = head;
    while (cursor != NULL) {
        if (cursor->value == target) {
            return count;
        }
        count++;
        cursor = cursor->next;
    }
    assert("OurSet don't have the target which you want to count !!!");
    return NULL;
}

//void OurSet::operator +(const value_type addend) {
//    //1 - 2 - 3  + 6 - 5 - 8
//
//
//    node* cur = head;
//    while (cur != NULL)
//    {
//        cur->value += addend;
//        cur = cur->next;
//    }
//
//
//
//}

void OurSet::operator+(const OurSet& addend) {
    //1 - 2 - 3  + 6 - 5 - 8
    if (addend.size != this->size) {
        return;
    }
    else if (addend.size <= 0 || 0 >= this->size) { //head = tail = NULL
        return;
    }
    else { // addend.size == this->size
        cout << "Befor: ";
        show_contents();
        cout << endl;
        node* cur = head;
        node* cur2 = addend.head;
        while (cur != NULL)
        {
            if (cur->value == NULL || cur2->value == NULL)
            {
                return;
            }
            else {
                cur->value += cur2->value;
            }
            cur = cur->next;
            cur2 = cur2->next;
        }
        cout << "After: ";
        show_contents();
        cout << endl;
    }

}
void OurSet:: operator+=(const OurSet& source){
        
    node* cpcur = source.tail;
    while (cpcur != NULL) {
        insert(cpcur->value);
        cpcur = cpcur->prev;
    }
}
void OurSet:: operator=(const OurSet& addend) {
    if (this == &addend) {
        cout << "They are same!!";
        return;
    }
    else if (&addend == NULL) {
        cout << "the source You've selected is NULL!" << endl;
        return;
    }
    else {
        cout << "Befor: ";
        show_contents();
        cout << endl;

        list_clear(head);
        /*list_copy(addend.head);

        head = cphead; tail = cptail; // 임시의 복사 포인터를 진짜 포인터 2개에 저장
        size = addend.size;*/
        node* cur = addend.tail;
        while (cur != NULL) {
            insert(cur->value);
            cur = cur->prev;
        }
        cout << "After: ";
        show_contents();
        cout << endl;
    }

}

bool OurSet:: operator==(const OurSet& addend) {
    show_contents();
    if (this == &addend) return true;
    else {
        node* cursor = head;
        node* add = addend.head;
        while (cursor != NULL) {
            if (cursor->value != add->value) return false;
            cursor = cursor->next;
            add = add->next;
        }
        return true;
    }

}
bool OurSet:: operator!=(const OurSet& addend) {
    show_contents();
    if (this == &addend) return false;
    else {
        node* cursor = head;
        node* add = addend.head;
        while (cursor != NULL) {
            if (cursor->value != add->value) return true;
            cursor = cursor->next;
            add = add->next;
        }
        return false;
    }
}

void OurSet::show_contents()
{
    if (head == NULL) {
        cout << "This OurSet is Null" << endl;
    }
    else {
        node* cur = head;
        while (cur != NULL)
        {
            if (cur->next == NULL) {
                cout << cur->value << endl;
            }
            else {
                cout << cur->value << " <- -> ";
            }
            cur = cur->next;
        }
    }

}
void OurSet::sort()
{
    cout << "Befor: ";
    show_contents();
    cout << endl;
    node* cur = head, * temp = NULL;
    value_type tem;
    if (head == NULL)
    {
        return;
    }
    else {
        while (cur != NULL)
        {
            temp = cur->next;
            while (temp != NULL) {
                if (cur->value > temp->value) {
                    tem = cur->value;
                    cur->value = temp->value;
                    temp->value = tem;
                }
                temp = temp->next;
            }
            cur = cur->next;
        }
    }
    cout << "After: ";
    show_contents();
    cout << endl;
}