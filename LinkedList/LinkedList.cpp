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
    void list_clear();
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
    node* head = NULL;
    node* tail = NULL;
    int size = 0;
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
    cout << "This is my list" << endl;
    OurSet list = OurSet(18); // OurSet(value_type value)
    for (int i = 0; i < 15; i += 3) {
        list.insert(i + 7); //insert()
    }
    cout << "This is my constructure" << endl;
    list.show_contents(); // show_contents
    OurSet list_2(list); // COPY
    cout << "this list2 is copy constructure" << endl;
    list_2.show_contents();
    int a = list.list_length(); // list_length
    cout << "This is list_length " << a << endl; // list_length
    cout << "list_head_insert(5)" << endl;
    list.list_head_insert(5);

    cout << endl;

    list.list_insert(list.list_search(5), 9); // list_search(const node::value_type& target)

    list.list_insert(list.list_locate(3), 77); // list_locate(size_t position)
    list.show_contents();

    cout << "This is list_head_remove " << endl << endl;
    list.list_head_remove();
    list.show_contents();

    list.list_remove(list.list_locate(3));
    list.show_contents();

    OurSet list3(130);
    for (int i = 0; i < 15; i += 3) {
        list3.insert(i +2);
    }
    list_2.list_copy(list3.list_locate(1));
    cout << "this is list_2 copy.." << endl;
    list_2.show_contents();
    cout << "this is list3 copy.." << endl;
    list3.show_contents();

    cout << "this is list_2" << endl;
    list_2.show_contents();
    cout << "this is erase_one(): " << list_2.erase_one(10) << endl;
    list_2.show_contents(); // erase_one()

    list_2.show_contents();
    cout << list_2.count(7) << endl; // count()
    // operator+()
    cout << "this is operator+(): " << endl;
    list.operator+(list_2); // error
    list.operator+(list); // not error
    list.show_contents(); 


    // operator+=()
    cout << "this is operator+=(): " << endl;
    list += list_2;
    list.show_contents(); 

    // operator =
    cout << "this is operator=(): " << endl;
    list = list_2;
    cout << "this is list_2 contents" << endl;
    list_2.show_contents();
    cout << "this is list contents" << endl;
    list.show_contents();

    // operator ==
    cout << "this is operator==(): " << endl;
    cout << (list == list) << endl;
    // operator !=
    cout << "this is operator!=(): " << endl;
    cout << (list != list) << endl;

    // sort()
    list.sort();
    list_2.sort();
    cout << "list: ";
    list.show_contents();
    cout << "list_2: ";
    list_2.show_contents();
    return 0;
}

OurSet::OurSet() {
}
OurSet::OurSet(value_type value) {
    head = tail = new node(value);
    size = 1;
}
OurSet::OurSet(const OurSet& copy) {
    if (copy.size <= 0 || copy.head == NULL) {
        cout << "nono" << endl;
        return;
    } 
    node* cur = copy.tail;

    while (cur != NULL) {
        insert(cur->value);
        cur = cur->prev;
    }
}
OurSet::~OurSet() {
    node* cur = head;
    while (cur != NULL) {
        node* next = cur->next;
        delete cur;
        cur = next;
    }
    head = NULL;
}

