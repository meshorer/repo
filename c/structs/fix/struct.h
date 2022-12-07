
#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#define MAX2(x,y) ((x>y)?x:y)
#define MAX3(x,y,z) \
(x>y && x> z) ? x; (y > z) ? y:z)
#define my_sizeof(type) (char *)(&type+1)-(char*)(&type)

struct mixed_types{

	void *element;
	void (*add)();
	void (*print)(void *);
	void (*clean)(void *);
};

/*void AddInt(struct mixed_types *ptr, int num_to_add);*/
void AddInt(void *ptr, int num_to_add);
/*void AddFloat(struct mixed_types *ptr, int num_to_add);*/
void AddFloat(void *ptr, int num_to_add);
void AddString(void **ptr, int num_to_add);
void PrintInt(void *ptr);
void PrintFloat(void *ptr);
void PrintString(void *ptr);
void Cleanup(void *ptr);
struct mixed_types InitInt(int num);
struct mixed_types InitFloat(float num);
struct mixed_types InitString(char *ptr);
void Empty();






#endif
