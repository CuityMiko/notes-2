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
    struct S *prev;
};

typedef struct S Status;

int from[] = {0, 2, 6, 8};
        //   {0, 0, 1, 1, 1, 1, 2, 2};
int to[]   = {1, 1, 0, 0, 2, 2, 1, 1};
int way[]  = {0, 1, 0, 1, 2, 3, 2, 3};

int equal (Status s1, Status s2) {
    return s1.pos == s2.pos && s1.value == s2.value && s1.way == s2.way;
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

Status hash[HASH_SIZE];
Status *queue[QUEUE_SIZE];

int get_key(Status s) {
    int v = s.value * 12 + s.pos * 4 + s.way;
    if (v >= 0) return v % HASH_SIZE;
    else return v % HASH_SIZE + HASH_SIZE;
}

Status* insert_hash(Status s) {
    int key = get_key(s);
    while (hash[key].pos != -1 && !equal(hash[key], s)) {
        key++;
        key %= HASH_SIZE;
    }

    if (hash[key].pos == -1) {
        hash[key] = s;
        return &hash[key];
    }

    return NULL;
}

int check(Status now, Status t) {
    if (now.pos == t.pos && now.value == t.value) {
        int num_buf[BUF_SIZE];
        int way_buf[BUF_SIZE];

        int i, n = 0;
        way_buf[n] = -1;
        num_buf[n++] = now.value;
        way_buf[n] = now.way;
        now = *now.prev;

        while (now.prev != NULL) {
            num_buf[n++] = now.value;
            way_buf[n] = now.way;
            now = *now.prev;
        }
        
        num_buf[n++] = now.value;

        for (i = n - 1; i > 0; i--) {
            printf("%d", num_buf[i]);
            switch (way_buf[i]) {
                case 0 : printf(" + 7 = \n"); break;
                case 1 : printf(" / 2 = \n"); break;
                case 2 : printf(" * 3 = \n"); break;
                case 3 : printf(" - 5 = \n"); break;
            }
        }
        printf("%d\n", num_buf[i]);

        return 1;
    }
    return 0;
}

void BFS(Status s, Status t) {
    memset(hash, -1, sizeof(hash));

    Status *p_now =  insert_hash(s);

    queue[0] = p_now;

    int top = 0, rear = 1, i;

    while (top < rear) {
        p_now = queue[top++];
        Status next;
        
        for (i = from[p_now->pos]; i < from[p_now->pos + 1]; i++) {
            if (p_now->way != way[i]) {
                next.pos = to[i];
                next.value = op(p_now->value, way[i]);
                if (next.value == p_now->value) {
                    continue;
                }
                next.way = way[i];
                next.prev = p_now;

                if (1 == check(next, t)) {
                    break;
                }

                Status *result = insert_hash(next);
                if (result) {
                    queue[rear++] = result; 
                }
            }
        }
        if (i < from[p_now->pos + 1]) {
            break;
        }
    }
}

int main() {
    Status s, t;
    s.pos = 0; s.value = 2011; s.prev = NULL; s.way = -1;
    t.pos = 2; t.value = 2012;

    BFS(s, t);

    return 0;
}