size_t OurSet::list_length() {

    cout << "list_length()" << endl;
    cout << "This OurSet: ";
    show_contents();
    cout << endl;

    size_t answer = 0;
    node* cursor = head;
    while (cursor != NULL)
    {
        answer++;
        cursor = cursor->next;
    }

    return answer;

}
node* OurSet::list_search(const node::value_type& target) {

    if (head == NULL) return NULL;

    cout << "list_search()" << endl;
    cout << "This OurSet: ";
    show_contents();
    cout << endl;

    node* cursor = head;
    while (cursor != NULL)
    {
        if (target == cursor->value)
        {
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

    cout << "list_locate()" << endl;
    cout << "This OurSet: ";
    show_contents();
    cout << endl;

    node* cursor = head;
    int i = 1;
    
    while (cursor != NULL) {

        if (position == i)
        {
            return cursor;
        }
        i++;
        cursor = cursor->next;
    }
}

void OurSet::list_head_insert(const value_type& entry) {
    //  15 -> 13 - > 7   ->  10 -> 15 -> 13 - > 7
    // head_ptr : 15
    node* newnode = new node(entry); // node: prev = next = NULL;
    if (head == NULL) {
        cout << "This OurSet is Null" << endl;
        head = newnode;
        tail = newnode;
    }
    else {
        cout << "Before insert: ";
        show_contents();
        cout << endl;

        newnode->next = head;
        head->prev = newnode;
        head = newnode;
    }
    ++size;

    cout << "After insert: ";
    show_contents();
    cout << endl;
}
void OurSet::list_insert(node* previous_ptr, const value_type& entry) { //13, 10 15 - o - 7 -? 10 15 13 7
    if (previous_ptr == NULL || entry == NULL) return;

    node* insert_ptr = new node(entry);
    node* pre = list_search(previous_ptr->value);

    if (pre == NULL) { // pre don't exit
        cout << "previous_ptr don't exit" << endl;
        return;
    }
    else { // end or mid
        cout << "list_insert Before: ";
        show_contents();
        cout << endl;

        insert_ptr->next = pre->next;
        insert_ptr->prev = pre;
        if (pre->next != nullptr) {
            pre->next->prev = insert_ptr;
        }
        pre->next = insert_ptr;
        ++size;

        cout << "After: ";
        show_contents();
        cout << endl;
    }
}
void OurSet::list_head_remove() {
    if (head == NULL) { // 10 -> 15 -> 13 - > 7   ->    15 -> 13 - > 7
        cout << "This OurSet is Null" << endl;
        head = tail = NULL;
        tail = head;
        return;
    }
    else
    { // 10 -> 15 -> 13 - > 7   ->    15 -> 13 - > 7
        cout << "list_head_remove()" << endl;
        cout << "This OurSet(Before): ";
        show_contents();
        cout << endl;

        node* del = head; // 10
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        delete del;
        size--;

        cout << "This OurSet(After): ";
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
    else {
        cout << "list_remove(Before): ";
        show_contents();
        cout << endl;
    }
    node* cur = list_search(previous_ptr->value);

    if (cur == NULL) { // pre don't exit
        cout << "previous_ptr don't exit" << endl;
    }
    else if (cur == tail) { // prev(CUR)이 꼬리일 떄
        cout << "Prev(CUR) node is tail node" << endl;
        return;
    }
    else if (cur->next == tail) { // 1 - 2 - 3(c) - 4(d)
        // target이 꼬리 노드일 때
        

        node* del = tail; 
        cur->next = NULL;
        tail = cur;
        --size;
        delete del;

        cout << "list_remove(After): ";
        show_contents();
        cout << endl;
    }
    else {
        //target(CUR)가 중간일 때
        cout << "list_remove(Before): ";
        show_contents();
        cout << endl;

        node* del = cur->next; // 1 - 2(c) - 3(d) - 4
        cur->next = del->next;
        del->next->prev = cur;
        --size;
        delete del;

        cout << "list_remove(After): ";
        show_contents();
        cout << endl;
    }

}
void OurSet::list_clear() {
    if (head == NULL || tail == NULL) {
        cout << "OurSet is Null" << endl;
        return;
    }
    else{
        cout << "befor: ";
        show_contents();
        cout << endl;

        while (head != NULL) {
            list_head_remove();
            cout << "mid: ";
            show_contents();
            cout << endl;
        }

        if (head == NULL) {
            cout << "OurSet is finally Null" << endl;
        }
    }
}
void OurSet::list_copy(const node* source_ptr) { // Basic i is 1
    if (source_ptr == NULL) return;


    cphead = NULL; cptail = NULL;
    cpsize = 0;
    if (cphead == NULL) {
        cout << "Copy Pointer is Null" << endl;
    }
    cptail = cphead;
    while (source_ptr->next != NULL)
    {
        source_ptr = source_ptr->next;
    }
    while (source_ptr != NULL) {    // 10 -> 15 -> 13 - > 7
        node* newnode = new node(source_ptr->value); // node: prev = next = NULL;
        if (cphead == NULL) {
            cphead = newnode;
        }
        else {
            newnode->next = cphead;
            cphead->prev = newnode;
            cphead = newnode;
        }
        ++size;
        source_ptr = source_ptr->prev;
    }
    head = cphead; tail = cptail;

    cout << "list_copy(afert): ";
    show_contents();
    cout << endl;
}

void OurSet::insert(const value_type& entry) {
    if (head == NULL) {
        cout << "This OurSet is Null" << endl;
    }
    else {
        cout << "Before insert: ";
        show_contents();
        cout << endl;
    }

    list_head_insert(entry);

    cout << "After insert: ";
    show_contents();
    cout << endl;
};
bool OurSet::erase_one(const value_type& target) {
    node* target_ptr = list_search(target);;
    if (target_ptr == NULL || head == NULL) {
        cout << "target_prt or Head_ptr is Null" << endl;
        return false;
    }
    if (target_ptr == head) { // head이니 그냥 냅둠
        cout << "erase_one(Before) ";
        show_contents();
        cout << endl;

        list_head_remove();
    
        cout << "erase_one(after) ";
        show_contents();
        cout << endl;
    }
    else if (tail == target_ptr) { // 꼬리이니 그냥 냅둠
        cout << "erase_one(Before) ";
        show_contents();
        cout << endl;

        list_remove(target_ptr->prev); //list_remove(prev)

        cout << "erase_one(after) ";
        show_contents();
        cout << endl;
    }
    else { // 중간이면 head부분을 빠질 부분으로 넣고 head을 재설정 해준다 1 - 5 - 6 - 2
        cout << "erase_one(Before) ";
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
        cout << "erase_one(after) ";
        show_contents();
        cout << endl;
    }
    return true;
};
int OurSet::count(const value_type& target) const {
    if (head == NULL)
    {
        cout << "This OurSet is Null" << endl;
        return 0;
    }
    cout << "This OurSet:  ";

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

    cout << endl;

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
    if (addend.size == this->size) {
        // addend.size == this->size
        cout << "operator+(before): ";
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
        cout << "operator+(after): ";
        show_contents();
        cout << endl;
    }
    else {
        cout << "Unknown Error!" << endl;
    }

}
void OurSet:: operator+=(const OurSet& source){
    if (&source == NULL)
    {
        cout << "source is null" << endl;
        return;
    }
    else if (head == NULL || tail == NULL) {
        cout << "This OurSet is null" << endl;
        head = tail = NULL;
        tail = head;
        cout << "continue.." << endl;
    }
    else
    {
        cout << "operator+=(before): ";
        show_contents();
        cout << endl;
    }

    node* cpcur = source.tail;
    while (cpcur != NULL) {
        insert(cpcur->value);
        cpcur = cpcur->prev;
    }

    cout << "operator+=(after): ";
    show_contents();
    cout << endl;
}
void OurSet:: operator=(const OurSet& addend) {
    if (this == &addend) {
        cout << "They are same!!" << endl;
        cout << "operator=" << endl;
        show_contents();
        cout << endl;
        return;
    }
    else if (&addend == NULL) {
        cout << "the source You've selected is NULL!" << endl;

        list_clear();

        if (head == NULL || tail == NULL) {
            cout << "This OurSet is Null" << endl;
        }
        return;
    }
    else {
        list_clear();
        /*list_copy(addend.head);

        head = cphead; tail = cptail; // 임시의 복사 포인터를 진짜 포인터 2개에 저장
        size = addend.size;*/
        node* cur = addend.tail;
        while (cur != NULL) {
            insert(cur->value);
            cur = cur->prev;
        }
        
    }

}

bool OurSet:: operator==(const OurSet& addend) {
    if (this == &addend) {
        cout << "This is same address" << endl;
        cout << "They are ";
        show_contents();
        cout << endl;
        return true;
    }
    else {
        node* cursor = head;
        node* add = addend.head;
        while (cursor != NULL) {
            if (cursor->value != add->value) return false;
            cursor = cursor->next;
            add = add->next;
        }
        cout << "They are different address but same values " << endl;
        cout << "They are ";
        show_contents();
        cout << endl;
        return true;
    }

}
bool OurSet:: operator!=(const OurSet& addend) {
    if (this == &addend) {
        cout << "This is same address" << endl;
        cout << "They are ";
        show_contents();
        cout << endl;
        return false;
    }
    else {
        node* cursor = head;
        node* add = addend.head;
        while (cursor != NULL) {
            if (cursor->value != add->value) return true;
            cursor = cursor->next;
            add = add->next;
        }
        cout << "They are different address but same values " << endl;
        cout << "They are ";
        show_contents();
        cout << endl;
        return false;
    }
}

void OurSet::show_contents()
{
    if (head == NULL) {
        cout << "This OurSet is Null" << endl;
        return;
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