#include <stdio.h>
#include <memory.h>
#define HASH_SIZE  1111111
#define QUEUE_SIZE 1111111
#define BUF_SIZE 111
 /*
����˵������һ��С�Թ��������ظ��ߣ����ǲ��ܵ��ˡ�����ÿ���߶���ζ��ִ��һ�����㣬����Ҫ2011���Թ��ڽ�ȥ��2012���Թ��ڳ�����
һ��˼����ǹ�������������ܹ��ҵ���̵�·���������ÿ��״̬������ȣ����ܻ����ҵ�����·�����Լ�ʵ����һ���򵥵�Hash����Ϊ���ղ��������࣬���Զ�Hash��Ҫ��Ҳ���ߡ�
֮�����ڹ�����������Ļ����Ͻ����޸ģ�ʵ����˫��������������һ�������ڿ�ʼ�ѣ�һ����ӳ��ڿ�ʼ�ѡ���Ҫע����Ǵӳ��ڿ�ʼ�ѵĻ����������㶼���෴�ġ��ѵ�ʱ������������У�ֱ�����ߡ���ͷ��Ϊֹ��
���Խ���п��Կ�����˫���������������Ը���һЩ��
*/
struct S {
    int pos;
    int value;
    int way;
    int flag;
    struct S *prev;
};
 
typedef struct S Status;
 
int from[] = {0, 2, 6, 8};
        //   {0, 0, 1, 1, 1, 1, 2, 2};
int to[]   = {1, 1, 0, 0, 2, 2, 1, 1};
int way[]  = {0, 1, 0, 1, 2, 3, 2, 3};
 
int equal (Status s1, Status s2) {
    if (s1.pos == s2.pos && s1.value == s2.value) {
        return s1.flag == s2.flag && s1.way == s2.way
            || s1.flag != s2.flag && s1.way != s2.way;
    }
    return 0;
}
 
int op(int val, int way_id) {
    switch(way_id) {
        case 0: return val + 7;
        case 1: return val % 2 == 0 ? val / 2 : val;
        case 2: return val * 3;
        case 3: return val - 5;
    }
    return val;
}
 
int op_rev(int val, int way_id) {
    switch(way_id) {
        case 0: return val - 7;
        case 1: return val * 2;
        case 2: return val % 3 == 0 ? val / 3 : val;
        case 3: return val + 5;
    }
    return val;
}
 
Status hash[HASH_SIZE];
Status *queue1[QUEUE_SIZE];
Status *queue2[QUEUE_SIZE];
 
int get_key(Status s) {
    int v = s.value * 3 + s.pos;
    if (v >= 0) return v % HASH_SIZE;
    else return v % HASH_SIZE + HASH_SIZE;
}
 
Status* insert_hash(Status s, int *flag) {
    int key = get_key(s);
    while (hash[key].pos != -1 && !equal(hash[key], s)) {
        key++;
        key %= HASH_SIZE;
    }
 
    if (hash[key].pos == -1) {
        hash[key] = s;
        *flag = 1;
    }
    else {
        *flag = 0;
    }
    return &hash[key];
}
 
void output(Status now1, Status now2) {
    int num_buf[BUF_SIZE];
    int way_buf[BUF_SIZE];
 
    int i, n = 0;
    way_buf[n] = -1;
    num_buf[n++] = now1.value;
    way_buf[n] = now1.way;
    now1 = *now1.prev;
 
    while (now1.prev != NULL) {
        num_buf[n++] = now1.value;
        way_buf[n] = now1.way;
        now1 = *now1.prev;
    }
 
    num_buf[n++] = now1.value;
 
    for (i = n - 1; i > 0; i--) {
        printf("%d", num_buf[i]);
        switch (way_buf[i]) {
            case 0 : printf(" + 7 = \n"); break;
            case 1 : printf(" / 2 = \n"); break;
            case 2 : printf(" * 3 = \n"); break;
            case 3 : printf(" - 5 = \n"); break;
        }
    }
    printf("%d", num_buf[i]);
 
    while (now2.prev != NULL) {
        switch (now2.way) {
            case 0 : printf(" + 7 = \n"); break;
            case 1 : printf(" / 2 = \n"); break;
            case 2 : printf(" * 3 = \n"); break;
            case 3 : printf(" - 5 = \n"); break;
        }
        now2 = *now2.prev;
        printf("%d", now2.value);
    }
    printf("\n");
}
 
void BFS(Status s, Status t) {
    memset(hash, -1, sizeof(hash));
 
    Status *p_now, next;
    int top1 = 0, rear1 = 1, top2 = 0, rear2 = 1, i, k, flag;
 
    queue1[0] = insert_hash(s, &flag);
    queue2[0] = insert_hash(t, &flag); 
 
 
    while (top1 < rear1 || top2 < rear2) {
        int rear = rear1;
        next.flag = 0;
        for (k = top1; k < rear; k++) {
            p_now = queue1[k];
            for (i = from[p_now->pos]; i < from[p_now->pos + 1]; i++) {
                if (p_now->way != way[i]) {
                    next.pos = to[i];
                    next.value = op(p_now->value, way[i]);
                    if (next.value == p_now->value) {
                        continue;
                    }
                    next.way = way[i];
                    next.prev = p_now;
 
                    Status *result = insert_hash(next, &flag);
                    if (result->flag != next.flag) {
                        output(next, *result);
                        break;
                    }
                    if (flag) {
                        queue1[rear1++] = result; 
                    }
                }
            }
            if (i < from[p_now->pos + 1]) {
                break;
            }
        }
        if (k < rear) {
            break;
        }
        top1 = rear;
 
        rear = rear2;
        next.flag = 1;
        for (k = top2; k < rear; k++) {
            p_now = queue2[k];
            for (i = from[p_now->pos]; i < from[p_now->pos + 1]; i++) {
                if (p_now->way != way[i]) {
                    next.pos = to[i];
                    next.value = op_rev(p_now->value, way[i]);
                    if (next.value == p_now->value) {
                        continue;
                    }
                    next.way = way[i];
                    next.prev = p_now;
 
                    Status *result = insert_hash(next, &flag);
                    if (result->flag != next.flag) {
                        output(*result, next);
                        break;
                    }
                    if (flag) {
                        queue2[rear2++] = result; 
                    }
                }
            }
            if (i < from[p_now->pos + 1]) {
                break;
            }
        }
        if (k < rear) {
            break;
        }
        top2 = rear;
 
    }
}
 
int main() {
    Status s, t;
    s.pos = 0; s.value = 2011; s.prev = NULL; s.way = -1;
    t.pos = 2; t.value = 2012; t.prev = NULL; t.way = -1;
 
    BFS(s, t);
 
    return 0;
}