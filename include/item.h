#define ITEM_H 1

//~~~~~~~~~~~~~~~~~~~~~
//custom headers:
#ifndef CHAR_H
#include "char.h"
#endif
//~~~~~~~~~~~~~~~~~~~~~

//general typedefs:
typedef struct {

    int type_name;

    unsigned int wh[2];
    unsigned int pos[2];

} item_struct;
//~~~~~~~~~~~~~~~~~~~~~
//general functions:
item_struct* gen_items(
    int num
);
void check_item_overlap(
    item_struct* item_chk,
    int ITEM_NUM
);
//~~~~~~~~~~~~~~~~~~~~~
