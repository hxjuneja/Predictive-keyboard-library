#include <stdio.h>
#include <malloc.h>
#include <ncurses.h>


typedef struct ll
{
    char a;
    struct ll *next;
    struct ll *prev;
}ll;

typedef struct master
{
    struct ll *start;
    struct ll *end;
    int count;
}mn;

mn *initialise(mn *m)
{
    m = (mn *)malloc(sizeof(mn));
    m->start = NULL;
    m->end = NULL;
    m->count = 0;
    return m;
}

ll *new_node(ll *n,char ch)
{
    n =(ll *)malloc(sizeof(ll));
    n->a = ch;
    n->next = NULL;
    n->prev = NULL;  
    return n;
}

mn *insert_end(mn *m,char ch)
{
    ll *n;
    ll *temp;
    n = new_node(n,ch);
    if(m->start == NULL)
    {
        m->start = n;
        m->end = n;
    } 

    else
    {
        n->prev = m->end;
        //m->end = (node *)malloc(sizeof(node));
        (m->end)->next = n;
        m->end = n; 
    }
return m;
}

void traverse(mn *m)
{
    ll *temp;
    temp = m->start;
    while(temp != NULL)
    {
        printw("%c",temp->a);
        refresh();
        temp = temp->next;
     }
    
    
}

mn *delete_node(mn *m)
{
    if((m->start)->next == NULL)
    {
        clear();
        m->start = NULL;
    }
    else
    {    
        ll *temp;
        temp = m->end;
        m->end =(m->end)->prev;
        (m->end)->next = NULL;
        temp->prev = NULL;
        free(temp);
        //printw("%c",(m->end)->a);
        //printw("%c",temp);
        //printw("check");
    }
    return m;  
}

char* get_key(mn *m)
{
	ll *temp;
	char *key;
	int i=0;
	temp = m->end;
	while(strcmp((temp->prev)->a," ")==0)
	{
		
		key[i] = temp->a;
		temp = temp->prev;
		i++;
	}
	
return key;
}


mn *start(mn *m)
{ 
    ll *temp;
    char dump,c;
	int ch;
	char *key;
    while(ch != 27)
    {
        ch = getch();
		c = ch;

        switch(ch)
		{
			case 127:
        	{	   
				m = delete_node(m);
				clear();
                refresh();
                traverse(m);
				break;
			}
			
			case 9:
			{
				key =  get_key(m);
				printw("%s",key);
				break;
			}		
			default:
			{    
				m = insert_end(m,c);
				clear();
				refresh();
				traverse(m);    
			}
		}
	}
		
		clear();
		refresh();
        printw("\npress any key to exit");
        refresh();
	
}
int main()
{
    initscr();
    noecho();
    cbreak();
    mn *m;
    m = initialise(m);
    printw("hello welcome to the editor we support auto complition! \n");
    printw("You can start writing now\n");
    refresh();
    m = start(m);
    getch();
    endwin();

    return 0;
}
