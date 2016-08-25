#include <stdio.h>
#include <stdlib.h>

#define PAUSE 'p'
#define EXIT 'x'
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define W 5
#define H 5

typedef struct node
{
	int x,y;
	int direc;
}part;

part head,nail;

typedef struct snake
{
part node;
struct snake *next;
}sk;

sk *hsk=NULL;
int score;
int speed;
int map[W][H];
int get_food,erase_nail;
int old_nail_x,old_nail_y;
int food[2];
int oldfood[2];

void init_game();

int get_key();

void create_node(part *head);
void del_node(part *nail);
part *get_node();
int cmp_node(part *node);

void create_food(int *food);

void refresh();

void end_game(void);

int main(int argc, const char *argv[])
{
init_game();
int key;
int x=head.x;
int y=head.y;
while(1)
{
    key=get_key();
    if(key==PAUSE)
    {
        getchar();
	}
    else if(key==EXIT)
    {
        break;
	}
    else
	{
     if(head.direc!=key)
     {
         head.direc=key;
         create_node(&head);
     }
    }
    switch(head.direc)
    {
        case UP : y--; break;
        case DOWN : y++; break;
        case LEFT : x--; break;
        case RIGHT : x++; break;
	}
	if(map[y][x]=='.')
	{
        score++;
        map[y][x]=0;
        oldfood[0]=food[0];
        oldfood[1]=food[1];
        create_food(food);
        map[food[1]][food[0]]='.';
        get_food=1;
        erase_nail=0;
	}
    else if(map[y][x]==1)
        break;
    head.x=x;
    head.y=y;
    map[y][x]=1;
	if(erase_nail)
	{
        map[nail.y][nail.x]=0;
        old_nail_x=nail.x;
        old_nail_y=nail.y;
        switch(nail.direc)
        {
            case UP : nail.y--; break;
            case DOWN : nail.y++; break;
            case LEFT : nail.x--; break;
            case RIGHT : nail.x++; break;
        }
	}
    if(cmp_node(get_node()))
    {
        del_node(&nail);
    }
    refresh();
}
end_game();
return 0;
}

void init_game()
{

}

int get_key()
{
int ch;
/* delay(speed);
    if(kbhit())
    ch=getch();
    if(ch==PAUSE)
    return PAUSE;
    else if(ch==EXIT)
    return EXIT;
    else if(head.direc==LEFT||head.direc==RIGHT)
    {
    if(ch=UP||ch==DOWN)
    return ch;
    }
    else if(ch==LEFT||ch==RIGHT)
    return ch;
    return head.direc;
*/
}

void create_node(part *head)
{
    if(hsk==NULL)
    {
        hsk=(sk *)molloc(sizeof(sk));
        hsk->node.x=head->x;
        hsk->node.y=head->y;
        hsk->node.direc=head->direc;
        hsk->next=NULL;
        return;
    }
    sk *p1=(sk *)molloc(sizeof(sk));
    p1->node.x=head->x;
    p1->node.y=head->y;
    p1->node.direc=head->direc;
    p1->next=NULL;
    sk *p2=hsk;
    while(p2->next!=NULL)
        p2=p2->next;
    p2->next=p1;
    p1=p2=NULL;
}

void del_node(part *nail)
{
    nail->direc=hsk->node.direc;
    sk *p=hsk->next;
    free(hsk);
    hsk=p;
    p=NULL;
}

part *get_node()
{
    if(hsk!=NULL)
        return &(hsk->node);
    return NULL;
}

int cmp_node(part *node)
{
    if(node=NULL)
        return 0;
    if(node->x==nail.x&&node->y==nail.y)
        return 1;
}

void create_food(int *food)
{
}

void refresh()
{
    //darw(head.x,head.y,color);
    if(erase_nail)
        darw(old_nail_x,old_nail_y,color);
    if(get_food)
    {
        //darw(food[0],food[1],color);
        //darw(oldfood[0],oldfood[1],color);
    }
}

void end_game(void)
{
    sk *p1=hsk;
    sk *p2=NULL;
    if(hsk!=NULL)
    {
        while(p1->next!=NULL)
        {
            p2=p1->next;
            p1=p2->next;
            free(p2);
        }
        free(hsk);
    }
}
