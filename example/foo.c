#include <stdio.h>
#include <stdint.h>

#include "stranslate.h"

typedef struct
{
    uint32_t    uint32;
} subtype_t;

typedef struct
{
    uint8_t     uint8;
    uint16_t    uint16;
    uint32_t    uint32;
    subtype_t   subtype;
    uint16_t    arr[4];
    uint32_t    uint32_2;
} foo_t;

type_map_t subtype_map[] =
    {
    strans_primitive( subtype_t, uint32 )
    };

type_map_t foo_map[] = 
    {
    strans_primitive( foo_t, uint8 ),
    strans_primitive( foo_t, uint16 ),
    strans_primitive( foo_t, uint32 ),
    strans_struct( foo_t, subtype, subtype_map, cnt_of_array(subtype_map) ),
    strans_primitive_array( foo_t, arr, 4 ),
    strans_primitive( foo_t, uint32_2 )
    };

//// FOR dev vvvvvv

void print_foo_type( foo_t * str )
{
    uint8_t * ptr;

    // foo_t : uint8
    ptr = (uint8_t *)&str->uint8;
    printf( "uint8:\t\t %02X\n", ptr[0] );

    // foo_t : uint16
    ptr = (uint8_t *)&str->uint16;
    printf( "uint16:\t\t %02X %02X\n", ptr[0], ptr[1] );

    // foo_t : uint32
    ptr = (uint8_t *)&str->uint32;
    printf( "uint32:\t\t %02X %02X %02X %02X\n", ptr[0], ptr[1], ptr[2], ptr[3]);

    // subtype_t : uint32
    ptr = (uint8_t *)&str->subtype.uint32;
    printf( "subtype.uint32:\t %02X %02X %02X %02X\n", ptr[0], ptr[1], ptr[2], ptr[3]);

    // foo_t : arr[0]
    ptr = (uint8_t *)&str->arr[0];
    printf( "arr[0]:\t\t %02X %02X\n", ptr[0], ptr[1] );

    // foo_t : arr[1]
    ptr = (uint8_t *)&str->arr[1];
    printf( "arr[1]:\t\t %02X %02X\n", ptr[0], ptr[1] );

    // foo_t : arr[2]
    ptr = (uint8_t *)&str->arr[2];
    printf( "arr[2]:\t\t %02X %02X\n", ptr[0], ptr[1] );

    // foo_t : arr[3]
    ptr = (uint8_t *)&str->arr[3];
    printf( "arr[3]:\t\t %02X %02X\n", ptr[0], ptr[1] );

    // foo_t : uint32_2
    ptr = (uint8_t *)&str->uint32_2;
    printf( "uint32_2:\t %02X %02X %02X %02X\n", ptr[0], ptr[1], ptr[2], ptr[3]);
}

int main( int argc, char * argv[] )
{
    foo_t foo;

    foo.uint8 = 117;
    foo.uint16 = 12345;
    foo.uint32 = 97293122;
    foo.subtype.uint32 = 24579234;
    foo.arr[0] = 3812;
    foo.arr[1] = 16231;
    foo.arr[2] = 114;
    foo.arr[3] = 33333;
    foo.uint32_2 = 8394023;

    printf("BEFORE:\n");
    print_foo_type( &foo );

    strans_reverse_bytes_by_map( &foo, foo_map, cnt_of_array(foo_map) );

    printf("AFTER:\n");
    print_foo_type( &foo );

    return( 0 );
}
